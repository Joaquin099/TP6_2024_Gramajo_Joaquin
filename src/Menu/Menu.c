#include "LCD.h"
#include "stdio.h"
#include "Teclado.h"
#include "Display_LCD.h"
#include "Definiciones.h"


static uint8_t constante = 0;
static char str_key[2];
uint8_t destello = 0;
//static float float_ADC;
//static char str_ADC[5];

char *texto[]={
		"Tecla pres.",
		"Backlight",
		"FUN Control",
		"Generador DAC",
		"Medicion ADC",
		""
};

typedef enum{
	Menu,
	Tecla_press,
	Backlight,
	FUN,
	Generador_DAC,
	Medicion_ADC,
	Mantener
}Estados;

Estados EST = Menu;

void Init_Menu(char tecla, char tiempo[6], char str_DAC[10]){

	switch(EST){
	case Menu:
		if(constante == 0 && tecla == 'A'){
			EST = Menu;
			break;
		}
		if(constante == 4 && tecla == 'B'){
			EST = Menu;
			break;
		}

		if(tecla == 'B'){
			constante++;
			LCD_clrscr();
			LCD_WriteString(0, 0, ">");
			LCD_WriteString(1, 0, texto[constante]);
			LCD_WriteString(0, 1, texto[constante+1]);
			EST = Mantener;
			break;
		}

		if(tecla == 'A'){
			constante=constante-1;
			LCD_clrscr();
			LCD_WriteString(0, 0, ">");
			LCD_WriteString(1, 0, texto[constante]);
			LCD_WriteString(0, 1, texto[constante+1]);
			EST = Mantener;
			break;
		}

		if(tecla == 'C'){
			LCD_clrscr();
			if(constante == 0){
				EST = Tecla_press;
				break;
			}else if(constante == 1){
				EST = Backlight;
				break;
			}else if(constante == 2){
				EST = FUN;
				break;
			}else if(constante == 3){
				EST = Generador_DAC;
				break;
			}else if(constante == 4){
				EST = Medicion_ADC;
				break;
			}
		}

		if(tecla == 'D'){
			LCD_clrscr();
			LCD_WriteString(0, 0, ">");
			LCD_WriteString(1, 0, texto[constante]);
			LCD_WriteString(0, 1, texto[constante+1]);
			EST = Menu;
		}
		break;

	case Mantener:
		if(tecla == 'A' || tecla == 'B'){
			EST = Mantener;
		}else{
			EST = Menu;
		}
		break;

	case Tecla_press:
		if(tecla == 'D'){
			EST = Menu;
			break;
		}
		sprintf(str_key, "%c", tecla);
		LCD_WriteString(0, 0, "Tecla pres.: ");
		LCD_WriteString(13, 0, str_key);
		break;

	case Backlight:
		if(tecla == 'D'){
			EST = Menu;
			break;
		}
		if(GPIO_ReadOutputDataBit(GPIOB, GPIO_Pin_13)){
			LCD_clrscr();
			LCD_WriteString(0, 0, "Backlight: ON");
		}else{
			LCD_clrscr();
			LCD_WriteString(0, 0, "Backlight: OFF");
		}
		break;

	case FUN:
		if(tecla == 'D'){
			EST = Menu;
			break;
		}
		LCD_WriteString(0, 0, "PWM: %");
		//LCD_WriteString(7, 0, valor pwm);

		if(tecla == 'C' || destello == 1){
			destello = 1;
			LCD_WriteString(0, 0, "PWM:");
			LCD_WriteString(7, 0, "      ");
			delay_ms(1000);
			LCD_WriteString(0, 0, "PWM: %");
			//Escribir valor pwm en espacio 7
			//LCD_WriteString(7, 0, valor pwm);
			break;
		}
		break;

	case Generador_DAC:
		if(tecla == 'D'){
			EST = Menu;
			break;
		}
		LCD_WriteString(0, 0, "DAC: ");
		str_DAC = str_DAC * 100;
		LCD_WriteString(5, 0, str_DAC);
		LCD_WriteString(9, 0, "mV");
		if((tecla=='1') && (tecla=='9')){
			writeDAC(4096 * (tecla - '2') * 100 / 3300);
			str_DAC = tecla - '2';
		}
		break;

	case Medicion_ADC:
		if(tecla == 'D'){
			EST = Menu;
			break;
		}
		break;
	}
}
