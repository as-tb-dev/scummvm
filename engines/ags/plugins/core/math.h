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

#ifndef AGS_PLUGINS_CORE_MATH_H
#define AGS_PLUGINS_CORE_MATH_H

#include "ags/plugins/ags_plugin.h"

namespace AGS3 {
namespace Plugins {
namespace Core {

class Math : public ScriptContainer {
	SCRIPT_HASH(Math)
public:
	virtual ~Math() {}
	void AGS_EngineStartup(IAGSEngine *engine) override;

	void ArcCos(ScriptMethodParams &params);
	void ArcSin(ScriptMethodParams &params);
	void ArcTan(ScriptMethodParams &params);
	void ArcTan2(ScriptMethodParams &params);
	void Cos(ScriptMethodParams &params);
	void Cosh(ScriptMethodParams &params);
	void DegreesToRadians(ScriptMethodParams &params);
	void Exp(ScriptMethodParams &params);
	void Log(ScriptMethodParams &params);
	void Log10(ScriptMethodParams &params);
	void RadiansToDegrees(ScriptMethodParams &params);
	void RaiseToPower(ScriptMethodParams &params);
	void Sin(ScriptMethodParams &params);
	void Sinh(ScriptMethodParams &params);
	void Sqrt(ScriptMethodParams &params);
	void Tan(ScriptMethodParams &params);
	void Tanh(ScriptMethodParams &params);
	void GetPi(ScriptMethodParams &params);
};

} // namespace Core
} // namespace Plugins
} // namespace AGS3

#endif
