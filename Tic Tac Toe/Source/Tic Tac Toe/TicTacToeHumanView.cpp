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
	// Load Sprites.
	m_background = g_pApp->LoadSprite("Images/BackgroundImage.png");
	m_naughtSprite = g_pApp->LoadSprite("Images/Naught.png");
	m_crossSprite = g_pApp->LoadSprite("Images/Cross.png");

	m_crossSprite.AddMask(CRect(0, 0, 90, 90));
	m_crossSprite.AddMask(CRect(90, 0, 90, 90));

	m_naughtSprite.AddMask(CRect(0, 0, 90, 90));
	m_naughtSprite.AddMask(CRect(90, 0, 90, 90));

	// Register Delegates into the GUI.
	m_guiBoard.RegisterDelegate("CTicTacToeHumanView::MoveTopLeft", MakeDelegate(this, &CTicTacToeHumanView::MoveTopLeft));
	m_guiBoard.RegisterDelegate("CTicTacToeHumanView::MoveTopRight", MakeDelegate(this, &CTicTacToeHumanView::MoveTopRight));
	m_guiBoard.RegisterDelegate("CTicTacToeHumanView::MoveMiddleLeft", MakeDelegate(this, &CTicTacToeHumanView::MoveMiddleLeft));
	m_guiBoard.RegisterDelegate("CTicTacToeHumanView::MoveMiddleMiddle", MakeDelegate(this, &CTicTacToeHumanView::MoveMiddleMiddle));
	m_guiBoard.RegisterDelegate("CTicTacToeHumanView::MoveMiddleRight", MakeDelegate(this, &CTicTacToeHumanView::MoveMiddleRight));
	m_guiBoard.RegisterDelegate("CTicTacToeHumanView::MoveBottomLeft", MakeDelegate(this, &CTicTacToeHumanView::MoveBottomLeft));
	m_guiBoard.RegisterDelegate("CTicTacToeHumanView::MoveBottomMiddle", MakeDelegate(this, &CTicTacToeHumanView::MoveBottomMiddle));
	m_guiBoard.RegisterDelegate("CTicTacToeHumanView::MoveBottomRight", MakeDelegate(this, &CTicTacToeHumanView::MoveBottomRight));
	m_guiBoard.RegisterDelegate("CTicTacToeHumanView::MoveTopMiddle", MakeDelegate(this, &CTicTacToeHumanView::MoveTopMiddle));

	m_guiAi.RegisterDelegate("CTicTacToeHumanView::Unbeatable", MakeDelegate(this, &CTicTacToeHumanView::Unbeatable));
	m_guiAi.RegisterDelegate("CTicTacToeHumanView::Easy", MakeDelegate(this, &CTicTacToeHumanView::Easy));

	m_guiStart.RegisterDelegate("CTicTacToeHumanView::StartOverComputer", MakeDelegate(this, &CTicTacToeHumanView::StartOverComputer));
	m_guiStart.RegisterDelegate("CTicTacToeHumanView::StartOverPlayer", MakeDelegate(this, &CTicTacToeHumanView::StartOverPlayer));

	m_guiStartOver.RegisterDelegate("CTicTacToeHumanView::StartOverComputer", MakeDelegate(this, &CTicTacToeHumanView::StartOverComputer));
	m_guiStartOver.RegisterDelegate("CTicTacToeHumanView::StartOverPlayer", MakeDelegate(this, &CTicTacToeHumanView::StartOverPlayer));

	// Load the GUIs from file.
	m_guiBoard.LoadGUIFromFile("GUI/MainGUI.xml");
	m_guiAi.LoadGUIFromFile("GUI/AiSelectGUI.xml");
	m_guiStart.LoadGUIFromFile("GUI/StartGUI.xml");
	m_guiStartOver.LoadGUIFromFile("GUI/StartOverGUI.xml");

	// Hide the ai and board GUIs.
	m_guiAi.Hide();
	m_guiBoard.Hide();
	m_guiStartOver.Hide();
}

CTicTacToeHumanView::~CTicTacToeHumanView()
{
	
}

void CTicTacToeHumanView::VUpdate(float _fDeltaTime)
{
	m_bIsThereAWinner = false;
	m_iWinPositions[CBoardState::s_kiBOARD_COL];

	if (m_boardState.GetWinner() != eBLANK || m_boardState.IsFull()) {
		m_guiBoard.Hide();

		if (m_boardState.GetWinPositions(m_iWinPositions)) {
			m_bIsThereAWinner = true;
		}
	}

	for (int i = 0; i < CBoardState::s_kiBOARD_SIZE && i < m_guiBoard.GetElements().size(); ++i) {
		if (m_boardState[i] != eBLANK) {
			m_guiBoard.GetElements()[i]->VHide();
		}
		else {
			//m_guiBoard.GetElements()[i]->Show();
		}
	}
}

void CTicTacToeHumanView::VRender(float _fDeltaTime)
{
	g_pApp->RenderSprite(m_background, 0, 0);

	// Render the GUI.
	m_guiStart.Render();
	m_guiStartOver.Render();
	m_guiBoard.Render();
	m_guiAi.Render();

	int iStartX = 108;
	int iStartY = 135;

	int iOffset = 162;


	for (int i = 0; i < CBoardState::s_kiBOARD_COL; ++i) {
		for (int j = 0; j < CBoardState::s_kiBOARD_COL; ++j) {
			CPoint position(iStartX + iOffset * i, iStartY + iOffset * j);

			int iBoardPosition = i + j * CBoardState::s_kiBOARD_COL;

			if (m_boardState[iBoardPosition] == eNAUGHT) {
				if (m_boardState.IsAWinPosition(iBoardPosition)) {
					g_pApp->RenderSprite(m_naughtSprite, position, 2);
				}
				else {
					g_pApp->RenderSprite(m_naughtSprite, position, 1);
				}
			}
			else if (m_boardState[iBoardPosition] == eCROSS) {
				if (m_boardState.IsAWinPosition(iBoardPosition)) {
					g_pApp->RenderSprite(m_crossSprite, position, 2);
				}
				else {
					g_pApp->RenderSprite(m_crossSprite, position, 1);
				}
			}
			else {
			}
		}
	}

	CHumanView::VRender(_fDeltaTime);
}


bool CTicTacToeHumanView::VMsgProc(const CAppMsg& _krMsg)
{
	bool bHandled = CHumanView::VMsgProc(_krMsg);

	// Let the GUI handle it's events.
	if (m_guiStart.HandleEvents(_krMsg)) {
		return true;
	}
	else if (m_guiStartOver.HandleEvents(_krMsg)) {
		return true;
	}
	else if (m_guiBoard.HandleEvents(_krMsg)) {
		return true;
	}
	else if (m_guiAi.HandleEvents(_krMsg)) {
		return true;
	}

	return bHandled;
}

// =====================================================
// Delegate Functions
// =====================================================

void CTicTacToeHumanView::MoveTopLeft()
{
	EInvalidMove eError = m_boardState.AttemptMove(0, eCROSS);

	if (eError == eVALID && !m_boardState.IsFull() && m_boardState.GetWinner() == eBLANK) {
		if (m_bIsComputerEasy) {
			m_boardState.MinMaxMove(eNAUGHT, g_kfCHANCE_OF_EASY_AI);
		}
		else {
			m_boardState.MinMaxMove(eNAUGHT);
		}
	}
}

void CTicTacToeHumanView::MoveTopMiddle()
{
	EInvalidMove eError = m_boardState.AttemptMove(1, eCROSS);
	if (eError == eVALID && !m_boardState.IsFull() && m_boardState.GetWinner() == eBLANK) {
		if (m_bIsComputerEasy) {
			m_boardState.MinMaxMove(eNAUGHT, g_kfCHANCE_OF_EASY_AI);
		}
		else {
			m_boardState.MinMaxMove(eNAUGHT);
		}
	}
}

void CTicTacToeHumanView::MoveTopRight()
{
	EInvalidMove eError = m_boardState.AttemptMove(2, eCROSS);
	if (eError == eVALID && !m_boardState.IsFull() && m_boardState.GetWinner() == eBLANK) {
		if (m_bIsComputerEasy) {
			m_boardState.MinMaxMove(eNAUGHT, g_kfCHANCE_OF_EASY_AI);
		}
		else {
			m_boardState.MinMaxMove(eNAUGHT);
		}
	}
}

void CTicTacToeHumanView::MoveMiddleLeft()
{
	EInvalidMove eError = m_boardState.AttemptMove(3, eCROSS);
	if (eError == eVALID && !m_boardState.IsFull() && m_boardState.GetWinner() == eBLANK) {
		if (m_bIsComputerEasy) {
			m_boardState.MinMaxMove(eNAUGHT, g_kfCHANCE_OF_EASY_AI);
		}
		else {
			m_boardState.MinMaxMove(eNAUGHT);
		}
	}
}

void CTicTacToeHumanView::MoveMiddleMiddle()
{
	EInvalidMove eError = m_boardState.AttemptMove(4, eCROSS);
	if (eError == eVALID && !m_boardState.IsFull() && m_boardState.GetWinner() == eBLANK) {
		if (m_bIsComputerEasy) {
			m_boardState.MinMaxMove(eNAUGHT, g_kfCHANCE_OF_EASY_AI);
		}
		else {
			m_boardState.MinMaxMove(eNAUGHT);
		}
	}
}

void CTicTacToeHumanView::MoveMiddleRight()
{
	EInvalidMove eError = m_boardState.AttemptMove(5, eCROSS);
	if (eError == eVALID && !m_boardState.IsFull() && m_boardState.GetWinner() == eBLANK) {
		if (m_bIsComputerEasy) {
			m_boardState.MinMaxMove(eNAUGHT, g_kfCHANCE_OF_EASY_AI);
		}
		else {
			m_boardState.MinMaxMove(eNAUGHT);
		}
	}
}

void CTicTacToeHumanView::MoveBottomLeft()
{
	EInvalidMove eError = m_boardState.AttemptMove(6, eCROSS);
	if (eError == eVALID && !m_boardState.IsFull() && m_boardState.GetWinner() == eBLANK) {
		if (m_bIsComputerEasy) {
			m_boardState.MinMaxMove(eNAUGHT, g_kfCHANCE_OF_EASY_AI);
		}
		else {
			m_boardState.MinMaxMove(eNAUGHT);
		}
	}
}

void CTicTacToeHumanView::MoveBottomMiddle()
{
	EInvalidMove eError = m_boardState.AttemptMove(7, eCROSS);
	if (eError == eVALID && !m_boardState.IsFull() && m_boardState.GetWinner() == eBLANK) {
		if (m_bIsComputerEasy) {
			m_boardState.MinMaxMove(eNAUGHT, g_kfCHANCE_OF_EASY_AI);
		}
		else {
			m_boardState.MinMaxMove(eNAUGHT);
		}
	}
}

void CTicTacToeHumanView::MoveBottomRight()
{
	EInvalidMove eError = m_boardState.AttemptMove(8, eCROSS);
	if (eError == eVALID && !m_boardState.IsFull() && m_boardState.GetWinner() == eBLANK) {
		if (m_bIsComputerEasy) {
			m_boardState.MinMaxMove(eNAUGHT, g_kfCHANCE_OF_EASY_AI);
		}
		else {
			m_boardState.MinMaxMove(eNAUGHT);
		}
	}
}

void CTicTacToeHumanView::StartOverComputer()
{
	m_guiStart.Hide();
	m_guiStartOver.Hide();

	m_guiAi.Show();

	m_boardState = CBoardState();

	m_bComputerStart = true;
}

void CTicTacToeHumanView::StartOverPlayer()
{
	m_guiStart.Hide();
	m_guiStartOver.Hide();

	m_guiAi.Show();

	// Clear the board.
	m_boardState = CBoardState();

	m_bComputerStart = false;
}

void CTicTacToeHumanView::Unbeatable() 
{
	m_guiAi.Hide();

	m_guiBoard.Show();
	m_guiStartOver.Show();

	m_bIsComputerEasy = false;

	if (m_bComputerStart) {
		m_boardState.MinMaxMove(eNAUGHT);
	}
}

void CTicTacToeHumanView::Easy()
{
	m_guiAi.Hide();

	m_guiBoard.Show();
	m_guiStartOver.Show();

	m_bIsComputerEasy = true;

	if (m_bComputerStart) {
		m_boardState.MinMaxMove(eNAUGHT, g_kfCHANCE_OF_EASY_AI);
	}
}