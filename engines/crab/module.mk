MODULE := engines/crab

MODULE_OBJS = \
	crab.o \
	console.o \
	metaengine.o

# This module can be built as a plugin
ifeq ($(ENABLE_CRAB), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk

# Detection objects
DETECT_OBJS += $(MODULE)/detection.o
