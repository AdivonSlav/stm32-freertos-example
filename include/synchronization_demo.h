#pragma once

void vSynchDemoInitSemaphore(void);
void vSyncDemoInitMutex(void);
void __attribute__((optimize("O0"))) vSyncDemoSemaphoreConsumer(void const *args);
void __attribute__((optimize("O0"))) vSyncDemoSemaphoreSignaller(void const *args);
void __attribute__((optimize("O0"))) vSyncDemoMutexTask1(void const *args);
void __attribute__((optimize("O0"))) vSyncDemoMutexTask2(void const *args);