#include "FreeRTOS.h"
#include "task.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>

#include <stdio.h>

#include "task_priorities.h"
#include "setup.h"

// Handler in case our application overflows the stack
void vApplicationStackOverflowHook(
    TaskHandle_t xTask __attribute__((unused)),
    char *pcTaskName)
{
  (void)pcTaskName;

  for (;;)
    ;
}

// Handler in case a memory allocation fails
void vApplicationMallocFailedHook(void)
{
  for (;;)
    ;
}

// Returns the current value of TIM2 for runtime stats purposes
uint32_t ulGetRunTimeCounterValue(void)
{
  return timer_get_counter(TIM2);
}

static uint32_t ulCounter = 0;

static void __attribute__((optimize("O0"))) vTask1(void const *args)
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

static void __attribute__((optimize("O0"))) vTask2(void const *args)
{
  (void)args;

  while (true)
  {
    for (int i = 0; i < 1000000; i++)
    {
      __asm__("nop");
    }

    ulCounter++;
  }
}

static void __attribute__((optimize("O0"))) vTask3(void const *args)
{
  (void)args;

  while (true)
  {
    for (int i = 0; i < 500000; i++)
    {
      __asm__("nop");
    }

    ulCounter++;
  }
}

int main(void)
{
  rcc_clock_setup_in_hse_8mhz_out_72mhz();
  vSetupGpio();

  xTaskCreate(vTask1, "Toggle LED", configMINIMAL_STACK_SIZE, NULL, mainHIGH_PRIORITY, NULL);
  xTaskCreate(vTask2, "Count", configMINIMAL_STACK_SIZE, NULL, mainLOW_PRIORITY, NULL);
  xTaskCreate(vTask3, "Count2", configMINIMAL_STACK_SIZE, NULL, mainLOW_PRIORITY, NULL);

  vTaskStartScheduler();

  while (true)
  {
  }

  return 0;
}
