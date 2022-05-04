#include "stm32f051x8.h"


uint8_t i=0;


void TIM2_IRQHandler(void)
{
  TIM2->SR &= ~TIM_SR_UIF; //Clean UIF Flag

    GPIOC->ODR ^= GPIO_ODR_9;   // Set PC8 bit
    GPIOC->ODR ^= GPIO_ODR_8;   // Reset PC9 bit

}



int main(void) 
{
  RCC->AHBENR |= RCC_AHBENR_GPIOCEN;  // Enable PORTC Periph clock
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;  // Enable TIM2 Periph clock
  // Clear PC8 and PC9 control register bits
  GPIOC->MODER &= ~(GPIO_MODER_MODER8 | GPIO_MODER_MODER9);
  // Configure PC.8 and PC.9 as Push Pull output at max 10Mhz
  GPIOC->MODER |= GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0;
  TIM2->PSC = SystemCoreClock / 1000 - 1; // 1000 tick/sec
  TIM2->ARR = 1000;  // 1 Interrupt/sec (1000/100)
  TIM2->DIER |= TIM_DIER_UIE; // Enable tim2 interrupt
  TIM2->CR1 |= TIM_CR1_CEN;   // Start count
  NVIC_EnableIRQ(TIM2_IRQn);  // Enable IRQ
  GPIOC -> BSRR |= GPIO_BSRR_BS_8;
  
}
 


/*

void TIM2_IRQHandler(void) //Функция обработчика прерывания от таймера 6
  {
    TIM2->SR &= ~TIM_SR_UIF; //Сбрасываем бит вызова прерывания. 
    GPIOC->ODR ^= GPIO_ODR_9;//Инвертируем состояние вывода - зажигаем/гасим светодиод
  }
int main()
{
  NVIC_SetPriority(TIM2_IRQn, 1); //Приоритет прерывания
  NVIC_EnableIRQ(TIM2_IRQn); //Разрешаем обработку прерывания от таймера 2
  
  RCC->AHBENR |= RCC_AHBENR_GPIOCEN; //Тактирование порта C
  GPIOC->MODER |= GPIO_MODER_MODER9_0;//Вывод PC8 порта C - выход 
    RCC -> APB2ENR |= RCC_APB2ENR_TIM15EN;

    TIM15->SMCR &= ~ TIM_SMCR_SMS;

    TIM15 -> CR1 = TIM_CR1_CEN;

    TIM15->PSC = 719;
    TIM15->ARR = 24999;

    TIM15->DIER |= TIM_DIER_UIE;


    NVIC_EnableIRQ (TIM15_IRQn);

}
// USER CODE BEGIN 15 

void TIM15_UP_IRQHandler(void) {

      
    GPIOC->ODR ^=  GPIO_ODR_9;
    TIM15->SR &= ~ TIM_SR_UIF;
}

*/

