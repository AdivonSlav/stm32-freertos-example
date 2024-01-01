#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "libopencm3/stm32/gpio.h"

#include "synchronization_demo.h"

SemaphoreHandle_t pSemaphoreHandle;

void vSynchDemoInitSemaphore(void)
{
  pSemaphoreHandle = xSemaphoreCreateBinary();
  xSemaphoreGive(pSemaphoreHandle);
}

void __attribute__((optimize("O0"))) vSynchDemoTask1(void const *args)
{
  (void)args;

  while (1)
  {
    if (xSemaphoreTake(pSemaphoreHandle, pdMS_TO_TICKS(100)) == pdTRUE)
    {
      gpio_clear(GPIOC, GPIO13);

      for (int i = 0; i < 400000; i++)
      {
        __asm__("nop");
      }

      xSemaphoreGive(pSemaphoreHandle);

      vTaskDelay(pdMS_TO_TICKS(2000));
    }
  }
}

void __attribute__((optimize("O0"))) vSynchDemoTask2(void const *args)
{
  (void)args;

  while (1)
  {
    if (xSemaphoreTake(pSemaphoreHandle, pdMS_TO_TICKS(100)) == pdTRUE)
    {
      gpio_set(GPIOC, GPIO13);
      vTaskDelay(pdMS_TO_TICKS(4000));
      xSemaphoreGive(pSemaphoreHandle);
    }
  }
}
