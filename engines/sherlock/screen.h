/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
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

#ifndef SHERLOCK_SCREEN_H
#define SHERLOCK_SCREEN_H

#include "common/list.h"
#include "common/rect.h"
#include "graphics/surface.h"
#include "sherlock/graphics.h"
#include "sherlock/resources.h"

namespace Sherlock {

#define PALETTE_SIZE 768
#define PALETTE_COUNT 256
#define VGA_COLOR_TRANS(x) ((x) * 255 / 63)

enum {
	INFO_BLACK		= 1,
	INFO_FOREGROUND	= 11,
	INFO_BACKGROUND	= 1,
	BORDER_COLOR	= 237,
	INV_FOREGROUND	= 14,
	INV_BACKGROUND	= 1,
	COMMAND_HIGHLIGHTED = 10,
	COMMAND_FOREGROUND = 15,
	BUTTON_TOP = 233,
	BUTTON_MIDDLE	= 244,
	BUTTON_BOTTOM	= 248
};

class SherlockEngine;

class Screen : public Surface {
private:
	SherlockEngine *_vm;
	int _fontNumber;
	Common::List<Common::Rect> _dirtyRects;
	uint32 _transitionSeed;
	ImageFile *_font;
	int _fontHeight;

	void mergeDirtyRects();

	bool unionRectangle(Common::Rect &destRect, const Common::Rect &src1, const Common::Rect &src2);

	void writeString(const Common::String &str, const Common::Point &pt, int color);
protected:
	virtual void addDirtyRect(const Common::Rect &r);
public:
	Surface _backBuffer, _backBuffer2;
	bool _fadeStyle;
	byte _cMap[PALETTE_SIZE];
	byte _sMap[PALETTE_SIZE];
public:
	Screen(SherlockEngine *vm);
	~Screen();

	void setFont(int fontNumber);

	void update();

	void getPalette(byte palette[PALETTE_SIZE]);

	void setPalette(const byte palette[PALETTE_SIZE]);

	int equalizePalette(const byte palette[PALETTE_SIZE]);

	void fadeToBlack(int speed = 2);

	void fadeIn(const byte palette[PALETTE_SIZE], int speed = 2);

	void randomTransition();

	void verticalTransition();

	void print(const Common::Point &pt, int color, const char *format, ...);
	void gPrint(const Common::Point &pt, int color, const char *format, ...);

	void restoreBackground(const Common::Rect &r);

	void slamArea(int16 xp, int16 yp, int16 w, int16 h);
	void slamRect(const Common::Rect &r);

	void flushImage(ImageFrame *frame, const Common::Point &pt,
		int16 *xp, int16 *yp, int16 *w, int16 *h);

	int stringWidth(const Common::String &str);

	int charWidth(char c);

	void bar(const Common::Rect &r, int color);
};

} // End of namespace Sherlock

#endif
