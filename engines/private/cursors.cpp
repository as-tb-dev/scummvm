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
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "graphics/cursorman.h"

#include "private/cursors.h"
#include "private.h"

namespace Private {

const byte MOUSECURSOR_SCI[] = {
    1,1,0,0,0,0,0,0,0,0,0,
    1,2,1,0,0,0,0,0,0,0,0,
    1,2,2,1,0,0,0,0,0,0,0,
    1,2,2,2,1,0,0,0,0,0,0,
    1,2,2,2,2,1,0,0,0,0,0,
    1,2,2,2,2,2,1,0,0,0,0,
    1,2,2,2,2,2,2,1,0,0,0,
    1,2,2,2,2,2,2,2,1,0,0,
    1,2,2,2,2,2,2,2,2,1,0,
    1,2,2,2,2,2,2,2,2,2,1,
    1,2,2,2,2,2,1,0,0,0,0,
    1,2,1,0,1,2,2,1,0,0,0,
    1,1,0,0,1,2,2,1,0,0,0,
    0,0,0,0,0,1,2,2,1,0,0,
    0,0,0,0,0,1,2,2,1,0,0,
    0,0,0,0,0,0,1,2,2,1,0
};

extern const byte MOUSECURSOR_kExit[] = {
    0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,3,3,3,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,1,3,3,3,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,1,3,3,3,3,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,1,1,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,1,1,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,1,1,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,1,1,2,2,2,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,1,1,2,2,2,1,1,2,2,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,1,1,2,2,2,1,2,2,2,1,1,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,1,1,2,2,2,1,2,2,2,1,2,2,2,1,1,1,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,1,1,1,2,2,2,1,2,2,2,1,2,2,2,1,2,2,1,0,0,0,0,0,0,0,0,0,
    0,0,0,0,1,1,0,1,2,2,2,2,2,2,2,2,2,2,2,1,2,2,1,0,0,0,0,0,0,0,0,0,
    0,0,0,1,1,0,0,1,2,2,2,2,2,2,2,2,2,2,2,1,2,2,1,0,0,0,0,0,0,0,0,0,
    0,0,0,1,1,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,
    0,0,0,1,1,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,
    0,0,0,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,
    0,0,0,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,
    0,0,0,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,0,0,0,0,0,0,0,0,0,
    0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,1,1,1,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,1,1,1,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,1,1,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,1,1,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,1,1,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

const byte MOUSECURSOR_kZoomIn[] = {
    0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,1,1,1,2,2,2,2,2,2,2,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,1,1,2,2,2,2,1,1,1,1,1,2,2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,1,2,2,2,2,2,2,2,2,2,1,2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,1,2,2,2,2,2,2,2,2,2,2,2,1,2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,1,2,2,2,2,2,2,3,3,2,2,2,2,1,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,1,1,2,2,2,2,2,3,3,3,2,2,2,2,1,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,1,2,2,2,2,3,3,3,3,3,3,2,2,1,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,1,1,2,2,2,2,2,3,3,3,3,2,2,2,1,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,1,1,2,2,2,2,2,2,3,3,2,2,2,2,2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,1,1,1,2,2,2,2,2,2,2,2,1,1,1,2,1,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,2,2,1,1,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,0,1,1,2,2,1,1,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,1,1,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,1,1,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,1,1,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,1,1,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,1,1,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,1,1,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,1,1,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,1,1,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,2,1,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,2,1,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

const byte MOUSECURSOR_kTurnRight[] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,2,2,2,1,1,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,2,2,2,2,1,1,0,0,0,0,0,0,0,0,0,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,1,1,0,0,0,0,0,0,0,0,
    1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,0,0,0,0,0,0,0,
    1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,0,0,0,0,0,0,
    1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,0,0,0,0,0,
    1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,0,0,0,0,
    1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,0,0,0,
    1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,0,0,0,
    1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,0,0,0,0,
    1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,0,0,0,0,0,
    1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,0,0,0,0,0,0,
    1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,0,0,0,0,0,0,0,
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,1,1,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,2,2,2,2,1,1,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,2,2,2,1,1,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,2,2,1,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

const byte MOUSECURSOR_kTurnLeft[] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,1,1,2,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,1,1,2,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,1,1,2,2,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,1,1,2,2,2,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,1,1,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
    0,0,0,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,
    0,0,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,
    0,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,
    1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,
    1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,
    1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,
    1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,
    0,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,
    0,0,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,
    0,0,0,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,
    0,0,0,0,1,1,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,
    0,0,0,0,0,1,1,2,2,2,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,1,1,2,2,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,1,1,2,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,1,1,2,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

const byte MOUSECURSOR_kInventory[] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,1,3,3,3,3,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,1,1,1,3,3,3,3,3,1,2,2,1,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,1,1,2,2,3,3,3,3,3,3,2,2,1,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,1,1,2,2,2,1,2,2,2,1,2,2,2,1,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,1,1,2,2,2,1,2,2,2,1,2,2,2,1,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,1,2,2,2,1,2,2,2,1,2,2,2,1,1,1,1,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,1,1,2,2,2,1,2,2,2,1,2,2,2,1,1,2,2,1,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,1,1,2,2,2,1,2,2,2,1,2,2,2,1,2,2,2,1,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,1,2,2,2,1,2,2,2,1,2,2,2,1,2,2,2,1,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,1,1,2,2,2,1,2,2,2,1,2,2,2,1,2,2,2,1,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,1,1,2,2,2,1,2,2,2,1,2,2,2,1,2,2,2,1,0,0,0,0,0,0,
    0,1,1,1,1,1,0,0,0,1,2,2,2,1,2,2,2,1,2,2,2,1,2,2,2,1,0,0,0,0,0,0,
    1,1,2,2,2,1,1,0,1,1,2,2,2,1,2,2,2,1,2,2,2,1,2,2,2,1,0,0,0,0,0,0,
    1,1,2,2,2,2,2,1,1,1,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,1,0,0,0,0,0,0,
    0,1,1,1,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,
    0,0,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,
    0,0,0,0,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,
    0,0,0,0,0,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,
    0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,
    0,0,0,0,0,0,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,
    0,0,0,0,0,0,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,1,1,1,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,1,1,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,1,1,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,1,1,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,1,1,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
};

const byte MOUSECURSOR_kZoomOut[] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,1,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0,0,0,
    1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,0,0,0,0,
    1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,
    1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,0,0,0,0,
    1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,0,0,0,0,
    0,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,0,0,0,0,
    0,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,0,0,0,0,0,
    0,0,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,0,0,0,0,0,0,
    0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,
    0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,
    0,0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,1,1,1,1,2,2,2,2,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,1,1,3,3,3,3,3,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,3,3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

const byte MOUSECURSOR_kPhone[] {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,
    0,0,0,0,1,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,0,0,0,0,
    0,0,0,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,
    0,0,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,
    0,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,
    1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,
    0,1,2,2,2,2,2,2,2,2,1,2,2,1,1,1,1,1,1,1,2,2,1,2,2,2,2,2,2,2,2,1,
    1,1,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,1,
    1,1,1,1,1,1,1,2,1,1,1,2,2,2,2,2,2,2,2,2,2,2,1,1,1,2,1,1,1,1,1,1,
    0,1,2,2,2,2,2,2,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,2,2,2,2,2,2,1,
    1,1,1,1,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,2,2,2,2,2,1,1,1,1,1,1,1,1,
    0,1,1,1,1,1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,2,2,2,2,1,1,1,1,1,1,1,0,
    0,0,0,0,0,0,1,1,2,2,2,2,1,1,1,1,1,1,1,1,1,2,2,2,2,1,0,0,0,0,0,0,
    0,0,0,0,0,0,1,1,2,2,2,2,1,1,1,1,1,1,1,1,1,2,2,2,2,1,0,0,0,0,0,0,
    0,0,0,0,0,1,1,2,2,2,2,2,1,1,1,1,1,1,1,1,1,2,2,2,2,2,1,0,0,0,0,0,
    0,0,0,0,0,0,1,2,2,2,2,2,1,1,1,1,1,1,1,1,1,2,2,2,2,2,1,0,0,0,0,0,
    0,0,0,0,0,1,1,2,2,2,2,2,1,1,1,1,1,1,1,1,1,2,2,2,2,2,1,0,0,0,0,0,
    0,0,0,0,1,1,2,2,2,2,2,2,2,1,1,1,1,1,1,1,2,2,2,2,2,2,2,1,0,0,0,0,
    0,0,0,0,1,1,2,2,2,2,2,2,2,2,1,1,1,1,1,2,2,2,2,2,2,2,2,1,0,0,0,0,
    0,0,0,0,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,
    0,0,0,0,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,
    0,0,0,0,1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,0,0,0,0,0,
    0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

extern const byte cursorPalette[] = {
    0, 0, 0,           // Black / Transparent
    0x01, 0x01, 0x01,  // Gray
    0xff, 0xff, 0xff,  // White
    0xff, 0x00, 0x00   // Red
};

static struct CursorDataTable {
    const char *name;
    const byte *cursor;
} cursorDataTable[] = {
    { "kExit",         MOUSECURSOR_kExit},
    { "kInventory",    MOUSECURSOR_kInventory},
    { "kTurnLeft",     MOUSECURSOR_kTurnLeft},
    { "kTurnRight",    MOUSECURSOR_kTurnRight},
    { "kZoomIn",       MOUSECURSOR_kZoomIn},
    { "kZoomOut",      MOUSECURSOR_kZoomOut},
    { "kPhone",        MOUSECURSOR_kPhone},
    { "default",       MOUSECURSOR_SCI},
    { 0, 0}
};

static struct CursorPointTable {
    const char *name;
    const Common::Point *point;
} cursorPointTable[] = {
    { "kExit",         new Common::Point(9, 0)},
    { "kInventory",    new Common::Point(15, 3)},
    { "kTurnLeft",     new Common::Point(29, 16)},
    { "kTurnRight",    new Common::Point(1, 15)},
    { "kZoomIn",       new Common::Point(10, 8)},
    { "kZoomOut",      new Common::Point(13, 31)},
    { "kPhone",        new Common::Point(17, 19)},
    { "default",       new Common::Point(0, 0)},
    { 0, 0}
};

CursorDataMap _cursorData;
CursorPointMap _cursorPoints;

void PrivateEngine::initCursors() {
    for (Private::CursorDataTable *cur = Private::cursorDataTable; cur->name; cur++) {
        Common::String *name = new Common::String(cur->name);
        _cursorData.setVal(*name, cur->cursor);
    }

    for (Private::CursorPointTable *cur = Private::cursorPointTable; cur->name; cur++) {
        Common::String *name = new Common::String(cur->name);
        Common::Point *point = new Common::Point(*cur->point);
        _cursorPoints.setVal(*name, point);
    }
    CursorMan.replaceCursorPalette(cursorPalette, 0, 3);

}

void PrivateEngine::changeCursor(Common::String cursor) {
    assert(_cursorData.contains(cursor));
    Common::Point p = *_cursorPoints.getVal(cursor);
    Common::Point s;
    if (strcmp(cursor.c_str(), "default") == 0)
        s = Common::Point(11, 16);
    else
        s = Common::Point(32, 32);

    CursorMan.replaceCursor(_cursorData.getVal(cursor), s.x, s.y, p.x, p.y, 0, false);
    CursorMan.showMouse(true);
}

}