
#ifndef BLdefComd_H_
#define BLdefComd_H_


extern uint16_t PWMvalue;

extern void BL_DefComd();  // define bluetooth command

void BL_GetMessage();

extern uint8_t BluetoothMessage[10];
	
void UART_Init (unsigned int ubrr); // initialize UART

extern uint8_t PWMChanged;

#endif 

