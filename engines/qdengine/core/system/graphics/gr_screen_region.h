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


#ifndef QDENGINE_CORE_SYSTEM_GRAPHICS_GR_SCREEN_REGION_H
#define QDENGINE_CORE_SYSTEM_GRAPHICS_GR_SCREEN_REGION_H

namespace QDEngine {

//! Прямоугольная область на экране.
class grScreenRegion {
public:
	grScreenRegion() : x_(0), y_(0), size_x_(0), size_y_(0) {}
	grScreenRegion(int x, int y, int sx, int sy) : x_(x), y_(y), size_x_(sx), size_y_(sy) {}

	bool operator == (const grScreenRegion &reg) const {
		if (x_ == reg.x_ && y_ == reg.y_ && size_x_ == reg.size_x_ && size_y_ == reg.size_y_)
			return true;

		if (is_empty() && reg.is_empty())
			return true;

		return false;
	}

	bool operator != (const grScreenRegion &reg) const {
		if (is_empty() && reg.is_empty())
			return false;

		if (x_ != reg.x_ || y_ != reg.y_ || size_x_ != reg.size_x_ || size_y_ != reg.size_y_)
			return true;

		return false;
	}

	grScreenRegion &operator += (const grScreenRegion &reg) {
		if (reg.is_empty()) return *this;

		if (is_empty()) {
			*this = reg;
			return *this;
		}

		int x0 = (min_x() < reg.min_x()) ? min_x() : reg.min_x();
		int x1 = (max_x() > reg.max_x()) ? max_x() : reg.max_x();

		int y0 = (min_y() < reg.min_y()) ? min_y() : reg.min_y();
		int y1 = (max_y() > reg.max_y()) ? max_y() : reg.max_y();

		x_ = (x0 + x1) / 2;
		y_ = (y0 + y1) / 2;

		size_x_ = x1 - x0;
		size_y_ = y1 - y0;

		return *this;
	}

	int x() const {
		return x_;
	}
	int y() const {
		return y_;
	}

	int size_x() const {
		return size_x_;
	}
	int size_y() const {
		return size_y_;
	}

	int min_x() const {
		return x_ - size_x_ / 2;
	}
	int max_x() const {
		return x_ + size_x_ / 2;
	}

	int min_y() const {
		return y_ - size_y_ / 2;
	}
	int max_y() const {
		return y_ + size_y_ / 2;
	}

	void move(int dx, int dy) {
		x_ += dx;
		y_ += dy;
	}

	bool is_empty() const {
		return (!size_x_ || !size_y_);
	}

	bool is_inside(int x, int y) const {
		if (x >= min_x() && x < max_x() && y >= min_y() && y < max_y()) return true;
		return false;
	}

	void clear() {
		size_x_ = 0;
	}

	static const grScreenRegion EMPTY;

private:

	//! координаты центра области
	int x_;
	int y_;

	int size_x_;
	int size_y_;
};

} // namespace QDEngine

#endif // QDENGINE_CORE_SYSTEM_GRAPHICS_GR_SCREEN_REGION_H
