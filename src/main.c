#include "stm32f051x8.h"
#define PC8 GPIO_ODR_8
#define PC9 GPIO_ODR_9
int DIV;




uint8_t i=0;


void TIM2_IRQHandler(void)
{
  TIM2->SR &= ~TIM_SR_UIF; //Clean UIF Flag

    GPIOC->ODR ^= PC9;   // Set PC8 bit
    
    if (DIV == 2){

      GPIOC->ODR ^= PC8;   // Reset PC9 bit
      DIV =0;
    }
    DIV++;
}



int main(void) 
{
  RCC->AHBENR |= RCC_AHBENR_GPIOCEN;  // Enable PORTC Periph clock
  RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;  // Enable TIM2 Periph clock
  // Clear PC8 and PC9 control register bits
  GPIOC->MODER &= ~(GPIO_MODER_MODER8 | GPIO_MODER_MODER9);
  // Configure PC.8 and PC.9 as Push Pull output at max 10Mhz
  GPIOC->MODER |= GPIO_MODER_MODER8_0 | GPIO_MODER_MODER9_0;
  TIM2->PSC = SystemCoreClock / 5000 - 1; // 1000 tick/sec
  TIM2->ARR = 1000;  // 1 Interrupt/sec (1000/100)
  TIM2->DIER |= TIM_DIER_UIE; // Enable tim2 interrupt
  TIM2->CR1 |= TIM_CR1_CEN;   // Start count
  NVIC_EnableIRQ(TIM2_IRQn);  // Enable IRQ
  //GPIOC -> BSRR |= GPIO_BSRR_BS_8;
}
 