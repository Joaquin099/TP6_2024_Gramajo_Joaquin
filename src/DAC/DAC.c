#include "DAC.h"
#include "Menu.h"
#include "Definiciones.h"


void Init_DAC(void){
	static DAC_InitTypeDef DAC_InitStructure;
	static GPIO_InitTypeDef GPIO_InitStruct;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);							//Clock Enable

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;										//Configuracion en el pin 4 - PORT A como salida Analogica (es la DAC OUT1)
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);

	RCC_AHB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);							//DAC: Activar Clock

	DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;							//DAC configuracion
	DAC_InitStructure.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);

	DAC_Cmd(DAC_Channel_1, ENABLE);												//DAC ON Channel 1
}

void writeDAC(uint16_t valor_DAC){
	if(valor_DAC > 4095){
		valor_DAC = 4095;
	}
	DAC_SetChannel1Data(DAC_Align_12b_R, valor_DAC);
}



