// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2015 Media Design School
//
// File Name	: TicTacToeHumanView.cpp
// Desrciption	: CTicTacToeHumanView implementation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "TicTacToeStd.h"

// Library Includes

// This Include
#include "TicTacToeHumanView.h"

// Local Includes
#include "TicTacToeLogic.h"

CTicTacToeHumanView::CTicTacToeHumanView()
{

	// Load Sprites
	m_background = g_pApp->LoadSprite("Images/BackgroundImage.png");
	m_boardButton = g_pApp->LoadSprite("Images/Buttons/Board Button.png");
	m_naughtSprite = g_pApp->LoadSprite("Images/Naught.png");
	m_crossSprite = g_pApp->LoadSprite("Images/Cross.png");

	m_boardButton.AddMask(CRect(0, 0, 160, 160));
	m_boardButton.AddMask(CRect(160, 0, 160, 160));

	int iWidth = 160;
	int iHeight = 160;
	int iOffset = 2;
	int iStartX = 73;
	int iStartY = 100;
	int iX = iStartX;
	int iY = iStartY;

	m_boardButtons.push_back(CButton(&m_boardButton, CRect(iX, iY, iWidth, iHeight), 
		                     MakeDelegate(this, &CTicTacToeHumanView::MoveTopLeft)));
	iX += iWidth + iOffset;

	m_boardButtons.push_back(CButton(&m_boardButton, CRect(iX, iY, iWidth, iHeight),
							 MakeDelegate(this, &CTicTacToeHumanView::MoveTopMiddle)));
	iX += iWidth + iOffset;

	m_boardButtons.push_back(CButton(&m_boardButton, CRect(iX, iY, iWidth, iHeight),
							 MakeDelegate(this, &CTicTacToeHumanView::MoveTopRight)));
	iX = iStartX;
	iY += iHeight + iOffset;

	m_boardButtons.push_back(CButton(&m_boardButton, CRect(iX, iY, iWidth, iHeight),
							 MakeDelegate(this, &CTicTacToeHumanView::MoveMiddleLeft)));
	iX += iWidth + iOffset;

	m_boardButtons.push_back(CButton(&m_boardButton, CRect(iX, iY, iWidth, iHeight),
							 MakeDelegate(this, &CTicTacToeHumanView::MoveMiddleMiddle)));
	iX += iWidth + iOffset;

	m_boardButtons.push_back(CButton(&m_boardButton, CRect(iX, iY, iWidth, iHeight),
							 MakeDelegate(this, &CTicTacToeHumanView::MoveMiddleRight)));
	iX = iStartX;
	iY += iHeight + iOffset;

	m_boardButtons.push_back(CButton(&m_boardButton, CRect(iX, iY, iWidth, iHeight),
							 MakeDelegate(this, &CTicTacToeHumanView::MoveBottomLeft)));
	iX += iWidth + iOffset;

	m_boardButtons.push_back(CButton(&m_boardButton, CRect(iX, iY, iWidth, iHeight),
							 MakeDelegate(this, &CTicTacToeHumanView::MoveBottomMiddle)));
	iX += iWidth + iOffset;

	m_boardButtons.push_back(CButton(&m_boardButton, CRect(iX, iY, iWidth, iHeight),
							 MakeDelegate(this, &CTicTacToeHumanView::MoveBottomRight)));

	// Computer makes first move.
	m_boardState.MinMaxMove(eNAUGHT);
}

CTicTacToeHumanView::~CTicTacToeHumanView()
{
	
}

void CTicTacToeHumanView::VUpdate(float _fDeltaTime)
{
}

void CTicTacToeHumanView::VRender(float _fDeltaTime)
{
	g_pApp->RenderSprite(m_background, 0, 0);

	for (int i = 0; i < m_boardButtons.size(); ++i) {
		if (m_boardState[i] == eBLANK) {
			m_boardButtons[i].Render();
		}
	}

	int iStartX = 73 + 35;
	int iStartY = 100 + 35;
	int iOffset = 2 + 160;


	for (int i = 0; i < CBoardState::s_kiBOARD_COL; ++i) {
		for (int j = 0; j < CBoardState::s_kiBOARD_COL; ++j) {
			CPoint position(iStartX + iOffset * i, iStartY + iOffset * j);

			if (m_boardState[i + j * CBoardState::s_kiBOARD_COL] == eNAUGHT) {
				g_pApp->RenderSprite(m_naughtSprite, position);
			}
			else if (m_boardState[i + j * CBoardState::s_kiBOARD_COL] == eCROSS) {
				g_pApp->RenderSprite(m_crossSprite, position);
			}
			else {
			}
		}
	}

	CHumanView::VRender(_fDeltaTime);
}


bool CTicTacToeHumanView::VMsgProc(const CAppMsg& _krMsg)
{
	switch (_krMsg.type) {
	case SDL_MOUSEMOTION: {
		// Update the current mouse position.		
		for (int i = 0; i < m_boardButtons.size(); ++i) {
			m_boardButtons[i].OnMouseMove(CPoint(_krMsg.x, _krMsg.y));
		}

		break;
	}

	case SDL_MOUSEBUTTONDOWN: {
		if (_krMsg.button == SDL_BUTTON_LEFT) {
		}

		break;
	}

	case SDL_MOUSEBUTTONUP: {
		if (_krMsg.button == SDL_BUTTON_LEFT) {
			for (int i = 0; i < m_boardButtons.size(); ++i) {
				m_boardButtons[i].OnRelease(m_cursorPosition);
			}
		}

		break;
	}
	default:break;
	}

	return CHumanView::VMsgProc(_krMsg);
}

// =====================================================
// Delegate Functions
// =====================================================

void CTicTacToeHumanView::MoveTopLeft()
{
	EInvalidMove eError = m_boardState.AttemptMove(0, eCROSS);

	if (eError == eVALID && !m_boardState.IsFull() && m_boardState.GetWinner() == eBLANK) {
		m_boardState.MinMaxMove(eNAUGHT);
	}
}

void CTicTacToeHumanView::MoveTopMiddle()
{
	EInvalidMove eError = m_boardState.AttemptMove(1, eCROSS);
	if (eError == eVALID && !m_boardState.IsFull() && m_boardState.GetWinner() == eBLANK) {
		m_boardState.MinMaxMove(eNAUGHT);
	}
}

void CTicTacToeHumanView::MoveTopRight()
{
	EInvalidMove eError = m_boardState.AttemptMove(2, eCROSS);
	if (eError == eVALID && !m_boardState.IsFull() && m_boardState.GetWinner() == eBLANK) {
		m_boardState.MinMaxMove(eNAUGHT);
	}
}

void CTicTacToeHumanView::MoveMiddleLeft()
{
	EInvalidMove eError = m_boardState.AttemptMove(3, eCROSS);
	if (eError == eVALID && !m_boardState.IsFull() && m_boardState.GetWinner() == eBLANK) {
		m_boardState.MinMaxMove(eNAUGHT);
	}
}

void CTicTacToeHumanView::MoveMiddleMiddle()
{
	EInvalidMove eError = m_boardState.AttemptMove(4, eCROSS);
	if (eError == eVALID && !m_boardState.IsFull() && m_boardState.GetWinner() == eBLANK) {
		m_boardState.MinMaxMove(eNAUGHT);
	}
}

void CTicTacToeHumanView::MoveMiddleRight()
{
	EInvalidMove eError = m_boardState.AttemptMove(5, eCROSS);
	if (eError == eVALID && !m_boardState.IsFull() && m_boardState.GetWinner() == eBLANK) {
		m_boardState.MinMaxMove(eNAUGHT);
	}
}

void CTicTacToeHumanView::MoveBottomLeft()
{
	EInvalidMove eError = m_boardState.AttemptMove(6, eCROSS);
	if (eError == eVALID && !m_boardState.IsFull() && m_boardState.GetWinner() == eBLANK) {
		m_boardState.MinMaxMove(eNAUGHT);
	}
}

void CTicTacToeHumanView::MoveBottomMiddle()
{
	EInvalidMove eError = m_boardState.AttemptMove(7, eCROSS);
	if (eError == eVALID && !m_boardState.IsFull() && m_boardState.GetWinner() == eBLANK) {
		m_boardState.MinMaxMove(eNAUGHT);
	}
}

void CTicTacToeHumanView::MoveBottomRight()
{
	EInvalidMove eError = m_boardState.AttemptMove(8, eCROSS);
	if (eError == eVALID && !m_boardState.IsFull() && m_boardState.GetWinner() == eBLANK) {
		m_boardState.MinMaxMove(eNAUGHT);
	}
}
