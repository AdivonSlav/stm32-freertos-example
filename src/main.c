#include "FreeRTOS.h"
#include "task.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

// TaskHandle_t *task_1_handle;

// Handler in case our application overflows the stack
void vApplicationStackOverflowHook(
    TaskHandle_t xTask __attribute__((unused)),
    char *pcTaskName)
{

  for (;;)
    ;
}

// Handler in case a memory allocation fails
void vApplicationMallocFailedHook(void)
{
  for (;;)
    ;
}

static void task_1(void const *args)
{
  while (true)
  {
    for (int i = 0; i < 500000; i++)
    {
      __asm__("nop");
    }

    gpio_toggle(GPIOC, GPIO13);
  }
}

static void setup_gpio()
{
  // Enable the system clock for GPIO channel C
  rcc_periph_clock_enable(RCC_GPIOC);

  // Set the pinmode for PC13 which is the onboard LED
  gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);

  gpio_set(GPIOC, GPIO13);
}

int main(void)
{
  setup_gpio();

  xTaskCreate(task_1, "Toggle LED", configMINIMAL_STACK_SIZE + 500, 2, NULL, NULL);

  vTaskStartScheduler();

  while (true)
  {
  }

  return 0;
}
