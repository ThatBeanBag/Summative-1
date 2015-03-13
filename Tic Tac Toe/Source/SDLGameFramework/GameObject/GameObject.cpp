// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: GameObject.cpp
// Desrciption	: CGameObject implementation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "GameStd.h"

// Library Includes

// This Include
#include "GameObject.h"

// Local Includes
#include "ObjectComponent.h"

CGameObject::CGameObject(TGameObjectId _id)
	:m_id(_id),
	m_strType("Invalid")
{

}

CGameObject::~CGameObject()
{
	assert(m_objectComponents.empty());	// Object was destroyed without a call to DestroyComponents().
}

bool CGameObject::Initialize(const std::string& _strType)
{
	m_strType = _strType;

	return true;
}

void CGameObject::PostInitialize()
{
	TObjectComponents::iterator iter;
	for(iter = m_objectComponents.begin(); iter != m_objectComponents.end(); ++iter) {
		iter->second->VPostInitialize();
	}
}

void CGameObject::Update(float _fDeltaTime)
{
	TObjectComponents::iterator iter;
	for(iter = m_objectComponents.begin(); iter != m_objectComponents.end(); ++iter) {
		iter->second->VUpdate(_fDeltaTime);
	}
}

void CGameObject::DestroyComponents()
{
	m_objectComponents.clear();
}

TGameObjectId CGameObject::GetId() const
{
	return m_id;
}

const std::string& CGameObject::GetType() const
{
	return m_strType;
}

void CGameObject::AddComponent(TStrongObjectComponentPtr _pComponent)
{
	// Insert the component into the list.
	m_objectComponents[std::type_index(typeid(*_pComponent))] = _pComponent;
}

