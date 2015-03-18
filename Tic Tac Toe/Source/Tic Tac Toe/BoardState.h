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
//
// The board is stored contiguously in memory with a size of N * N.
//
// You can imagine a 3 x 3 board like so:
// 
// +---+---+---+
// | 0 | 1 | 2 |
// +---+---+---+
// | 3 | 4 | 5 |
// +---+---+---+
// | 6 | 7 | 8 |
// +---+---+---+
//
// ======================================================================

class CBoardState {
	// Static members.
public:
	static const int s_kiBOARD_COL = 3;
	static const int s_kiBOARD_SIZE = s_kiBOARD_COL * s_kiBOARD_COL;

	// Member Functions
public:
	CBoardState();
	CBoardState(const CBoardState& _krBoardState);

	~CBoardState();

	CBoardState& operator=(const CBoardState& _krBoardState);

	const EPlayer& operator[](int _iBoardPosition) const;
	EPlayer& operator[](int _iBoardPosition);

	// Returns the winner, if there is one. If there is no winner this will return a blank.
	EPlayer GetWinner() const;

	// Returns true if the board has no empty or blank slots, false otherwise.
	bool IsFull() const;

	// Places a move only if the space is eBLANK and _iBoardPosition is within bounds.
	EInvalidMove AttemptMove(int _iBoardPosition, EPlayer _ePlayer);

	// Forces a move regardless if it's occuppied. Will fail if _iBoardPosition is out of bounds.
	EInvalidMove ForceMove(int _iBoardPosition, EPlayer _ePlayer);

	// Finds and makes the best possible move for the given player
	// _fChanceOfRandomMove defines the chance, in decimal form, for MinMaxMove() to choose randomly
	// instead of picking the best possible move. If _fChanceOfRandomMove >= 1 this will always
	// make a random move.
	void MinMaxMove(EPlayer _ePlayer, float _fChanceOfRandomMove = 0);

	// Makes a psuedo-random move for the given player if the board is not full, otherwise it will
	// just return false.
	bool PerformRandomMove(EPlayer _ePlayer);

	// Prints the tic tac toe board to the console. Useful for quick debugging.
	void PrintToConsole();

protected:
private:
	// These next three functions are made static as they do not manipulate or call on any 
	// non-static member variables/functions. They are merely here to restrict their use to only
	// from within the CBoardState class. 
	//
	// They're main purpose is in the optimization of MinMax() algorithm.

	// Returns the score of the _krBoard state for the given _ePlayer.
	static int MinMax(EPlayer _eBoard[s_kiBOARD_SIZE], EPlayer _ePlayer);

	static int MinMaxAlphaBeta(EPlayer _eBoard[s_kiBOARD_SIZE], int _iAlpha, int _iBeta, EPlayer _ePlayer);

	// Returns the winner, if there is one. If there is no winner this will return a blank.
	static EPlayer GetWinner(const EPlayer _eBoard[s_kiBOARD_SIZE]);

	// Returns true if the board has no empty or blank slots, false otherwise.
	static bool IsFull(const EPlayer _eBoard[s_kiBOARD_SIZE]);

	// Member Variables
public:
protected:
private:
	EPlayer m_eBoard[s_kiBOARD_SIZE];	// The actual representation of the board.
};

#endif	// __BOARDSTATE_H__