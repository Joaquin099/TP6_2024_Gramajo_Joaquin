#ifndef DEFINICIONES_DEFINICIONES_H_
#define DEFINICIONES_DEFINICIONES_H_
#endif /* DEFINICIONES_DEFINICIONES_H_ */

#include "stm32f4xx.h"

typedef	struct {
	uint32_t u32_Systick;
} General;

General Gen;

void Init_BackL(void);
void delay_ms(uint16_t timeDelay);
void delay_us(uint16_t timeDelay);

