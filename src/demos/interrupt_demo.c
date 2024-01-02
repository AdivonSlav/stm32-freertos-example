#include "FreeRTOS.h"
#include "task.h"

#include "libopencm3/stm32/rcc.h"
#include "libopencm3/stm32/timer.h"
#include "libopencm3/stm32/gpio.h"
#include "libopencm3/cm3/nvic.h"

#include "interrupt_demo.h"

TaskHandle_t xTask1Handle;
TaskHandle_t xTask2Handle;

void vInterruptDemoInitClock(void)
{
  nvic_enable_irq(NVIC_TIM2_IRQ);
  nvic_set_priority(NVIC_TIM2_IRQ, configMAX_SYSCALL_INTERRUPT_PRIORITY);

  rcc_periph_clock_enable(RCC_TIM2);

  timer_set_counter(TIM2, 1);

  // 2 second interval
  // 72000000Hz / (0.5Hz * (65535 + 1))
  // Prescaler = 2195
  timer_set_prescaler(TIM2, 4390);
  timer_enable_preload(TIM2);
  timer_set_period(TIM2, 65535);

  timer_enable_irq(TIM2, TIM_DIER_UIE);
  timer_enable_counter(TIM2);
}

void __attribute__((optimize("O0"))) vInterruptDemoTask1(void const *args)
{
  (void)args;

  while (true)
  {
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    gpio_toggle(GPIOC, GPIO13);
  }
}

void __attribute__((optimize("O0"))) vInterruptDemoTask2(void const *args)
{
  (void)args;

  while (true)
  {
    for (int i = 0; i < 1000000; i++)
    {
      __asm__("nop");
    }
  }
}

void tim2_isr(void)
{
  BaseType_t xHigherPriorityTaskWoken;

  if (timer_get_flag(TIM2, TIM_SR_UIF))
  {
    timer_clear_flag(TIM2, TIM_SR_UIF);

    xHigherPriorityTaskWoken = pdFALSE;
    vTaskNotifyGiveFromISR(xTask1Handle, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
  }
}