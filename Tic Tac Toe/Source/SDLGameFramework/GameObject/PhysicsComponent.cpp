// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: PhysicsComponent.cpp
// Desrciption	: CPhysicsComponent implmentation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "GameStd.h"

// Library Includes

// This Include 
#include "PhysicsComponent.h"

// Local Includes
#include "PositionComponent.h"
#include "../Events/EventManager.h"

CPhysicsComponent::CPhysicsComponent()
	:m_boundingBox(CRect(0,0,0,0)),
	m_bIsBoundToScreen(false),
	m_bIsDestroyOffScreen(false),
	m_fVelocityX(0.0f),
	m_fVelocityY(0.0f),
	m_fMaxVelocityX(0.0f),
	m_fMaxVelocityY(0.0f),
	m_fAccelerationX(0.0f),
	m_fAccelerationY(0.0f)
{

}

CPhysicsComponent::~CPhysicsComponent()
{
	CPhysics* pPhysics = g_pApp->m_pGame->GetPhysics();

	if(pPhysics) {
		pPhysics->DeregisterObject(m_pOwner->GetId());	
	}
}

bool CPhysicsComponent::VInitialize(TiXmlElement* _pXmlData) 
{
	TiXmlElement* pBoundingBox = _pXmlData->FirstChildElement("BoundingBox");
	if(pBoundingBox) {
		double dX = 0.0;
		double dY = 0.0;
		double dWidth = 0.0;
		double dHeight = 0.0;

		pBoundingBox->Attribute("X", &dX);
		pBoundingBox->Attribute("Y", &dY);
		pBoundingBox->Attribute("Width", &dWidth);
		pBoundingBox->Attribute("Height", &dHeight);

		m_boundingBox = CRect(static_cast<int>(dX), static_cast<int>(dY), 
							  static_cast<int>(dWidth), static_cast<int>(dHeight));
	}
	else {
	// Failed to retrieve BoundingBox info.
		std::cerr << "ERROR: No BoundingBox info found when initializing CPhysicsComponent" << std::endl; 
		return false;
	}

	// Check to see if the xml wants to bound the object to the screen.
	TiXmlElement* pIsBoundToScreen = _pXmlData->FirstChildElement("BoundToScreen");

	if(pIsBoundToScreen) {
		m_bIsBoundToScreen = true;
	}
	else {
		m_bIsBoundToScreen = false;
	}

	// Check to see if the xml wants to destroy the object if it goes off the screen.
	TiXmlElement* pIsDestroyOffScreen = _pXmlData->FirstChildElement("DestroyOffScreen");

	if(pIsDestroyOffScreen) {
		m_bIsDestroyOffScreen = true;
	}
	else {
		m_bIsDestroyOffScreen = false;
	}

	return true;
}

void CPhysicsComponent::VPostInitialize()
{
	CPhysics* pPhysics = g_pApp->m_pGame->GetPhysics();

	if(pPhysics) {
		pPhysics->RegisterObject(m_pOwner->GetId());	
	}
	else {
		std::cerr << "ERROR: No physics found when post intializing object id \"";
		std::cerr << m_pOwner->GetId() << "\"" << std::endl;
	}

	return;
}

void CPhysicsComponent::VUpdate(float _fDeltaTime)
{
	// Retrieve the position component of the object.
	shared_ptr<CPositionComponent> pPositionComponent = m_pOwner->GetComponent<CPositionComponent>();

	if(!pPositionComponent) {
		std::cerr << "ERROR: No position component found when updating physics component of ObjectId ";
		std::cerr << m_pOwner->GetId() << std::endl;
		return;
	}
	else {
	// Retrieved position component fine.
	}

	CPoint objectPosition = pPositionComponent->GetPosition();

	if(m_fAccelerationX != 0.0f) {
	// There is a horizontal acceleration.
		// Retrieve the acceleration to apply this frame
		float fAccelerationToApplyThisUpdateX = m_fAccelerationX * _fDeltaTime;

		m_fVelocityX += fAccelerationToApplyThisUpdateX;

		// Limit the magnitude of the velocity to the maximum velocity on the x axis. If velocity is decreasing
		// limit only if the absolute value of the current velocity is less than the absolute value of the 
		// max velocity.
		if(m_fAccelerationX > 0.0f && m_fVelocityX > abs(m_fMaxVelocityX)) {
		// Object is accelerating right and has now reached the maximum velocity.
				m_fVelocityX = abs(m_fMaxVelocityX);

				// Acceleration completed, remove it.
				RemoveAccelerationX();
			}
		else if(m_fAccelerationX < 0.0f && -m_fVelocityX > abs(m_fMaxVelocityX)) {
		// Object is accelerating left and has now reached the maximum velocity.
				m_fVelocityX = -abs(m_fMaxVelocityX);

				// Acceleration completed, remove it.
				RemoveAccelerationX();
			}
	}
	else {
	// No horizontal acceleration. 
	}

	if(m_fAccelerationY != 0.0f) {
	// There is a vertical horizontal acceleration.
		// Retrieve the acceleration to apply this frame
		float fAccelerationToApplyThisFrameY = m_fAccelerationY * _fDeltaTime;

		m_fVelocityY += fAccelerationToApplyThisFrameY;

		// Limit the magnitude of the velocity to the maximum velocity on the y axis. If velocity is decreasing
		// limit only if the absolute value of the current velocity is less than the absolute value of the 
		// max velocity.
		if(m_fAccelerationY > 0.0f && m_fVelocityY > abs(m_fMaxVelocityY)) {
		// Object is accelerating down and has now reached the maximum velocity.
				m_fVelocityY = abs(m_fMaxVelocityY);

				// Acceleration completed, remove it. 
				RemoveAccelerationY();
		}
		else if(m_fAccelerationY < 0.0f && -m_fVelocityY > abs(m_fMaxVelocityY)) {
		// Object is accelerating up and has now reached the maximum velocity.
				m_fVelocityY = -abs(m_fMaxVelocityY);

				// Acceleration completed, remove it.
				RemoveAccelerationY();
		}
	}
	else {
	// No vertical acceleration.
	}

	int iIncrementX = static_cast<int>(m_fVelocityX * _fDeltaTime);
	int iIncrementY = static_cast<int>(m_fVelocityY * _fDeltaTime);

	// Increment the position of the object.
	objectPosition += CPoint(iIncrementX, iIncrementY);

	// Check to see if BoundingBox has gone outside of the screen.
	if(m_bIsBoundToScreen) {
		CRect worldBox(m_boundingBox);
		CPoint screenSize(g_pApp->GetScreenSize());

		worldBox.m_iX += objectPosition.m_iX;
		worldBox.m_iY += objectPosition.m_iY;

		if(worldBox.GetLeft() < 0) {
		// Object is out of bounds on the left.
			objectPosition.m_iX = -m_boundingBox.m_iX;

			m_fVelocityX = 0;
		}
		else if(worldBox.GetRight() > screenSize.m_iX) {
		// Object is out of bounds on the right.
			objectPosition.m_iX = screenSize.m_iX - m_boundingBox.GetRight(); 
			
			m_fVelocityX = 0;
		}
		else {
		// This object is in bounds on the horizontal axis.
		}

		if(worldBox.GetTop() < 0) {
		// Object is out of bounds on the top.
			objectPosition.m_iY = -m_boundingBox.m_iY;
			
			m_fVelocityY = 0;
		}
		else if(worldBox.GetBottom() > screenSize.m_iY) {
		// Object is out of bounds on the bottom.
			objectPosition.m_iY = screenSize.m_iY - m_boundingBox.GetBottom();
			
			m_fVelocityY = 0;
		}
		else {
		// This object is in bounds on the vertical axis.
		}
	}

	// Check to see if BoundingBox has gone entirely outside of the screen.
	if(m_bIsDestroyOffScreen) {
		CRect worldBox(m_boundingBox);
		CPoint screenSize(g_pApp->GetScreenSize());

		worldBox.m_iX += objectPosition.m_iX;
		worldBox.m_iY += objectPosition.m_iY;
		
		if(!IsIntersecting(worldBox, CRect(0, 0, screenSize.m_iX, screenSize.m_iY))) {
		// The world bounding box lies outside the screen rectangle area.
			// Queue a destroy object event to destroy the object next tick.
			shared_ptr<CEvtDataDestroyObject> pEvent(new CEvtDataDestroyObject(m_pOwner->GetId()));
			CEventManager::GetInstance()->QueueEvent(pEvent);

			return;
		}
	}

	if(objectPosition != pPositionComponent->GetPosition()) {
	// Have we changed positions?
		// Check for collisions.
		CRect worldBox(m_boundingBox);

		worldBox.m_iX += objectPosition.m_iX;
		worldBox.m_iY += objectPosition.m_iY;

		CPhysics* pPhysics = g_pApp->m_pGame->GetPhysics();

		if(pPhysics) {
			pPhysics->CheckCollisions(m_pOwner, worldBox);
		}
	}

	// Set the position in the position component.
	pPositionComponent->SetPosition(objectPosition);

	return;
}

void CPhysicsComponent::Stop()
{
	m_fVelocityX = 0;
	m_fVelocityY = 0;

	m_fMaxVelocityX = 0; 
	m_fMaxVelocityY = 0;

	m_fAccelerationX = 0;
	m_fAccelerationY = 0;
}

const CRect& CPhysicsComponent::GetBoundingBox() const
{
	return m_boundingBox;
}

CRect CPhysicsComponent::GetWorldBoundingBox() const
{
	// Retrieve the position component of the object.
	shared_ptr<CPositionComponent> pPositionComponent = m_pOwner->GetComponent<CPositionComponent>();

	CPoint objectPosition = pPositionComponent->GetPosition();

	if(pPositionComponent) {
		// Return the bounding box relative to the world.
		return CRect(objectPosition.m_iX + m_boundingBox.m_iX, 
				     objectPosition.m_iY + m_boundingBox.m_iY,
					 m_boundingBox.m_iWidth, 
					 m_boundingBox.m_iHeight);
	}
	else {
	// This object has no CPositionComponent.
		std::cerr << "ERROR: No position component found when getting world position of ObjectId ";
		std::cerr << m_pOwner->GetId() << std::endl;

		return CRect(); 
	}
}

bool CPhysicsComponent::IsBoundToScreen() const
{
	return m_bIsBoundToScreen;
}

bool CPhysicsComponent::IsDestroyOffScreen() const
{
	return m_bIsDestroyOffScreen;
}

float CPhysicsComponent::GetVelocityX() const
{
	return m_fVelocityX;
}
float CPhysicsComponent::GetVelocityY() const
{
	return m_fVelocityY;
}

float CPhysicsComponent::GetAccelerationX() const
{
	return m_fAccelerationX;
}

float CPhysicsComponent::GetAccelerationY() const
{
	return m_fAccelerationY;
}

void CPhysicsComponent::ApplyAccelerationX(float _fAcceleration, float _fMaxVelocity)
{
	m_fAccelerationX = _fAcceleration;
	m_fMaxVelocityX = _fMaxVelocity;
}

void CPhysicsComponent::ApplyAccelerationY(float _fAcceleration, float _fMaxVelocity)
{
	m_fAccelerationY = _fAcceleration;
	m_fMaxVelocityY = _fMaxVelocity;
}


void CPhysicsComponent::RemoveAccelerationX()
{
	m_fAccelerationX = 0.0f;
	m_fMaxVelocityX = 0.0f;
}

void CPhysicsComponent::RemoveAccelerationY()
{
	m_fAccelerationY = 0.0f;
	m_fMaxVelocityY = 0.0f;
}

void CPhysicsComponent::SetVelocityX(float _fVelocity)
{
	m_fVelocityX = _fVelocity;

	RemoveAccelerationX();
}

void CPhysicsComponent::SetVelocityY(float _fVelocity)
{
	m_fVelocityY = _fVelocity;

	RemoveAccelerationY();
}

TStrongObjectComponentPtr CreatePhysicsComponent()
{
	return TStrongObjectComponentPtr(new CPhysicsComponent());
}

