// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: RenderComponent.cpp
// Desrciption	: CRenderComponent implementation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "GameStd.h"

// Library Includes

// This Include
#include "RenderComponent.h"

// Local Includes
#include "../Renderer/Renderer.h"
#include "AnimationComponent.h"

CRenderComponent::CRenderComponent()
	:m_pSprite(0),
	m_iLayer(0)
{

}

CRenderComponent::~CRenderComponent()
{
	CRenderer* pRenderer = g_pApp->m_pGame->GetRenderer();

	if(pRenderer) {
		if(m_pOwner) {
			pRenderer->DeregisterObject(m_pOwner->GetId());
		}
		else {
			// Can't deregister the owner since it doesn't exist.
		}
	}

	// The renderer handles the freeing of the sprite, nullify our reference instead.
	m_pSprite = 0;
}

bool CRenderComponent::VInitialize(TiXmlElement* _pXmlData)
{
	CRenderer* pRenderer = g_pApp->m_pGame->GetRenderer();

	if(!pRenderer) {
		std::cerr << "ERROR: Can't have a render component without a renderer" << std::endl;

		// Return failed to initialize.
		return false;
	}
	else {
		TiXmlElement* pResource = _pXmlData->FirstChildElement("Resource");
		if(pResource) {
			// Get the int resource from the xml.
			std::string value = pResource->FirstChild()->Value();

			// Obtain and possibly create from the renderer.
			m_pSprite = pRenderer->GetSprite(value);

			if(!m_pSprite) {
			// Failed to load sprite.
				std::cerr << "ERROR: Failed to retrieve sprite from int resource \"" << value << "\"" << std::endl;

				// Return failed to initialize.
				return false;
			}
		} 
		else {
		// No resource found in xml.
			return false;
		}

		TiXmlElement* pLayer = _pXmlData->FirstChildElement("Layer");
		if(pLayer) {
			// Get the layer from the xml.
			std::string value = pLayer->FirstChild()->Value();

			m_iLayer = atoi(value.c_str());
		}
		else {
		// No layer specified.
			std::cerr << "WARNING: No layer specified when initializing render component, was this intended?" << std::endl;

			// Set the layer to default 0 (bottom).
			m_iLayer = 0;
		}
	}

	return true;
}

void CRenderComponent::VPostInitialize()
{
	CRenderer* pRenderer = g_pApp->m_pGame->GetRenderer();

	if(!pRenderer) {
	// Renderer not found.
		std::cerr << "ERROR: Can't retrieve renderer when registering actor with renderer" << std::endl;

		// Return failed to initialize.
		return;
	}
	else {
	// Renderer retrieved successfully.
		// Register the object with the renderer, so that it can be rendered.
		pRenderer->RegisterObject(m_pOwner, m_iLayer);
	}

	return;
}

void CRenderComponent::VUpdate(float _fDeltaTime)
{
	// Nothing to update.
	return;
}

void CRenderComponent::Render()
{
	if(!m_pSprite) {
	// No sprite.
		// We need a sprite in order to render return.
		std::cerr << "ERROR: No sprite when rendering object id \"" << m_pOwner->GetId() << "\"" << std::endl;
		return;
	}

	// Get the position component.
	shared_ptr<CPositionComponent> pPositionComponent = m_pOwner->GetComponent<CPositionComponent>();

	if(!pPositionComponent) {
		std::cerr << "ERROR: No position component found when updating physics component of ObjectId ";
		std::cerr << m_pOwner->GetId() << std::endl;
		return;
	}
	else {
	// Retrieved position component fine.
	}

	// Get the position to render the object at.
	CPoint position = pPositionComponent->GetPosition();

	// See if the owner object has an animation component.
	shared_ptr<CAnimationComponent> pAnimComponent = m_pOwner->GetComponent<CAnimationComponent>();

	if(pAnimComponent) {
	// Onwer has a animation component.
		int iCurrentFrame = pAnimComponent->GetCurrentMaskToRender();

		// Render the sprite to the screen.
		g_pApp->RenderSprite(*m_pSprite, position, iCurrentFrame);
	}
	else {
	// No animation component.
		// Render the sprite to the screen normally using the first mask.
		g_pApp->RenderSprite(*m_pSprite, position, 0);
	}
}

CSprite* CRenderComponent::GetSprite() const
{
	return m_pSprite;
}

TStrongObjectComponentPtr CreateRenderComponent()
{
	return TStrongObjectComponentPtr(new CRenderComponent);
}