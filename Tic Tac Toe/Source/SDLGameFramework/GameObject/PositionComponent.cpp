// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: PositionComponent.cpp
// Desrciption	: CPositionComponent implmentation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "GameStd.h"

// Library Includes

// This Include 
#include "PositionComponent.h"

// Local Includes

CPositionComponent::CPositionComponent()
	:m_position(CPoint(0, 0))
{

}

CPositionComponent::~CPositionComponent()
{

}

bool CPositionComponent::VInitialize(TiXmlElement* _pXmlData) 
{
	// Retrive the xml position component definition.
	TiXmlElement* pPosition = _pXmlData->FirstChildElement("Position");

	if(pPosition) {
		double dX = 0.0;
		double dY = 0.0;

		// Retrieve the attributes.
		pPosition->Attribute("X", &dX);
		pPosition->Attribute("Y", &dY);

		m_position = CPoint(static_cast<int>(dX), static_cast<int>(dY));
	}
	else {
		std::cerr  << "ERROR: A position component needs a position." << std::endl;
		return false;
	}

	return true;
}

void CPositionComponent::VPostInitialize()
{
	return;
}

void CPositionComponent::VUpdate(float _fDeltaTime)
{
	// Nothing to update.
	return;
}

const CPoint& CPositionComponent::GetPosition() const
{
	return m_position;
}

void CPositionComponent::SetPosition(const CPoint& _krPosition)
{
	m_position = _krPosition;
}

TStrongObjectComponentPtr CreatePositionComponent()
{
	return TStrongObjectComponentPtr(new CPositionComponent());
}

