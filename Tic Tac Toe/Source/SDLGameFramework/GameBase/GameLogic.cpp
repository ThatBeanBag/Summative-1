// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: GameLogic.cpp
// Desrciption	: CGameLogic implementation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "GameStd.h"

// Library Includes

// This Include
#include "GameLogic.h"

// Local Includes
#include "GameApp.h"

CGameLogic::CGameLogic()
{
	m_pRenderer = 0;
	m_fElapsedTime = 0;
	m_eState = GS_Invalid;
}

CGameLogic::~CGameLogic()
{
	VRemoveEventListeners();

	// Remove game views.
	while(!m_gameViews.empty()) {
		m_gameViews.pop_front();
	}

	// De-allocate GameObjects.
	std::map<TGameObjectId, CGameObject*>::iterator iter;

	for(auto iter = m_gameObjects.begin(); iter != m_gameObjects.end(); ++iter) {
		// Destroy the components first.
		iter->second->DestroyComponents();

		// De-allocate.
		delete iter->second;
	}

	// Clear the map.
	m_gameObjects.clear();

	// De-allocate physics engine, renderer and object factory.
	delete m_pObjectFactory;
	delete m_pPhysics;
	delete m_pRenderer;
}

bool CGameLogic::VInit()
{
	VChangeState(GS_Initializing);

	VRegisterEventListeners();

	// Create the object factory.
	m_pObjectFactory = VCreateObjectFactory();

	if(!m_pObjectFactory) {
		return false;
	}

	m_pRenderer = new CRenderer();

	if(!m_pRenderer) {
		return false;
	}

	m_pPhysics = new CPhysics();

	if(!m_pPhysics) {
		return false;
	}

	return true;
}

void CGameLogic::VUpdate(float _fDeltaTime)
{
	m_fElapsedTime += _fDeltaTime;

	switch(m_eState) {
		case GS_Initializing: {
		// If we get here, we've successfully initialized.
			// Move to next state.
			VChangeState(GS_TitleScreen);

			break;
		}
	}

	CEventManager::GetInstance()->VFireOffEvents();

	// Update the views.
	for(TGameViewList::iterator iter = m_gameViews.begin(); iter != m_gameViews.end(); ++iter) {
		(*iter)->VUpdate(_fDeltaTime);
	}

	// Update all game objects and their components
	for(TGameObjectMap::iterator iter = m_gameObjects.begin(); iter != m_gameObjects.end(); ++iter) {
		iter->second->Update(_fDeltaTime);
	}
}

void CGameLogic::VChangeState(EGameState _eState)
{
	switch(_eState) {
		case GS_TitleScreen: {
			break;
		}
		case GS_MainMenu: {
			break;
		}
		case GS_HighScore: {
			break;
		}
		case GS_Options: {
			break;
		}
		case GS_Running: {
			break;
		}
		default: {
			break;
		}
	}

	m_eState = _eState;
}

bool CGameLogic::VMsgProc(const CAppMsg& _krMsg)
{
	for(auto iter = m_gameViews.begin(); iter != m_gameViews.end(); ++iter) {
		if((*iter)->VMsgProc(_krMsg)) {
		// Message handled.
			return true;		// Breaks out of the loop.
		}	
	}

	// Message wasn't handled.
	return false;
}

void CGameLogic::Render(float _fDeltaTime)
{
	for(auto iter = m_gameViews.begin(); iter != m_gameViews.end(); ++iter) {
		(*iter)->VRender(_fDeltaTime);
	}
}

CRenderer* CGameLogic::GetRenderer()
{
	return m_pRenderer;
}

CPhysics* CGameLogic::GetPhysics()
{
	return m_pPhysics;
}

CGameObject* CGameLogic::CreateGameObject(const std::string& _krObjectResource)
{
	CGameObject* pObject = m_pObjectFactory->CreateObject(_krObjectResource);
	if(pObject) {
		// Insert into list of game objects.
		m_gameObjects[pObject->GetId()] = pObject;
	}
	else {
		// Return NULL pointer.
		return 0;
	}

	return pObject;
}

CGameObject* CGameLogic::GetGameObject(TGameObjectId _id)
{
	TGameObjectMap::iterator findIter = m_gameObjects.find(_id);

	if(findIter != m_gameObjects.end()) {
	// Found an object with the specified id.
		return findIter->second;
	}
	else {
 		std::cerr << "ERROR: Couldn't retrieve game object from id \"" << _id << "\"" << std::endl;

		// Return NULL pointer.
		return 0;
	}

	// Return NULL pointer.
	return 0;
}

void CGameLogic::DestroyGameObject(TGameObjectId _id) 
{
	TGameObjectMap::iterator findIter = m_gameObjects.find(_id);

	if(findIter != m_gameObjects.end()) {
		// Destroy the components first.
		findIter->second->DestroyComponents();

		delete findIter->second;
		m_gameObjects.erase(findIter);
	}
	else {
	// Couldn't find object.
		std::cerr << "WARNING: Couldn't find object with id " << _id << " when destroying" << std::endl;
	}
}

void CGameLogic::AddView(TStrongGameViewPtr _pView, TGameObjectId _id)
{
	m_gameViews.push_back(_pView);

	_pView->VAttach(_id);
}

void CGameLogic::RemoveView(TStrongGameViewPtr _pView)
{
	m_gameViews.remove(_pView);
}

void CGameLogic::VRegisterEventListeners()
{
	// Register Listeners
	CEventManager::GetInstance()->AddListener<CEvtDataDestroyObject>(MakeDelegate(this, &CGameLogic::DestroyObjectListener));
	CEventManager::GetInstance()->AddListener<CEvtDataMoveObject>(MakeDelegate(this, &CGameLogic::MoveObjectListener));
}

void CGameLogic::VRemoveEventListeners()
{
	// Remove Listeners
	CEventManager::GetInstance()->RemoveListener<CEvtDataDestroyObject>(MakeDelegate(this, &CGameLogic::DestroyObjectListener));
	CEventManager::GetInstance()->RemoveListener<CEvtDataMoveObject>(MakeDelegate(this, &CGameLogic::MoveObjectListener));
}

//=================================================================
// Event Listeners
//=================================================================

void CGameLogic::DestroyObjectListener(TEventDataPtr _pEventData)
{
	// Obtain the event data.
	shared_ptr<CEvtDataDestroyObject> pDestroyObjectData = static_pointer_cast<CEvtDataDestroyObject>(_pEventData);

	DestroyGameObject(pDestroyObjectData->GetObjectId());
}

void CGameLogic::MoveObjectListener(TEventDataPtr _pEventData)
{
	// Obtain the event data.
	shared_ptr<CEvtDataMoveObject> pMoveObjectData = static_pointer_cast<CEvtDataMoveObject>(_pEventData);

	// Retrieve the object.
	CGameObject* pObject = GetGameObject(pMoveObjectData->GetObjectId());

	if(pObject) {
	// Does this object exist?
		// Retrieve the physics component of the object.
		shared_ptr<CPhysicsComponent> pPhysicsComponent = pObject->GetComponent<CPhysicsComponent>();

		bool bIsXAxis = pMoveObjectData->GetIsXAxis();

		if(pPhysicsComponent) {
			if(pMoveObjectData->GetAcceleration() != 0.0f) {
			// Are we applying an acceleration?
				if(bIsXAxis) {
				// Are we applying this to the X axis?
					pPhysicsComponent->ApplyAccelerationX(pMoveObjectData->GetAcceleration(), pMoveObjectData->GetMaxVelocity());
				}
				else {
					pPhysicsComponent->ApplyAccelerationY(pMoveObjectData->GetAcceleration(), pMoveObjectData->GetMaxVelocity());
				}
			}
			else {
			// No acceleration is being applied.
				// Set the velocity to the max velocity.
				if(bIsXAxis) {
				// Are we setting this to the X axis?
					pPhysicsComponent->SetVelocityX(pMoveObjectData->GetMaxVelocity());
				}
				else {
					pPhysicsComponent->SetVelocityY(pMoveObjectData->GetMaxVelocity());
				}

			}
		}
		else {
			std::cerr << "ERROR: Can't move an object that doesn't have a physics component" << std::endl;
			return;
		}
	}
}

CObjectFactory* CGameLogic::VCreateObjectFactory()
{
	return new CObjectFactory();
}