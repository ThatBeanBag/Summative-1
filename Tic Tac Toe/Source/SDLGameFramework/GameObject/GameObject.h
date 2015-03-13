// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: GameObject.h
// Desrciption	: CGameObject declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

// Library Includes
#include <typeindex>

// Local Includes

class CObjectComponent;

typedef unsigned long TGameObjectId;
typedef shared_ptr<CObjectComponent> TStrongObjectComponentPtr;

// type_index allows for the retrieval of ObjectComponents with compile-time
// casting. This could also be achieved by giving each Component Type a unique
// identifier, however this way, different component types are easier to create.
typedef std::map<std::type_index, TStrongObjectComponentPtr> TObjectComponents;

const TGameObjectId g_kINVALID_OBJECT_ID = 0;

class CGameObject {
	// Member Functions
public:
	explicit CGameObject(TGameObjectId _id);	// Explicit constructor, disallows implicit conversion from usigned 
												// long to CGameObject.
	~CGameObject();

	bool Initialize(const std::string& _strType);
	void PostInitialize();			// Runs the post initialization sequence which calls the PostInitialize() 
									// method of each component.
	void Update(float _fDeltaTime);	// Updates the components of this object.
	void DestroyComponents();		// Destroys the components, should be called before object is destroyed.

	// Accessors
	TGameObjectId GetId() const;
	const std::string& GetType() const;

	template<typename ComponentType>
	shared_ptr<ComponentType> GetComponent();	// Retreives a component of the specified type, if none found a null
												// shared_ptr is returned. 

	void AddComponent(TStrongObjectComponentPtr _pComponent);	// Should only be called from within the CObjectFactory.
protected:
private:

	// Member Variables
public:
protected:	
private:
	TObjectComponents m_objectComponents;	// The components of this object.
	TGameObjectId m_id;		// This object's unique id.

	std::string m_strType;	// The type of this object.
};

template<typename ComponentType>
shared_ptr<ComponentType> CGameObject::GetComponent()
{
	std::type_index index(typeid(ComponentType));

	// Find the component at the index.
	TObjectComponents::iterator findIter = m_objectComponents.find(index);

	if(findIter != m_objectComponents.end()) {
	// This actor has a component of the specified type.
		// Cast to the specified type and return.
		return static_pointer_cast<ComponentType>(m_objectComponents[index]);
	}
	else {
		// return a NULL component of the ComponentType.
		return shared_ptr<ComponentType>();
	}
}

#endif