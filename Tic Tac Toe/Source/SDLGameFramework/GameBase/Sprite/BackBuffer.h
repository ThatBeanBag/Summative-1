// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: BackBuffer.h
// Desrciption	: CBackBuffer declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef __BACKBUFFER_H__
#define __BACKBUFFER_H__

#include "../../Utilities/Point.h"

class CBackBuffer {
	// Member Functions
public:
	CBackBuffer();
	~CBackBuffer();

	bool Init(HWND _hWnd, int _iScreenWidth, int _iScreenHeight);
	void Clear();
	void Render();

	void UpdateScreenSize(const CPoint& _screenSize);

	HDC GetDCBuffer() const;
	HDC GetDCMem() const;
protected:
private:

	// Member Variables
public:
protected:
private:
	HWND m_hWnd;
	HDC m_hdcBuffer;
	HDC m_hdcMem;

	HBITMAP m_hbmBuffer;
	HBITMAP m_hbmOldBuffer;

	CPoint m_screenSize;
};

#endif