// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: Renderer.cpp
// Desrciption	: CRenderer implementation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "GameStd.h"

// Library Includes

// This Include
#include "Renderer.h"

// Local Includes


CRenderer::CRenderer()
{

}

CRenderer::~CRenderer()
{
	TResourceToSpriteMap::iterator iter;

	// Deallocated memory used by sprites.
	for(iter = m_sprites.begin(); iter != m_sprites.end(); ++iter) {
		// Deallocated memory.
		delete iter->second;

		iter->second = 0;
	}
	
	// Clear lists.
	m_sprites.clear();
	m_registeredObjects.clear();
}

void CRenderer::RenderGameObjects()
{
	TLayerObjectIdMap::iterator mapIter;
	std::list<TGameObjectId>::iterator listIter;

	// Iterate through layers in order, to render in Z-Order.
	for(mapIter = m_registeredObjects.begin(); mapIter != m_registeredObjects.end(); ++mapIter) {
		// Iterate through all objects the curent layer.
		for(listIter = mapIter->second.begin(); listIter != mapIter->second.end(); ++listIter) {
			CGameObject* pObject = g_pApp->m_pGame->GetGameObject(*listIter);

			assert(pObject);
			
			// Obtain the render component of the object.
			shared_ptr<CRenderComponent> pRenderComponent = pObject->GetComponent<CRenderComponent>();

			assert(pRenderComponent); // All objects registered should have a render component.

			// Render the component.
			pRenderComponent->Render();
		}
	}
}

void CRenderer::RegisterObject(CGameObject* _pObject, int _iLayer)
{
	// Make sure the object exists.
	assert(_pObject);

	if(_pObject) {
		// Get the render component of the object.
		shared_ptr<CRenderComponent> pRenderComponent = _pObject->GetComponent<CRenderComponent>();

		// Make sure only components with render components are registered.
		assert(pRenderComponent);

		if(pRenderComponent) {
			// Try to find the layer to insert the object into.
			TLayerObjectIdMap::iterator findIter = m_registeredObjects.find(_iLayer);

			if(findIter != m_registeredObjects.end()) {
			// Found the layer.
				// Insert.
				findIter->second.push_back(_pObject->GetId());
			}
			else {
			// Couldn't find layer.
				// Create a new layer.
				std::list<TGameObjectId> listTemp;

				// Add object to layer.
				listTemp.push_back(_pObject->GetId());

				// Insert layer into map.
				m_registeredObjects[_iLayer] = listTemp;
			}
		}
		else {
		// No render component.
			std::cerr << "ERROR: Only objects with a render component should be registered with the renderer" << std::endl;\
			return;
		}
	}
}

void CRenderer::DeregisterObject(TGameObjectId _id)
{
	TLayerObjectIdMap::iterator mapIter;
	std::list<TGameObjectId>::iterator listIter;

	// Iterate through layers in order, to render in Z-Order.
	for(mapIter = m_registeredObjects.begin(); mapIter != m_registeredObjects.end(); ++mapIter) {
		// Iterate through all objects the curent layer.
		for(listIter = mapIter->second.begin(); listIter != mapIter->second.end(); ++listIter) {
			if(*listIter == _id) {
				mapIter->second.erase(listIter);
				return;
			}
		}
	}
}

CSprite* CRenderer::GetSprite(const std::string& _krstrFile)
{
	TResourceToSpriteMap::iterator findIter = m_sprites.find(_krstrFile);

	if(findIter != m_sprites.end()) {
		return findIter->second;
	} 
	else {
	// Couldn't find sprite by specified resource.
		// Attempt to load it.
		CSprite sprite = g_pApp->LoadSprite(_krstrFile);

		if(!sprite.GetSprite()) {
		// Failed to load.

			// Return NULL pointer.
			return 0;
		} 
		else {
		// Load successfull.
			// Allocate memory.
			CSprite* pSprite = new CSprite(sprite);

			// Insert into resource to sprite map.
			m_sprites[_krstrFile] = pSprite;

			return pSprite;
		}
	}
}

