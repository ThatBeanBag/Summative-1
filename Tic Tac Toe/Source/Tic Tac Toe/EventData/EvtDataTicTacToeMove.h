// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: EventData.h
// Desrciption	: CIEventData declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef __EVTDATATICTACTOEMOVE_H__
#define __EVTDATATICTACTOEMOVE_H__

// Library Includes

// Local Includes
#include "../BoardState.h"

class CEvtDataTicTacToe : public CIEventData {
	// Member Functions
public:
	CEvtDataTicTacToe(int _iMove, EPlayer _ePlayer);
	~CEvtDataTicTacToe();

	virtual std::type_index VGetTypeIndex();

	int GetMove() const;
	EPlayer GetPlayer() const;
protected:
private:

	// Member Variables
public:
protected:
private:
	int m_iMove;		// The move itself.
	EPlayer m_ePlayer;	// The player to put on the board.
};

#endif // __EVTDATATICTACTOEMOVE_H__