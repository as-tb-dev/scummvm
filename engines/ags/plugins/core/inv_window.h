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

#ifndef AGS_PLUGINS_CORE_INV_WINDOW_H
#define AGS_PLUGINS_CORE_INV_WINDOW_H

#include "ags/plugins/ags_plugin.h"

namespace AGS3 {
namespace Plugins {
namespace Core {

class InvWindow : public ScriptContainer {
	SCRIPT_HASH(InvWindow)
public:
	virtual ~InvWindow() {}
	void AGS_EngineStartup(IAGSEngine *engine) override;

	void ScrollDown(ScriptMethodParams &params);
	void ScrollUp(ScriptMethodParams &params);
	void GetCharacterToUse(ScriptMethodParams &params);
	void SetCharacterToUse(ScriptMethodParams &params);
	void GetItemAtIndex(ScriptMethodParams &params);
	void GetItemCount(ScriptMethodParams &params);
	void GetItemHeight(ScriptMethodParams &params);
	void SetItemHeight(ScriptMethodParams &params);
	void GetItemWidth(ScriptMethodParams &params);
	void SetItemWidth(ScriptMethodParams &params);
	void GetItemsPerRow(ScriptMethodParams &params);
	void GetRowCount(ScriptMethodParams &params);
	void GetTopItem(ScriptMethodParams &params);
	void SetTopItem(ScriptMethodParams &params);
};

} // namespace Core
} // namespace Plugins
} // namespace AGS3

#endif
