// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: DestroyAfterComponent.cpp
// Desrciption	: CDestroyAfterComponent implementation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "GameStd.h"

// Library Includes

// This Include
#include "DestroyAfterComponent.h"

// Local Includes

CDestroyAfterComponent::CDestroyAfterComponent()
	:m_fElapsedTime(0.0f),
	m_fWaitTime(0.0f)
{

}

CDestroyAfterComponent::~CDestroyAfterComponent()
{
}

bool CDestroyAfterComponent::VInitialize(TiXmlElement* _pXmlData)
{
	TiXmlElement* pWaitTime = _pXmlData->FirstChildElement("WaitTime");

	if(pWaitTime) {
		// Get the wait time from the xml.
		std::string value = pWaitTime->FirstChild()->Value();

		m_fWaitTime = static_cast<float>(atof(value.c_str()));
	}
	else {
	// No wait time specified.
		// A destroy after component needs to have a wait time.
		return false;
	}

	return true;
}

void CDestroyAfterComponent::VPostInitialize()
{
	// Nothing to post initialize.
}

void CDestroyAfterComponent::VUpdate(float _fDeltaTime)
{
	m_fElapsedTime += _fDeltaTime;

	if(m_fElapsedTime > m_fWaitTime) {
	// Have we waited long enough.
		// Queue an event to destroy the owner object.
		TEventDataPtr pEvent(new CEvtDataDestroyObject(m_pOwner->GetId()));

		CEventManager::GetInstance()->QueueEvent(pEvent);
	}
	else {
	// Not enough time has surpassed.
		return;
	}

	return;
}


TStrongObjectComponentPtr CreateDestroyAfterComponent()
{
	return TStrongObjectComponentPtr(new CDestroyAfterComponent);
}