#include "libopencm3/stm32/rcc.h"
#include "libopencm3/stm32/timer.h"
#include "libopencm3/cm3/nvic.h"
#include "libopencm3/stm32/gpio.h"

#include "interrupt_demo.h"

void vInterruptDemoInitClock(void)
{
  nvic_enable_irq(NVIC_TIM2_IRQ);
  nvic_set_priority(NVIC_TIM2_IRQ, 1);

  rcc_periph_clock_enable(RCC_TIM2);

  timer_set_counter(TIM2, 1);

  // 2 second interval
  // 72000000Hz / (0.5Hz * (65535 + 1))
  // Prescaler = 2195
  timer_set_prescaler(TIM2, 2195);
  timer_enable_preload(TIM2);
  timer_set_period(TIM2, 65535);

  timer_enable_irq(TIM2, TIM_DIER_UIE);
  timer_enable_counter(TIM2);
}

void tim2_isr(void)
{
  if (timer_get_flag(TIM2, TIM_SR_UIF))
  {
    timer_clear_flag(TIM2, TIM_SR_UIF);
  }
}