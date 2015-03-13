// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: Physics.cpp
// Desrciption	: CPhysics implmentation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "GameStd.h"

// Library Includes

// This Include 
#include "Physics.h"

// Local Includes

CPhysics::CPhysics()
{
}

CPhysics::~CPhysics()
{
}

void CPhysics::Update(float _fDeltaTime)
{

}

void CPhysics::CheckCollisions(CGameObject* _pObject, const CRect& newBoundingBox)
{
	assert(_pObject);

	std::list<TGameObjectId>::iterator iter;

	// Loop through all registered game objects.
	for(iter = m_registeredObjects.begin(); iter != m_registeredObjects.end(); ++iter) {
		// Obtain the current game object.
		CGameObject* pCurrentObject = g_pApp->m_pGame->GetGameObject(*iter);

		if(pCurrentObject && pCurrentObject != _pObject) {	// Make sure we are not colliding with ourselves.
			// Get the physics component of the current object so that we can check with the world bounding box.
			shared_ptr<CPhysicsComponent> pPhysicsComponent = pCurrentObject->GetComponent<CPhysicsComponent>();

			if(pPhysicsComponent) {
				if(IsIntersecting(pPhysicsComponent->GetWorldBoundingBox(), newBoundingBox)) {
				// Collision found.
					// Trigger a collision event.
					shared_ptr<CEvtDataCollision> pEvent(new CEvtDataCollision(_pObject->GetId(), pCurrentObject->GetId()));
					CEventManager::GetInstance()->QueueEvent(pEvent);
				}
			}
		}
	}
}

void CPhysics::RegisterObject(TGameObjectId _id)
{
	m_registeredObjects.push_back(_id);
}

void CPhysics::DeregisterObject(TGameObjectId _id)
{
	m_registeredObjects.remove(_id);
}