// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2015 Media Design School
//
// File Name	: main.cpp
// Desrciption	: main implementation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// Library Includes
#include <iostream>

// Local Includes
#include "NimBoard.h"

using namespace std;

void PlayerMove(CNimBoard& _rBoard)
{
	while (true) {
		cout << "It's your turn, please enter a stack followed by an amount to split by: ";

		int iStack = 0;
		int iAmount = 0;

		cin >> iStack;
		cin >> iAmount;

		EInvalidMove eError = _rBoard.AttemptMove(iStack, iAmount);

		if (eError == eOUT_OF_BOUNDS) {
			cout << "That stack you have entered is not valid." << endl;
		}
		else if (eError == eAMOUNT_TOO_HIGH) {
			cout << "The amount you have entered cannot be used to split the stack." << endl;
		}
		else if (eError == eAMOUNT_NEGATIVE) {
			cout << "The amount you have entered is a negative and not valid." << endl;
		}
		else if (eError == eLOSS) {
			cout << "The move you have entered will result in a loss." << endl;
		}
		else {
			// Valid
			break;
		}
	}
}

int main()
{
	CNimBoard nimBoard(7);

	nimBoard.PrintToConsole();

	while (true) {
		PlayerMove(nimBoard);

		nimBoard.PrintToConsole();
		cout << endl;

		if (nimBoard.NoMoreMoves()) {
			cout << "You Win!" << endl;
			break;
		}

		nimBoard.MinMaxMove();

		nimBoard.PrintToConsole();
		cout << endl;

		if (nimBoard.NoMoreMoves()) {
			cout << "You Lose!" << endl;
			break;
		}

	}

	int iTemp; 
	cin >> iTemp;

	return 0;
}