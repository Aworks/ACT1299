#define __ADS1299_C__


#include "ADS1299.h"
#include "user_coreconfig.h"
#include "User_handle.h"
#include "global.h"
#include "delay.h"
#include "printf.h"
#include "spi.h"
#include "queue.h"

void init_ADS1x9x_IO (unsigned char device_slot)
{
  // LD TODO:  This could probably be modularized in a better way (less repeated code)
       
        // Power Down Pin (ACTIVE LOW)
        ADS1298_PowerDown();                                       // HIGH, LOW
       
        // RESET Pin (ACTIVE LOW)
        ADS1298_ResetHigh();                                       // HIGH, LOW 

		//Chip select High
		ADS1298_CS_High();

        // Start (ACTIVE High)
        ADS1298_StartLow();                                        // HIGH, LOW  
    
        // Clock Select (Low -> External Clock, High -> Internal Clock
        ADS1298_ClkselLow();                                        // HIGH, LOW  
}

void POR_Reset_ADS1x9x (unsigned char device_slot)
{
    unsigned int i;
 
    //LD TODO: Use universal clock settings to set delays

    // Small Delay 
    ADS1298_ResetHigh();                                       // Reset HIGH
	Puts("\r\n 41");
   // for (i = 0xFFFF; i > 0; i--)
    //{
	   //Delay_1us(20);
    //}
    Puts("\r\n 46");
    Delay_1ms(500);
    Puts("\r\n 48");
    ADS1298_ResetLow();                                        // Reset LOW    
	Delay_1us(20);                                // Small Delay   
	Puts("\r\n 49");
    ADS1298_ResetHigh();                                       // Reset HIGH
    Delay_1us(40);       
}

void Power_Down_ADS1x9x (unsigned char device_slot)
{
    ADS1298_PowerDown();
    ADS1298_ClkselLow();

}

void Power_Up_ADS1x9x (unsigned char device_slot)
{    
    ADS1298_PowerUp();
	ADS1298_StartHigh();

}


void Set_ADS1x9x_Chip_Enable (unsigned char device_slot)                        // ADS1x9x module uses GPIO as the SPI CS
{
    //此处片选是由SPI总线自动产生

	ADS1298_CS_Low();
	
	//delayUS(1);                                                   // Short Delay before invoking the SPI Port
}

void Clear_ADS1x9x_Chip_Enable (unsigned char device_slot)                      // ADS1x9x uses GPIO for SPI CS
{
    //此处片选是由SPI总线自动产生  
	ADS1298_CS_High(); 

	//delayUS(1);
}

unsigned char ADS1x9x_SPI_Data (unsigned char device_slot, unsigned char Data)  // Complements the SPI_Address command 
{
    //清发送中断标志
    USR_SPI_ClearFlag(SPI1,SPI_FLAG_TXE);
    //清接收中断标志
    USR_SPI_ClearFlag(SPI1,SPI_FLAG_RXNE); 

	USR_SPI_SendData(SPI1,Data);                              // Send the data sitting at the pointer Data to the TX Buffer
	while (USR_SPI_GetFlagStatus(SPI1,SPI_FLAG_TXE) == RESET);
    while (USR_SPI_GetFlagStatus(SPI1,SPI_FLAG_RXNE) == RESET);
     //清发送中断标志
    USR_SPI_ClearFlag(SPI1,SPI_FLAG_TXE);
    //清接收中断标志
    USR_SPI_ClearFlag(SPI1,SPI_FLAG_RXNE);     

	//delayUS(10);
	//delayUS(10);
//    Clear_ADS1x9x_Chip_Enable (device_slot);                                    // Clear the Chip ENABLE to terminate the SPI transaction
    return (USR_SPI_ReceiveData(SPI1));                             // Return Status Data or Requested Read Data
}

 

void Soft_Start_ReStart_ADS1x9x (unsigned char device_slot)
{
    ADS1298_StartLow();                                                 // Start Pin LOW   
    //delayUS(20);  
	Set_ADS1x9x_Chip_Enable (device_slot);  
	delayUS(10);                                              // Small Delay   
    ADS1x9x_SPI_Data (device_slot, START_RESTART_CONVERSION);                   // Send 0x08 to the ADS1x9x
    delayUS(40);
	Clear_ADS1x9x_Chip_Enable (device_slot); 
	delayUS(10);                                                      
}

void Soft_Reset_ADS1x9x (unsigned char device_slot)
{
    Set_ADS1x9x_Chip_Enable (device_slot); 
	Delay_1us(10);
	ADS1x9x_SPI_Data (device_slot, RESET_CONVERTER);                            // Send 0x06 to the ADS1x9x
	Delay_1us(70);
	Clear_ADS1x9x_Chip_Enable (device_slot);
 	Delay_1us(40);
}

void Start_Read_Data_Continuous (unsigned char device_slot)
{
   	Set_ADS1x9x_Chip_Enable (device_slot); 
	delayUS(10); 
	ADS1x9x_SPI_Data (device_slot, SET_READ_DATA_CONTINUOUSLY);       // Send 0x06 to the ADS1x9x
	delayUS(70);
	Clear_ADS1x9x_Chip_Enable (device_slot);
 	delayUS(40);
}


void Stop_Read_Data_Continuous (unsigned char device_slot)
{
    Set_ADS1x9x_Chip_Enable (device_slot);
	Delay_1us(10);
    ADS1x9x_SPI_Data (device_slot, STOP_READ_DATA_CONTINUOUSLY);
	Delay_1us(40);
	Clear_ADS1x9x_Chip_Enable (device_slot);
	Delay_1us(20);
}


void ADS1x9x_SPI_Address_Byte_Count (unsigned char device_slot, unsigned char Read_Write_Address, unsigned char Number_Of_Bytes)
{ 
  	//清发送中断标志
    USR_SPI_ClearFlag(SPI1,SPI_FLAG_TXE);
	//清接收中断标志
    USR_SPI_ClearFlag(SPI1,SPI_FLAG_RXNE);
	USR_SPI_SendData(SPI1,Read_Write_Address);               // Transmit the Funtion/Address payload
   	while (USR_SPI_GetFlagStatus(SPI1,SPI_FLAG_TXE) == RESET);
    while (USR_SPI_GetFlagStatus(SPI1,SPI_FLAG_RXNE) == RESET);
	
	//清发送中断标志
    USR_SPI_ClearFlag(SPI1,SPI_FLAG_TXE);
    //清接收中断标志
    USR_SPI_ClearFlag(SPI1,SPI_FLAG_RXNE);
	//delayUS(40);
    //此处片选是由SPI总线自动产生
	USR_SPI_SendData(SPI1,Number_Of_Bytes);                  // Transmit the Number of Bytes payload
	while (USR_SPI_GetFlagStatus(SPI1,SPI_FLAG_TXE) == RESET);
    while (USR_SPI_GetFlagStatus(SPI1,SPI_FLAG_RXNE) == RESET);
    //清发送中断标志
    USR_SPI_ClearFlag(SPI1,SPI_FLAG_TXE);;
    //清接收中断标志
    USR_SPI_ClearFlag(SPI1,SPI_FLAG_RXNE);
    
//	delayUS(10);
}


unsigned char ADS1x9x_Read_Version (unsigned char device_slot)  
{
    unsigned char Version_ID = 0;
	
	Set_ADS1x9x_Chip_Enable (device_slot);
	Delay_1us(10);
    ADS1x9x_SPI_Address_Byte_Count (device_slot, READ_DEVICE_ID, SINGLE_BYTE_READ_WRITE);    // Read Device ID, Single Byte the Part Number
	//delayUS(40);
	Version_ID = ADS1x9x_SPI_Data (device_slot, SPI_TEST_DATA); // Send Dummy variable (0x55) to return the part number (Chip Select Cleared automatically)
	//Version_ID = ADS1x9x_SPI_Data (device_slot, SPI_TEST_DATA); // Send Dummy variable (0x55) to return the part number (Chip Select Cleared automatically)
	Delay_1us(40);
	Clear_ADS1x9x_Chip_Enable (device_slot);
	Delay_1us(20);
	return Version_ID;
}  


unsigned char init_ADS1x9x (unsigned char device_slot)
{
    unsigned char Verify_Check = 0;
    unsigned char Module_Present = 0;
	unsigned char ADS1x9x_Version_ID_Number=0;
    unsigned char number_of_retries = 10;
	//WORD i = 0;
	Puts("\r\n init_ADS1x9x_Data_Ready_Interrupt");
    init_ADS1x9x_Data_Ready_Interrupt ();     // Set up the ADS1x9x Interrupt pin
    init_ADS1x9x_IO (device_slot);    
    Puts("\r\n Delay_1us");
    Delay_1us(10);
    Power_Up_ADS1x9x (device_slot);                 // Power up Digital portion of the ADS1x9x                                              
	
	Puts("\r\n Power_Up_ADS1x9x");

    POR_Reset_ADS1x9x (device_slot);
    Puts("\r\n Soft_Reset_ADS1x9x");
	//ADS1298软复位
	Soft_Reset_ADS1x9x(device_slot);

	//停止连续读数
	Puts("\r\n Stop_Read_Data_Continuous");
	Stop_Read_Data_Continuous (device_slot);
	Puts("\r\n Module_Present");
	while (!Module_Present)                                                     // Wait for Module to be present
	{
	    if (number_of_retries)
	    {
			ADS1x9x_Version_ID_Number = ADS1x9x_Read_Version (device_slot);

			printf("\r\n ADS1x9x_Version_ID_Number %x", ADS1x9x_Version_ID_Number);
			if (ADS1x9x_Version_ID_Number == ADS1x9x_VERSION_ID)                  // (0x22 for old board, 0x42 for new one)                 
			{
				Module_Present = SET;  
			}
			
			number_of_retries--;
	    }
	    else
	    {
			Puts("\r\n ADS_1x9x_NOT_FOUND");
	        return ADS_1x9x_NOT_FOUND;
	    }
	} 

	
	//从AT24C01空间读取配置参数

	 // AT24CXX_Read(Parmnent_Addr,	ADS1298_Parment,Parmnent_Length);
   	  //Verify_Check = Initialize_ADS1x9x_Registers (device_slot, (unsigned char*) ADS1x9x_download_pointer);
	  //Verify_Check = Initialize_ADS1x9x_Registers (device_slot, ADS1298_Parment);

#if 0
	Puts("\r\n 350");
    init_ADS1x9x_Via_Constant_Table (device_slot, (unsigned char*) ADS1x9x_download_pointer);
    Puts("\r\n 352");
    Verify_Check = verify_ADS1x9x_Registers (device_slot, (unsigned char*) ADS1x9x_download_pointer);
    Puts("\r\n 354");
    Verify_Check = Initialize_ADS1x9x_Data_Rate (device_slot, (*ADS1x9x_download_pointer)&0x7f/*MODULATION_FREQUENCY_DIVIDED_BY_1024*/);    // DEFAULT_MODULATION_FREQUENCY_DIVIDED_BY_16
                                                                                             // MODULATION_FREQUENCY_DIVIDED_BY_512
    Puts("\r\n 357");                                                                                // MODULATION_FREQUENCY_DIVIDED_BY_1024
    if((*ADS1x9x_download_pointer)>>7)
	{
    	Verify_Check = Initialize_ADS1x9x_Mode (device_slot, HIGH_RESOLUTION_MODE);                         // DEFAULT_LOW_POWER_MODE, HIGH_RESOLUTION_MODE
    }
	else
	{

	   Verify_Check = Initialize_ADS1x9x_Mode (device_slot, DEFAULT_LOW_POWER_MODE);
	}
	Puts("\r\n 367");
    for (i = 0; i < ECG_Num_Channels; i++)
    {
        Verify_Check = Initialize_ADS1x9x_Channel                             //  Context Save will store the previous setting of the channel 
        (
            device_slot, 
            i + 1,                                                              // references channels 1 - 8
            DEFAULT_ADS1x9x_ELECTRODE_INPUT,                                    // DEFAULT_ADS1x9x_ELECTRODE_INPUT, ADS1x9x_INPUT_SHORTED, ADS1x9x_RIGHT_LEG_DETECT, ADS1x9x_ONE_HALF_DIGITAL_SUPPLY
                                                                                // ADS1x9x_TEMPERATURE_SENSOR, ADS1x9x_CALIBRATION_SIGNAL, ADS1x9x_RIGHT_LEG_DETECT_POSITIVE, ADS1x9x_RIGHT_LEG_DETECT_NEGATIVE
            DEFAULT_GAIN_OF_6,                                                  // DEFAULT_GAIN_OF_6, GAIN_OF_1, GAIN_OF_2, GAIN_OF_3, GAIN_OF_4, GAIN_OF_8, GAIN_OF_12
            DEFAULT_DISABLE_POWER_DOWN,                                         // DEFAULT_DISABLE_POWER_DOWN, ENABLE_POWER_DOWN
            IGNORE_PREVIOUS_STATE                                               // CONTEXT_SAVE_CHANNEL, IGNORE_PREVIOUS_STATE
       		
	    ); 
        
        if (Verify_Check == ADS_1x9x_VERIFY_ERROR)
        {
            break;                                                              // exit loop and report verify error
        }
    }
#endif
   
    disable_ADS1x9x_Interrupt (device_slot);
    
    return Verify_Check;
}




void enable_ADS1x9x_Conversion (unsigned char device_slot)
{    
    
	enable_ADS1x9x_Interrupt (device_slot);                                     // Interrupts must be enabled to transmit and receive data

	//执行RDATAC命令行将忽略操作寄存器命令
    Start_Read_Data_Continuous (device_slot);                                   // Enable continuous conversion mode
    
	//停止连续读数
//	Stop_Read_Data_Continuous (device_slot);
//	Hard_Start_ReStart_ADS1x9x (device_slot);                                   // Pull START pin high
//    delayUS(40);
    Soft_Start_ReStart_ADS1x9x (device_slot);
    ADS1x9x_Status_Flags.ADC_Data_Ready = RESET;                                // Clear Data Ready flag
}

unsigned char ADS1x9x_SPI_Burst (unsigned char device_slot, unsigned char Data) // Complements the SPI_Address command 
{   
     //清发送中断标志
    USR_SPI_ClearFlag(SPI1,SPI_FLAG_TXE);;                                                                        //  But allows multiple transactions (no Clear Chip ENABLE)
    //清接收中断标志
    USR_SPI_ClearFlag(SPI1,SPI_FLAG_RXNE);
    USR_SPI_SendData(SPI1,Data);                              // Send the data sitting at the pointer Data to the TX Buffer

    //while (USR_SPI_GetFlagStatus(SPI1,SPI_FLAG_TXE) == RESET);
    while (USR_SPI_GetFlagStatus(SPI1,SPI_FLAG_RXNE) == RESET);

    //delayUS(40);   
    return (USR_SPI_ReceiveData(SPI1));                             // Return Status Data or Requested Read Data
}


void Soft_Stop_ADS1x9x (unsigned char device_slot)
{  	
    ADS1298_StartLow();                                                 // Start Pin LOW   
    delayUS(20);                                                   // Small Delay   
    Set_ADS1x9x_Chip_Enable (device_slot); 
    delayUS(40);
	ADS1x9x_SPI_Data (device_slot, STOP_CONVERSION);                            // Send 0x0A to the ADS1x9x
	delayUS(40);
}
