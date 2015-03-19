// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2015 Media Design School
//
// File Name	: NimBoard.cpp
// Desrciption	: CNimBoard implementation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// Library Includes
#include <iostream>
#include <assert.h>

// This Include
#include "NimBoard.h"

// Local Includes

CNimBoard::CNimBoard(int _iStartAmount)
{
	m_board.push_back(_iStartAmount);
}

CNimBoard::~CNimBoard()
{

}

bool CNimBoard::NoMoreMoves() const
{
	return NoMoreMoves(m_board);
}

EInvalidMove CNimBoard::AttemptMove(int _iStack, int _iAmount)
{
	if (_iStack < 0 || _iStack >= m_board.size()) {
	// The _iStack is not a stack on the board.
		return eOUT_OF_BOUNDS;
	}
	else if (_iAmount <= 0) {
		return eAMOUNT_NEGATIVE;
	}
	else {
		int iCurrentStack = 0;	// Tracks the iterator as an integer.

		auto iter = m_board.begin();

		for (; iter != m_board.end(); ++iter) {
			if (iCurrentStack == _iStack) {
			// We've come to the iterator pointing to the stack we want.
				break;
			}

			++iCurrentStack;
		}

		if (iter == m_board.end()) {
			return eOUT_OF_BOUNDS;
		}
		else {
			if (_iAmount >= (*iter)) {
				return eAMOUNT_TOO_HIGH;
			}
			else {
				// Set the first half of the split.
				int iSplit1 = (*iter) - _iAmount;
				int iSplit2 = _iAmount;

				if (iSplit1 == iSplit2) {
					return eLOSS;
				}

				(*iter) = iSplit1;

				// Insert the second half of the split before the first.
				m_board.insert(iter, iSplit2);
			}
		}
	}

	// If we make it here, our move was valid.
	return eVALID;
}

bool CNimBoard::MinMaxMove()
{
	if (NoMoreMoves()) {
	// We've lost.
		return false;
	}

	int iScore = INT_MIN;
	int iMoveAmount = -1;

	auto iterMove = m_board.end();
	auto iter = m_board.begin();

	for (iter; iter != m_board.end(); ++iter) {
		if (*iter != 2 && *iter != 1) {
			// Can this be split?
			for (int i = 1; i < *iter; ++i) {
				int iCurrent = *iter;

				int iSplit1 = i;
				int iSplit2 = iCurrent - i;

				if (iSplit1 >= iSplit2) {
					// We've reached the mid point.
					// All possible moves have been made.
					break;
				}
				else {
					*iter = iSplit1;
					m_board.push_back(iSplit2);

					int iAttemptMove = MinMax(m_board, false);

					if (iScore < iAttemptMove) {
					// Is attempt is greater than current score?
						iScore = iAttemptMove;
						iMoveAmount = iSplit1;
						iterMove = iter;
					}

					// Undo move.
					m_board.pop_back();
					*iter = iCurrent;
				}
			}
		}
		else {
			// Continue.
		}
	}

	assert(iterMove != m_board.end());
	assert(iMoveAmount != -1);

	std::cout << "Computer splits " << *iterMove << " to make " << (*iterMove) - iMoveAmount << " and " << iMoveAmount << std::endl;

	// Make the move.
	*iterMove = (*iterMove) - iMoveAmount;
	m_board.insert(iterMove, iMoveAmount);

	return true;
}

void CNimBoard::PrintToConsole()
{
	int iCurrentStack = 0;

	for (auto iter = m_board.begin(); iter != m_board.end(); ++iter) {
		std::cout << '[' << iCurrentStack << "] = " << *iter << std::endl;

		++iCurrentStack;
	}
}

int CNimBoard::MinMax(std::list<int>& _rBoard, bool _bIsMax)
{
	if (NoMoreMoves(_rBoard)) {
		if (_bIsMax) {
			return 0;
		}
		else {
			return 1;
		}
	}
	else {
		int iScore = 0;

		if (_bIsMax) {
			iScore = INT_MIN;
		}
		else {
			iScore = INT_MAX;
		}

		for (auto iter = _rBoard.begin(); iter != _rBoard.end(); ++iter) {
			if (*iter != 2 && *iter != 1) {
			// Can this be split?
				for (int i = 1; i < *iter; ++i) {
					int iCurrent = *iter;

					int iSplit1 = i;
					int iSplit2 = iCurrent - i;

					if (iSplit1 >= iSplit2) {
					// We've reached the mid point.
						// All possible moves have been made.
						break;
					}
					else {
						*iter = iSplit1;
						_rBoard.push_back(iSplit2);

						int iAttemptMove = MinMax(_rBoard, !_bIsMax);

						if (_bIsMax && iScore < iAttemptMove) {
						// Is maximizing and attempt is greater than current score.
							iScore = iAttemptMove;
						}
						else if (!_bIsMax && iScore > iAttemptMove) {
						// Is minimizing and attempt is smaller than current score.
							iScore = iAttemptMove;
						}
						else {
							// Do nothing.
						}

						// Undo move.
						_rBoard.pop_back();
						*iter = iCurrent;
					}
				}
			}
			else {
				// Continue.
			}
		}

		return iScore;
	}
}


bool CNimBoard::NoMoreMoves(const std::list<int>& _krBoard)
{
	for (auto iter = _krBoard.begin(); iter != _krBoard.end(); ++iter) {
		if (*iter != 2 && *iter != 1) {
			return false;
		}
	}

	return true;
}
