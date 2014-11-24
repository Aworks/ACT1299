#define __I2C_C__


#include "I2C.h"
#include "SysTick.h"
#include "printf.h"

void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
						    
	GPIO_InitStructure.GPIO_Pin = IIC_SCL_PIN | IIC_SDA_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(IIC_SCL_PORT, &GPIO_InitStructure);
	Set_IIC_SCL;
	Set_IIC_SDA;
}
void IIC_Start(void)
{
	SDA_OUT();   
	Set_IIC_SDA;	  	  
	Set_IIC_SCL;
	Delay_1us(4);
 	Clr_IIC_SDA;
	Delay_1us(4);
	Clr_IIC_SCL;
}	  

void IIC_Stop(void)
{
	SDA_OUT();
	Clr_IIC_SCL;
	Clr_IIC_SDA;
 	Delay_1us(4);
	Set_IIC_SCL; 
	Set_IIC_SDA;
	Delay_1us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();
	Set_IIC_SDA;Delay_1us(5);	   
	Set_IIC_SCL;Delay_1us(5);	 
	while(READ_SDA)
	{
		ucErrTime++;
		Puts(USART1,"\r\n IIC_Wait_Ack");
		if(ucErrTime>255)
		{
			IIC_Stop();
			return 1;
		}
	}
	Clr_IIC_SCL;
	return 0;  
} 
//产生ACK应答
void IIC_Ack(void)
{
	Clr_IIC_SCL;
	SDA_OUT();
	Clr_IIC_SDA;
	Delay_1us(2);
	Set_IIC_SCL;
	Delay_1us(2);
	Clr_IIC_SCL;
}
//不产生ACK应答		    
void IIC_NAck(void)
{
	Clr_IIC_SCL;
	SDA_OUT();
	Set_IIC_SDA;
	Delay_1us(2);
	Set_IIC_SCL;
	Delay_1us(2);
	Clr_IIC_SCL;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    Clr_IIC_SCL;
    for(t=0;t<8;t++)
    {              
       
		if ((txd&0x80)>>7) 	
		{
			Set_IIC_SDA;
		}
		else 
		{
			Clr_IIC_SDA;
		}
		
        txd<<=1; 	  
		Delay_1us(2);
		Set_IIC_SCL;
		Delay_1us(2); 
		Clr_IIC_SCL;	
		Delay_1us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();
    for(i=0;i<8;i++ )
	{
        Clr_IIC_SCL; 
        Delay_1us(2);
		Set_IIC_SCL;
        receive<<=1;
        if(READ_SDA)receive++;   
		Delay_1us(1); 
    }					 
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}

#define AT24C01		127
#define AT24C02		255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	    8191
#define AT24C128	16383
#define AT24C256	32767  
//Mini STM32开发板使用的是24c02，所以定义EE_TYPE为AT24C02
#define EE_TYPE AT24C02


U8 Read(U8 addr)
{
	U8 ucTmp = 0;
	IIC_Start();
	IIC_Send_Byte(0XA0);
	if(IIC_Wait_Ack()) return 0;
	IIC_Send_Byte(addr);
	if(IIC_Wait_Ack()) return 1;
	IIC_Send_Byte(0XA1);
	if(IIC_Wait_Ack()) return 2;
	ucTmp=IIC_Read_Byte(0);
	IIC_Stop();
	return ucTmp;
}

U8 Write(U8 addr, U8 dat)
{
	IIC_Start();
	IIC_Send_Byte(0XA0);
	if(IIC_Wait_Ack()) return 0;
	IIC_Send_Byte(addr);
	if(IIC_Wait_Ack()) return 1;
	IIC_Send_Byte(dat);
	if(IIC_Wait_Ack()) return 2;
	IIC_Stop();
	Delay_1ms(10);
	return 1;
	
}
u8 AT24CXX_ReadOneByte(u16 ReadAddr)
{				  
	u8 temp=0;		  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	   //发送写命令
		IIC_Wait_Ack();
		IIC_Send_Byte(ReadAddr>>8);//发送高地址
		IIC_Wait_Ack();		 
	}else IIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   //发送器件地址0XA0,写数据 	 

	IIC_Wait_Ack(); 
    IIC_Send_Byte(ReadAddr%256);   //发送低地址
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XA1);           //进入接收模式			   
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();//产生一个停止条件	    
	return temp;
}
//在AT24CXX指定地址写入一个数据
//WriteAddr  :写入数据的目的地址    
//DataToWrite:要写入的数据
void AT24CXX_WriteOneByte(u16 WriteAddr,u8 DataToWrite)
{				   	  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	    //发送写命令
		IIC_Wait_Ack();
		IIC_Send_Byte(WriteAddr>>8);//发送高地址
		IIC_Wait_Ack();		 
	}else
	{
		IIC_Send_Byte(0XA0+((WriteAddr/256)<<1));   //发送器件地址0XA0,写数据 
	}	 
	IIC_Wait_Ack();	   
    IIC_Send_Byte(WriteAddr%256);   //发送低地址
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(DataToWrite);     //发送字节							   
	IIC_Wait_Ack();  		    	   
    IIC_Stop();//产生一个停止条件 
	Delay_1ms(10);	 
}





U8 ack = 0;
void Start_I2c(void)
{
	Set_IIC_SDA;
    Delay_1us(2);
	Set_IIC_SCL;
	Delay_1us(5);
	Clr_IIC_SDA;
	Delay_1us(5);
	Clr_IIC_SCL;
    Delay_1us(2);
}



/**********************************************************
 Function:
 Description:
 Calls:
 Called By:
 Table Accessed:
 Table Updated:
 Input:
 Output:
 Return:
 Others:
**********************************************************/
void Stop_I2c(void)
{
	Clr_IIC_SCL;
    Delay_1us(2);
	Clr_IIC_SDA;
    Delay_1us(2);
	Set_IIC_SCL;
	Delay_1us(5);
	Set_IIC_SDA;
	Delay_1us(5);
}

void Ack_I2c(INT8U a)
{
	if(a == 0)
	{
		Clr_IIC_SDA;		/* ack */
	}
	else
	{
		Set_IIC_SDA;		/* no ack */
	}

	Delay_1us(5);

	Set_IIC_SCL;

    Delay_1us(5);

	if(a == 1)
	{
		Clr_IIC_SDA;
	}

	Delay_1us(5);

	Clr_IIC_SCL;			/* clear SCL and ready for next transfer data */

    Delay_1us(2);
}


/**********************************************************
 Function:
 Description:
 Calls:
 Called By:
 Table Accessed:
 Table Updated:
 Input:
 Output:
 Return:
 Others:
**********************************************************/
void SendByte(INT8U c)
{
	INT8U BitCnt = 0x00;

	Clr_IIC_SCL;

	for(BitCnt = 0x00; BitCnt < 0x08; BitCnt++)
	{
		if((c << BitCnt) & 0x80)
		{
			Set_IIC_SDA;
		}
		else
		{
			Clr_IIC_SDA;
		}

		Delay_1us(2);
		Set_IIC_SCL;		/* set SCL and notice receiver begin to receive data */

		Delay_1us(5);

		Clr_IIC_SCL;
    }

	Delay_1us(2);

	Set_IIC_SDA;			/* release SDA after received 8 bits , and ready for receive ack bit */

	Delay_1us(5);

	Set_IIC_SCL;

	Delay_1us(5);

	SDA_IN();

	if(READ_SDA == 1)		/* judge received ack signal or not */
	{
		ack = 0;
	}
	else
	{
		ack = 1;
	}

	SDA_OUT();

	Clr_IIC_SCL;
}



/**********************************************************
 Function:
 Description:
 Calls:
 Called By:
 Table Accessed:
 Table Updated:
 Input:
 Output:
 Return:
 Others:
**********************************************************/
INT8U RcvByte(void)
{
	INT8U retc   = 0x00;
	INT8U BitCnt = 0x00;

	SDA_IN();

	for(BitCnt=0;BitCnt<8;BitCnt++)
	{
		Delay_1us(2);

		Clr_IIC_SCL;					/* clr SCL and ready for receive data */

        Delay_1us(5);

		Set_IIC_SCL;					/* set SCL and enable data bit active */

        Delay_1us(2);

		retc = retc << 0x01;

		if(READ_SDA == 1)
		{
			retc = retc + 0x01;		/* read data bit and save to rect */
		}

        Delay_1us(2);
	}

	SDA_OUT();

	Clr_IIC_SCL;

    Delay_1us(2);

	return(retc);
}

#if 1
U8 ISendStr(U8 sla, U8 suba, U8 *s, U8 no)
{
    U8 i;
    Start_I2c();               /*启动总线*/
    SendByte(sla);             /*发送器件地址*/
    if(ack==0)
        return(0);
    SendByte(suba);            /*发送器件子地址*/
    if(ack==0)
        return(0);
    for(i=0;i<no;i++)
    {   
        SendByte(*s);            /*发送数据*/
        if(ack==0)
            return(0);
        s++;
    } 
    Stop_I2c();                /*结束总线*/ 
    return(1);
}



U8 IRcvStr(U8 sla, U8 suba, U8 *s, U8 no)
{
    U8 i;

    Start_I2c();                 // /*启动总线
    SendByte(sla);                ///*发送器件地址 58
    if(ack==0)
        return(0);
    SendByte(suba);               ///*发送器件子地址
    if(ack==0)
        return(1);
    Stop_I2c();                  ///  /*结束总线


    Start_I2c();			// /*重新启动总线
    SendByte(sla+1);
    if(ack==0)
        return(2);
    for(i=0;i<no-1;i++)
    {   
        *s=RcvByte();               ///*发送数据
        Ack_I2c(0);                ///*发送就答位  
        s++;
    } 
    *s=RcvByte();
    Ack_I2c(1);                   ///*发送非应位
    Stop_I2c();                   ///*结束总线 
    return(1);
}



#else
U8 ISendStr(U8 sla, U8 suba, U8 *s, U8 no)
{
    U8 i;
    IIC_Start();              
    IIC_Send_Byte(sla);           
    if(IIC_Wait_Ack() == 0)
	return(0);
    IIC_Send_Byte(suba);            
    if(IIC_Wait_Ack() == 0)
	return(0);
    for(i=0;i<no;i++)
    {   
        IIC_Send_Byte(*s);          
        if(IIC_Wait_Ack() == 0)
		return(0);
        s++;
    } 
    IIC_Stop();              
    return(1);
}


U8 IRcvStr(U8 sla, U8 suba, U8 *s, U8 no)
{
    U8 i;

    IIC_Start();               
    IIC_Send_Byte(sla);                
    if(IIC_Wait_Ack() == 0)
        return(0);
    IIC_Send_Byte(suba);
    if(IIC_Wait_Ack() == 0)
        return(0);
    IIC_Stop();            


    IIC_Start();			
    IIC_Send_Byte(sla+1);
    if(IIC_Wait_Ack() == 0)
        return(0);
    for(i=0;i<no-1;i++)
    {   
        *s=IIC_Read_Byte();      
        IIC_Ack();        
        s++;
    } 
    *s=IIC_Read_Byte();
    IIC_NAck();            
    IIC_Stop();            
    return(1);
}
#endif
