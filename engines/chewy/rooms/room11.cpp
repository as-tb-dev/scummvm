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

#include "chewy/defines.h"
#include "chewy/events.h"
#include "chewy/globals.h"
#include "chewy/ani_dat.h"
#include "chewy/room.h"
#include "chewy/rooms/room11.h"

namespace Chewy {
namespace Rooms {

AniBlock ABLOCK17[2] = {
	{ 8, 1, ANI_VOR, ANI_WAIT, 0 },
	{ 9, 255, ANI_VOR, ANI_GO, 0 },
};

AniBlock ABLOCK18[2] = {
	{ 7, 1, ANI_VOR, ANI_WAIT, 0 },
	{ 7, 1, ANI_RUECK, ANI_WAIT, 0 },
};


void Room11::entry() {
	_G(zoom_horizont) = 80;
	_G(flags).ZoomMov = true;
	_G(zoom_mov_fak) = 2;

	if (_G(spieler).R12ChewyBork) {
		if (!_G(spieler).R11DoorRightB) {
			_G(obj)->calc_rsi_flip_flop(SIB_TKNOPF2_R11);
			_G(spieler).R11DoorRightB = exit_flip_flop(5, 22, -1, 98, -1, -1,
				AUSGANG_OBEN, -1, (int16)_G(spieler).R11DoorRightB);
			_G(obj)->calc_all_static_detail();
		}

		_G(obj)->hide_sib(SIB_TKNOPF1_R11);
		_G(obj)->hide_sib(SIB_SCHLITZ_R11);
		_G(obj)->hide_sib(SIB_TKNOPF2_R11);
		_G(obj)->hide_sib(SIB_TKNOPF3_R11);
		_G(spieler).room_e_obj[20].Attribut = 255;
		_G(spieler).room_e_obj[21].Attribut = 255;
		_G(atds)->del_steuer_bit(121, ATS_AKTIV_BIT, ATS_DATEI);

		if (!_G(flags).LoadGame) {
			start_ani_block(2, ABLOCK17);
			auto_move(8, P_CHEWY);
			start_aad_wait(31, -1);
			_G(det)->stop_detail(9);
		}
		_G(det)->show_static_spr(8);
		if (!_G(flags).LoadGame)
			auto_move(6, P_CHEWY);
		_G(timer_nr)[0] = _G(room)->set_timer(255, 10);
	}
}

bool Room11::timer(int16 t_nr, int16 ani_nr) {
	if (t_nr == _G(timer_nr)[0])
		bork_zwinkert();

	return false;
}

void Room11::gedAction(int index) {
	switch (index) {
	case 0:
		chewy_bo_use();
		break;

	default:
		break;
	}
}

void Room11::bork_zwinkert() {
	if (!_G(flags).AutoAniPlay) {
		_G(flags).AutoAniPlay = true;
		_G(det)->hide_static_spr(8);
		start_ani_block(2, ABLOCK18);
		_G(uhr)->reset_timer(_G(timer_nr)[0], 0);
		_G(det)->show_static_spr(8);
		_G(flags).AutoAniPlay = false;
	}
}

void Room11::talk_debug() {
	if (_G(spieler).R12ChewyBork) {
		_G(flags).AutoAniPlay = true;
		auto_move(8, P_CHEWY);
		start_ads_wait(5);
		_G(menu_item) = CUR_WALK;
		cursor_wahl(CUR_WALK);

		_G(flags).AutoAniPlay = false;
	}
}

void Room11::chewy_bo_use() {
	if (_G(spieler).R12ChewyBork) {
		hide_cur();
		_G(flags).AutoAniPlay = true;

		stop_person(P_CHEWY);
		_G(det)->hide_static_spr(8);
		start_ani_block(2, ABLOCK17);
		start_aad_wait(32, -1);
		_G(det)->stop_detail(9);
		_G(det)->show_static_spr(8);
		auto_move(6, P_CHEWY);

		_G(flags).AutoAniPlay = false;
		show_cur();
	}
}

int16 Room11::scanner() {
	int16 actionFl = false;

	if (!_G(spieler).R12ChewyBork) {
		auto_move(7, P_CHEWY);

		if (!_G(spieler).R11CardOk) {
			actionFl = true;
			start_aad_wait(13, -1);
		} else if (is_cur_inventar(BORK_INV)) {
			hide_cur();
			set_up_screen(DO_SETUP);
			actionFl = true;

			start_aad(105, 0);
			flic_cut(FCUT_010);
			register_cutscene(4);
			_G(spieler).R11TerminalOk = true;
			cur_2_inventory();
			_G(menu_item) = CUR_TALK;
			cursor_wahl(_G(menu_item));
			start_aad_wait(12, -1);
			show_cur();
			load_ads_dia(3);
		} else if (!_G(spieler).inv_cur) {
			if (!_G(spieler).R11TerminalOk) {
				actionFl = true;
				flic_cut(FCUT_009);
				start_aad_wait(20, -1);
			} else {
				actionFl = true;
				start_aad_wait(12, -1);
				_G(menu_item) = CUR_TALK;
				cursor_wahl(_G(menu_item));
				load_ads_dia(3);
			}
		}
	}

	return actionFl;
}

void Room11::get_card() {
	if (_G(spieler).R11CardOk) {
		cur_2_inventory();
		_G(spieler).R11CardOk = false;
		_G(obj)->add_inventar(_G(spieler).R11IdCardNr, &_G(room_blk));

		_G(spieler).AkInvent = _G(spieler).R11IdCardNr;
		cursor_wahl(CUR_AK_INVENT);
		cursor_wahl(CUR_AK_INVENT);
		_G(det)->stop_detail(0);
		_G(atds)->set_ats_str(83, TXT_MARK_LOOK, 0, ATS_DATEI);
		_G(atds)->set_ats_str(84, TXT_MARK_LOOK, 0, ATS_DATEI);
	}
}

void Room11::put_card() {
	if (is_cur_inventar(RED_CARD_INV) || is_cur_inventar(YEL_CARD_INV)) {
		_G(spieler).R11IdCardNr = _G(spieler).AkInvent;
		del_inventar(_G(spieler).R11IdCardNr);
		_G(det)->start_detail(0, 255, ANI_VOR);
		_G(atds)->set_ats_str(83, TXT_MARK_LOOK, 1, ATS_DATEI);
		_G(atds)->set_ats_str(84, TXT_MARK_LOOK, 1, ATS_DATEI);
		_G(spieler).R11CardOk = true;

		if (!_G(spieler).R11TerminalOk)
			start_aad_wait(16, -1);
	}
}

int16 Room11::cut_serv(int16 frame) {
	if (_G(spieler).R11DoorRightF)
		_G(det)->plot_static_details(0, 0, 0, 0);

	if (_G(spieler).R11DoorRightB)
		_G(det)->plot_static_details(0, 0, 6, 6);

	if (_G(spieler).R45MagOk)
		_G(det)->plot_static_details(0, 0, 7, 7);

	return 0;
}

int16 Room11::cut_serv_2(int16 frame) {
	if (_G(spieler).R11DoorRightF)
		_G(det)->plot_static_details(0, 0, 0, 0);

	if (_G(spieler).R11DoorRightB)
		_G(det)->plot_static_details(0, 0, 6, 6);

	if (_G(spieler).R6DoorRightB)
		_G(det)->plot_static_details(0, 0, 7, 7);

	_G(atds)->print_aad(_G(spieler).scrollx, _G(spieler).scrolly);

	if (frame == 43)
		start_aad(106, 0);

	return 0;
}

} // namespace Rooms
} // namespace Chewy
