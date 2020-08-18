/*
 * application_isr.c
 *
 * Created: 5/5/2020 8:40:04 AM
 *  Author: I20946
 */ 
#include "application_isr.h"

volatile uint16_t timerCounterValue[3] = {0};   //we need uint16_t array for 64 pin controller timer calculation
volatile uint8_t timer1OverflowFlag = 0;
volatile uint8_t ZCD_Int_flag[3] = {0};
volatile uint8_t PhaseLossFlag[3] = {0};      //For 3 ZCD solution (64 pin controller)
volatile uint32_t refreshCount = 0;
volatile uint16_t timer1OvfCnt = 0;

/*******************************************************************************
 * void ZCD0_ZCD_vect
 *
 * Interrupt routine, executes when zero-cross detects, routine start the timer for
 * measuring the period between the two zero crossingAPI to Initialize the SPI0 
 *
 * @param void 
 * @return void 
 ******************************************************************************/
ISR(ZCD0_ZCD_vect)
{
	/* Insert your ZCD interrupt handling code here */
	TCA0_SINGLE_CNT = 0;
	ZCD_Int_flag[0] = 1;
	PhaseLossFlag[0] = 1;
	
	ZCD0.STATUS = ZCD_CROSSIF_bm;
}

/*******************************************************************************
 * void ZCD1_ZCD_vect
 *
 * Interrupt routine, executes when zero-cross detects,
 *   
 * @param void 
 * @return void 
 ******************************************************************************/
ISR(ZCD1_ZCD_vect)
{
	/* Insert your ZCD interrupt handling code here */
	if (ZCD_Int_flag[0] == 1)
	{
		ZCD_Int_flag[0] = 0;
		timerCounterValue[0] = TCA0_SINGLE_CNT;
		
	}
	ZCD_Int_flag[1] = 1;
	PhaseLossFlag[1] = 1;
	
	ZCD1.STATUS = ZCD_CROSSIF_bm;
}

/*******************************************************************************
 * void SPI_Init(void)
 *
 * API to Initialize the SPI0 
 *
 * @param void 
 * @return void 
 ******************************************************************************/
ISR(TCA0_OVF_vect)
{
	/* Insert your TCA overflow interrupt handling code */

	/* The interrupt flag has to be cleared manually */
	TCA0.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
}

/*******************************************************************************
 * void SPI_Init(void)
 *
 * API to Initialize the SPI0 
 *
 * @param void 
 * @return void 
 ******************************************************************************/
ISR(TCA1_OVF_vect)
{
	/* The interrupt flag has to be cleared manually */
	TCA1.SINGLE.INTFLAGS = TCA_SINGLE_OVF_bm;
	/* Insert your TCA overflow interrupt handling code */
	timer1OverflowFlag = 1;
	timer1OvfCnt += 1;
	refreshCount += 1;
}