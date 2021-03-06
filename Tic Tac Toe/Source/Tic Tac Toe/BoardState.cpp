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
#include <algorithm>

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

CBoardState::CBoardState(const CBoardState& _krBoardState)
{
	// Just call the assignment operator to eliminate code duplication.
	*this = _krBoardState;
}

CBoardState::~CBoardState()
{

}

CBoardState& CBoardState::operator=(const CBoardState& _krBoardState)
{
	// Copy all the elements in the board over.
	for (int i = 0; i < s_kiBOARD_SIZE; ++i) {
		m_eBoard[i] = _krBoardState[i];
	}

	return *this;
}

const EPlayer& CBoardState::operator[](int _iBoardPosition) const
{
	// Do out of bounds error checking.
	if (_iBoardPosition < 0 || _iBoardPosition >= s_kiBOARD_SIZE) {
		// Just assert. Really this should throw an exception or provide some other more
		// elegant solution, but for now an assertion will suffice.
		assert(false);
	}


	return m_eBoard[_iBoardPosition];
}

EPlayer& CBoardState::operator[](int _boardPosition)
{
	// Call const version of operator[], by adding constness to *this's type.
	const EPlayer& constPlayer = static_cast<const CBoardState&>(*this)[_boardPosition];

	// Cast away constness from const operator[]'s return type.
	return const_cast<EPlayer&>(constPlayer);

	// Calling the const version of this operator avoids code duplication, which allows this
	// code to be easily maintained and debugged. Since we only need to maintain/debug the const 
	// version of the operator.
}

EPlayer CBoardState::GetWinner() const
{
	// Call the static member function on the board avoiding code duplication.
	return GetWinner(m_eBoard);
}

bool CBoardState::GetWinPositions(int _iWinPositions[s_kiBOARD_COL]) const
{
	// Call the static private version of this function to avoid code duplication.
	return GetWinPositions(_iWinPositions, m_eBoard);
}

bool CBoardState::IsAWinPosition(int _iBoardPosition) const
{
	int iWinPositions[s_kiBOARD_COL];	// Array to store the win positions.

	// Define all iWinPositions values to an out of bounds value so that
	// they can be accurately compared with _iBoardPosition in the event
	// that there is no winner with this board.
	for (int i = 0; i < s_kiBOARD_COL; ++i) {
		iWinPositions[i] = -1;
	}

	if (!GetWinPositions(iWinPositions)) {
	// Is there currently no winner?
		// Return not a win position, as there is no winner on this board state.
		return false;
	}

	// Loop through all the win positions.
	for (int i = 0; i < s_kiBOARD_COL; ++i) {
		if (iWinPositions[i] == _iBoardPosition) {
			return true;
		}
		else {
			// Continue.
		}
	}

	// Return not a win position.
	return false;
}

bool CBoardState::IsFull() const
{
	// Call the static member function on the board avoiding code duplication.
	return IsFull(m_eBoard);
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

void CBoardState::MinMaxMove(EPlayer _ePlayer, float _fChanceOfRandomMove)
{
	//AlphaBetaMove(_ePlayer, _fChanceOfRandomMove);
	//return;

	// We can optimize this in such a way that the first move is hard coded.
	// The first move will always take ~9 times the amount of the second move.
	// Thus hard coding this one move will provide a significant optimization.
	// To win the first move will always be in a corner no matter what, it
	// doesn't matter which corner (any will do).

	// Get a random number between 0 and 1.
	double dRand = rand() / static_cast<double>(RAND_MAX + 1);

	if (dRand < _fChanceOfRandomMove) {
		PerformRandomMove(_ePlayer);
	}
	else {
		int iScore = -2;	// Losing is better than not making a move.
		int iMove = -1;

		for (int i = 0; i < s_kiBOARD_SIZE; ++i) {
			if (m_eBoard[i] == eBLANK) {
				// Is this space empty?
				EPlayer eNext;	// The player who will player after this move.

				if (_ePlayer == eNAUGHT) {
					eNext = eCROSS;
				}
				else if (_ePlayer == eCROSS) {
					eNext = eNAUGHT;
				}
				else {
					// There is no blank player, thus we need no make a move.
					assert(false); // We should never get to this branch, a eBLANK has been passed.
					return;
				}

				m_eBoard[i] = _ePlayer;

				int iAttemptScore = -MinMax(m_eBoard, eNext);

				if (iAttemptScore > iScore) {
					iScore = iAttemptScore;
					iMove = i;
				}

				// Reset the state back to blank after attempt.
				m_eBoard[i] = eBLANK;
			}
		}

		m_eBoard[iMove] = _ePlayer;
	}
}

void CBoardState::AlphaBetaMove(EPlayer _ePlayer, float _fChanceOfRandomMove)
{
	// We can optimize this in such a way that the first move is hard coded.
	// The first move will always take ~9 times the amount of the second move.
	// Thus hard coding this one move will provide a significant optimization.
	// To win the first move will always be in a corner no matter what, it
	// doesn't matter which corner (any will do).

	// Get a random number between 0 and 1.
	double dRand = rand() / static_cast<double>(RAND_MAX + 1);

	if (dRand < _fChanceOfRandomMove) {
		PerformRandomMove(_ePlayer);
	}
	else {
		int iAlpha = static_cast<int>(eNAUGHT) - 1;
		int iBeta = static_cast<int>(eCROSS) + 1;
		int iMove = -1;

		if (_ePlayer == eCROSS) {
			// Maximum player.
			int iScore = static_cast<int>(eNAUGHT) - 1;	// Effectively -infinity.

			for (int i = 0; i < s_kiBOARD_SIZE; ++i) {
				if (m_eBoard[i] == eBLANK) {
					// Is this space empty?

					// Perform the move on the next board state.
					m_eBoard[i] = _ePlayer;

					iScore = MinMaxAlphaBeta(m_eBoard, iAlpha, iBeta, eNAUGHT);

					if (iScore > iAlpha) {
						iMove = i;

						iAlpha = iScore;
					}

					// Reset the state back to blank after attempt.
					m_eBoard[i] = eBLANK;

					if (iBeta <= iAlpha) {
						// B cut-off.
						break;
					}
				}
			}
		}
		else if (_ePlayer == eNAUGHT) {
			// Minimizing player.
			int iScore = static_cast<int>(eCROSS) + 1; // Effectively infinity.

			for (int i = 0; i < s_kiBOARD_SIZE; ++i) {
				if (m_eBoard[i] == eBLANK) {
					// Is this space empty?

					// Perform the move on the next board state.
					m_eBoard[i] = _ePlayer;

					iScore = MinMaxAlphaBeta(m_eBoard, iAlpha, iBeta, eCROSS);

					if (iScore < iBeta) {
						iMove = i;
						iBeta = iScore;
					}

					// Reset the state back to blank after attempt.
					m_eBoard[i] = eBLANK;

					if (iBeta <= iAlpha) {
						// A cut-off.
						break;
					}
				}
			}
		}

		m_eBoard[iMove] = _ePlayer;
	}
}

bool CBoardState::PerformRandomMove(EPlayer _ePlayer)
{
	if (IsFull()) {
	// The board is full we can't make a move here.
		return false;
	}

	std::vector<int> vecMovesLeft;

	// Get all the moves the left to be made.
	for (int i = 0; i < s_kiBOARD_SIZE; ++i) {
		if (m_eBoard[i] == eBLANK) {
			vecMovesLeft.push_back(i);
		}
	}

	// Get a random move.
	int iRandomMove = GetRandomNumber(0, vecMovesLeft.size());

	// Make that move.
	m_eBoard[vecMovesLeft[iRandomMove]] = _ePlayer;

	return true;
}

void CBoardState::PrintToConsole()
{
	std::cout << "+---+---+---+" << std::endl;

	for (int i = 0; i < s_kiBOARD_COL; ++i) {
		for (int j = 0; j < s_kiBOARD_COL; ++j) {
			EPlayer ePlayer = m_eBoard[i * s_kiBOARD_COL + j];
			char cPlayer = ' ';

			// Convert the Player into a character to display.
			if (ePlayer == eCROSS) {
				cPlayer = 'X';
			}
			else if (ePlayer == eNAUGHT) {
				cPlayer = 'O';
			}
			else {
				cPlayer = ' ';
			}

			// Print the character.
			std::cout << "| " << cPlayer << " ";
		}
		std::cout << "|" << std::endl;
		std::cout << "+---+---+---+" << std::endl;
	}
}

int CBoardState::MinMax(EPlayer _eBoard[s_kiBOARD_SIZE], EPlayer _ePlayer)
{
	EPlayer eWinner = GetWinner(_eBoard);

	if (eWinner != eBLANK) {
		return static_cast<int>(_ePlayer * eWinner);
	}
	else if (IsFull(_eBoard)) {
	// The board is full and there is no winner. This means it's a draw.
		// Return the score corresponding to a draw (0).
		return static_cast<int>(eBLANK);
	}
	else {
		int iScore = -2;	// Not making a move is worse than losing.

		for (int i = 0; i < s_kiBOARD_SIZE; ++i) {
			if (_eBoard[i] == eBLANK) {
			// Is this space empty?
				EPlayer eNext;	// The player who will player after this move.

				if (_ePlayer == eNAUGHT) {
					eNext = eCROSS;
				}
				else if (_ePlayer == eCROSS) {
					eNext = eNAUGHT;
				}
				else {
					// There is no blank player, thus we need no make a move.
					assert(false);	// We should never get to this branch, a eBLANK has been passed.
					return iScore;
				}

				// Perform the move on the next board state.
				_eBoard[i] = _ePlayer;

				int iAttemptScore = -MinMax(_eBoard, eNext);

				if (iAttemptScore > iScore) {
					iScore = iAttemptScore;
				}

				// Reset the state back to blank after attempt.
				_eBoard[i] = eBLANK;
			}
		}

		return iScore;
	}
}

int CBoardState::MinMaxAlphaBeta(EPlayer _eBoard[s_kiBOARD_SIZE], int _iAlpha, int _iBeta, EPlayer _ePlayer)
{
	EPlayer eWinner = GetWinner(_eBoard);

	if (eWinner != eBLANK) {
		return static_cast<int>(eWinner);
	}
	else if (IsFull(_eBoard)) {
		// The board is full and there is no winner. This means it's a draw.
		// Return the score corresponding to a draw (0).
		return static_cast<int>(eBLANK);
	}
	else {
		if (_ePlayer == eCROSS) {
			// Maximum player.

			int iScore = static_cast<int>(eNAUGHT) - 1;	// Effectively -infinity.

			for (int i = 0; i < s_kiBOARD_SIZE; ++i) {
				if (_eBoard[i] == eBLANK) {
					// Is this space empty?

					// Perform the move on the next board state.
					_eBoard[i] = _ePlayer;

					iScore = MinMaxAlphaBeta(_eBoard, _iAlpha, _iBeta, eNAUGHT);

					_iAlpha = std::max(iScore, _iAlpha);

					// Reset the state back to blank after attempt.
					_eBoard[i] = eBLANK;

					if (_iBeta <= _iAlpha) {
						// B cut-off.
						break;
					}
				}
			}

			return iScore;
		}
		else if (_ePlayer == eNAUGHT) {
		// Minimizing player.
			int iScore = static_cast<int>(eCROSS) + 1; // Effectively infinity.

			for (int i = 0; i < s_kiBOARD_SIZE; ++i) {
				if (_eBoard[i] == eBLANK) {
					// Is this space empty?

					// Perform the move on the next board state.
					_eBoard[i] = _ePlayer;

					iScore = MinMaxAlphaBeta(_eBoard, _iAlpha, _iBeta, eCROSS);

					_iBeta = std::min(iScore, _iBeta);

					// Reset the state back to blank after attempt.
					_eBoard[i] = eBLANK;

					if (_iBeta <= _iAlpha) {
						// A cut-off.
						break;
					}
				}
			}

			return iScore;
		}
	}
}

EPlayer CBoardState::GetWinner(const EPlayer _eBoard[s_kiBOARD_SIZE])
{
	int iWinPositions[s_kiBOARD_SIZE];	// Array to store the win positions.

	if (GetWinPositions(iWinPositions, _eBoard)) {
	// Is there are winner?
		// Return the player at the first win position.
		return _eBoard[iWinPositions[0]];
	}
	else {
	// There's no winner.
		// Return eBLANK as a default return value.
		return eBLANK;
	}

	return eBLANK;
}

bool CBoardState::GetWinPositions(int _iWinPositions[s_kiBOARD_COL], const EPlayer _eBoard[s_kiBOARD_SIZE])
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
		if (_eBoard[_iWins[i][0]] != eBLANK) {
			// This is not a blank.
			bool bHasWon = true;

			// Check the rest in the row.
			for (int j = 0; j < s_kiBOARD_COL; ++j) {
				if (_eBoard[_iWins[i][0]] != _eBoard[_iWins[i][j]]) {
					bHasWon = false;

					break;
				}
			}

			if (bHasWon) {
				// Copy the wins into the _iWinPositions.
				for (int j = 0; j < s_kiBOARD_COL; ++j) {
					_iWinPositions[j] = _iWins[i][j];
				}

				return true;
			}
		}
	}

	// No-one is the winner yet.
	return false;
}

bool CBoardState::IsFull(const EPlayer _keBoard[s_kiBOARD_SIZE])
{
	for (int i = 0; i < s_kiBOARD_SIZE; ++i) {
		if (_keBoard[i] == eBLANK) {
			// A spot on this board is blank.
			// Return not full.
			return false;
		}
	}

	// Return full.
	return true;
}