MODULE := engines/nancy

MODULE_OBJS = \
  action/actionmanager.o \
  action/actionrecord.o \
  action/arfactory.o \
  action/navigationrecords.o \
  action/soundrecords.o \
  action/miscrecords.o \
  action/conversation.o \
  action/overlay.o \
  action/secondarymovie.o \
  action/secondaryvideo.o \
  action/puzzle/bombpuzzle.o \
  action/puzzle/collisionpuzzle.o \
  action/puzzle/leverpuzzle.o \
  action/puzzle/orderingpuzzle.o \
  action/puzzle/overridelockpuzzle.o \
  action/puzzle/passwordpuzzle.o \
  action/puzzle/raycastpuzzle.o \
  action/puzzle/riddlepuzzle.o \
  action/puzzle/rippedletterpuzzle.o \
  action/puzzle/rotatinglockpuzzle.o \
  action/puzzle/safelockpuzzle.o \
  action/puzzle/setplayerclock.o \
  action/puzzle/sliderpuzzle.o \
  action/puzzle/soundequalizerpuzzle.o \
  action/puzzle/tangrampuzzle.o \
  action/puzzle/telephone.o \
  action/puzzle/towerpuzzle.o \
  action/puzzle/turningpuzzle.o \
  ui/fullscreenimage.o \
  ui/animatedbutton.o \
  ui/button.o \
  ui/clock.o \
  ui/inventorybox.o \
  ui/ornaments.o \
  ui/scrollbar.o \
  ui/textbox.o \
  ui/viewport.o \
  state/credits.o \
  state/logo.o \
  state/loadsave.o \
  state/help.o \
  state/mainmenu.o \
  state/map.o \
  state/savedialog.o \
  state/scene.o \
  state/setupmenu.o \
  misc/lightning.o \
  misc/specialeffect.o \
  commontypes.o \
  console.o \
  cursor.o \
  decompress.o \
  enginedata.o \
  font.o \
  graphics.o \
  iff.o \
  input.o \
  metaengine.o \
  nancy.o \
  puzzledata.o \
  renderobject.o \
  resource.o \
  sound.o \
  util.o \
  video.o

# This module can be built as a plugin
ifeq ($(ENABLE_NANCY), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk

# Detection objects
DETECT_OBJS += $(MODULE)/detection.o
