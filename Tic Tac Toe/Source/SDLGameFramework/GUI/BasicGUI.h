// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2015 Media Design School
//
// File Name	: BasicGUI.h
// Desrciption	: CBasicGUI declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once 

#ifndef __BASICGUI_H__
#define __BASICGUI_H__

// Library Includes

// Local Includes
#include "GUIButton.h"
#include "GUIStatic.h"

class CBasicGUI {
	typedef std::map<std::string, TButtonDelegate> TDelegateMap;

	// Member Functions
public:
	CBasicGUI();
	~CBasicGUI();

	// Register a delegate so that it can be assigned to buttons through it's name only. 
	// The delegate must be registered before the LoadGUIFromFile() functions is called, otherwise
	// it will fail to load.
	// The _krDelegateName should always be Class::Function.
	void RegisterDelegate(const std::string& _krDelegateName, const TButtonDelegate& _krDelegate);

	// Loads the ui from a file 
	bool LoadGUIFromFile(const std::string& _strFilePath);

	bool HandleEvents(const CAppMsg& _krMsg);
	void Render();

	void Hide();
	void Show();

	const std::vector<CGUIElement*> GetElements();
protected:
private:
	bool LoadButtonFromFile(TiXmlElement* _pXmlData);
	bool LoadStaticFromFile(TiXmlElement* _pXmlData);

	// Member Variables
public:
protected:
	std::vector<CGUIElement*> m_guiElements;
	std::vector<CSprite*> m_guiSprites;
	TDelegateMap m_delegateMap;
private:
};

#endif // __BASICGUI_H__

