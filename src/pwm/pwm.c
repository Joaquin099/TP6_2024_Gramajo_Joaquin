#include "main.h"
#include "Definiciones.h"
#include "pwm.h"

void PWM_Configuracion(void) {

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);						// Habilitar el reloj del timer utilizado TIM4

	uint16_t prescalerValue = (uint16_t) ((SystemCoreClock / 2) / 1000) - 1;	// Calcular los valores para la frecuencia deseada (1000 Hz) y el ciclo de trabajo del 50%
	uint16_t periodValue = (uint16_t) (prescalerValue / 2);

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;								// Configurar el timer para modo PWM
	TIM_TimeBaseStructure.TIM_Prescaler = prescalerValue;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = periodValue;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	TIM_OCInitTypeDef TIM_OCInitStructure;										// Configurar canal para salida PWM
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = periodValue / 2; 							// Ciclo de trabajo del 50%
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 					// Polaridad alta
	TIM_OC3Init(TIM4, &TIM_OCInitStructure); 									// Canal 3 del timer (ajusta seg n tus necesidades)

	TIM_Cmd(TIM4, ENABLE);														// Habilitar el timer
	TIM_CtrlPWMOutputs(TIM4, ENABLE);											// Habilitar el canal PWM

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);						// Configurar el pin correspondiente para la salida PWM
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM4);
}
