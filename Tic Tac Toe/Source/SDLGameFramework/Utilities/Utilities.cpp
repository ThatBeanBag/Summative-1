// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: Utilities.cpp
// Desrciption	: Several useful ultilies implementation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "GameStd.h"

// Library Includes

// This Include
#include "Utilities.h"

// Local Includes

int GetRandomNumber(int _iMin, int _iMax)
{
	// dRand is between 0 and 1.
	double dRand = rand()/static_cast<double>(RAND_MAX + 1);

	// linearly distribute dRand on min, max.
	int iRand = _iMin + static_cast<int>(dRand * (_iMax - _iMin));

	return iRand;
}