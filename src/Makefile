PROJECT = stm32-freertos-example
BUILD_DIR = bin

FREERTOS_SRC = ../freertos
FREERTOS_HEADERS = ../freertos/include

PROJ_HEADERS = ../include

INCLUDES += -I$(FREERTOS_HEADERS)
INCLUDES += -I$(PROJ_HEADERS)

TGT_CFLAGS	+= -I$(FREERTOS_HEADERS) -I$(PROJ_HEADERS)
TGT_CXXFLAGS	+= -I$(FREERTOS_HEADERS) -I$(PROJ_HEADERS)

LDFLAGS += --specs=rdimon.specs
LDLIBS += -lrdimon

CFILES = main.c setup.c
CFILES +=$(FREERTOS_SRC)/port.c  $(FREERTOS_SRC)/tasks.c  $(FREERTOS_SRC)/list.c $(FREERTOS_SRC)/queue.c $(FREERTOS_SRC)/heap_4.c 

# Edit for a specific microcontroller
DEVICE=stm32f103c8

# You shouldn't have to edit anything below here.
VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
