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

#include "common/scummsys.h"
#include "common/error.h"
#include "common/system.h"
#include "common/events.h"
#include "common/archive.h"
#include "common/config-manager.h"
#include "common/fs.h"
#include "common/str.h"

#include "trecision/trecision.h"
#include "trecision/anim.h"
#include "trecision/scheduler.h"
#include "trecision/actor.h"
#include "trecision/3d.h"
#include "trecision/defines.h"
#include "trecision/console.h"
#include "trecision/dialog.h"
#include "trecision/graphics.h"
#include "trecision/video.h"
#include "trecision/logic.h"
#include "trecision/text.h"
#include "trecision/sound.h"

namespace Common {
class File;
}

namespace Trecision {

TrecisionEngine::TrecisionEngine(OSystem *syst, const ADGameDescription *desc) : Engine(syst), _gameDescription(desc) {
	const Common::FSNode gameDataDir(ConfMan.get("path"));
	SearchMan.addSubDirectoryMatching(gameDataDir, "AUTORUN");
	SearchMan.addSubDirectoryMatching(gameDataDir, "DATA");
	SearchMan.addSubDirectoryMatching(gameDataDir, "FMV");

	_curRoom = 0;
	_oldRoom = 0;

	_curInventory = 0;

	for (int i = 0; i < 10; ++i)
		_curScriptFrame[i] = 0;

	_iconBase = 0;
	_inventoryRefreshStartIcon = 0;
	_flagInventoryLocked = false;
	_inventorySpeed[0] = 20;
	_inventorySpeed[1] = 10;
	_inventorySpeed[2] = 5;
	_inventorySpeed[3] = 3;
	_inventorySpeed[4] = 2;
	_inventorySpeed[5] = _inventorySpeed[6] = _inventorySpeed[7] = 0;
	_inventorySpeedIndex = 0;
	_inventoryScrollTime = 0;

	_fastWalk = false;

	// Use With
	_useWith[0] = _useWith[1] = 0;
	_useWithInv[0] = _useWithInv[1] = false;

	// Messages
	for (int i = 0; i < MAXOBJNAME; ++i)
		_objName[i] = nullptr;

	for (int i = 0; i < MAXSENTENCE; ++i)
		_sentence[i] = nullptr;

	for (int i = 0; i < MAXSYSTEXT; ++i)
		_sysText[i] = nullptr;

	_curMessage = nullptr;

	// Original values
	_idleMsg = {MC_IDLE, 0, MP_DEFAULT, 0, 0, 0, 0, 0};
	_curObj = 1;
	_inventoryStatus = INV_OFF;
	_lightIcon = 0xFF;
	_inventoryRefreshStartLine = INVENTORY_HIDE;
	_inventoryCounter = INVENTORY_HIDE;

	_animMgr = nullptr;
	_dialogMgr = nullptr;
	_graphicsMgr = nullptr;
	_logicMgr = nullptr;
	_soundMgr = nullptr;
	_renderer = nullptr;
	_pathFind = nullptr;
	_textMgr = nullptr;
	_animTypeMgr = nullptr;

	_actorRect = nullptr;
	_nextRefresh = 0;

	_curKey = Common::KEYCODE_INVALID;
	_curAscii = 0;
	_mousePos = Common::Point(0, 0);
	_mouseLeftBtn = _mouseRightBtn = false;
	_keybInput = false;

	_gamePaused = false;

	_textPtr = nullptr;
	_lastInv = 0;
	_lastObj = 0;

	_curStack = 0;

	_flagScriptActive = false;

	_actor = nullptr;

	_flagDialogActive = false;
	_flagDialogMenuActive = false;
	_flagSkipTalk = false;
	_flagPaintCharacter = false;
	_flagShowCharacter = true;
	_flagSomeoneSpeaks = false;
	_flagCharacterSpeak = false;
	_flagUseWithStarted = false;
	_flagCharacterExists = true;
	_flagNoPaintScreen = false;
	_flagWaitRegen = false;

	for (int i = 0; i < MAXOBJINROOM; ++i) {
		_objPointers[i] = nullptr;
		_maskPointers[i] = nullptr;
	}

	_blinkLastDTextChar = MASKCOL;
	_curTime = 0;
	_characterSpeakTime = 0;

	_actorPos = 0;
	_forcedActorPos = 0;

	maskMouse = false;
	oldMousePos = Common::Point(0, 0);
	lastMouseOn = true;

	_pauseStartTime = 0;
	_textStatus = TEXT_OFF;

	_cx = _cy = 0;
}

TrecisionEngine::~TrecisionEngine() {
	if (_animMgr)
		_animMgr->stopAllSmkAnims();

	_dataFile.close();
	_thumbnail.free();

	delete _animMgr;
	delete _dialogMgr;
	delete _graphicsMgr;
	delete _logicMgr;
	delete _soundMgr;
	delete _renderer;
	delete _pathFind;
	delete _textMgr;
	delete _scheduler;
	delete _animTypeMgr;

	delete _actor;
	delete[] _textArea;

	for (int i = 0; i < MAXOBJINROOM; ++i) {
		delete[] _objPointers[i];
		delete[] _maskPointers[i];
	}
}

Common::Error TrecisionEngine::run() {
	syncSoundSettings();

	if (!_dataFile.open("nldata.cd0"))
		error("Error opening nldata.cd0");

	_graphicsMgr = new GraphicsManager(this);
	if (!_graphicsMgr->init())
		return Common::kUnsupportedColorMode;
	_animMgr = new AnimManager(this);
	_dialogMgr = new DialogManager(this);
	_logicMgr = new LogicManager(this);
	_soundMgr = new SoundManager(this);
	_pathFind = new PathFinding3D(this);
	_renderer = new Renderer3D(this);
	_textMgr = new TextManager(this);
	_scheduler = new Scheduler(this);
	_animTypeMgr = new AnimTypeManager(this);
	_actor = new Actor(this);

	setDebugger(new Console(this));

	initMain();

	// Check if a saved game is to be loaded from the launcher
	if (ConfMan.hasKey("save_slot"))
		loadGameState(ConfMan.getInt("save_slot"));

	while (!shouldQuit()) {
		eventLoop();
		if (!_flagNoPaintScreen)
			processTime();

		processMouse();
		_scheduler->process();

		_animTypeMgr->handler(kAnimTypeBackground);

		processCurrentMessage();

		if (_flagScriptActive)
			evalScript();
	}

	if (isDemo())
		_graphicsMgr->showDemoPic();

	return Common::kNoError;
}

bool TrecisionEngine::isDemo() const {
	return _gameDescription->flags & ADGF_DEMO;
}

void TrecisionEngine::eventLoop() {
	Common::Event event;
	while (g_system->getEventManager()->pollEvent(event)) {
		switch (event.type) {
		case Common::EVENT_MOUSEMOVE:
			_mousePos = event.mouse;
			break;

		case Common::EVENT_LBUTTONDOWN:
			_mouseLeftBtn = true;
			break;

		case Common::EVENT_LBUTTONUP:
			_mouseLeftBtn = false;
			break;

		case Common::EVENT_RBUTTONDOWN:
			_mouseRightBtn = true;
			break;

		case Common::EVENT_RBUTTONUP:
			_mouseRightBtn = false;
			break;

		case Common::EVENT_KEYUP:
			_curKey = event.kbd.keycode;
			_curAscii = event.kbd.ascii;
			switch (event.kbd.keycode) {
			case Common::KEYCODE_p:
				if (!_gamePaused && !_keybInput) {
					_curKey = Common::KEYCODE_INVALID;
					_gamePaused = true;
					waitKey();
				}
				_gamePaused = false;
				break;

			case Common::KEYCODE_CAPSLOCK:
				_fastWalk ^= true;
				break;
			default:
				break;
			}
			break;

		default:
			break;
		}
	}
	g_system->delayMillis(10);
	g_system->updateScreen();
}

void TrecisionEngine::initMain() {
	for (int c = 0; c < MAXOBJ; c++)
		_obj[c]._position = -1;

	_curRoom = kRoomIntro;
	_gameQueue.initQueue();
	_animQueue.initQueue();
	_characterQueue.initQueue();
	for (uint8 i = 0; i < MAXMESSAGE; i++) {
		_gameQueue._event[i] = &_gameMsg[i];
		_characterQueue._event[i] = &_characterMsg[i];
		_animQueue._event[i] = &_animMsg[i];
	}

	loadAll();
	processTime();

	_scheduler->changeRoom(_curRoom, 0, 0, _curObj);
}

void TrecisionEngine::checkSystem() {
	eventLoop();
}

void TrecisionEngine::startCharacterAction(uint16 action, uint16 newRoom, uint8 newPos, uint16 sent) {
	_characterQueue.initQueue();

	_flagInventoryLocked = false;
	if (action > hLAST) {
		_animMgr->startSmkAnim(action);
		_animTypeMgr->init(action, _curObj);
		_graphicsMgr->hideCursor();
		_flagShowCharacter = false;
		_scheduler->doEvent(MC_CHARACTER, ME_CHARACTERCONTINUEACTION, MP_DEFAULT, action, newRoom, newPos, _curObj);
	} else {
		if ((action == aWALKIN) || (action == aWALKOUT))
			_curObj = 0;
		_graphicsMgr->hideCursor();
		_actor->actorDoAction(action);
		_pathFind->nextStep();
	}

	if (sent)
		_textMgr->characterSayInAction(sent);
	else
		_textMgr->clearLastText();
}

bool TrecisionEngine::canPlayerInteract() {
	return (!_flagSomeoneSpeaks &&
			!_flagScriptActive &&
			!_flagDialogActive &&
			!_flagDialogMenuActive &&
			(_actor->_curAction < hWALKIN) &&
			!_flagUseWithStarted &&
			_flagShowCharacter &&
			!_animMgr->_playingAnims[kSmackerAction]);
}

void TrecisionEngine::addDirtyRect(Common::Rect rect) {
	rect.translate(0, TOP);
	_dirtyRects.push_back(rect);
}

void TrecisionEngine::setObjectVisible(uint16 objectId, bool visible) {
	if (visible)
		_obj[objectId]._mode |= OBJMODE_OBJSTATUS;
	else
		_obj[objectId]._mode &= ~OBJMODE_OBJSTATUS;

	if (_obj[objectId]._mode & (OBJMODE_MASK | OBJMODE_FULL)) {
		SSortTable entry;
		entry._objectId = objectId;
		entry._remove = !isObjectVisible(objectId);
		_sortTable.push_back(entry);
	}
}

bool TrecisionEngine::isObjectVisible(uint16 objectId) const {
	return _obj[objectId]._mode & OBJMODE_OBJSTATUS;
}

void TrecisionEngine::setObjectAnim(uint16 objectId, uint16 animId) {
	_obj[objectId]._anim = animId;
}

void TrecisionEngine::reEvent() {
	_scheduler->doEvent(_curMessage->_class, _curMessage->_event, _curMessage->_priority, _curMessage->_u16Param1, _curMessage->_u16Param2, _curMessage->_u8Param, _curMessage->_u32Param);
}

void TrecisionEngine::readLoc() {
	if (_curRoom == kRoom11 && !(_room[kRoom11]._flag & kObjFlagDone))
		_flagShowCharacter = true;

	_soundMgr->stopAllExceptMusic();

	_graphicsMgr->clearScreenBufferTop();

	Common::String filename = Common::String::format("%s.cr", _room[_curRoom]._baseName);
	Common::SeekableReadStream *picFile = _dataFile.createReadStreamForCompressedMember(filename);

	SObject bgInfo;
	bgInfo.readRect(picFile);

	_graphicsMgr->loadBackground(picFile, bgInfo._rect.width(), bgInfo._rect.height());
	_sortTable.clear();
	readObj(picFile);

	_soundMgr->stopAll();

	if (_room[_curRoom]._sounds[0] != 0)
		_soundMgr->loadRoomSounds();

	Common::String fname = Common::String::format("%s.3d", _room[_curRoom]._baseName);
	read3D(fname);

	if (_room[_curRoom]._bkgAnim) {
		_animMgr->startSmkAnim(_room[_curRoom]._bkgAnim);
	} else
		_animMgr->smkStop(kSmackerBackground);

	_animTypeMgr->init(_room[_curRoom]._bkgAnim, 0);
}

void TrecisionEngine::redrawRoom() {
	const uint16 curDialog = _dialogMgr->_curDialog;
	const uint16 curChoice = _dialogMgr->_curChoice;
	const uint16 bgAnim = _room[_curRoom]._bkgAnim;
	const ElevatorAction elevatorActions[6] = {
		{dASCENSORE12, 3, a129PARLACOMPUTERESCENDE, kRoom13},
		{dASCENSORE12, 4, a129PARLACOMPUTERESCENDE, kRoom16},
		{dASCENSORE13, 17, a139CHIUDONOPORTESU, kRoom12},
		{dASCENSORE13, 18, a1316CHIUDONOPORTEGIU, kRoom16},
		{dASCENSORE16, 32, a1616SALECONASCENSORE, kRoom12},
		{dASCENSORE16, 33, a1616SALECONASCENSORE, kRoom13},
	};

	_flagShowCharacter = _dialogMgr->showCharacterAfterDialog();
	_flagPaintCharacter = true;
	_textStatus = TEXT_OFF;

	for (int i = 0; i < 6; ++i) {
		if (curDialog == elevatorActions[i].dialog && curChoice == elevatorActions[i].choice) {
			startCharacterAction(elevatorActions[i].action, elevatorActions[i].newRoom, 20, 0);
			break;
		}
	}

	Common::String filename = Common::String::format("%s.cr", _room[_curRoom]._baseName);
	Common::SeekableReadStream *picFile = _dataFile.createReadStreamForCompressedMember(filename);

	SObject bgInfo;
	bgInfo.readRect(picFile);

	_graphicsMgr->loadBackground(picFile, bgInfo._rect.width(), bgInfo._rect.height());
	_sortTable.clear();

	if (bgAnim)
		_animMgr->startSmkAnim(bgAnim);

	if (_curRoom == kRoom4P && curDialog == dF4PI)
		_animMgr->smkGoto(kSmackerBackground, 21);

	_renderer->paintScreen(true);
}

void TrecisionEngine::tendIn() {
	_textStatus = TEXT_OFF;

	if (_curRoom == kRoomIntro) {
		_dialogMgr->playDialog(dFLOG);
		return;
	}

	_flagPaintCharacter = true;
	_renderer->paintScreen(true);

	_graphicsMgr->copyToScreen(0, 0, MAXX, MAXY);
}

} // End of namespace Trecision
