/* ResidualVM - A 3D game interpreter
 *
 * ResidualVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the AUTHORS
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

#include "engines/stark/gfx/renderentry.h"
#include "engines/stark/gfx/driver.h"

#include "engines/stark/resources/item.h"

#include "engines/stark/visual/actor.h"
#include "engines/stark/visual/image.h"
#include "engines/stark/visual/prop.h"
#include "engines/stark/visual/smacker.h"
#include "engines/stark/visual/text.h"
#include "engines/stark/visual/visual.h"

namespace Stark {
namespace Gfx {

RenderEntry::RenderEntry(Resources::ItemVisual *owner, const Common::String &name) :
	_visual(nullptr),
	_name(name),
	_owner(owner),
	_direction3D(0.0),
	_sortKey(0.0),
	_clickable(true) {
}

void RenderEntry::render(const LightEntryArray &lights) {
	if (!_visual) {
		// warning("No visual for render entry '%s'", _name.c_str());
		return;
	}

	VisualImageXMG *imageXMG = _visual->get<VisualImageXMG>();
	if (imageXMG) {
		imageXMG->render(_position, true);
	}

	VisualActor *actor = _visual->get<VisualActor>();
	if (actor) {
		actor->render(_position3D, _direction3D, lights);
	}

	VisualProp *prop = _visual->get<VisualProp>();
	if (prop) {
		prop->render(_position3D, _direction3D);
	}

	VisualSmacker *smacker = _visual->get<VisualSmacker>();
	if (smacker) {
		smacker->render(_position);
	}

	VisualText *text = _visual->get<VisualText>();
	if (text) {
		text->render(_position);
	}
}

void RenderEntry::setVisual(Visual *visual) {
	_visual = visual;
}

void RenderEntry::setPosition(const Common::Point &position) {
	_position = position;
}

void RenderEntry::setPosition3D(const Math::Vector3d &position, float direction) {
	_position3D = position;
	_direction3D = direction;
}

void RenderEntry::setSortKey(float sortKey) {
	_sortKey = sortKey;
}

void RenderEntry::setClickable(bool clickable) {
	_clickable = clickable;
}

bool RenderEntry::compare(const RenderEntry *x, const RenderEntry *y) {
	if (x->_sortKey != y->_sortKey) {
		return x->_sortKey < y->_sortKey;
	} else if (x->_owner && y->_owner) {
		// The original used a stable sort. Common::sort is not.
		// This should ensure the items remain in the same order if they have the same sort key
		return x->_owner->getIndex() < y->_owner->getIndex();
	} else {
		return -1;
	}
}

bool RenderEntry::containsPoint(const Common::Point &position, Common::Point &relativePosition) const {
	if (!_visual || !_clickable) {
		return false;
	}

	VisualImageXMG *image = _visual->get<VisualImageXMG>();
	if (image) {
		Common::Rect imageRect = Common::Rect(image->getWidth(), image->getHeight());
		imageRect.translate(_position.x, _position.y);
		imageRect.translate(-image->getHotspot().x, -image->getHotspot().y);

		relativePosition.x = position.x - imageRect.left - image->getHotspot().x;
		relativePosition.y = position.y - imageRect.top - image->getHotspot().y;
		if (imageRect.contains(position) && image->isPointSolid(relativePosition)) {
			return true;
		}
	}

	VisualSmacker *smacker = _visual->get<VisualSmacker>();
	if (smacker) {
		Common::Point smackerPosition = smacker->getPosition();
		smackerPosition -= _position;

		Common::Rect smackerRect = Common::Rect(smacker->getWidth(), smacker->getHeight());
		smackerRect.translate(smackerPosition.x, smackerPosition.y);

		relativePosition.x = position.x - smackerRect.left;
		relativePosition.y = position.y - smackerRect.top;
		if (smackerRect.contains(position) && smacker->isPointSolid(relativePosition)) {
			return true;
		}
	}

	VisualText *text = _visual->get<VisualText>();
	if (text) {
		Common::Rect textRect = text->getRect();
		textRect.translate(_position.x, _position.y);

		relativePosition.x = position.x - textRect.left;
		relativePosition.y = position.y - textRect.top;
		if (textRect.contains(position)) {
			return true;
		}
	}

	return false;
}

bool RenderEntry::intersectRay(const Math::Ray &ray) const {
	if (!_visual || !_clickable) {
		return false;
	}

	VisualActor *actor = _visual->get<VisualActor>();
	if (actor) {
		return actor->intersectRay(ray, _position3D, _direction3D);
	}

	VisualProp *prop = _visual->get<VisualProp>();
	if (prop) {
		return prop->intersectRay(ray, _position3D, _direction3D);
	}

	return false;
}

VisualImageXMG *RenderEntry::getImage() const {
	return _visual->get<VisualImageXMG>();
}

} // End of namespace Gfx
} // End of namespace Stark
