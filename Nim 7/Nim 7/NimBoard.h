// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2015 Media Design School
//
// File Name	: NimBoard.h
// Desrciption	: CNimBoard declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef __NIMBOARD_H__
#define __NIMBOARD_H__

// Library Includes
#include <list>

// Local Includes

enum EInvalidMove {
	eOUT_OF_BOUNDS,
	eAMOUNT_TOO_HIGH,
	eAMOUNT_NEGATIVE,
	eLOSS,
	eVALID
};

class CNimBoard {
	// Member Functions
public:
	CNimBoard(int _iStartAmount);

	~CNimBoard();

	bool NoMoreMoves() const;

	EInvalidMove AttemptMove(int _iStack, int _iAmount);
	bool MinMaxMove();

	void PrintToConsole();
protected:
private:
	static bool NoMoreMoves(const std::list<int>& _krBoard);

	static int MinMax(std::list<int>& _rBoard, bool _bIsMax);

	// Member Variables
public:
protected:
private:
	std::list<int> m_board; // The actual representation of the board.
};

#endif // __NIMBOARD_H__



