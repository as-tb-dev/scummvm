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

#ifndef AGS_SHARED_GUI_GUIOBJECT_H
#define AGS_SHARED_GUI_GUIOBJECT_H

#include "ags/shared/core/types.h"
#include "ags/shared/gfx/bitmap.h"
#include "ags/shared/gui/guidefines.h"
#include "ags/shared/util/string.h"

namespace AGS3 {

#define GUIDIS_GREYOUT   1
#define GUIDIS_BLACKOUT  2
#define GUIDIS_UNCHANGED 4
#define GUIDIS_GUIOFF  0x80

namespace AGS {
namespace Shared {

enum LegacyGUIAlignment {
	kLegacyGUIAlign_Left = 0,
	kLegacyGUIAlign_Right = 1,
	kLegacyGUIAlign_Center = 2
};

class GUIObject {
public:
	GUIObject();
	virtual ~GUIObject() {}

	String          GetEventArgs(int event) const;
	int             GetEventCount() const;
	String          GetEventName(int event) const;
	bool            IsDeleted() const;
	// tells if control itself is enabled
	bool            IsEnabled() const;
	// overridable routine to determine whether the mouse is over the control
	virtual bool    IsOverControl(int x, int y, int leeway) const;
	bool            IsTranslated() const;
	bool            IsVisible() const;
	// implemented separately in engine and editor
	bool            IsClickable() const;

	// Operations
	virtual void    Draw(Bitmap *ds) {
	}
	void            SetClickable(bool on);
	void            SetEnabled(bool on);
	void            SetTranslated(bool on);
	void            SetVisible(bool on);

	// Events
	// Key pressed for control
	virtual void    OnKeyPress(int keycode) {
	}
	// Mouse button down - return 'True' to lock focus
	virtual bool    OnMouseDown() {
		return false;
	}
	// Mouse moves onto control
	virtual void    OnMouseEnter() {
	}
	// Mouse moves off control
	virtual void    OnMouseLeave() {
	}
	// Mouse moves over control - x,y relative to gui
	virtual void    OnMouseMove(int x, int y) {
	}
	// Mouse button up
	virtual void    OnMouseUp() {
	}
	// Control was resized
	virtual void    OnResized() {
	}

	// Serialization
	virtual void    ReadFromFile(Stream *in, GuiVersion gui_version);
	virtual void    WriteToFile(Stream *out) const;
	virtual void    ReadFromSavegame(Stream *in, GuiSvgVersion svg_ver);
	virtual void    WriteToSavegame(Stream *out) const;

	// TODO: these members are currently public; hide them later
public:
	int  Id;         // GUI object's identifier
	int  ParentId;   // id of parent GUI
	String   Name;       // script name

	int  X;
	int  Y;
	int  Width;
	int  Height;
	int  ZOrder;
	bool     IsActivated; // signals user interaction

	String   EventHandlers[MAX_GUIOBJ_EVENTS]; // script function names

protected:
	uint32 Flags;      // generic style and behavior flags

	// TODO: explicit event names & handlers for every event
	int  _scEventCount;                    // number of supported script events
	String   _scEventNames[MAX_GUIOBJ_EVENTS]; // script event names
	String   _scEventArgs[MAX_GUIOBJ_EVENTS];  // script handler params
};

// Converts legacy alignment type used in GUI Label/ListBox data (only left/right/center)
HorAlignment ConvertLegacyGUIAlignment(LegacyGUIAlignment align);

} // namespace Shared
} // namespace AGS

// Tells if all controls are disabled
extern int all_buttons_disabled;
// Tells if the given control is considered enabled, taking global flag into account
inline bool IsGUIEnabled(AGS::Shared::GUIObject *g) {
	return !all_buttons_disabled && g->IsEnabled();
}

} // namespace AGS3

#endif
