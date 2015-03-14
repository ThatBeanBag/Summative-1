// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2015 Media Design School
//
// File Name	: BoardState.h
// Desrciption	: CBoardState decleration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef __BOARDSTATE_H__
#define __BOARDSTATE_H__

// Library Includes

// Local Includes

// ======================================================================
// The EPlayer enumerator defines the different states a particular slot
// on the board can have (a naught, cross or empty/blank). 
//
// The states are assigned to corresponding score values. This is for use
// with the minmax algorithm to determine the potential score of each
// move. The values of -1, and 1 are important in that we don't know which
// player is the max and which player is the min, therefore a we can
// multiply the winner (naught, cross or no-one determined as a blank) by
// the player to retrieve a score that's in favour of the player.
//
// The blank can also be read as no-one or nothing in many situations.
// The name 'eBLANK' is less situational and thus has been used.
// ======================================================================

enum EPlayer {
	eNAUGHT = -1,
	eBLANK = 0,
	eCROSS = 1
};

// ======================================================================
// The EInvalidMove enumerator is for error checking an elegant solution
// for when the player makes an invalid move by trying to play ontop of
// an occuppied space. 
// 
// The caller of any function with an EInvalidMove return type is
// responsible for resolving the error.
// ======================================================================

enum EInvalidMove {
	eOUT_OF_BOUNDS,
	eALREADY_OCCUPIED,
	eVALID,
};

// ======================================================================
// The CBoardState class encapsulates the representation and 
// implementation of the tic tac toe board.
// ======================================================================

class CBoardState {
	// Member Functions
public:
	CBoardState();
	~CBoardState();

	// Returns the winner, if there is one. If there is no winner this will return a blank.
	EPlayer GetWinner();

	// Returns true if the board has no empty or blank slots, false otherwise.
	bool IsFull();

	// Places a move only if the space is eBLANK and _iBoardPosition is within bounds.
	EInvalidMove AttemptMove(int _iBoardPosition, EPlayer _ePlayer);

	// Forces a move regardless if it's occuppied. Will fail if _iBoardPosition is out of bounds.
	EInvalidMove ForceMove(int _iBoardPosition, EPlayer _ePlayer);

protected:
private:

	// Member Variables
public:
	static const int s_kiBOARD_COL = 3;
	static const int s_kiBOARD_SIZE = s_kiBOARD_COL * s_kiBOARD_COL;
protected:
private:
	EPlayer m_eBoard[s_kiBOARD_SIZE];	// The actual board.
};

#endif	// __BOARDSTATE_H__