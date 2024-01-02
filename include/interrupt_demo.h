#pragma once

extern TaskHandle_t xTask1Handle;
extern TaskHandle_t xTask2Handle;

void vInterruptDemoInitClock(void);
void __attribute__((optimize("O0"))) vInterruptDemoTask1(void const *args);
void __attribute__((optimize("O0"))) vInterruptDemoTask2(void const *args);