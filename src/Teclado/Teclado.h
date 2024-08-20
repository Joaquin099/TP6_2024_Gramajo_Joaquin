#ifndef TECLADO_H_
#define TECLADO_H_
#endif /* TECLADO_H_ */

#define RCC_PINES RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOA

void Delay_MS(uint32_t ms);
void Init_Keypad(void);
char Read_Keypad(void);
