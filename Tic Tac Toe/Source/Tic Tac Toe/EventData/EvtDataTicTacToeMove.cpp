// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: EventManager.cpp
// Desrciption	: CEventManager implementation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "TicTacToeStd.h"

// Library Includes

// This Include
#include "EvtDataTicTacToeMove.h"

// Local Includes

CEvtDataTicTacToe::CEvtDataTicTacToe(int _iMove, EPlayer _ePlayer)
	:m_iMove(_iMove),
	m_ePlayer(_ePlayer)
{

}

CEvtDataTicTacToe::~CEvtDataTicTacToe()
{

}

std::type_index CEvtDataTicTacToe::VGetTypeIndex()
{
	return typeid(*this);
}

int CEvtDataTicTacToe::GetMove() const
{
	return m_iMove;
}

EPlayer CEvtDataTicTacToe::GetPlayer() const
{
	return m_ePlayer;
}