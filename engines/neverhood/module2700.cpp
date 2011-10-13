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

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "neverhood/module2700.h"
#include "neverhood/gamemodule.h"
#include "neverhood/module1000.h"

namespace Neverhood {

static const NRect kScene2710ClipRect = NRect(0, 0, 626, 480);

static const uint32 kScene2710StaticSprites[] = {
	0x0D2016C0,
	0
};

static const NRect kScene2711ClipRect = NRect(0, 0, 521, 480);

static const uint32 kScene2711FileHashes1[] = {
	0,
	0x100801A1,
	0x201081A0,
	0x006800A4,
	0x40390120,
	0x000001B1,
	0x001000A1,
	0
};

static const uint32 kScene2711FileHashes2[] = {
	0,
	0x40403308,
	0x71403168,
	0x80423928,
	0x224131A8,
	0x50401328,
	0x70423328,
	0
};

static const uint32 kScene2711FileHashes3[] = {
	0,
	0x1088A021,
	0x108120E5,
	0x18A02321,
	0x148221A9,
	0x10082061,
	0x188820E1,
	0
};

static const NRect kScene2724ClipRect = NRect(0, 141, 640, 480);

static const uint32 kScene2724StaticSprites[] = {
	0xC20D00A5,
	0
};

static const NRect kScene2725ClipRect = NRect(0, 0, 640, 413);

static const uint32 kScene2725StaticSprites[] = {
	0xC20E00A5,
	0
};

Module2700::Module2700(NeverhoodEngine *vm, Module *parentModule, int which)
	: Module(vm, parentModule), _soundResource1(vm), _soundResource2(vm),
	_soundResource3(vm), _soundResource4(vm), _soundIndex(0), _flag1(false) {
	
	// TODO Music18hList_add(0x42212411, 0x04020210);
	// TODO Music18hList_play(0x04020210, 24, 2, 1);
	SetMessageHandler(&Module2700::handleMessage);


	if (which < 0) {
		which = _vm->gameState().which;
		if (_vm->gameState().sceneNum == 0 || _vm->gameState().sceneNum == 30 || _vm->gameState().sceneNum == 31)
			which = -1;
		createScene(_vm->gameState().sceneNum, which);
	} else {
		createScene(0, 0);
	}

	_soundResource1.load(0x00880CCC);
	_soundResource2.load(0x00880CC0);
	_soundResource3.load(0x00880CCC);
	_soundResource4.load(0x00880CC0);

}

Module2700::~Module2700() {
	// TODO Sound1ChList_sub_407A50(0x42212411);
}

void Module2700::createScene(int sceneNum, int which) {
	debug("Module2700::createScene(%d, %d)", sceneNum, which);
	if (sceneNum != 30 && sceneNum != 31)
		_vm->gameState().which = which;
	_vm->gameState().sceneNum = sceneNum;
	switch (_vm->gameState().sceneNum) {
	case 0:
//TODO		_childObject = new Scene2701(_vm, this, which);
		break;
	case 1:
//TODO		_childObject = new Scene2702(_vm, this, which);
		break;
	case 2:
		if (which == 6 || which == 7)
			createScene2703(which, 0x004B1710);
		else if (which == 4 || which == 5)
			createScene2703(which, 0x004B1738);
		else if (which == 2 || which == 3)
			createScene2703(which, 0x004B1760);
		else
			createScene2703(which, 0x004B1788);
		break;
	case 3:
		createScene2704(which, 0x004B17B0, 150);
		break;
	case 4:
		createScene2704(which, 0x004B17D8, 150);
		break;
	case 5:
		if (which >= 4) {
//TODO		_childObject = new Scene2706(_vm, this, which);
		} else if (which == 2 || which == 3) {
			createScene2704(which, 0x004B1828, 150);
		} else {
			createScene2704(which, 0x004B1800, 150);
		}
		break;
	case 6:
		createScene2704(which, 0x004B1850, 150);
		break;
	case 7:
		if (which == 2 || which == 3) {
			createScene2704(which, 0x004B1878, 150);
		} else {
			createScene2704(which, 0x004B18A0, 150);
		}
		break;
	case 8:
		if (which == 2 || which == 3) {
			createScene2704(which, 0x004B18C8, 150);
		} else {
			createScene2704(which, 0x004B18F0, 150);
		}
		break;
	case 9:
		createScene2704(which, 0x004B1918, 150, kScene2710StaticSprites, &kScene2710ClipRect);
		break;
	case 10:
		// TODO _vm->gameModule()->initScene2808Vars2();
		_scene2711StaticSprites[0] = kScene2711FileHashes1[getSubVar(0x40005834, 2)];
		_scene2711StaticSprites[1] = kScene2711FileHashes2[getSubVar(0x40005834, 1)];
		_scene2711StaticSprites[2] = kScene2711FileHashes3[getSubVar(0x40005834, 0)];
		_scene2711StaticSprites[3] = 0x0261282E;
		_scene2711StaticSprites[4] = 0x9608E5A0;
		_scene2711StaticSprites[5] = 0;
		createScene2704(which, 0x004B1950, 150, _scene2711StaticSprites, &kScene2711ClipRect);
		break;
	case 11:
		createScene2704(which, 0x004B19E0, 150);
		break;
	case 12:
		createScene2704(which, 0x004B1A08, 150);
		break;
	case 13:
		createScene2704(which, 0x004B1A30, 150);
		break;
	case 14:
		if (which == 4 || which == 5) {
			createScene2704(which, 0x004B1A58, 150);
		} else if (which == 2 || which == 3) {
			createScene2704(which, 0x004B1A80, 150);
		} else {
			createScene2704(which, 0x004B1AA8, 150);
		}
		break;
	case 15:
		if (which == 4 || which == 5) {
			createScene2704(which, 0x004B1AD0, 150);
		} else if (which == 2 || which == 3) {
			createScene2704(which, 0x004B1AF8, 150);
		} else {
			createScene2704(which, 0x004B1B20, 150);
		}
		break;
	case 16:
		if (which == 4 || which == 5) {
			createScene2704(which, 0x004B1B48, 150);
		} else if (which == 2 || which == 3) {
			createScene2704(which, 0x004B1B70, 150);
		} else {
			createScene2704(which, 0x004B1B98, 150);
		}
		break;
	case 17:
		if (which == 4 || which == 5) {
			createScene2704(which, 0x004B1BC0, 150);
		} else if (which == 2 || which == 3) {
			createScene2704(which, 0x004B1BE8, 150);
		} else {
			createScene2704(which, 0x004B1C10, 150);
		}
		break;
	case 18:
		if (which == 2 || which == 3) {
			createScene2704(which, 0x004B1C38, 150);
		} else {
			createScene2704(which, 0x004B1C60, 150);
		}
		break;
	case 19:
		if (which == 2 || which == 3) {
			createScene2704(which, 0x004B1CB0, 150);
		} else {
			createScene2704(which, 0x004B1C88, 150);
		}
		break;
	case 20:
		if (which == 2 || which == 3) {
			createScene2704(which, 0x004B1CD8, 150);
		} else {
			createScene2704(which, 0x004B1D00, 150);
		}
		break;
	case 21:
		createScene2704(which, 0x004B1D28, 150);
		break;
	case 22:
		createScene2704(which, 0x004B1D50, 150);
		break;
	case 23:
		createScene2704(which, 0x004B1D78, 150, kScene2724StaticSprites, &kScene2724ClipRect);
		break;
	case 24:
		createScene2704(which, 0x004B1DB0, 150, kScene2725StaticSprites, &kScene2725ClipRect);
		break;
	case 25:
		createScene2704(which, 0x004B1DE8, 150);
		break;
	case 26:
		createScene2704(which, 0x004B1E10, 150);
		break;
	case 27:
		createScene2704(which, 0x004B1E38, 150);
		break;
	case 28:
		createScene2704(which, 0x004B1E60, 150);
		break;
	case 30:
		_childObject = new Class152(_vm, this, 0x09507248, 0x0724C09D);
		break;
	case 31:
//TODO		_childObject = new Scene2732(_vm, this, which);
		break;
	}
	SetUpdateHandler(&Module2700::updateScene);
	_childObject->handleUpdate();
}

#define SceneLinkIf(moduleResult, sceneNum, which) \
	if (_moduleResult == moduleResult) { createScene(sceneNum, which); break; }

void Module2700::updateScene() {
	if (!updateChild()) {
	
		debug("sceneNum = %d; _moduleResult = %d", _vm->gameState().sceneNum, _moduleResult);
	
		switch (_vm->gameState().sceneNum) {
		case 0:
			SceneLinkIf(1, 1, 0);
			leaveModule(0);
			break;
		case 1:
			SceneLinkIf(1, 14, 1);
			SceneLinkIf(2,  2, 2);
			SceneLinkIf(3, 14, 3);
			SceneLinkIf(4,  2, 6);
			SceneLinkIf(5,  2, 4);
			createScene(0, 1);
			break;
		case 2:
			SceneLinkIf(1,  5, 0);
			SceneLinkIf(2,  1, 2);
			SceneLinkIf(3,  5, 2);
			SceneLinkIf(4,  1, 5);
			SceneLinkIf(5,  5, 4);
			SceneLinkIf(6,  1, 4);
			SceneLinkIf(7, 11, 0);
			createScene(3, 0);
			break;
		case 3:
			createScene(2, 0);
			break;
		case 4:
			SceneLinkIf(1, 7, 2);
			createScene(5, 5);
			break;
		case 5:
			SceneLinkIf(1, 6, 0);
			SceneLinkIf(2, 2, 3);
			SceneLinkIf(3, 8, 2);
			SceneLinkIf(4, 2, 5);
			SceneLinkIf(5, 4, 0);
			SceneLinkIf(6, 7, 0);
			createScene(2, 1);
			break;
		case 6:
			SceneLinkIf(1, 8, 0);
			createScene(5, 1);
			break;
		case 7:
			SceneLinkIf(1, 8, 3);
			SceneLinkIf(2, 4, 1);
			SceneLinkIf(3, 9, 0);
			createScene(5, 6);
			break;
		case 8:
			SceneLinkIf(1, 10, 0);
			SceneLinkIf(2,  5, 3);
			SceneLinkIf(3,  7, 1);
			createScene(6, 1);
			break;
		case 9:
			SceneLinkIf(1, 10, 1);
			createScene(7, 3);
			break;
		case 10:
			SceneLinkIf(1, 9, 1);
			createScene(8, 1);
			break;
		case 11:
			SceneLinkIf(1, 12, 0);
			createScene(2, 7);
			break;
		case 12:
			SceneLinkIf(1, 13, 0);
			createScene(11, 1);
			break;
		case 13:
			SceneLinkIf(1, 30, 0);
			createScene(12, 1);
			break;
		case 14:
			SceneLinkIf(1, 1, 1);
			SceneLinkIf(2, 15, 3);
			SceneLinkIf(3, 1, 3);
			SceneLinkIf(4, 15, 5);
			SceneLinkIf(5, 22, 0);
			createScene(15, 1);
			break;
		case 15:
			SceneLinkIf(1, 14, 0);
			SceneLinkIf(2, 16, 3);
			SceneLinkIf(3, 14, 2);
			SceneLinkIf(4, 16, 5);
			SceneLinkIf(5, 14, 4);
			createScene(16, 1);
			break;
		case 16:
			SceneLinkIf(1, 15, 0);
			SceneLinkIf(2, 17, 3);
			SceneLinkIf(3, 15, 2);
			SceneLinkIf(4, 17, 5);
			SceneLinkIf(5, 15, 4);
			createScene(17, 1);
			break;
		case 17:
			SceneLinkIf(1, 16, 0);
			SceneLinkIf(2, 18, 3);
			SceneLinkIf(3, 16, 2);
			SceneLinkIf(4, 20, 1);
			SceneLinkIf(5, 16, 4);
			createScene(18, 1);
			break;
		case 18:
			SceneLinkIf(1, 17, 0);
			SceneLinkIf(2, 19, 2);
			SceneLinkIf(3, 17, 2);
			createScene(19, 0);
			break;
		case 19:
			SceneLinkIf(1, 20, 2);
			SceneLinkIf(2, 18, 2);
			SceneLinkIf(3, 20, 0);
			createScene(18, 0);
			break;
		case 20:
			SceneLinkIf(1, 17, 4);
			SceneLinkIf(2, 19, 1);
			SceneLinkIf(3, 21, 0);
			createScene(19, 3);
			break;
		case 21:
			// TODO? GameState_sub_469C50(&field_52, 0);
			// TODO MusicMan_stopAll (if field_52 above = 1)
			// TODO Music18hList_delete(_musicFileHash);
			// TODO Music18hList_play(0x04020210, 0, 2, 1);
			// TODO Sound1ChList_sub_407AF0(0x42212411);
			createScene(20, 3);
			break;
		case 22:
			SceneLinkIf(1, 23, 0);
			createScene(14, 5);
			break;
		case 23:
			SceneLinkIf(1, 24, 0);
			createScene(22, 1);
			break;
		case 24:
			SceneLinkIf(1, 25, 0);
			createScene(23, 1);
			break;
		case 25:
			SceneLinkIf(1, 26, 0);
			createScene(24, 1);
			break;
		case 26:
			SceneLinkIf(1, 27, 0);
			createScene(25, 1);
			break;
		case 27:
			SceneLinkIf(1, 28, 0);
			createScene(26, 1);
			break;
		case 28:
			SceneLinkIf(1, 31, 0);
			createScene(27, 1);
			break;
		case 29:
			createScene(13, 1);
			break;
		case 30:
			createScene(28, 1);
			break;
		}
	} else {
		switch (_vm->gameState().sceneNum) {
		case 21:
			if (!_flag1) {
				// TODO Music18hList_stop(0x04020210, 0, 1);
				// TODO _vm->gameModule()->initScene2801Vars();
				_musicFileHash = getGlobalVar(0x89A82A15);
				// TODO? GameState_sub_469C50(&field_52, 0);
				// TODO MusicMan_create();
				// TODO Music18hList_add2(0x42212411, _musicFileHash);
				// TODO Music18hList_play2(_musicFileHash, 0, /*TODO */???, 1);
				// TODO Sound1ChList_addSoundResource(0x42212411, 0x44014282, true);
				// TODO Sound1ChList_setSoundValues(0x44014282, true, 120, 360, 72, 0);
				_flag1 = true;
			}
			break;
		}
	}
}

void Module2700::update() {

}

uint32 Module2700::handleMessage(int messageNum, const MessageParam &param, Entity *sender) {
	uint32 messageResult = Module::handleMessage(messageNum, param, sender);
	switch (messageNum) {
	case 0x200D:
		switch (_soundIndex) {
		case 0:
			_soundResource1.play();
			break;
		case 1:
			_soundResource2.play();
			break;
		case 2:
			_soundResource3.play();
			break;
		case 3:
			_soundResource4.play();
			break;
		}
		_soundIndex++;
		if (_soundIndex >= 4)
			_soundIndex = 0;
		break;
	}
	return messageResult;
}
			
void Module2700::createScene2703(int which, uint32 sceneInfoId, const uint32 *staticSprites, const NRect *clipRect) {
	// TODO
}

void Module2700::createScene2704(int which, uint32 sceneInfoId, int16 value, const uint32 *staticSprites, const NRect *clipRect) {
	_childObject = new Scene2704(_vm, this, which, sceneInfoId, value, staticSprites, clipRect);
}

Scene2704::Scene2704(NeverhoodEngine *vm, Module *parentModule, int which, uint32 sceneInfoId, int16 value,
	const uint32 *staticSprites, const NRect *clipRect)
	: Scene(vm, parentModule, true) {

	SceneInfo2700 *sceneInfo = _vm->_staticData->getSceneInfo2700(sceneInfoId);
	
	_surfaceFlag = true;
	SetMessageHandler(&Scene2704::handleMessage);
	SetUpdateHandler(&Scene2704::update);
	
	setBackground(sceneInfo->bgFilename);
	setPalette(sceneInfo->bgFilename);
	
	if (sceneInfo->exPaletteFilename1)
		_palette->addPalette(sceneInfo->exPaletteFilename1, 0, 65, 0);
	
	if (sceneInfo->exPaletteFilename2)
		_palette->addPalette(sceneInfo->exPaletteFilename2, 65, 31, 65);
	
	while (staticSprites && *staticSprites)
		insertStaticSprite(*staticSprites++, 1100);

	insertMouse433(sceneInfo->mouseCursorFilename);
	
	if (sceneInfo->class437Filename) {
//TODO		_class437 = insertSprite<Class437>(sceneInfo->class437Filename);
		_class521 = insertSprite<Class521>(this, 320, 240);
//TODO		_class517 = insertSprite<Class517>(_class521, _class437->getSurface(), 4);
//TODO		_class520 = insertSprite<Class520>(_class521, _class437->getSurface(), 4);
//TODO		_class519 = insertSprite<Class519>(_class521, _class437->getSurface(), 4);
	} else {
//TODO		_class437 = NULL;
//TODO		_class517 = NULL;
		_class521 = insertSprite<Class521>(this, 320, 240);
	}

//TODO	_class518 = insertSprite<Class518>(_class521);
	
	_which1 = sceneInfo->which1;
	_which2 = sceneInfo->which2;

	_dataResource.load(sceneInfo->dataResourceFilename);
	_pointList = _dataResource.getPointArray(sceneInfo->pointListName);
	_class521->setPathPoints(_pointList);
	
	if (sceneInfo->rectListName) {
		_rectList = _dataResource.getRectArray(sceneInfo->rectListName);
		// TODO _class521->setPathRects(_rectList);
	}

	if (which == _which2) {
		NPoint testPoint = (*_pointList)[_pointList->size() - 1];
		sendMessage(_class521, 0x2002, _pointList->size() - 1);
		if (testPoint.x > 0 && testPoint.x < 640 && testPoint.y > 0 && testPoint.y < 480)
			sendMessage(_class521, 0x2009, 0);
		else
			sendMessage(_class521, 0x2007, 0);
	} else {
		NPoint testPoint = (*_pointList)[0];
		sendMessage(_class521, 0x2002, 0);
		if (testPoint.x > 0 && testPoint.x < 640 && testPoint.y > 0 && testPoint.y < 480)
			sendMessage(_class521, 0x2009, 0);
		else
			sendMessage(_class521, 0x2008, 0);
	}
	
	if (clipRect) {
		_class521->getClipRect() = *clipRect;
		if (_class517)
			_class517->getClipRect() = *clipRect; 
		if (_class520)
			_class520->getClipRect() = *clipRect; 
		if (_class519)
			_class519->getClipRect() = *clipRect; 
		if (_class518)
			_class518->getClipRect() = *clipRect; 
	}

}
		
void Scene2704::update() {
	Scene::update();
	if (_mouseClicked) {
		sendPointMessage(_class521, 0x2004, _mouseClickPos);
		_mouseClicked = false;
	}
}

uint32 Scene2704::handleMessage(int messageNum, const MessageParam &param, Entity *sender) {
	Scene::handleMessage(messageNum, param, sender);
	switch (messageNum) {
	case 0x2005:
		if (_which1 >= 0)
			leaveScene(_which1);
		break;
	case 0x2006:
		if (_which2 >= 0)
			leaveScene(_which2);
		break;
	case 0x200D:
		sendMessage(_parentModule, 0x200D, 0);
		break;
	}
	return 0;
}

} // End of namespace Neverhood
