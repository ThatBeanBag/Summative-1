// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2015 Media Design School
//
// File Name	: GUIStatic.cpp
// Desrciption	: CGUIStatic implementation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "GameStd.h"

// Library Includes

// This Include
#include "GUIStatic.h"

// Local Includes

CGUIStatic::CGUIStatic(CSprite* _pSprite, const CRect& _krBoundingBox, EGUIAnchor _eAnchor)
	:CGUIElement(_krBoundingBox, _eAnchor),
	m_pSprite(_pSprite)
{

}

CGUIStatic::~CGUIStatic()
{

}

void CGUIStatic::VRender()
{
	if (m_bIsShown) {
		g_pApp->RenderSprite(*m_pSprite, GetWorldPosition());
	}
}