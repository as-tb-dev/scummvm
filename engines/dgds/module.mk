MODULE := engines/dgds

MODULE_OBJS := \
	console.o \
	decompress.o \
	dialogue.o \
	dgds.o \
	font.o \
	image.o \
	metaengine.o \
	music.o \
	parser.o \
	resource.o \
	scripts.o \
	sound.o

# This module can be built as a plugin
ifeq ($(ENABLE_DGDS), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk

# Detection objects
DETECT_OBJS += $(MODULE)/detection.o
