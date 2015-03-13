#pragma once

#ifndef __LINE_H__
#define __LINE_H__

class BadIntersection {
public:
	enum EError {
		NO_INTERSECTION,
		INF_INTERSECTIONS
	};

	// Member Functions
public:
	BadIntersection(EError _eError);

	// Member Variables
public:
	EError m_eError;
};

class CLine {
	// Member Functions
public:
	// Constructors
	CLine(const CPoint& _krPoint1, const CPoint& _krPoint2);
	CLine(const CLine& _krLine);
	
	// Assignment operator.
	CLine& operator=(const CLine& _krLine);

	CPoint GetPoint1() const;
	CPoint GetPoint2() const;

	void SetPoint1(const CPoint& _krPoint);
	void SetPoint1(int _iX, int _iY);
	void SetPoint2(const CPoint& _krPoint);
	void SetPoint2(int _iX, int _iY);


protected:
private:

	// Member Variables
public:
protected:
private:
	CPoint m_point1;
	CPoint m_point2;
};

CPoint GetIntersection(const CLine& _krLine1, const CLine& _krLine2, CPoint& _krIntersection);

#endif