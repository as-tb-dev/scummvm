/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or(at your option) any later version.
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

#ifndef AGS_PLUGINS_AGSCONTROLLER_AGSCONTROLLER_H
#define AGS_PLUGINS_AGSCONTROLLER_AGSCONTROLLER_H

#include "ags/plugins/plugin_base.h"

namespace AGS3 {
namespace Plugins {
namespace AGSController {

class AGSController : public PluginBase {
private:
IAGSEngine *_engine;

private:
const char *AGS_GetPluginName();
void AGS_EngineStartup(IAGSEngine *engine) override;
void AGS_EngineShutdown();
int64 AGS_EngineOnEvent(int event, NumberPtr data);

private:
void Controller_Update();

void ControllerCount(ScriptMethodParams &params);
void Controller_Open(ScriptMethodParams &params);
void Controller_Plugged(ScriptMethodParams &params);
void Controller_GetAxis(ScriptMethodParams &params);
void Controller_GetPOV(ScriptMethodParams &params);
void Controller_IsButtonDown(ScriptMethodParams &params);
void Controller_Close(ScriptMethodParams &params);
void Controller_GetName(ScriptMethodParams &params);
void Controller_Rumble(ScriptMethodParams &params);
void Controller_IsButtonDownOnce(ScriptMethodParams &params);
void Controller_PressAnyKey(ScriptMethodParams &params);
void Controller_BatteryStatus(ScriptMethodParams &params);
void ClickMouse(ScriptMethodParams &params);
public:
AGSController();
};

} // namespace AGSController
} // namespace Plugins
} // namespace AGS3

#endif
