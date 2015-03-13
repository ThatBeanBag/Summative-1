// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: ObjectComponent.cpp
// Desrciption	: CObjectComponent implmentation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "GameStd.h"

// Library Includes

// This Include
#include "ObjectComponent.h"

// Local Includes

CObjectComponent::CObjectComponent()
	:m_pOwner(0)
{

}

CObjectComponent::~CObjectComponent()
{

}


void CObjectComponent::SetOwner(CGameObject* _pOwner)
// Should only be called by ObjectFactory.
{
	m_pOwner = _pOwner;
}
