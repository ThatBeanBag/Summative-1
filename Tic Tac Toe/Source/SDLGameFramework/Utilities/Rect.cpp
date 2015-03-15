// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: Rect.cpp
// Desrciption	: CRect implementation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "GameStd.h"

// Library Includes

// This Include
#include "Rect.h"

// Local Includes

CRect::CRect()
	:m_iX(0),
	m_iY(0),
	m_iWidth(0),
	m_iHeight(0)
{

}

CRect::CRect(int _iX, int _iY, int _iW, int _iH)
	:m_iX(_iX),
	m_iY(_iY),
	m_iWidth(_iW),
	m_iHeight(_iH)
{

}

CRect::CRect(const CRect& _krRect)
	:m_iX(_krRect.m_iX),
	m_iY(_krRect.m_iY),
	m_iWidth(_krRect.m_iWidth),
	m_iHeight(_krRect.m_iHeight)
{

}

CRect& CRect::operator=(const CRect& _krRect)
{
	m_iX = _krRect.m_iX;
	m_iY = _krRect.m_iY;
	m_iWidth = _krRect.m_iWidth;
	m_iHeight = _krRect.m_iHeight;

	return *this;
}

bool CRect::operator==(const CRect& _krRect) const
{
	return m_iX == _krRect.m_iX && 
		   m_iY == _krRect.m_iY &&
		   m_iWidth == _krRect.m_iWidth &&
		   m_iHeight == _krRect.m_iHeight;
}

bool CRect::operator!=(const CRect& _krRect) const
{
	return !(*this == _krRect);
}

int CRect::GetLeft() const
{
	return m_iX;
}

int CRect::GetRight() const
{
	return m_iX + m_iWidth;
}

int CRect::GetTop() const
{
	return m_iY;
}

int CRect::GetBottom() const
{
	return m_iY + m_iHeight;
}

bool IsIntersecting(const CRect& _krRectA, const CRect& _krRectB)
{
	// Are the sides of _krRectA outside _krRectB. 
	if(_krRectA.m_iY + _krRectA.m_iHeight <= _krRectB.m_iY) {
		return false;
	}
	else if(_krRectA.m_iY >= _krRectB.m_iY + _krRectB.m_iHeight) {
		return false;
	}
	else if(_krRectA.m_iX + _krRectA.m_iWidth <= _krRectB.m_iX) {
		return false;
	}
	else if(_krRectA.m_iX >= _krRectB.m_iX + _krRectB.m_iWidth) {
		return false;
	}
	else {
	// There's an overlap.
		return true;
	}

	// We passed the test.
	return true;
}

bool IsInside(const CRect& _krRectA, const CRect& _krRectB)
// Is _krRectA inside _krRectB
{
	// Are any of the sides of _krRectA outside _krRectB. 
	if(_krRectA.m_iY + _krRectA.m_iHeight > _krRectB.m_iY + _krRectB.m_iY) {
		return false;
	}
	else if(_krRectA.m_iY < _krRectB.m_iY) {
		return false;
	}
	else if(_krRectA.m_iX + _krRectA.m_iWidth > _krRectB.m_iX + _krRectB.m_iWidth) {
		return false;
	}
	else if(_krRectA.m_iX < _krRectB.m_iX) {
		return false;
	}
	else {
	// A is inside B.
		return true;
	}

	// We passed the test.
	return true;
}

bool IsPointInside(const CRect& _krRect, const CPoint& _krPoint)
{
	if (_krPoint.m_iX < _krRect.m_iX) {
	// _krPoint is outside on the left.
		return false;
	}
	else if (_krPoint.m_iX > _krRect.m_iX + _krRect.m_iWidth) {
	// _krPoint is outside on the right.
		return false;
	}
	else if (_krPoint.m_iY < _krRect.m_iY) {
	// _krPoint is outside on the top.
		return false;
	}
	else if (_krPoint.m_iY > _krRect.m_iY + _krRect.m_iHeight) {
	// _krPoint is outside on the bottom.
		return false;
	}
	else {
	// _krPoint is inside.
		return true;
	}

	return true;
}
