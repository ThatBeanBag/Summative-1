// PCH
#include "GameStd.h"

#include "Line.h"

CLine::CLine(const CPoint& _krPoint1, const CPoint& _krPoint2)
	:m_point1(_krPoint1),
	m_point2(_krPoint2)
{

}

CLine::CLine(const CLine& _krLine)
	:m_point1(_krLine.GetPoint1()),
	m_point2(_krLine.GetPoint2())
{

}

CLine& CLine::operator=(const CLine& _krLine)
{
	m_point1 = _krLine.GetPoint1();
	m_point2 = _krLine.GetPoint2();

	return *this;
}

CPoint CLine::GetPoint1() const
{
	return m_point1;
}

CPoint CLine::GetPoint2() const
{
	return m_point2;
}

void CLine::SetPoint1(const CPoint& _krPoint)
{
	m_point1 = _krPoint;
}

void CLine::SetPoint1(int _iX, int _iY)
{
	m_point1.m_iX = _iX;
	m_point1.m_iY = _iY;
}

void CLine::SetPoint2(const CPoint& _krPoint)
{
	m_point2 = _krPoint;
}

void CLine::SetPoint2(int _iX, int _iY)
{
	m_point2.m_iX = _iX;
	m_point2.m_iY = _iY;
}

CPoint GetIntersection(const CLine& _krLine1, const CLine& _krLine2)
{
	CPoint intersection;	// The point of intersection.
	float fIntersectionX = 0.0f;
	float fIntersectionY = 0.0f;

	float fM1 = 0.0f;		// Gradient of line 1.
	float fC1 = 0.0f;		// Y-Intersect of line 1.
	float fM2 = 0.0f;		// Gradient of line 2.
	float fC2 = 0.0f;		// Y-Intersect of line 2.

	int iDeltaX1 = _krLine1.GetPoint2().m_iX - _krLine1.GetPoint1().m_iX;
	int iDeltaY1 = _krLine1.GetPoint2().m_iY - _krLine1.GetPoint1().m_iY;

	int iDeltaX2 = _krLine2.GetPoint2().m_iX - _krLine2.GetPoint1().m_iX;
	int iDeltaY2 = _krLine2.GetPoint2().m_iY - _krLine2.GetPoint1().m_iY;

	if(iDeltaX1 == 0 && iDeltaX2 == 0) {
	// Both lines are vertical.
		// They may be the same line, thus have infinite intersections.
		if(_krLine1.GetPoint1().m_iX == _krLine2.GetPoint1().m_iX) {
			throw BadIntersection(BadIntersection::INF_INTERSECTIONS);
		}
		else {
			throw BadIntersection(BadIntersection::NO_INTERSECTION);
		}
	}
	else if(iDeltaX1 == 0) {
	// The first line is vertical.
		// Gradient of the second line.
		fM2 = static_cast<float>(iDeltaY2 / iDeltaX2);

		// The constant of y = mx + c for the second line.
		fC2 = _krLine2.GetPoint1().m_iY - fM1 * _krLine2.GetPoint1().m_iX;

		fIntersectionX = static_cast<float>(_krLine1.GetPoint1().m_iX);
		fIntersectionY = fM2 * fIntersectionX + fC2;
	}
	else if(iDeltaX2 == 0) {
	// The second line is vertical.
		// Gradient of the first line.
		fM1 = static_cast<float>(iDeltaY1 / iDeltaX1);

		// The constant of y = mx + c for the first line.
		fC1 = _krLine1.GetPoint1().m_iY - fM1 * _krLine1.GetPoint1().m_iX;

		fIntersectionX = static_cast<float>(_krLine2.GetPoint1().m_iX);
		fIntersectionY = fM1 * fIntersectionX + fC1;
	}
	else {
		// Gradient of the first line.
		fM1 = static_cast<float>(iDeltaY1 / iDeltaX1);

		// The constant of y = mx + c for the first line.
		fC1 = _krLine1.GetPoint1().m_iY - fM1 * _krLine1.GetPoint1().m_iX;

		// Gradient of the second line.
		fM2 = static_cast<float>(iDeltaY2 / iDeltaX2);

		// The constant of y = mx + c for the second line.
		fC2 = _krLine2.GetPoint1().m_iY - fM1 * _krLine2.GetPoint1().m_iX;

		if(fM1 == fM2) {
		// These lines are parallel.
			// They may be the same line, thus have infinite intersections.
			if(fC1 == fC2) {
				throw BadIntersection(BadIntersection::INF_INTERSECTIONS);
			}
			else {
				throw BadIntersection(BadIntersection::NO_INTERSECTION);
			}
		}

		fIntersectionX = (fC1 - fC2) / (fM2 - fM1);
		fIntersectionY = fM1 * fIntersectionX + fC1;
	}

	intersection.m_iX = static_cast<int>(fIntersectionX);
	intersection.m_iY = static_cast<int>(fIntersectionY);

	return intersection;
}



