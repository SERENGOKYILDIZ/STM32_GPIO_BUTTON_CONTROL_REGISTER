#include "stm32f4xx.h"
#include "stm32f4_discovery.h"

void RCC_Config(void)
{
	// 8Mhz -> 168Mhz
	RCC->CR &= ~(1 << 0);
	RCC->CR |= 1 << 16;
	while(!(RCC->CR & (1 << 17)));
	RCC->CR |= 1<<19;
	RCC->PLLCFGR = 0x00000000;
	RCC->PLLCFGR |= (1 << 22);
	RCC->PLLCFGR |= (4<<0);
	RCC->PLLCFGR |= (168<<6);
	RCC->PLLCFGR &= ~(1 << 16);
	RCC->PLLCFGR &= ~(1 << 17);
	RCC->CR |= (1 << 24);
	while(!(RCC->CR & (1 << 25)));
	RCC->CFGR &= ~(1 << 0);
	RCC->CFGR |= (1 << 1);
	while(!(RCC->CFGR & (1 << 1)));
}
void GPIO_Config(void)
{
	RCC->AHB1ENR = 0x9; 				//->GPIOA and GPIOD clock's enabled.

	//Settings of GPIOD
	GPIOD->MODER |= (0x55 << 24);   	//->D12, D13, D14, D15 = Output.
	GPIOD->OTYPER |= (0xff << 3);       //->D12, D13, D14, D15 = Open-drain.
	GPIOD->OSPEEDR |= (0xff << 24);   	//->D12, D13, D14, D15 = Very High speed.
}
void delay(uint32_t time)
{
	while(--time);
}
int main(void)
{
	//Settings of Clock
	RCC_Config();
	SystemCoreClockUpdate();

	//Settings of GPIO
	GPIO_Config();

	uint8_t count;
	while (1)
	{
		if(GPIOA->IDR & 0x1)
		{
			while(GPIOA->IDR & 0x1);
			delay(1680000);
			count++;
		}
		switch(count)
		{
			case 1:
			GPIOD->ODR |= (1 << 12);
			break;

			case 2:
			GPIOD->ODR |= (1 << 13);
			break;

			case 3:
			GPIOD->ODR |= (1 << 14);
			break;

			case 4:
			GPIOD->ODR |= (1 << 15);
			break;

			case 5:
			GPIOD->ODR &= ~(1 << 12);
			delay(1680000);
			GPIOD->ODR &= ~(1 << 13);
			delay(1680000);
			GPIOD->ODR &= ~(1 << 14);
			delay(1680000);
			GPIOD->ODR &= ~(1 << 15);
			delay(1680000);
			count = 0;
			break;
		}
	}
}







void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
  /* TODO, implement your code here */
  return;
}
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
  /* TODO, implement your code here */
  return -1;
}
