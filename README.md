# FreeRTOS example project

This is an example project meant to showcase some real-time embedded programming concepts as part of a university assignment. The microcontroller used is a STM32F103C8T6.

The following libraries were used:

- [libopencm3](https://github.com/libopencm3/libopencm3), an open-source firmware library for ARM Cortex-M microcontrollers
- [FreeRTOS](https://www.freertos.org/index.html), a real-time operating system for microcontrollers

Furthermore, the toolchain used consisted of:

- [GNU ARM Embedded Toolchain](https://developer.arm.com/downloads/-/gnu-rm), for compilation
- [OpenOCD](https://openocd.org/), for debugging and microcontroller programming

## Building

Ensure that you have `make` installed and the GNU ARM embedded toolchain (`arm-none-eabi-gcc`) installed and in your system or user path.

First build libopencm3 by running
```bash
make -C libopencm3/
```

Then, run the following to build the actual project. This will generate a .bin and .elf file for flashing and symbols respectively.
```bash
make -C src/
```
