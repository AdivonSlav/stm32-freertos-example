#include "FreeRTOS.h"
#include "queue.h"

#include "libopencm3/stm32/gpio.h"

#include "communication_demo.h"

#include <stdbool.h>

QueueHandle_t xQueue;

void vCommunicationDemoInitQueue(void)
{
  xQueue = xQueueCreate(10, sizeof(uint16_t));
}

void __attribute__((optimize("O0"))) vCommunicationDemoTask1(void const *args)
{
  (void)args;

  while (true)
  {
    for (int i = 1; i < 65535; i++)
    {
      if (xQueue != NULL)
      {
        xQueueSendToBack(xQueue, (void *)&i, portMAX_DELAY);
        vTaskDelay(pdMS_TO_TICKS(2000));
      }
    }
  }
}

void __attribute__((optimize("O0"))) vCommunicationDemoTask2(void const *args)
{
  (void)args;

  while (true)
  {
    uint16_t usReceivedNumber;
    bool bIsPrime = true;

    if (xQueue != NULL)
    {
      if (xQueueReceive(xQueue, &usReceivedNumber, portMAX_DELAY))
      {
        if (usReceivedNumber <= 1)
        {
          bIsPrime = false;
        }
        else
        {
          for (int i = 2; i <= usReceivedNumber / 2; i++)
          {
            if (usReceivedNumber % i == 0)
            {
              bIsPrime = false;
            }
          }
        }

        if (bIsPrime)
        {
          gpio_clear(GPIOC, GPIO13);
        }
        else
        {
          gpio_set(GPIOC, GPIO13);
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
      }
    }
  }
}