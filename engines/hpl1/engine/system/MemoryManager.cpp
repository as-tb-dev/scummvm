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

#include "hpl1/engine/system/MemoryManager.h"

#include "hpl1/engine/system/LowLevelSystem.h"

namespace hpl {


	tAllocatedPointerMap cMemoryManager::m_mapPointers;
	size_t cMemoryManager::mlTotalMemoryUsage=0;
	bool cMemoryManager::mbLogDeletion = false;
	bool cMemoryManager::mbLogCreation = false;
	int cMemoryManager::mlCreationCount =0;

	//////////////////////////////////////////////////////////////////////////
	// ALLOCATED POINTER
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

	cAllocatedPointer::cAllocatedPointer(void *apData,const std::string &asFile, int alLine, size_t alMemory)
	{
		mpData = apData;
		msFile = asFile;
		mlLine = alLine;
		mlMemory = alMemory;
	}


	//-----------------------------------------------------------------------

	//////////////////////////////////////////////////////////////////////////
	// PUBLIC METHODS
	//////////////////////////////////////////////////////////////////////////

	//-----------------------------------------------------------------------

	void* cMemoryManager::AddPointer(const cAllocatedPointer& aAllocatedPointer)
	{
		m_mapPointers.insert(tAllocatedPointerMap::value_type(aAllocatedPointer.mpData,aAllocatedPointer));
		mlTotalMemoryUsage += aAllocatedPointer.mlMemory;

		if(mbLogCreation)
		{
			//Log("Creation at: %s, line %d\n",aAllocatedPointer.msFile.c_str(),aAllocatedPointer.mlLine);
			mlCreationCount++;
		}

		return aAllocatedPointer.mpData;
	}
	//-----------------------------------------------------------------------

	bool cMemoryManager::RemovePointer(void *apData)
	{
		bool bFound=false;
		tAllocatedPointerMapIt it = m_mapPointers.upper_bound(apData);
		it--;
		if(it != m_mapPointers.end())
		{
			char* apTest = (char*)it->second.mpData;
			size_t testSize = it->second.mlMemory;
			if(apData >= apTest && apData < apTest + testSize) bFound = true;
		}


		if(bFound==false)
		{
			Warning("Trying to delete pointer %d created that does not exist!\n",apData);
			return false;
		}


		mlTotalMemoryUsage -= it->second.mlMemory;

		m_mapPointers.erase(it);

		return true;
	}

	//-----------------------------------------------------------------------

	void cMemoryManager::LogResults()
	{
		Log("\n|--Memory Manager Report-------------------------------|\n");
		Log("|\n");

		if(m_mapPointers.empty())
		{
			Log("| No memory leaks detected. Memory left: %d\n",mlTotalMemoryUsage);
		}
		else
		{
			Log("| Memory leaks detected: \n");
			Log("|\n");

			Log("| address\t file");

			//Get max length of file name
			int lMax =0;
			tAllocatedPointerMapIt it = m_mapPointers.begin();
			for(; it != m_mapPointers.end();++it){
				cAllocatedPointer &ap = it->second;
				if((int)ap.msFile.length() > lMax) lMax = (int)ap.msFile.length();
			}

			lMax += 5;

			for(int i=0; i<lMax-4; ++i) Log(" ");


			Log("line\t\t memory usage\t  \n");

			Log("|------------------------------------------------------------\n");

			it = m_mapPointers.begin();
			for(; it != m_mapPointers.end();++it)
			{
				cAllocatedPointer &ap = it->second;
				Log("| %d\t %s",ap.mpData, ap.msFile.c_str());
				for(int i=0; i<lMax - (int)ap.msFile.length(); ++i) Log(" ");
				Log("%d\t\t %d\t\n", ap.mlLine, ap.mlMemory);
			}
		}
		Log("|\n");
		Log("|------------------------------------------------------|\n\n");

	}

	//-----------------------------------------------------------------------

	void cMemoryManager::SetLogCreation(bool abX)
	{
		mbLogCreation = abX;
	}

	//-----------------------------------------------------------------------


}
