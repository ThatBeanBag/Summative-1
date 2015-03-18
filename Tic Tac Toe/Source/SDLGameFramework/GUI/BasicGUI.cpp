// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2015 Media Design School
//
// File Name	: BasicGUI.cpp
// Desrciption	: CBasicGUI implementation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "GameStd.h"

// Library Includes

// This Include 
#include "BasicGUI.h"

// Local Includes


CBasicGUI::CBasicGUI()
{

}

CBasicGUI::~CBasicGUI()
{
	for (unsigned int i = 0; i < m_guiElements.size(); ++i) {
		if (m_guiElements[i]) {
		// Is this element not NULL?
			// D-eallocate.
			delete m_guiElements[i];

			// Assign to NULL.
			m_guiElements[i] = NULL;
		}
	}

	for (unsigned int i = 0; i < m_guiElements.size(); ++i) {
		if (m_guiElements[i]) {
			// Is this element not NULL?
			// D-eallocate.
			delete m_guiElements[i];

			// Assign to NULL.
			m_guiElements[i] = NULL;
		}
	}

	// Clear the vector.
	m_guiElements.clear();
}

bool CBasicGUI::LoadGUIFromFile(const std::string& _strFilePath)
{
	TiXmlDocument xmlDoc;

	// Load the document from file.
	xmlDoc.LoadFile(_strFilePath.c_str());

	TiXmlElement* pRoot = xmlDoc.RootElement();

	if (!pRoot) {
	// Failed to get the root element.
		std::cerr << "ERROR: Failed to create GUI from resource \"" << _strFilePath << "\"" << std::endl;

		return false;
	}
	else {
		TiXmlElement* pButtons = pRoot->FirstChildElement("Buttons");

		if (pButtons) {
			// Loop through the child elements of pButtons and load the buttons from file.
			for (TiXmlElement* pNode = pButtons->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement()) {
				
				// Load the button.
				LoadButtonFromFile(pNode);
			}
		}

		TiXmlElement* pStatics = pRoot->FirstChildElement("Statics");

		if (pStatics) {
			// Loop through the child elements of pButtons and load the buttons from file.
			for (TiXmlElement* pNode = pStatics->FirstChildElement(); pNode; pNode = pNode->NextSiblingElement()) {

				// Load the button.
				LoadStaticFromFile(pNode);
			}
		}
	}

	return true;
}

void CBasicGUI::RegisterDelegate(const std::string& _krDelegateName, const TButtonDelegate& _krDelegate)
{
	m_delegateMap[_krDelegateName] = _krDelegate;
}

bool CBasicGUI::HandleEvents(const CAppMsg& _krMsg)
{
	for (unsigned int i = 0; i < m_guiElements.size(); ++i) {
		if (m_guiElements[i]) {
			if (m_guiElements[i]->VHandleEvents(_krMsg)) {
			// If the event is handled.
				return true;
			}
		}
	}

	return false;
}

void CBasicGUI::Render() 
{
	for (unsigned int i = 0; i < m_guiElements.size(); ++i) {
		if (m_guiElements[i]) {
			m_guiElements[i]->VRender();
		}
	}
}

void CBasicGUI::Hide()
{
	for (unsigned int i = 0; i < m_guiElements.size(); ++i) {
		if (m_guiElements[i]) {
			m_guiElements[i]->VHide();
		}
	}
}

void CBasicGUI::Show()
{
	for (unsigned int i = 0; i < m_guiElements.size(); ++i) {
		if (m_guiElements[i]) {
			m_guiElements[i]->VShow();
		}
	}
}

const std::vector<CGUIElement*> CBasicGUI::GetElements()
{
	return m_guiElements;
}

bool CBasicGUI::LoadButtonFromFile(TiXmlElement* _pXmlData)
{
	if (!_pXmlData) {
		std::cerr << "ERROR: Failed to create button" << std::endl;
		std::cerr << "Reason: Unknown" << std::endl;
		return false;
	}

	// ================================
	// Load the bounding box.
	// ================================

	TiXmlElement* pXmlBoundingBox = _pXmlData->FirstChildElement("BoundingBox");

	if (!pXmlBoundingBox) {
		std::cerr << "ERROR: Failed to create button \"" << _pXmlData->Value() << "\"" << std::endl;
		std::cerr << "Reason: Missing \"BoundingBox\" element" << std::endl;
		return false;
	}

	std::string strValue;

	double dX = 0.0;
	double dY = 0.0;
	double dWidth = 0.0;
	double dHeight = 0.0;

	EGUIAnchor eAnchor = eTOP_LEFT;

	pXmlBoundingBox->Attribute("X", &dX);
	pXmlBoundingBox->Attribute("Y", &dY);
	pXmlBoundingBox->Attribute("Width", &dWidth);
	pXmlBoundingBox->Attribute("Height", &dHeight);
	strValue = pXmlBoundingBox->Attribute("Anchor");

	if (strValue == "TR") {
		eAnchor = eTOP_RIGHT;
	}
	else if (strValue == "BL") {
		eAnchor = eBOTTOM_LEFT;
	}
	else if (strValue == "BR") {
		eAnchor = eBOTTOM_RIGHT;
	}
	else {
		eAnchor = eTOP_LEFT;
	}

	CRect rect(static_cast<int>(dX), 
			   static_cast<int>(dY), 
			   static_cast<int>(dWidth), 
			   static_cast<int>(dHeight));

	// ================================
	// Load the sprite.
	// ================================

	TiXmlElement* pXmlSprite = _pXmlData->FirstChildElement("Sprite");

	if (!pXmlSprite) {
		std::cerr << "ERROR: Failed to create button \"" << _pXmlData->Value() << "\"" << std::endl;
		std::cerr << "Reason: Missing \"Sprite\" element" << std::endl;

		return false;
	}

	bool m_bIsAlreadyThere = false;

	strValue = pXmlSprite->Attribute("Resource");

	CSprite* pSprite = NULL;

	for (unsigned int i = 0; i < m_guiSprites.size(); ++i) {
		if (m_guiSprites[i]->GetResource() == strValue) {
			m_bIsAlreadyThere = true;

			pSprite = m_guiSprites[i];
		}
	}

	if (!m_bIsAlreadyThere) {
		pSprite = new CSprite(g_pApp->LoadSprite(strValue));
		m_guiSprites.push_back(pSprite);
	}

	if (!pSprite) {
		std::cerr << "ERROR: Failed to create button \"" << _pXmlData->Value() << "\"" << std::endl;
		std::cerr << "Reason: Unable to create sprite." << std::endl;

		return false;
	}

	// ================================
	// Load the delegate.
	// ================================

	TiXmlElement* pXmlDelegate = _pXmlData->FirstChildElement("Delegate");

	if (!pXmlSprite) {
		std::cerr << "ERROR: Failed to create button \"" << _pXmlData->Value() << "\"" << std::endl;
		std::cerr << "Reason: Missing \"Delegate\" element" << std::endl;

		return false;
	}
	
	strValue = pXmlDelegate->Attribute("Name");

	TDelegateMap::iterator findIter = m_delegateMap.find(strValue);

	if (findIter == m_delegateMap.end()) {
		std::cerr << "ERROR: Failed to create button \"" << _pXmlData->Value() << "\"" << std::endl;
		std::cerr << "Reason: Delegate\"" << strValue << "\" not found." << std::endl;

		return false;
	}

	// Create the button.
	CGUIElement* pButton = new CGUIButton(m_guiSprites.back(), rect, findIter->second, eAnchor);

	m_guiElements.push_back(pButton);

	// ================================
	// Load the masks.
	// ================================

	TiXmlElement* pXmlOutMask = _pXmlData->FirstChildElement("OutMask");

	if (pXmlOutMask && !m_bIsAlreadyThere) {
		pXmlOutMask->Attribute("X", &dX);
		pXmlOutMask->Attribute("Y", &dY);
		pXmlOutMask->Attribute("Width", &dWidth);
		pXmlOutMask->Attribute("Height", &dHeight);

		rect = CRect(static_cast<int>(dX),
					 static_cast<int>(dY),
					 static_cast<int>(dWidth),
					 static_cast<int>(dHeight));

		m_guiSprites.back()->AddMask(rect);

		TiXmlElement* pXmlHoverMask = _pXmlData->FirstChildElement("HoverMask");

		if (pXmlHoverMask) {
			pXmlHoverMask->Attribute("X", &dX);
			pXmlHoverMask->Attribute("Y", &dY);
			pXmlHoverMask->Attribute("Width", &dWidth);
			pXmlHoverMask->Attribute("Height", &dHeight);

			rect = CRect(static_cast<int>(dX),
						 static_cast<int>(dY),
						 static_cast<int>(dWidth),
						 static_cast<int>(dHeight));

			m_guiSprites.back()->AddMask(rect);

			TiXmlElement* pXmlPressedMask = _pXmlData->FirstChildElement("PressedMask");

			if (pXmlPressedMask) {
				pXmlPressedMask->Attribute("X", &dX);
				pXmlPressedMask->Attribute("Y", &dY);
				pXmlPressedMask->Attribute("Width", &dWidth);
				pXmlPressedMask->Attribute("Height", &dHeight);

				rect = CRect(static_cast<int>(dX),
							 static_cast<int>(dY),
							 static_cast<int>(dWidth),
							 static_cast<int>(dHeight));

				m_guiSprites.back()->AddMask(rect);
			}
		}
	}

	return true;
}

bool CBasicGUI::LoadStaticFromFile(TiXmlElement* _pXmlData)
{
	if (!_pXmlData) {
		std::cerr << "ERROR: Failed to create static" << std::endl;
		std::cerr << "Reason: Unknown" << std::endl;
		return false;
	}

	// ================================
	// Load the bounding box.
	// ================================

	TiXmlElement* pXmlBoundingBox = _pXmlData->FirstChildElement("BoundingBox");

	if (!pXmlBoundingBox) {
		std::cerr << "ERROR: Failed to create static \"" << _pXmlData->Value() << "\"" << std::endl;
		std::cerr << "Reason: Missing \"BoundingBox\" element" << std::endl;
		return false;
	}

	std::string strValue;

	double dX = 0.0;
	double dY = 0.0;
	double dWidth = 0.0;
	double dHeight = 0.0;

	EGUIAnchor eAnchor = eTOP_LEFT;

	pXmlBoundingBox->Attribute("X", &dX);
	pXmlBoundingBox->Attribute("Y", &dY);
	pXmlBoundingBox->Attribute("Width", &dWidth);
	pXmlBoundingBox->Attribute("Height", &dHeight);
	strValue = pXmlBoundingBox->Attribute("Anchor");

	if (strValue == "TR") {
		eAnchor = eTOP_RIGHT;
	}
	else if (strValue == "BL") {
		eAnchor = eBOTTOM_LEFT;
	}
	else if (strValue == "BR") {
		eAnchor = eBOTTOM_RIGHT;
	}
	else {
		eAnchor = eTOP_LEFT;
	}

	CRect rect(static_cast<int>(dX),
		static_cast<int>(dY),
		static_cast<int>(dWidth),
		static_cast<int>(dHeight));

	// ================================
	// Load the sprite.
	// ================================

	TiXmlElement* pXmlSprite = _pXmlData->FirstChildElement("Sprite");

	if (!pXmlSprite) {
		std::cerr << "ERROR: Failed to create button \"" << _pXmlData->Value() << "\"" << std::endl;
		std::cerr << "Reason: Missing \"Sprite\" element" << std::endl;

		return false;
	}

	bool m_bIsAlreadyThere = false;

	strValue = pXmlSprite->Attribute("Resource");

	CSprite* pSprite = NULL;

	for (unsigned int i = 0; i < m_guiSprites.size(); ++i) {
		if (m_guiSprites[i]->GetResource() == strValue) {
			m_bIsAlreadyThere = true;

			pSprite = m_guiSprites[i];
		}
	}

	if (!m_bIsAlreadyThere) {
		pSprite = new CSprite(g_pApp->LoadSprite(strValue));
		m_guiSprites.push_back(pSprite);
	}

	if (!pSprite) {
		std::cerr << "ERROR: Failed to create button \"" << _pXmlData->Value() << "\"" << std::endl;
		std::cerr << "Reason: Unable to create sprite." << std::endl;

		return false;
	}

	m_guiElements.push_back(new CGUIStatic(pSprite, rect, eAnchor));

	return true;
}



