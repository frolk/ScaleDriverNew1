#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "RX_UART.h"
#include "BLrxtx.h"
#include "BLdefComd.h"
#include "PWM.h"

float ScaleValue;
float ScaleValueChange;
int ScaleValueDetect;
uint8_t StrScaleValueDetect[5];
uint8_t StrPWMValue[5];
uint8_t StrOCR[5];
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
			if ((ScaleValue > 0) && !(ScaleValue == ScaleValueChange))
			{
				ScaleValueChange = ScaleValue;
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
				StrScaleValueDetect[5] = itoa(ScaleValueDetect,StrScaleValueDetect,10);
				StrPWMValue[5] = itoa(PWMvalue, StrPWMValue, 10);
				StrOCR[5] = itoa(OCR2A, StrOCR, 10);
				BL_SendStr(StrScaleValueDetect);
				BL_SendStr(StrPWMValue);
				BL_SendStr(StrOCR);
				DebugAsk = 0;
			}
				
		if (PWMvalue && PWMChanged && (ScaleValue > 20))
				{
					PWM_PinValue();   // write gotten correction value from smartphone to OCR2A for change OC2A pin PWM
					ScaleValueDetect = ScaleValue; 
					PWMChanged = 0;
				}	
				
		if((ScaleValue < (ScaleValueDetect - 2)) && (ScaleValue > 5))
		{
			OCR2A = 0;
			ScaleValueDetect = 0;
		}
	}
	}

