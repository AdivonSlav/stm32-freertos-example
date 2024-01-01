#include "FreeRTOS.h"
#include "task.h"

#include "libopencm3/stm32/rcc.h"
#include "libopencm3/stm32/gpio.h"
#include "libopencm3/stm32/timer.h"

#include "setup.h"
#include "task_priorities.h"
#include "scheduler_demo.h"
#include "synchronization_demo.h"

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

int main(void)
{
  rcc_clock_setup_in_hse_8mhz_out_72mhz();
  vSetupGpio();

  // Task scheduler demo

  // xTaskCreate(vSchedulerDemoTask1, "Toggle LED", configMINIMAL_STACK_SIZE, NULL, mainHIGH_PRIORITY, NULL);
  // xTaskCreate(vSchedulerDemoTask2, "Count", configMINIMAL_STACK_SIZE, NULL, mainLOW_PRIORITY, NULL);
  // xTaskCreate(vSchedulerDemoTask3, "Count2", configMINIMAL_STACK_SIZE, NULL, mainLOW_PRIORITY, NULL);

  // vTaskStartScheduler();

  //////////////////////////////

  vSynchDemoInitSemaphore();
  xTaskCreate(vSynchDemoTask1, "Toggle LED with semaphore wait", configMINIMAL_STACK_SIZE, NULL, mainHIGH_PRIORITY, NULL);
  xTaskCreate(vSynchDemoTask2, "Toggle LED", configMINIMAL_STACK_SIZE, NULL, mainLOW_PRIORITY, NULL);

  vTaskStartScheduler();

  while (true)
  {
  }

  return 0;
}
