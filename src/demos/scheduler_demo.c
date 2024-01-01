#include "libopencm3/stm32/gpio.h"

#include "FreeRTOS.h"
#include "task.h"

#include "scheduler_demo.h"

void __attribute__((optimize("O0"))) vSchedulerDemoTask1(void const *args)
{
  (void)args;
  TickType_t ulLastExecutionTime = xTaskGetTickCount();
  uint32_t ulTimeToWait = pdMS_TO_TICKS(3000);

  while (true)
  {
    vTaskDelayUntil(&ulLastExecutionTime, ulTimeToWait);
    gpio_toggle(GPIOC, GPIO13);
  }
}

void __attribute__((optimize("O0"))) vSchedulerDemoTask2(void const *args)
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

void __attribute__((optimize("O0"))) vSchedulerDemoTask3(void const *args)
{
  (void)args;

  while (true)
  {
    for (int i = 0; i < 500000; i++)
    {
      __asm__("nop");
    }
  }
}