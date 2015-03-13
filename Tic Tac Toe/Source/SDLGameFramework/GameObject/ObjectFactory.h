// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: ObjectFactory.h
// Desrciption	: CObjectFactory declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef __OBJECTFACTORY_H__
#define __OBJECTFACTORY_H__

// Library Includes

// Local Includes
#include "GameObject.h"
#include "ObjectComponent.h"
#include "PositionComponent.h"
#include "PhysicsComponent.h"
#include "RenderComponent.h"
#include "AnimationComponent.h"
#include "DestroyAfterComponent.h"

typedef TStrongObjectComponentPtr (*ObjectComponentCreator)();
typedef std::map<std::string, ObjectComponentCreator> ObjectComponentCreatorMap;
typedef std::map<std::string, TiXmlDocument> TXmlResourceMap;

class CObjectFactory {
	// Member Functions
public:
	CObjectFactory();
	virtual ~CObjectFactory();

	CGameObject* CreateObject(const std::string& _krObjectResource);
protected:
private:
	TStrongObjectComponentPtr CreateComponent(TiXmlElement* _pXmlData);
	TGameObjectId GetNextObjectId();

	// Member Variables
public:
protected:
	ObjectComponentCreatorMap m_objectComponentCreators;	// Protected so that a devired class can add it's own creators.
private:
	TGameObjectId m_lastObjectId;

	TXmlResourceMap m_xmlResources;		// This is so that we don't need to keep loading xml's from file.
};


#endif