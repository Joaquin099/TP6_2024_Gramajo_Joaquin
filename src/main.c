/*-----------------------------------Includes-----------------------------------*/
#include "LCD.h"
#include "DAC.h"
#include "ADC.h"
#include "Menu.h"
#include "stdio.h"
#include "Teclado.h"
#include "Display_LCD.h"
#include "Definiciones.h"


/*-----------------------------------Functions----------------------------------*/
void SysTick_Handler(void);
void delay_ms (uint16_t timeDelay);
void delay_us (uint16_t timeDelay);
void Init_BackL(void);

/*-----------------------------------Variables----------------------------------*/
uint32_t u32_Sys_Display;
uint32_t u32_Sys_Keyboard;
uint32_t u32_Sys_Contador;
uint16_t u16_Sys_Time = 0;
uint16_t u16_DAC;

char Key;
char ctime[6];
char c_DAC[10];

/*------------------------------------Main-------------------------------------*/
int main(void)
{
	Gen.u32_Systick = 0;

	u32_Sys_Display  = Gen.u32_Systick;
	u32_Sys_Keyboard = Gen.u32_Systick;
	u32_Sys_Contador = Gen.u32_Systick;

	Init_Keypad();
	Init_BackL();
	Init_Display();
	Init_DAC();
	Init_ADC();


	while(1){

		if (Gen.u32_Systick - u32_Sys_Contador > 1000) {				//CONTADOR SEGUNDOS
			u32_Sys_Contador = Gen.u32_Systick;
			u16_Sys_Time++;
		}

		if (Gen.u32_Systick - u32_Sys_Keyboard > 10) {					//TECLADO MATRICIAL
			u32_Sys_Keyboard = Gen.u32_Systick;
			Key = Read_Keypad();
		}

		if (Gen.u32_Systick - u32_Sys_Display > 250) {					//REFRESCO LCD
			//La condicion del if puede cambiarse a que key != 0 para hacer el refresco de la pantalla. Probar.
			u32_Sys_Display = Gen.u32_Systick;
			sprintf(ctime, "%d", u16_Sys_Time);
			sprintf(c_DAC, "%d", u16_DAC);
			Init_Menu(Key, ctime, c_DAC);
			if(Key == '#'){
				GPIO_SetBits(GPIOB, GPIO_Pin_13);
			}else if(Key == '*'){
				GPIO_ResetBits(GPIOB, GPIO_Pin_13);
			}
		}
	}
}

/*-----------------------------------Functions---------------------------------*/
void SysTick_Handler(void) {
	if (Gen.u32_Systick > 0xFFFF){
		Gen.u32_Systick = 0;
	}
	Gen.u32_Systick++;
}

void delay_ms (uint16_t timeDelay){										//FUNCIONES
	uint16_t LocalSystick = Gen.u32_Systick;
	while (1)
		if (Gen.u32_Systick - LocalSystick > timeDelay){
			return;
		}
}

void delay_us (uint16_t timeDelay){
	uint16_t u16i;
	while (timeDelay){
		for (u16i = 0; u16i < 14; u16i++);								//DELAY DE 1us
		timeDelay--;
	}
}

void Init_BackL(void){													//INICIO BL Y CK
	SysTick_Config(SystemCoreClock / 1000);
	NVIC_SetPriority (SysTick_IRQn, 0);

	GPIO_InitTypeDef GPIO_InitStruct;

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_SetBits(GPIOB, GPIO_Pin_13); 								//ENCENDIDO PRINCIPAL BACKLIGHT
}
