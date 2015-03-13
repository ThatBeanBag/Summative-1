// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: ObjectFactory.cpp
// Desrciption	: CObjectFactory implementation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "GameStd.h"

// Library Includes

// This Include
#include "ObjectFactory.h"

// Local Includes

CObjectFactory::CObjectFactory()
	:m_lastObjectId(g_kINVALID_OBJECT_ID)
{
	// Register component creators.
	m_objectComponentCreators["PositionComponent"] = CreatePositionComponent;
	m_objectComponentCreators["PhysicsComponent"] = CreatePhysicsComponent;
	m_objectComponentCreators["RenderComponent"] = CreateRenderComponent;
	m_objectComponentCreators["AnimationComponent"] = CreateAnimationComponent;
	m_objectComponentCreators["DestroyAfterComponent"] = CreateDestroyAfterComponent;
}

CObjectFactory::~CObjectFactory()
{

}

CGameObject* CObjectFactory::CreateObject(const std::string& _krObjectResource)
{
	TiXmlDocument xmlDoc;

	// Try to find an already loaded xml.
	TXmlResourceMap::iterator findIter = m_xmlResources.find(_krObjectResource);

	if(findIter != m_xmlResources.end()) {
	// This xml has already been loaded.
		xmlDoc = findIter->second;
	}
	else {
		// Load the xml document.
		xmlDoc.LoadFile(_krObjectResource.c_str());

		// Insert the newly loaded xml into the resource map.
		m_xmlResources[_krObjectResource] = xmlDoc;
	}

	// Obtain the root element.
 	TiXmlElement* pRoot = xmlDoc.RootElement();


	if(!pRoot) {
		std::cerr << "ERROR: Failed to create object from resource \"" << _krObjectResource << "\"" << std::endl;

		// Return NULL pointer.
		return 0;
	}

	// Create the instance of the CGameObject.
	CGameObject* pObject(new CGameObject(GetNextObjectId()));

	if(!pObject) {
		std::cerr << "ERROR: Failed to create object from resource \"" << _krObjectResource << "\"" << std::endl;

		// Return NULL pointer.
		return 0;
	}

	if(!pObject->Initialize(pRoot->Attribute("type"))) {
		std::cerr << "ERROR: Failed to initialize object from resource \"" << _krObjectResource << "\"" << std::endl;

		// De-allocate.
		delete pObject;

		// Return NULL pointer
		return 0;
	}

	// Loop through all child elements of the root node for components.
	for(TiXmlElement* pNode = pRoot->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement()) {
		TStrongObjectComponentPtr pComponent(CreateComponent(pNode));

		if(pComponent) {
			pObject->AddComponent(pComponent);
			pComponent->SetOwner(pObject);
		}
		else {
			std::cerr << "ERROR: Failed to create component and actor from resource \"" << _krObjectResource << "\"" << std::endl;

			// Return NULL pointer.
			return 0;
		}
	}

	// Run the post initialize sequence.
	pObject->PostInitialize();

	//std::cout << "SUCCESS: Object created with id " << pObject->GetId(); 
	//std::cout << " and resource \"" << _krObjectResource << "\"" << std::endl;

	// Return successfully created object
	return pObject;
}

TStrongObjectComponentPtr CObjectFactory::CreateComponent(TiXmlElement* _pXmlData)
{
	std::string name(_pXmlData->Value());

	TStrongObjectComponentPtr pComponent;

	auto findIter = m_objectComponentCreators.find(name);
	if(findIter != m_objectComponentCreators.end()) {
		ObjectComponentCreator componentCreator = findIter->second;
		
		pComponent = componentCreator();
	}
	else {
		std::cerr << "ERROR: Couldn't find ObjectComponent named: " << name << std::endl;

		// Return NULL shared_ptr.
		return TStrongObjectComponentPtr();
	}

	assert(pComponent);

	if(!pComponent->VInitialize(_pXmlData)) {
		std::cerr << "ERROR: Component failed to initialize: " << name << std::endl;

		// Return NULL shared_ptr.
		return TStrongObjectComponentPtr();
	}

	return pComponent;
}

TGameObjectId CObjectFactory::GetNextObjectId()
{
	++m_lastObjectId;

	return m_lastObjectId;
}