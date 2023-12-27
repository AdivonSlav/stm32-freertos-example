#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#include "setup.h"

void setup_gpio(void)
{
  // Enable the system clock for GPIO channel C
  rcc_periph_clock_enable(RCC_GPIOC);

  // Set the pinmode for PC13 which is the onboard LED
  gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);

  // Turn off the LED
  gpio_set(GPIOC, GPIO13);
}