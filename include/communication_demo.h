#pragma once

#include "queue.h"

void vCommunicationDemoInitQueue(void);
void __attribute__((optimize("O0"))) vCommunicationDemoTask1(void const *args);
void __attribute__((optimize("O0"))) vCommunicationDemoTask2(void const *args);