// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: BackBuffer.cpp
// Desrciption	: CBackBuffer implementation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//


// PCH
#include "GameStd.h"

// Library Includes

// This Include
#include "BackBuffer.h"

// Local Includes

CBackBuffer::CBackBuffer()
	:m_hWnd(0),
	m_hdcBuffer(0),
	m_hdcMem(0),
	m_hbmBuffer(0),
	m_hbmOldBuffer(0)
{
	m_screenSize = CPoint(0, 0);
}

CBackBuffer::~CBackBuffer()
{
	SelectObject(m_hdcBuffer, m_hbmOldBuffer);

	DeleteObject(m_hbmBuffer);
	DeleteObject(m_hdcBuffer);
}

bool CBackBuffer::Init(HWND _hWnd, int _iScreenWidth, int _iScreenHeight)
{
	if(!_hWnd) {
	// Invalid handle.
		// Return failed to initialize.
		return false;
	}

	m_hWnd = _hWnd;
	m_screenSize = CPoint(_iScreenWidth, _iScreenHeight);

	HDC hdcWindow = GetDC(m_hWnd);

	m_hdcBuffer = CreateCompatibleDC(hdcWindow);
	m_hbmBuffer = CreateCompatibleBitmap(hdcWindow, m_screenSize.m_iX, m_screenSize.m_iY);
	m_hdcMem = CreateCompatibleDC(NULL);

	// Release the handle to the device context of the window.
	ReleaseDC(m_hWnd, hdcWindow);

	m_hbmOldBuffer = static_cast<HBITMAP>(SelectObject(m_hdcBuffer, m_hbmBuffer));

	HBRUSH hBrushWhite = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	HBRUSH hOldBrush = static_cast<HBRUSH>(SelectObject(m_hdcBuffer, hBrushWhite));

	Rectangle(m_hdcBuffer, 0, 0, m_screenSize.m_iX, m_screenSize.m_iY);

	SelectObject(m_hdcBuffer, hOldBrush);

	// Return initialization succeeded.
	return true;
}

void CBackBuffer::Clear()
{
	// Obtain the old brush.
	HBRUSH hOldBrush = static_cast<HBRUSH>(SelectObject(m_hdcBuffer, GetStockObject(BLACK_BRUSH)));

	Rectangle(m_hdcBuffer, 0, 0, m_screenSize.m_iX, m_screenSize.m_iY);
	SelectObject(m_hdcBuffer, hOldBrush);
}

void CBackBuffer::Render()
{
	HDC hdcWindow = GetDC(m_hWnd);
	BitBlt(hdcWindow, 0, 0, m_screenSize.m_iX, m_screenSize.m_iY, m_hdcBuffer, 0, 0, SRCCOPY);

	ReleaseDC(m_hWnd, hdcWindow);
}

void CBackBuffer::UpdateScreenSize(const CPoint& _screenSize)
{
	m_screenSize = _screenSize;

	DeleteObject(m_hbmBuffer);
	DeleteObject(m_hbmOldBuffer);

	HDC hdcWindow = GetDC(m_hWnd);
	m_hbmBuffer = CreateCompatibleBitmap(hdcWindow, m_screenSize.m_iX, m_screenSize.m_iY);
	ReleaseDC(m_hWnd, hdcWindow);

	m_hbmOldBuffer = static_cast<HBITMAP>(SelectObject(m_hdcBuffer, m_hbmBuffer));
}

HDC CBackBuffer::GetDCBuffer() const
{
	return m_hdcBuffer;
}

HDC CBackBuffer::GetDCMem() const
{
	return m_hdcMem;
}
