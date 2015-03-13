// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: Physics.h
// Desrciption	: CPhysics declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef __PHYSICS_H__
#define __PHYSICS_H__

// Library Includes

// Local Includes
#include "../GameObject/GameObject.h"

class CPhysics {
	// Member Functions
public:
	CPhysics();
	~CPhysics();

	void Update(float _fDeltaTime);
	void CheckCollisions(CGameObject* _pObject, const CRect& newBoundingBox);

	void RegisterObject(TGameObjectId _id);
	void DeregisterObject(TGameObjectId _id);
protected:
private:

	// Member Variables
public:
protected:
private:
	std::list<TGameObjectId> m_registeredObjects;
};

#endif