// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: Rect.h
// Desrciption	: CRect declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef _RECT_H__
#define _RECT_H__

// Library Includes

// Local Includes

class CRect {
	// Member Functions
public:
	// Constructors
	CRect();
	CRect(int _iX, int _iY, int _iW, int _iH);
	CRect(const CRect& _krRect);

	// Assignments
	CRect& operator=(const CRect& _krRect);

	// Operators
	bool operator==(const CRect& _krRect) const;
	bool operator!=(const CRect& _krRect) const;

	// Acessors
	int GetLeft() const;
	int GetRight() const;
	int GetTop() const;
	int GetBottom() const;

protected:
private:

	// Member variables
public:
	int m_iX;		// x coordinate.
	int m_iY;		// y coordinate.
	int m_iWidth;	// The width.
	int m_iHeight;	// The height.
protected:
private:
};

bool IsIntersecting(const CRect& _krRectA, const CRect& _krRectB);

#endif