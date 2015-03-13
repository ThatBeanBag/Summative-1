// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: PhysicsComponent.h
// Desrciption	: CPhysicsComponent declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef __PHYSICSCOMPONENT_H__
#define __PHYSICSCOMPONENT_H__

// Library Includes

// Local Includes
#include "ObjectComponent.h"

class CPhysicsComponent : public CObjectComponent {
	// Member Functions
public:
	CPhysicsComponent();
	~CPhysicsComponent();

	virtual bool VInitialize(TiXmlElement* _pXmlData);
	virtual void VPostInitialize();
	virtual void VUpdate(float _fDeltaTime);

	void Stop();	// Sets all velocities and accelerations to 0.

	// Accessors
	const CRect& GetBoundingBox() const;	// Returns the bounding box relative to it's position.
	CRect GetWorldBoundingBox() const;		// Returns the bounding box relative to the world.

	bool IsBoundToScreen() const;
	bool IsDestroyOffScreen() const;

	float GetVelocityX() const;
	float GetVelocityY() const;
	float GetAccelerationX() const;
	float GetAccelerationY() const;

	// Applying an acceleration also requires a maximum velocity. The default max velocity
	// is set to the highest possible max velocity, essentially accelerating forever.
	void ApplyAccelerationX(float _fAcceleration, float _fMaxVelocity = g_kfINFINITY);
	void ApplyAccelerationY(float _fAcceleration, float _fMaxVelocity = g_kfINFINITY);

	// Removing the acceleration on an object does not change it's velocity.
	// Accelerations are removed whenever the velocity 
	void RemoveAccelerationX();
	void RemoveAccelerationY();

	void SetVelocityX(float _fVelocity);
	void SetVelocityY(float _fVelocity);
protected:
private:

	// Member Variables
public:
protected:
private:
	CRect m_boundingBox;	// The collisional box of this object relative to the 
							// position in the CPositionComponent.

	bool m_bIsBoundToScreen;	// True if the object should not move beyond the bounds of 
								// the screen, false otherwise.
	bool m_bIsDestroyOffScreen;	// True if the object should be destroyed when it goes off 
								// the screen, false if not.

	// Velocity of the object, both horizontal and vertical movement is possible.
	// These values are vector values, therefore object will move left if a negative
	// value is given.
	float m_fVelocityX;
	float m_fVelocityY;

	// These values stop the horizontal or vertical accelaration of the object when
	// the absolute value of the velocity is at the maximum velocity. Should only
	// be used for accelarations.
	float m_fMaxVelocityX;
	float m_fMaxVelocityY;

	// The acceleration of the object. Also sometimes the decceleration of the object.
	float m_fAccelerationX;
	float m_fAccelerationY;
};

TStrongObjectComponentPtr CreatePhysicsComponent();

#endif