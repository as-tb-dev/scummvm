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

/********************************************
   DISCLAIMER:

   This is a wrapper code to mimic the relevant std:: class
   Please use it ONLY when porting an existing code e.g. from the original sources

   For all new development please use classes from Common::
 *********************************************/

#ifndef COMMON_STD_TYPE_TRAITS_H
#define COMMON_STD_TYPE_TRAITS_H

#include "common/scummsys.h"

namespace Std {

// STRUCT TEMPLATE remove_extent
template <class _Ty>
struct remove_extent { // remove array extent
	using type = _Ty;
};

template <class _Ty, size_t _Ix>
struct remove_extent<_Ty[_Ix]> {
	using type = _Ty;
};

template <class _Ty>
struct remove_extent<_Ty[]> {
	using type = _Ty;
};

template <class _Ty>
using remove_extent_t = typename remove_extent<_Ty>::type;

} // namespace Std

#endif
