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

#include "common/system.h"
#include "graphics/screen.h"
#include "mm/mm1/events.h"
#include "mm/mm1/mm1.h"

namespace MM {
namespace MM1 {

#define FRAME_RATE 20
#define FRAME_DELAY (1000 / FRAME_RATE)

void Events::runGame() {
	uint currTime, nextFrameTime = 0;
	_screen = new Graphics::Screen();

	Common::Event e;
	for (;;) {
		while (g_system->getEventManager()->pollEvent(e)) {
			if (e.type == Common::EVENT_QUIT)
				return;
			else
				processEvent(e);
		}

		g_system->delayMillis(10);
		if ((currTime = g_system->getMillis()) >= nextFrameTime) {
			nextFrameTime = currTime + FRAME_DELAY;
			tick();
			drawElements();
			_screen->update();
		}
	}

	delete _screen;
}

void Events::processEvent(Common::Event &ev) {
	switch (ev.type) {
	case Common::EVENT_KEYDOWN:
		msgKeypress(KeypressMessage(ev.kbd));
		break;
	default:
		break;
	}
}

void Events::replaceView(UIElement *ui) {
	if (!_views.empty()) {
		focusedView()->msgUnfocus(UnfocusMessage());
		_views.clear();
	}

	_views.push(ui);
	ui->msgFocus(FocusMessage());
}

void Events::replaceView(const Common::String &name) {
	replaceView(findView(name));
}

void Events::addView(UIElement *ui) {
	if (!_views.empty())
		focusedView()->msgUnfocus(UnfocusMessage());

	_views.push(ui);
	ui->msgFocus(FocusMessage());
}

void Events::addView(const Common::String &name) {
	addView(findView(name));
}

/*-------------------------------------------------------------------*/

UIElement::UIElement(const Common::String &name, UIElement *uiParent) :
		_name(name), _parent(uiParent) {
	if (_parent)
		_parent->_children.push_back(this);
}

void UIElement::redraw() {
	_needsRedraw = true;

	for (size_t i = 0; i < _children.size(); ++i)
		_children[i]->redraw();
}

void UIElement::drawElements() {
	if (_needsRedraw) {
		draw();
		_needsRedraw = false;

		for (size_t i = 0; i < _children.size(); ++i)
			_children[i]->drawElements();
	}
}

void UIElement::focus() {
	g_engine->replaceView(this);
}

bool UIElement::tick() {
	for (size_t i = 0; i < _children.size(); ++i) {
		if (_children[i]->tick())
			return true;
	}

	return false;
}

UIElement *UIElement::findView(const Common::String &name) {
	if (_name.equalsIgnoreCase(name))
		return this;

	UIElement *result;
	for (size_t i = 0; i < _children.size(); ++i) {
		if ((result = _children[i]->findView(name)) != nullptr)
			return result;
	}

	return nullptr;
}


} // namespace MM1
} // namespace MM
