
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

#ifndef BAGEL_BAGLIB_GUI_FMOVIE_H
#define BAGEL_BAGLIB_GUI_FMOVIE_H

#include "bagel/boflib/boffo.h"
#include "bagel/boflib/gui/dialog.h"
#include "bagel/boflib/timer.h"
#include "bagel/boflib/rect.h"
#include "bagel/boflib/error.h"
#include "bagel/boflib/object.h"
#include "bagel/boflib/gfx/palette.h"
#include "bagel/boflib/llist.h"
#include "bagel/baglib/gui/storage_dev_win.h"
#include "bagel/api/smacker.h"

namespace Bagel {

#define BUFFER_LENGTH 254

class CBagFMovie : public CBofDialog {
public:
	enum MVSTATUS { STOPPED, PAUSED, FOREWARD, REVERSE };
	enum MVTYPE { QT, SMACKER };
	// BOOL 			m_bReverseWait;		// removed the need for the timer mdm 8/4
protected:
	// CBofTimer 	*	m_pMovTimer;	 	// removed the need for the timer mdm 8/4
#if BOF_WINDOWS
	UINT m_wMCIDeviceID; // MCI Device ID for the QT file
#endif

	SmackBuf *m_pSbuf;
	Smack *m_pSmk;

	MVTYPE m_eMovType;
	BOOL m_bEscCanStop;
	BOOL m_bLoop;
	MVSTATUS m_eMovStatus;
#if BOF_MAC
	BOOL m_bPositioned;
#endif
	CBofBitmap *m_pBmpBuf;
	CBofBitmap *m_pFilterBmp;
	CBofPalette *m_pSmackerPal;
	char *m_pBufferStart;
	int m_nBufferLength;
	uint32 m_nReversed;
	CBofRect m_xBounds;
	BOOL m_bUseNewPalette;
	BOOL m_bBlackOutWindow; // jwl 1.22.97 Used to avoid palette shift land

	virtual ERROR_CODE Initialize(CBofWindow *pParent); // Initialize

	virtual BOOL OpenMovie(const char *sFilename); // MCI_OPEN
	virtual VOID CloseMovie(VOID);

	virtual BOOL FileOpenWin(); // Display the File Open Dialog box

	virtual VOID OnReSize(CBofSize *pSize);

	virtual BOOL Play();
	virtual BOOL Reverse();

	// virtual VOID 	OnMouseMove(UINT nFlags, CBofPoint *pPoint){}
	virtual VOID OnLButtonUp(UINT nFlags, CBofPoint *pPoint) { OnButtonUp(nFlags, pPoint); }
	virtual VOID OnButtonUp(UINT nFlags, CBofPoint *pPoint);
	virtual VOID OnPaint(CBofRect *pRect);
	virtual VOID OnMovieDone(VOID);
	virtual VOID OnClose(VOID);
	virtual VOID OnMainLoop(VOID);
	virtual VOID OnKeyHit(ULONG lKey, ULONG lRepCount);

public:
	CBagFMovie(CBofWindow *pParent = NULL, const char *sFilename = NULL, CBofRect *pBounds = NULL, BOOL bUseNewPalette = TRUE, BOOL bBlackOutWindow = FALSE);
	~CBagFMovie();

	virtual BOOL Open(const char *sFilename = NULL, CBofRect *pBounds = NULL);

	virtual BOOL Play(BOOL bLoop, BOOL bEscCanStop = TRUE);
	virtual BOOL Reverse(BOOL bLoop, BOOL bEscCanStop = TRUE);
	virtual BOOL Pause(void);
	virtual BOOL Stop(void);

	virtual MVSTATUS Status(void) { return m_eMovStatus; }

	virtual BOOL SeekToStart(void); // Seek to the start of the movie
	virtual BOOL SeekToEnd(void);   // Seek to the start of the movie

	virtual DWORD GetFrame(void);
	virtual BOOL SetFrame(DWORD dwFrameNum);

	virtual BOOL CenterRect();

	virtual BOOL ShowMovie(void);
	virtual BOOL HideMovie(void);
	virtual HPALETTE WinPalFromSmkPal(void);

	// jwl 1.24.97 need to access members from outside of class for
	// performance optimization.
	SmackBuf *GetSmackBuffer(void) { return m_pSbuf; }
	Smack *GetSmackMovie(void) { return m_pSmk; }
#if SMACKOFFSCREEN
	CBofBitmap *GetSmackBitmap(void) { return m_pBmpBuf; }
#endif
};

} // namespace Bagel

#endif
