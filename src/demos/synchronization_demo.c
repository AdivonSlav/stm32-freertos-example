#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "libopencm3/stm32/gpio.h"

#include "synchronization_demo.h"

SemaphoreHandle_t xSemaphore;
SemaphoreHandle_t xMutex;

void vSynchDemoInitSemaphore(void)
{
  xSemaphore = xSemaphoreCreateBinary();
  xSemaphoreGive(xSemaphore);
}

void vSyncDemoInitMutex(void)
{
  xMutex = xSemaphoreCreateMutex();
  xSemaphoreGive(xMutex);
}

void __attribute__((optimize("O0"))) vSyncDemoSemaphoreConsumer(void const *args)
{
  (void)args;

  while (true)
  {
    if (xSemaphoreTake(xSemaphore, pdMS_TO_TICKS(200)))
    {
      gpio_set(GPIOC, GPIO13);

      for (int i = 0; i < 1000000; i++)
      {
        __asm__("nop");
      }
    }
  }
}

void __attribute__((optimize("O0"))) vSyncDemoSemaphoreSignaller(void const *args)
{
  (void)args;

  static uint8_t ucTickCount = 0;
  static const uint8_t ucTicksToWait = 100;

  while (true)
  {
    for (int i = 0; i < 1000000; i++)
    {
      __asm__("nop");
    }

    ucTickCount++;

    if (ucTickCount >= ucTicksToWait)
    {
      gpio_clear(GPIOC, GPIO13);
      xSemaphoreGive(xSemaphore);
      ucTickCount = 0;
    }
  }
}

void __attribute__((optimize("O0"))) vSyncDemoMutexTask1(void const *args)
{
  (void)args;

  while (1)
  {
    if (xSemaphoreTake(xMutex, pdMS_TO_TICKS(100)) == pdTRUE)
    {
      gpio_clear(GPIOC, GPIO13);

      for (int i = 0; i < 1000000; i++)
      {
        __asm__("nop");
      }

      xSemaphoreGive(xMutex);
      vTaskDelay(pdMS_TO_TICKS(2000));
    }
  }
}

void __attribute__((optimize("O0"))) vSyncDemoMutexTask2(void const *args)
{
  (void)args;

  while (1)
  {
    if (xSemaphoreTake(xMutex, pdMS_TO_TICKS(100)) == pdTRUE)
    {
      gpio_set(GPIOC, GPIO13);

      for (int i = 0; i < 1000000; i++)
      {
        __asm__("nop");
      }

      vTaskDelay(pdMS_TO_TICKS(4000));
      xSemaphoreGive(xMutex);
    }
  }
}