/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * Additional copyright for this file:
 * Copyright (C) 1995-1997 Presto Studios, Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef PEGASUS_ELEMENTS_H
#define PEGASUS_ELEMENTS_H

#include "common/rect.h"
#include "common/str.h"
#include "common/system.h"
#include "graphics/pict.h"
#include "graphics/surface.h"

#include "pegasus/pegasus.h"
#include "pegasus/timers.h"
#include "pegasus/util.h"

namespace Common {
	class MacResManager;
}

namespace Pegasus {

class DisplayElement : public IDObject {
friend class GraphicsManager;
public:
	DisplayElement(const tDisplayElementID);
	virtual ~DisplayElement();
	
	void setDisplayOrder(const tDisplayOrder);
	tDisplayOrder getDisplayOrder() const { return _elementOrder; }
	
	bool validToDraw(tDisplayOrder, tDisplayOrder);
	
	virtual void draw(const Common::Rect&) {}
	bool isDisplaying() { return _elementIsDisplaying; }
	virtual void startDisplaying();
	virtual void stopDisplaying();
	
	virtual void show();
	virtual void hide();
	bool isVisible() { return _elementIsVisible; }
	
	// triggerRedraw only triggers a draw if the element is displaying and visible.
	void triggerRedraw();
	void setTriggeredElement(DisplayElement *);
	
	virtual void setBounds(const tCoordType, const tCoordType, const tCoordType, const tCoordType);
	virtual void setBounds(const Common::Rect&);
	virtual void getBounds(Common::Rect&) const;
	virtual void sizeElement(const tCoordType, const tCoordType);
	virtual void moveElementTo(const tCoordType, const tCoordType);
	virtual void moveElement(const tCoordType, const tCoordType);
	virtual void getLocation(tCoordType&, tCoordType&) const;
	virtual void getCenter(tCoordType&, tCoordType&) const;
	virtual void centerElementAt(const tCoordType, const tCoordType);

protected:
	Common::Rect _bounds;
	bool _elementIsVisible;
	DisplayElement *_triggeredElement;

	// Used only by PegasusEngine
	bool _elementIsDisplaying;
	tDisplayOrder _elementOrder;
	DisplayElement *_nextElement;
};

// I'm using the proper "highlight" instead of the evil
// QuickDraw "hilite" :P (deal with it!)
class DropHighlight : public DisplayElement {
public:
	DropHighlight(const tDisplayElementID);
	virtual ~DropHighlight() {}

	void setHighlightColor(const uint32 &highlight) { _highlightColor = highlight; }
	void getHighlightColor(uint32 &highlight) const { highlight = _highlightColor; } 

	void setHighlightThickness(const uint16 thickness) { _thickness = thickness; }
	uint16 getHighlightThickness() const { return _thickness; }

	void setHighlightCornerDiameter(const uint16 diameter) { _cornerDiameter = diameter; }
	uint16 getHighlightCornerDiameter() const { return _cornerDiameter; }

	virtual void draw(const Common::Rect&);

protected:
	uint32 _highlightColor;
	uint16 _thickness;
	uint16 _cornerDiameter;
};

class Animation : public DisplayElement, public DynamicElement {
public:
	Animation(const tDisplayElementID id) : DisplayElement(id) {}
};

class IdlerAnimation : public Animation, public Idler {
public:
	IdlerAnimation(const tDisplayElementID);
	
	virtual void startDisplaying();
	virtual void stopDisplaying();
	
	TimeValue getLastTime() const { return _lastTime; }

protected:
	virtual void useIdleTime();
	virtual void timeChanged(const TimeValue);
	
	TimeValue _lastTime;
};

//	This class reads PICT resources and plays them like a movie.
//	Assumes there is a resource of type 'PFrm' describing the time values for each
//	PICT frame, as well as the total time in the movie.
//	Assumes that PICT frames begin at PICT 128

class FrameSequence : public IdlerAnimation {
public:
	FrameSequence(const tDisplayElementID);
	virtual ~FrameSequence();

	void useFileName(const Common::String &fileName);

	virtual void openFrameSequence();
	virtual void closeFrameSequence();
	bool isSequenceOpen() const;
	
	uint16 getNumFrames() const { return _numFrames; }
	virtual uint16 getFrameNum() const { return _currentFrameNum; }
	virtual void setFrameNum(const int16);

protected:		
	virtual void timeChanged(const TimeValue);
	virtual void newFrame(const uint16) {}

	Common::MacResManager *_resFork;
	TimeValue _duration;

	uint16 _numFrames;
	Common::Array<TimeValue> _frameTimes;

	uint16 _currentFrameNum;
};

class SpriteFrame;

class Sprite : public DisplayElement {
friend class SpriteFrame;
public:
	Sprite(const tDisplayElementID);
	virtual ~Sprite();

	virtual void addPICTResourceFrame(const tResIDType, const bool, const tCoordType, const tCoordType);
	virtual uint32 addFrame(SpriteFrame *, const tCoordType, const tCoordType);
	virtual void removeFrame(const uint32);
	virtual void discardFrames();
	
	// Setting the current frame.
	// If the index is negative, sets the current frame to NULL and hides the sprite.
	// If the index is larger than the number of frames in the sprite, the number
	// is treated modulo the number of frames.
	virtual void setCurrentFrameIndex(const int32);
	virtual uint32 getCurrentFrameIndex() const { return _currentFrameNum; }
	
	virtual SpriteFrame *getFrame(const int32);
	
	virtual void draw(const Common::Rect &);
	
	uint32 getNumFrames() const { return _numFrames; }

protected:
	struct SpriteFrameRec {
		SpriteFrame *frame;
		tCoordType frameLeft;
		tCoordType frameTop;
	};

	uint32 _numFrames;
	uint32 _currentFrameNum;
	SpriteFrameRec *_currentFrame;
	Common::Array<SpriteFrameRec> _frameArray;
};

class SpriteSequence : public FrameSequence {
public:
	SpriteSequence(const tDisplayElementID id, const tDisplayElementID spriteID);
	virtual ~SpriteSequence() {}

	void useTransparent(bool transparent) { _transparent = transparent; }

	virtual void openFrameSequence();
	virtual void closeFrameSequence();

	virtual void draw(const Common::Rect &);

	virtual void setBounds(const Common::Rect &);

protected:
	virtual void newFrame(const uint16);

	bool _transparent;
	Sprite _sprite;
};

} // End of namespace Pegasus

#endif
