// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2015 Media Design School
//
// File Name	: BoardState.cpp
// Desrciption	: CBoardState implementation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "TicTacToeStd.h"

// Library Includes

// This Include
#include "BoardState.h"

// Local Includes

const int CBoardState::s_kiBOARD_COL;
const int CBoardState::s_kiBOARD_SIZE;

CBoardState::CBoardState()
{
	// Fill the board with blanks.
	for (int i = 0; i < s_kiBOARD_SIZE; ++i) {
		m_eBoard[i] = eBLANK;
	}
}

CBoardState::~CBoardState()
{

}

EPlayer CBoardState::GetWinner()
{
	// For an N x N board the total win board position configurations are 2N + 2. 
	// This is determined by 1 for each column, 1 for each row and the two diagonals.
	const int iNumOfWins = 2 * s_kiBOARD_COL + 2;	// The total number of winning combinations.

	int _iWins[iNumOfWins][s_kiBOARD_COL];	// An array of all the winning combinations.

	// Fill the array of winning configurations.
	for (int i = 0; i < s_kiBOARD_COL; ++i) {
		for (int j = 0; j < s_kiBOARD_COL; ++j) {
			// Collumn win combinations.
			_iWins[i][j] = j * s_kiBOARD_COL + i;

			// Row win combinations.
			_iWins[i + s_kiBOARD_COL][j] = i * s_kiBOARD_COL + j;
		}
	}

	// Diagonal winning combinations.
	for (int i = 0; i < s_kiBOARD_COL; ++i) {
		_iWins[2 * s_kiBOARD_COL + 1][i] = i * s_kiBOARD_COL + i;		// Left diagonal
		_iWins[2 * s_kiBOARD_COL][i] = (i + 1) * (s_kiBOARD_COL - 1);	// Right diagonal
	}

	// Check each combinations and see if a player fully occupies one.
	for (int i = 0; i < iNumOfWins; ++i) {
		if (m_eBoard[_iWins[i][0]] != eBLANK) {
		// This is not a blank.
			bool bHasWon = true;

			// Check the rest in the row.
			for (int j = 0; j < s_kiBOARD_COL; ++j) {
				if (m_eBoard[_iWins[i][0]] != m_eBoard[_iWins[i][j]]) {
					bHasWon = false;

					break;
				}
			}

			if (bHasWon) {
				return m_eBoard[_iWins[i][0]];
			}
		}
	}

	// No-one is the winner yet.
	return eBLANK;
}

bool CBoardState::IsFull()
{
	for (int i = 0; i < s_kiBOARD_SIZE; ++i) {
		if (m_eBoard[i] == eBLANK) {
		// A spot on this board is blank.
			// Return not full.
			return false;
		}
	}

	// Return full.
	return true;
}

EInvalidMove CBoardState::AttemptMove(int _iBoardPosition, EPlayer _ePlayer)
{
	// Check if _iBoardPosition is in bounds.
	if (_iBoardPosition >= 0 && _iBoardPosition < s_kiBOARD_SIZE) {
		// Check is the space is free to use.
		if (m_eBoard[_iBoardPosition] == eBLANK) {
		// The move is valid.
			// Make the move.
			m_eBoard[_iBoardPosition] = _ePlayer;

			return eVALID;
		}
		else {
		// This space is already occupied.
			return eALREADY_OCCUPIED;
		}
	}
	else {
	// _iBoardPosition is out of bounds.
		return eOUT_OF_BOUNDS;
	}

	return eVALID;
}

EInvalidMove CBoardState::ForceMove(int _iBoardPosition, EPlayer _ePlayer)
{
	// Check if _iBoardPosition is in bounds.
	if (_iBoardPosition >= 0 && _iBoardPosition < s_kiBOARD_SIZE) {
	// _iBoardPosition is in bound.
		// Make the move.
		m_eBoard[_iBoardPosition] = _ePlayer;

		return eVALID;
	}
	else {
		// _iBoardPosition is out of bounds.
		return eOUT_OF_BOUNDS;
	}

	return eVALID;
}