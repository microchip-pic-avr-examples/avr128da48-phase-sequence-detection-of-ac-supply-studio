/*
 * Communication.c
 *
 * Created: 12/13/2019 1:58:18 PM
 *  Author: I20946
 */ 

/******************************************************************************/
/* Include Files                                                              */
/******************************************************************************/
#include "Communication.h"
#include "spi_basic.h"
#include "spi_basic_example.h"
#include "atomic.h"


void drive_slave_select_low();
void drive_slave_select_high();
/*******************************************************************************
 * void SPI_Init(void)
 *
 * API to Initialize the SPI0 
 *
 * @param void 
 * @return void 
 ******************************************************************************/
unsigned char SPI_Init()
{
         SPI_0_init();
		 
		 return 0;
}

/*******************************************************************************
 * unsigned char SPI_Write(unsigned char* data,
 *                       unsigned char bytesNumber)
 *
 * API to write block to slave target through SPI0 
 *
 * @param data - data to be write, bytesNumber - number of bytes to write 
 * @return dummy char  
 ******************************************************************************/
unsigned char SPI_Write(unsigned char* data,
                        unsigned char bytesNumber)
{
           SPI_0_write_block(data,bytesNumber);
	 return 0;
}

/*******************************************************************************
 * unsigned char SPI_Read(unsigned char* data,
 *                      unsigned char bytesNumber)
 *
 * API to Read through SPIO from target slave  
 *
 * @param data - data to be read (empty buffer), bytesNumber - number of bytes to be read
 * @return dummy char  
 ******************************************************************************/
unsigned char SPI_Read(unsigned char* data,
                       unsigned char bytesNumber)
{
       SPI_0_read_block(data,bytesNumber);
	   return 0;
}

/*******************************************************************************
 * void AD9833_chipSelect (uint8_t selAD9833, uint8_t level)
 *
 * API to select SPI0 slave1 
 *
 * @param selAD9833 - slave to be select , bytesNumber - number of bytes to be read
 * @return void 
 ******************************************************************************/
void AD9833_chipSelect (uint8_t selAD9833, uint8_t level)
{
 
       switch(selAD9833)
	   {
	     case 1:
		  AD9833_FSN1_set_level(level);
		 break;
		 case 2:
		  AD9833_FSN2_set_level(level);
		 break;
		 case 3:
		  AD9833_FSN3_set_level(level);
		 break;

	   }
	   
}
/*******************************************************************************
 * void AD5227_chipSelect (uint8_t selAD9833, uint8_t level)
 *
 * API to select SPI0 slave2 
 *
 * @param selAD9833 - slave to be select , bytesNumber - number of bytes to be read
 * @return void 
 ******************************************************************************/
void AD5227_chipSelect (uint8_t selAD5227, uint8_t level)
{
	switch(selAD5227)
	{
		case 1:
		AD5227_CS1_set_level(level);
		break;
		case 2:
		AD5227_CS2_set_level(level);
		break;
		case 3:
		AD5227_CS3_set_level(level);
		break;
	}
}