#include "stm32f10x.h"
#include "parameters.h"
#include "systemDev.h"
#include "init.h"
#include "i2c1.h"
#include "usart3.h"
#include "tasks.h"

void TIM2_IRQHandler(void){
	counter++;
	if(counter == 1){
		addTask(green_on);
	}
	if(counter == 2){
		addTask(green_off);
		counter=0;
	}
	TIM2->SR &= ~TIM_SR_UIF;
}

int main(){
	u8 res;
	initRCC();
	initGPIO();
	initTIM2();
	initUSART3();
	initI2C1();

	__enable_irq();                       // глобальное включение прерывания

	// I2C1_tx(0xD0,0x6B,0x00);
	// I2C1_tx(0xD0,0x1B,0xE0);
	// I2C1_tx(0xD0,0x1C,0xE0);
	read_I2C1(GY521_ADRESS,WHO_I_AM);
	// read_data_acc();
	green_on();
	while(1){
	    while(!number_of_tasks)
	        {}
	    (*buffer_of_tasks[head_of_tasks])();
	    deleteTask();
	    }
	return 0;
}
