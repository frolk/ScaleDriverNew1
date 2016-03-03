#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "RX_UART.h"
#include "BLrxtx.h"
#include "BLdefComd.h"
#include "PWM.h"

float ScaleValue;
int ScaleValueDetect;
uint8_t *StrScaleValueDetect;
uint8_t DebugAskAnswer[16];


int main(void)
{
	SW_RX_Init(); 
	BL_Init(MYUBRR);
	PWM_Init();
		
    while (1) 
    {
		if(SWrxDataPending)
			{
				SW_RX_Fill_Buffer();
			}
		if(SWmesIsComplete)
			{

			SW_GetMessage();
			ScaleValue = atof(SWscaleValueForBL+1);
			//OCR2A = ScaleValue;
			if (ScaleValue > 0)
			{
				BL_SendStr (SWscaleValueForBL);
			}
			SWmesIsComplete = 0;		
			
			}
				
			
						
		if (BLmesIsComplete) 
			{
			//BL_SendStr (BluetoothMessage);
						
			BL_DefComd(); // defining gotten message from bluetooth (smartphone)
			BLmesIsComplete = 0;  // reset flag "complete message from smartphone"
			}
		
		if(DebugAsk)
			{
				BL_SendStr(StrScaleValueDetect);
				DebugAsk = 0;
			}
				
		if (PWMvalue && (ScaleValue > 20))
				{
					PWM_PinValue();   // write gotten correction value from smartphone to OCR2A for change OC2A pin PWM
					//PWMvalue = 0;
					ScaleValueDetect = ScaleValue; 
					StrScaleValueDetect = itoa(ScaleValueDetect,StrScaleValueDetect,10);
				}	
				
		if((ScaleValue < (ScaleValueDetect - 2)) && (ScaleValue > 5))
		{
			OCR2A = 0;
		}
			
	}
	}

