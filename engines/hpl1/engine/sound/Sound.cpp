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

/*
 * Copyright (C) 2006-2010 - Frictional Games
 *
 * This file is part of HPL1 Engine.
 *
 * HPL1 Engine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HPL1 Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HPL1 Engine.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "hpl1/engine/sound/Sound.h"
#include "hpl1/engine/system/LowLevelSystem.h"
#include "hpl1/engine/sound/LowLevelSound.h"
#include "hpl1/engine/resources/Resources.h"
#include "hpl1/engine/sound/SoundHandler.h"
#include "hpl1/engine/sound/MusicHandler.h"


namespace hpl {

	//////////////////////////////////////////////////////////////////////////
	// CONSTRUCTORS
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

	cSound::cSound(iLowLevelSound *apLowLevelSound) : iUpdateable("HPL_Sound")
	{
		mpLowLevelSound = apLowLevelSound;
	}

	//-----------------------------------------------------------------------

	cSound::~cSound()
	{
		Log("Exiting Sound Module\n");
		Log("--------------------------------------------------------\n");

		hplDelete(mpSoundHandler);
		hplDelete(mpMusicHandler);

		Log("--------------------------------------------------------\n\n");
	}

	//-----------------------------------------------------------------------

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHODS
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

	void cSound::Update(float afTimeStep)
	{
		mpSoundHandler->Update(afTimeStep);
		mpMusicHandler->Update(afTimeStep);

		mpLowLevelSound->UpdateSound(afTimeStep);
	}

	//-----------------------------------------------------------------------

	void cSound::Init(	cResources *apResources, bool abUseHardware, bool abForceGeneric, bool abUseEnvAudio, int alMaxChannels,
						int alStreamUpdateFreq, bool abUseThreading, bool abUseVoiceManagement,
						int alMaxMonoSourceHint, int alMaxStereoSourceHint,
						int alStreamingBufferSize, int alStreamingBufferCount, bool abEnableLowLevelLog, tString asDeviceName)
	{
		mpResources = apResources;

		Log("Initializing Sound Module\n");
		Log("--------------------------------------------------------\n");

		mpLowLevelSound->Init(	abUseHardware, abForceGeneric, abUseEnvAudio, alMaxChannels, alStreamUpdateFreq, abUseThreading,
								abUseVoiceManagement, alMaxMonoSourceHint, alMaxStereoSourceHint,
								alStreamingBufferSize, alStreamingBufferCount, abEnableLowLevelLog, asDeviceName);

		mpSoundHandler = hplNew( cSoundHandler, (mpLowLevelSound, mpResources) );
		mpMusicHandler = hplNew( cMusicHandler, (mpLowLevelSound, mpResources) );

		Log("--------------------------------------------------------\n\n");
	}

	//-----------------------------------------------------------------------

}
