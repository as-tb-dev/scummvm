/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef ACCESS_DETECTION_H
#define ACCESS_DETECTION_H

#include "engines/advancedDetector.h"

namespace Access {

enum {
	GType_Amazon = 1,
	GType_MartianMemorandum = 2,
	GType_Noctropolis = 3
};

struct AccessGameDescription {
	AD_GAME_DESCRIPTION_HELPERS(desc);

	ADGameDescription desc;

	int gameID;
	uint32 features;
};

} // End of namespace Access

#endif // ACCESS_DETECTION_H
