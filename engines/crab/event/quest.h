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

/*
 * This code is based on the CRAB engine
 *
 * Copyright (c) Arvind Raja Yadav
 *
 * Licensed under MIT
 *
 */

#ifndef CRAB_QUEST_H
#define CRAB_QUEST_H

#include "crab/common_header.h"
#include "crab/loaders.h"

namespace Crab {

namespace pyrodactyl {
namespace event {
struct Quest {
	// The title of the quest
	std::string title;

	// The objective text, the last one being the current objective
	std::deque<std::string> text;

	// Keep track of which quests the player has read
	bool unread;

	// Does this quest have an associated destination marker
	bool marker;

	Quest() {
		unread = true;
		marker = false;
	}
	Quest(const std::string &Title, const std::string &Text, const bool &Unread, const bool &Marker);

	void LoadState(rapidxml::xml_node<char> *node);
	void SaveState(rapidxml::xml_document<char> &doc, rapidxml::xml_node<char> *root);
};
} // End of namespace event
} // End of namespace pyrodactyl

} // End of namespace Crab

#endif // CRAB_QUEST_H
