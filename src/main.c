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

  for (;;)
    ;
}

// Handler in case a memory allocation fails
void vApplicationMallocFailedHook(void)
{
  for (;;)
    ;
}

void vConfigureTimerForRunTimeStats(void)
{
  // Enable clock for Timer 2
  rcc_periph_clock_enable(RCC_TIM2);

  // Rese the clock to 0
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

uint32_t ulGetRunTimeCounterValue(void)
{
  return timer_get_counter(TIM2);
}

static uint32_t counter = 0;

static void __attribute__((optimize("O0"))) task_1(void const *args)
{
  (void)args;
  TickType_t last_execution_time = xTaskGetTickCount();
  uint32_t time_to_wait = pdMS_TO_TICKS(3000);

  while (true)
  {
    vTaskDelayUntil(&last_execution_time, time_to_wait);
    gpio_toggle(GPIOC, GPIO13);
  }
}

static void __attribute__((optimize("O0"))) task_2(void const *args)
{
  (void)args;

  while (true)
  {
    for (int i = 0; i < 1000000; i++)
    {
      __asm__("nop");
    }

    counter++;
  }
}

static void __attribute__((optimize("O0"))) task_3(void const *args)
{
  (void)args;

  while (true)
  {
    for (int i = 0; i < 500000; i++)
    {
      __asm__("nop");
    }

    counter++;
  }
}

int main(void)
{
  rcc_clock_setup_in_hse_8mhz_out_72mhz();

  setup_gpio();

  xTaskCreate(task_1, "Toggle LED", configMINIMAL_STACK_SIZE, NULL, mainHIGH_PRIORITY, NULL);
  xTaskCreate(task_2, "Count", configMINIMAL_STACK_SIZE, NULL, mainLOW_PRIORITY, NULL);
  xTaskCreate(task_3, "Count2", configMINIMAL_STACK_SIZE, NULL, mainLOW_PRIORITY, NULL);

  vTaskStartScheduler();

  while (true)
  {
  }

  return 0;
}
