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
	:m_sprite(g_pApp->LoadSprite("Images/Buttons/Unbeatable.png")),
	m_sprite2(g_pApp->LoadSprite("Images/Buttons/Easy.png")),
	m_buttonTest(&m_sprite, 
				  CRect(50, 20, 190, 190), 
				  MakeDelegate(dynamic_cast<CTicTacToeLogic*>(g_pApp->m_pGame), &CTicTacToeLogic::CloseDelegateTest),
				  eBOTTOM_RIGHT),
	m_buttonTest2(&m_sprite2,
				  CRect(50, 20, 190, 190),
				  MakeDelegate(dynamic_cast<CTicTacToeLogic*>(g_pApp->m_pGame), &CTicTacToeLogic::CloseDelegateTest),
				  eTOP_RIGHT)
{
	m_sprite.AddMask(CRect(0, 0, 190, 190));
	m_sprite.AddMask(CRect(190, 0, 190, 190));

	m_sprite2.AddMask(CRect(0, 0, 190, 190));
	m_sprite2.AddMask(CRect(190, 0, 190, 190));

	m_background = g_pApp->LoadSprite("Images/BackgroundImage.png");
}

CTicTacToeHumanView::~CTicTacToeHumanView()
{

}

void CTicTacToeHumanView::VUpdate(float _fDeltaTime)
{
	g_pApp->RenderSprite(m_background, 0, 0);

	m_buttonTest.Render();
	m_buttonTest2.Render();
}

bool CTicTacToeHumanView::VMsgProc(const CAppMsg& _krMsg)
{
	switch (_krMsg.type) {
	case SDL_MOUSEMOTION: {
		// Update the current mouse position.		
		m_buttonTest.OnMouseMove(CPoint(_krMsg.x, _krMsg.y));
		m_buttonTest2.OnMouseMove(CPoint(_krMsg.x, _krMsg.y));

		break;
	}

	case SDL_MOUSEBUTTONDOWN: {
		if (_krMsg.button == SDL_BUTTON_LEFT) {
		}

		break;
	}

	case SDL_MOUSEBUTTONUP: {
		if (_krMsg.button == SDL_BUTTON_LEFT) {
			m_buttonTest.OnRelease(m_cursorPosition);
			m_buttonTest2.OnRelease(m_cursorPosition);
		}

		break;
	}
	default:break;
	}

	return CHumanView::VMsgProc(_krMsg);
}