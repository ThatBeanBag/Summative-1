// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: PositionComponent.h
// Desrciption	: CPositionComponent declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef __POSITIONCOMPONENT_H__
#define __POSITIONCOMPONENT_H__

// Library Includes

// Local Includes
#include "ObjectComponent.h"

//==========================================================
// PositionComponent is a very simple component as it just
// defines the position of the object and doesn't register
// this object with the physics system.
//
// Almost every object will have a position component as it
// is required in most other components.
//==========================================================

class CPositionComponent : public CObjectComponent {
	// Member Functions
public:
	CPositionComponent();
	~CPositionComponent();

	virtual bool VInitialize(TiXmlElement* _pXmlData);
	virtual void VPostInitialize();
	virtual void VUpdate(float _fDeltaTime);

	// Accessors
	const CPoint& GetPosition() const;

	void SetPosition(const CPoint& _krPosition);
protected:
private:

	// Member Variables
public:
protected:
private:
	CPoint m_position;	// The world coordinates of the object.
};

TStrongObjectComponentPtr CreatePositionComponent();

#endif