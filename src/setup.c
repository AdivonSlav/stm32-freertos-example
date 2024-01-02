#include "FreeRTOS.h"

#include "libopencm3/stm32/rcc.h"
#include "libopencm3/stm32/gpio.h"
#include "libopencm3/stm32/timer.h"
#include "libopencm3/cm3/dwt.h"

#include "setup.h"

// Sets up the system clock at 72MHz using the 8MHz HSE oscillator
void vSetupSystemClock(void)
{
  rcc_clock_setup_in_hse_8mhz_out_72mhz();
}

void vSetupGpio(void)
{
  // Enable the system clock for GPIO channel C
  rcc_periph_clock_enable(RCC_GPIOC);

  // Set the pinmode for PC13 which is the onboard LED
  gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO13);

  // Turn off the LED
  gpio_set(GPIOC, GPIO13);
}

// Configures the DWT CPU cycle counter for runtime stats purposes
void vConfigureTimerForRunTimeStats(void)
{
  bool bEnabledCycleCounter = dwt_enable_cycle_counter();
}

// Gets the current value of the CPU cycle counter for runtime stats purposes
uint32_t ulGetRunTimeCounterValue(void)
{
  return dwt_read_cycle_counter();
}
