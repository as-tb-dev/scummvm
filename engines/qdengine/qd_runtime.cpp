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

#define FORBIDDEN_SYMBOL_ALLOW_ALL
#include "common/archive.h"
#include "common/config-manager.h"
#include "common/events.h"

#include "qdengine/resource.h"
#include "qdengine/qdcore/qd_game_dispatcher.h"
#include "qdengine/qdcore/qd_game_scene.h"
#include "qdengine/qdcore/qd_trigger_chain.h"
#include "qdengine/qdcore/qd_setup.h"
#include "qdengine/system/sound/ds_snd_dispatcher.h"
#include "qdengine/qdcore/qd_trigger_profiler.h"
#include "qdengine/qdcore/qd_file_manager.h"
#include "qdengine/qdcore/util/plaympp_api.h"
#include "qdengine/qdcore/util/splash_screen.h"
#include "qdengine/qdcore/util/ResourceDispatcher.h"
#include "qdengine/qdcore/util/WinVideo.h"
#include "qdengine/system/graphics/gr_dispatcher.h"
#include "qdengine/system/app_core.h"
#include "qdengine/system/input/input_wndproc.h"
#include "qdengine/system/input/mouse_input.h"
#include "qdengine/system/input/keyboard_input.h"

#include "qdengine/qd_precomp.h"

namespace QDEngine {

namespace qdrt {

void init_graphics();
bool init_graphics_dispatcher();
bool is_graphics_reinit_needed();
void restore_graphics();

void toggle_fullscreen(bool force_fullscreen = false);
void maximize_window() {
	toggle_fullscreen(true);
}

void qd_show_load_progress(int percents_loaded, void *p);

void restore();

bool request_CD_handler(int cd_id);

/* --------------------------- DEFINITION SECTION --------------------------- */

grDispatcher *grD = NULL;

HWND hmainWnd;

qdGameDispatcher *qd_gameD = NULL;

}; // namespace qdrt

using namespace qdrt;

static void generateTagMap(int date, bool verbose = true) {
	int n = 0;

	memset(g_engine->_tagMap, 0, QDSCR_MAX_KEYWORD_ID);

	for (int i = 0; i < QDSCR_MAX_KEYWORD_ID; i++)
		if (idTagVersionAll[i * 2] <= date)
			g_engine->_tagMap[n++] = idTagVersionAll[i * 2 + 1];

	if (verbose)
		warning("Generated %d ids for version %d", n, date);
}

void searchTagMap(int id, int targetVal) {
	Common::HashMap<int, bool> dates;

	for (int i = 0; i < QDSCR_MAX_KEYWORD_ID; i++)
		dates[idTagVersionAll[i * 2]] = true;

	Common::Array<int> sdates;
	for (auto it : dates)
		sdates.push_back(it._key);

	Common::sort(sdates.begin(), sdates.end());

	for (auto d : sdates) {
		generateTagMap(d, false);

		for (int i = 0; i < QDSCR_MAX_KEYWORD_ID; i++)
			if (g_engine->_tagMap[i] == id)
				warning("ver: %d  val: %d", d, i + 1);

		if (g_engine->_tagMap[targetVal - 1] == id)
			warning("searchTagMap(): Matched version %d", d);
	}

	warning("searchTagMap(): No match");
}

int engineMain() {
	Common::ArchiveMemberList files;
	SearchMan.listMatchingMembers(files, "*.qml");
	Common::ArchiveMemberPtr p = files.front();
	Common::String firstFileName;
	std::string script_name;

	if (p) {
		firstFileName = p->getFileName();
		script_name = firstFileName.c_str();
	}

	if (script_name.empty()) {
		return 0;
	}

	grD = new grDispatcher();

#ifdef __QD_TRIGGER_PROFILER__
	if (ConfMan.getBool("trigger_profiler"))
		qdTriggerProfiler::instance().enable();
#endif

	grD->set_maximize_handler(maximize_window);

	grD->HideMouse();

	grD->ShowMouse(); // FIXME HACK

	qdGameConfig::get_config().load();

#ifdef __QD_TRIGGER_PROFILER__
	if (qdGameConfig::get_config().is_profiler_enabled())
		qdTriggerProfiler::instance().enable();
	if (0 != strlen(qdGameConfig::get_config().profiler_file()))
		qdTriggerProfiler::instance().set_work_file(qdGameConfig::get_config().profiler_file());
#endif

	SplashScreen sp;
	if (qdGameConfig::get_config().is_splash_enabled()) {
		sp.create(IDB_SPLASH);
		sp.set_mask(IDB_SPLASH_MASK);
		sp.show();
	}

	// searchTagMap(QDSCR_GAME_TITLE, 203);

	Common::String gameID = g_engine->getGameId();
	if (gameID == "pilots3") {
		generateTagMap(20040519);
	} else if (gameID == "pilots3d") {
		generateTagMap(20040706);
	} else if (gameID == "3mice1") {
		generateTagMap(20060630);
	} else if (gameID == "shveik") {
		generateTagMap(20070503);
	} else {
		warning("Unprocessed tagMap, switching to shveik");

		generateTagMap(20070503);
	}

	SetErrorMode(SEM_FAILCRITICALERRORS);

//	qdFileManager::instance().check_drive('E');
	qdFileManager::instance().set_request_CD_handler(request_CD_handler);
#if 0
	for (int i = 1; i < __argc; i ++) {
		debugCN(3, kDebugLog, "'\' %s '\'", __argv[i]);
	}
	debugC(3, kDebugLog, "");
#endif
	grDispatcher::set_default_font(qdGameDispatcher::create_font(0));

	qd_gameD = new qdGameDispatcher;
	qd_gameD->load_script(script_name.c_str());

	if (ConfMan.getBool("dump_scripts")) {
		qd_gameD->save_script("qd_game.xml");
	}

	qd_gameD->set_scene_loading_progress_callback(qd_show_load_progress);

	if (qdGameConfig::get_config().is_splash_enabled()) {
		sp.wait(qdGameConfig::get_config().splash_time());
		sp.destroy();
	}

	init_graphics();

	ds_sndDispatcher *sndD = new ds_sndDispatcher;

	qdGameConfig::get_config().update_sound_settings();
	qdGameConfig::get_config().update_music_settings();

	winVideo::init();

	qd_gameD->load_resources();

	if (ConfMan.hasKey("boot_param")) {
		const char *scene_name = ""; // FIXME. Implement actual scene selection
		if (!qd_gameD->select_scene(scene_name))
			error("Cannot find the startup scene");
	} else {
		bool music_enabled = mpegPlayer::instance().is_enabled();
		mpegPlayer::instance().disable();

		qd_gameD->toggle_main_menu(true);
		if (!qd_gameD->start_intro_videos()) {
			if (music_enabled)
				mpegPlayer::instance().enable(true);
		} else {
			if (music_enabled)
				mpegPlayer::instance().enable(false);
		}
	}

	qd_gameD->update_time();
	qd_gameD->quant();

	ResourceDispatcher resD;
	resD.setTimer(qdGameConfig::get_config().logic_synchro_by_clock(), qdGameConfig::get_config().logic_period(), 300);
	resD.attach(new MemberFunctionCallResourceUser<qdGameDispatcher>(*qd_gameD, &qdGameDispatcher::quant, qdGameConfig::get_config().logic_period()));
	sndD->set_frequency_coeff(qdGameConfig::get_config().game_speed());
	resD.set_speed(qdGameConfig::get_config().game_speed());
	resD.start();

	bool exit_flag = false;
	bool was_inactive = false;

	// Activate the window
	grDispatcher::activate(true);

	Common::Event event;

	while (!exit_flag && !qd_gameD->need_exit()) {
		while (g_system->getEventManager()->pollEvent(event)) {
			switch (event.type) {
			case Common::EVENT_QUIT:
				if (!grDispatcher::instance()->is_in_reinit_mode())
					exit_flag = true;
				break;
			case Common::EVENT_KEYDOWN:
				if (event.kbd.ascii == 'f')
					qdGameConfig::get_config().toggle_fps();
#ifdef __QD_DEBUG_ENABLE__
				else if (event.kbd.keycode == Common::KEYCODE_PAGEDOWN) {
					float speed = qdGameConfig::get_config().game_speed() * 0.9f;
					if (speed < 0.1f) speed = 0.1f;
					qdGameConfig::get_config().set_game_speed(speed);
					sndD->set_frequency_coeff(speed);
					resD.set_speed(qdGameConfig::get_config().game_speed());
				} else if (event.kbd.keycode == Common::KEYCODE_PAGEUP) {
					float speed = qdGameConfig::get_config().game_speed() * 1.1f;
					if (speed > 10.0f) speed = 10.0f;
					qdGameConfig::get_config().set_game_speed(speed);
					sndD->set_frequency_coeff(speed);
					resD.set_speed(qdGameConfig::get_config().game_speed());
				} else if (event.kbd.keycode == Common::KEYCODE_HOME) {
					qdGameConfig::get_config().set_game_speed(1.0f);
					sndD->set_frequency_coeff(1.0f);
					resD.set_speed(qdGameConfig::get_config().game_speed());
				} else if (event.kbd.ascii == 'g')
					qdGameConfig::get_config().toggle_show_grid();
#endif
				break;
			default:
				break;
			}

			input::keyboard_wndproc(event, keyboardDispatcher::instance());
			input::mouse_wndproc(event, mouseDispatcher::instance());
		}

		if (grDispatcher::instance()->is_mouse_hidden())
			grDispatcher::instance()->set_null_mouse_cursor();
		else
			grDispatcher::instance()->set_default_mouse_cursor();

		if (grDispatcher::is_active()) {
			if (was_inactive) {
				was_inactive = false;
				// При активации ждем, чтобы звукововая система успела настроиться
				// на наше приложение (предположение)
				g_system->delayMillis(500);
			}
			resD.quant();
			qd_gameD->redraw();

		} else {
			was_inactive = true;
			g_system->delayMillis(100);
			resD.skip_time();
		}

		g_system->updateScreen();
	}

	delete qd_gameD;

	grDispatcher::instance()->Finit();

	qdFileManager::instance().Finit();

	ShowWindow(hmainWnd, SW_HIDE);
	CloseWindow(hmainWnd);
	DestroyWindow(hmainWnd);

	delete sndD;
	delete grD;

	winVideo::done();

	return 0;
}

namespace qdrt {

void init_graphics() {
	grDispatcher::set_restore_handler(restore_graphics);
	grDispatcher::instance()->Finit();

	grDispatcher::set_instance(grD);

	if (!init_graphics_dispatcher())
		return;

	grDispatcher::instance()->resize_window();

	qdGameConfig::get_config().set_pixel_format(grDispatcher::instance()->pixel_format());

	grDispatcher::instance()->SetClip();
	grDispatcher::instance()->SetClipMode(1);

	grDispatcher::instance()->Fill(0);

	g_system->updateScreen();

	grDispatcher::instance()->Flush();
}

bool init_graphics_dispatcher() {
	if (grDispatcher::instance()->init(qdGameConfig::get_config().screen_sx(), qdGameConfig::get_config().screen_sy(), (grPixelFormat)qdGameConfig::get_config().pixel_format(), hmainWnd, qdGameConfig::get_config().fullscreen()))
		return true;

	for (int i = 0; i <= GR_ARGB8888; i++) {
		if (grDispatcher::instance()->init(qdGameConfig::get_config().screen_sx(), qdGameConfig::get_config().screen_sy(), (grPixelFormat)i, hmainWnd, qdGameConfig::get_config().fullscreen()))
			return true;
	}

	qdGameConfig::get_config().toggle_fullscreen();

	for (int i = 0; i <= GR_ARGB8888; i++) {
		if (grDispatcher::instance()->init(qdGameConfig::get_config().screen_sx(), qdGameConfig::get_config().screen_sy(), (grPixelFormat)i, hmainWnd, qdGameConfig::get_config().fullscreen()))
			return true;
	}

	grDispatcher::set_instance(grD);
	if (grDispatcher::instance()->init(qdGameConfig::get_config().screen_sx(), qdGameConfig::get_config().screen_sy(), (grPixelFormat)qdGameConfig::get_config().pixel_format(), hmainWnd, qdGameConfig::get_config().fullscreen()))
		return true;

	return false;
}

void qd_show_load_progress(int percents_loaded, void *p) {
	const int rect_sx = 200;
	const int rect_sy = 10;

	int sx = rect_sx * percents_loaded / 100;
	if (sx < 0) sx = 0;
	if (sx > rect_sx) sx = rect_sx;

	int x = 10;
	int y = grDispatcher::instance()->Get_SizeY() - rect_sy - 10;

	grDispatcher::instance()->Rectangle(x, y, rect_sx, rect_sy, 0xFFFFFF, 0, GR_OUTLINED);
	grDispatcher::instance()->Rectangle(x, y, sx, rect_sy, 0xFFFFFF, 0xFFFFFF, GR_FILLED);
	grDispatcher::instance()->Flush(x, y, rect_sx, rect_sy);
}

bool is_graphics_reinit_needed() {
	if (qdGameConfig::get_config().pixel_format() != (int)grDispatcher::instance()->pixel_format() || qdGameConfig::get_config().fullscreen() != grDispatcher::instance()->is_in_fullscreen_mode())
		return true;

	return false;
}

void restore_graphics() {
	if (sndDispatcher * dp = sndDispatcher::get_dispatcher())
		dp->set_volume(dp->volume());

	if (qdGameDispatcher * dp = qdGameDispatcher::get_dispatcher())
		dp->set_flag(qdGameDispatcher::FULLSCREEN_REDRAW_FLAG);
}

void restore() {
}

void toggle_fullscreen(bool force_fullscreen) {
	if (force_fullscreen && qdGameConfig::get_config().fullscreen()) return;

	qdGameConfig::get_config().toggle_fullscreen();
	qdGameConfig::get_config().set_driver_ID(1);

	grDispatcher::instance()->toggle_reinit();
	grDispatcher::instance()->Finit();
	grDispatcher::instance()->destroy_window();

	hmainWnd = NULL;

	init_graphics();

	qdGameDispatcher::get_dispatcher()->toggle_full_redraw();
//	qdGameDispatcher::get_dispatcher()->convert_graphics();
}

bool request_CD_handler(int cd_id) {
	if (qdGameDispatcher * p = qdGameDispatcher::get_dispatcher())
		p->request_CD(cd_id);

	return true;
}

}; // namespace main
} // namespace QDEngine

