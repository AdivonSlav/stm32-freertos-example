#include "FreeRTOS.h"
#include "task.h"

#include "setup.h"
#include "task_priorities.h"
#include "scheduler_demo.h"
#include "synchronization_demo.h"
#include "interrupt_demo.h"
#include "communication_demo.h"

#include <stdbool.h>

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

int main(void)
{
  vSetupSystemClock();
  vSetupGpio();

  // Task scheduler example //
  // xTaskCreate(vSchedulerDemoTask1, "Toggle LED", configMINIMAL_STACK_SIZE, NULL, mainHIGH_PRIORITY, NULL);
  // xTaskCreate(vSchedulerDemoTask2, "Count", configMINIMAL_STACK_SIZE, NULL, mainLOW_PRIORITY, NULL);
  // xTaskCreate(vSchedulerDemoTask3, "Count2", configMINIMAL_STACK_SIZE, NULL, mainLOW_PRIORITY, NULL);

  //////////////////////////////

  // Synchronization example //

  // Binary semaphore example
  // vSynchDemoInitSemaphore();
  // xTaskCreate(vSyncDemoSemaphoreConsumer, "Consume semaphore", configMINIMAL_STACK_SIZE, NULL, mainLOW_PRIORITY, NULL);
  // xTaskCreate(vSyncDemoSemaphoreSignaller, "Signal semaphore", configMINIMAL_STACK_SIZE, NULL, mainLOW_PRIORITY, NULL);

  // Mutex example
  // vSyncDemoInitMutex();
  // xTaskCreate(vSyncDemoMutexTask1, "Mutex task 1", configMINIMAL_STACK_SIZE, NULL, mainHIGH_PRIORITY, NULL);
  // xTaskCreate(vSyncDemoMutexTask2, "Mutex task 2", configMINIMAL_STACK_SIZE, NULL, mainLOW_PRIORITY, NULL);

  //////////////////////////////

  // Interrupt example //

  // vInterruptDemoInitClock();
  // xTaskCreate(vInterruptDemoTask1, "Task 1 (needs to be notified)", configMINIMAL_STACK_SIZE, NULL, mainHIGH_PRIORITY, &xTask1Handle);
  // xTaskCreate(vInterruptDemoTask2, "Task 2", configMINIMAL_STACK_SIZE, NULL, mainNORMAL_PRIORITY, &xTask2Handle);

  //////////////////////////////

  // Communication example

  // vCommunicationDemoInitQueue();

  // xTaskCreate(vCommunicationDemoTask1, "Queue sender", configMINIMAL_STACK_SIZE, NULL, mainNORMAL_PRIORITY, NULL);
  // xTaskCreate(vCommunicationDemoTask2, "Queue consumer", configMINIMAL_STACK_SIZE, NULL, mainLOW_PRIORITY, NULL);

  /////////////////////////////

  vTaskStartScheduler();

  while (true)
  {
  }

  return 0;
}
