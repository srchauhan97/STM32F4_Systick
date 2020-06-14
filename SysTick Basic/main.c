#include "stm32f4xx.h"


void SystickDelayMs(uint8_t Count)
{
	//now since clock is 16Mhz, so 16 000 000 cycles per second
	//so 16000 cycles per 1mili second
	//so we will load the Systick with 1msec value
	SysTick->LOAD |= 16000-1;
	SysTick->VAL = 0;
	//5= 101, so Clocksource bit which is 3rd bit is set,  enable bit whnich is 1st bit is set in Control register
	SysTick->CTRL |= 5;
	
	for(int i=0;i<Count;i++)
	{
		while(!((SysTick->CTRL >> 16) & 0x1));
	}
	//now disable the Systick
	SysTick->CTRL = 0;
}
void SystickDelayS(uint8_t Count)
{
	//now since clock is 16Mhz, so 16 000 000 cycles per second
	//so we will load the Systick with 1msec value
	SysTick->LOAD |= 16000000-1;
	SysTick->VAL = 0;
	
	//now run for no of seconds.
	for(int i=0;i<Count;i++)
	{
		while((!(SysTick->CTRL) >> 16) & 0x1);
	}
	SysTick->CTRL = 0;
}

int main(void)
{
	//Enable clock for led
	//led is connected to PA5,  Port A is in AHB bus
	RCC->AHB1ENR |= (1 << 1);
	//give gpio configurations
	GPIOA->MODER |= ( 1 << 10);
	GPIOA->OSPEEDR |= (1 << 10);
	
	
	while(1)
	{
		//Check if flag is set
			SystickDelayMs((uint8_t)500);
			GPIOA->ODR ^= 1<< 5;
		
	}
	
}
