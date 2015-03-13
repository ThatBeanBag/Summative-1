// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: Point.h
// Desrciption	: CPoint declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef _POINT_H__
#define _POINT_H__

class CPoint {
	// Member Functions
public:
	// Constructors
	CPoint();
	CPoint(int _iX, int _iY);
	CPoint(const CPoint& _krPoint);

	// Assignments
	CPoint& operator=(const CPoint& _krPoint);

	// Operators
	CPoint& operator+=(const CPoint& _krPoint);
	CPoint& operator-=(const CPoint& _krPoint);
	CPoint operator+(const CPoint& _krPoint) const;
	CPoint operator-(const CPoint& _krPoint) const;

	bool operator==(const CPoint& _krPoint) const;
	bool operator!=(const CPoint& _krPoint) const;

protected:
private:

	// Member variables
public:
	int m_iX;	// x coordinate.
	int m_iY;	// y coordinate.
protected:
private:
};

int DistanceSquared(const CPoint& _krPoint1, const CPoint& _krPoint2);

#endif