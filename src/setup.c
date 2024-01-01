#include "FreeRTOS.h"

#include "libopencm3/stm32/rcc.h"
#include "libopencm3/stm32/gpio.h"
#include "libopencm3/stm32/timer.h"
#include "libopencm3/cm3/nvic.h"

#include "setup.h"

void vSetupSystemClock(void)
{
  rcc_clock_setup_in_hse_8mhz_out_72mhz();
}

void vSetupGpio(void)
{
  // Enable the system clock for GPIO channel C
  rcc_periph_clock_enable(RCC_GPIOC);

  // Set the pinmode for PC13 which is the onboard LED
  gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);

  // Turn off the LED
  gpio_set(GPIOC, GPIO13);
}

// void vInterruptDemoSetupClock(void)
// {
//   nvic_enable_irq(NVIC_TIM2_IRQ);
//   nvic_set_priority(NVIC_TIM2_IRQ, 1);
//   rcc_periph_clock_enable(RCC_TIM2);

//   rcc_periph_reset_pulse(RST_TIM2);

//   timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

//   // timer_set_prescaler(TIM2, rcc_ahb_frequency / 1000);
//   timer_set_prescaler(TIM2, 72000);

//   timer_enable_preload(TIM2);

//   timer_set_period(TIM2, 3000);

//   timer_enable_irq(TIM2, TIM_DIER_UIE);
//   timer_enable_counter(TIM2);
// }

/*
void vConfigureTimerForRunTimeStats(void)
{
  // Enable clock for Timer 2
  rcc_periph_clock_enable(RCC_TIM2);

  // Reset the clock to 0
  timer_set_counter(TIM2, 0);

  // Configure it to count up and etc.
  timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

  // Calculate and set a good prescaler value
  uint32_t prescaler_value = (configCPU_CLOCK_HZ / configTICK_RATE_HZ) - 1;
  timer_set_prescaler(TIM2, prescaler_value);

  // Generate an update event and enable the counter
  timer_generate_event(TIM2, TIM_EGR_UG);
  timer_enable_counter(TIM2);
}
*/