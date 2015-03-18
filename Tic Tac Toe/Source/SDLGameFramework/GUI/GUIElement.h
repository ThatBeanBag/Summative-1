// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2015 Media Design School
//
// File Name	: GUIElement.h
// Desrciption	: CGUIElement declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef __GUIELEMENT_H__
#define __GUIELEMENT_H__

// Library Includes

// Local Includes

// ======================================================================
// The EGUIAnchor enumerator defines how the position of a GUIElement
// should be interpreted. 
// ======================================================================

enum EGUIAnchor {
	eTOP_LEFT,
	eTOP_RIGHT,
	eBOTTOM_LEFT,
	eBOTTOM_RIGHT
};

class CGUIElement {
	// Member Functions
public:
	CGUIElement();
	CGUIElement(const CRect& _krBoundingBox, EGUIAnchor _eAnchor = eTOP_LEFT);
	CGUIElement(int _iBoxX, int _iBoxY, int _iBoxWidth = 0, int _iBoxHeight = 0, EGUIAnchor _eAnchor = eTOP_LEFT);

	// Makes a GUI element with only a position, instead of bounding box.
	// This is useful when a bounding box is not required in event handling.
	CGUIElement(const CPoint& _krPosition, EGUIAnchor _eAnchor = eTOP_LEFT);

	~CGUIElement();

	// Presents the GUI element to the screen. This is done usually with a call to the application layer.
	// Derived classes must implement this if they are to be non-abstract even if they leave it empty (as some might).
	virtual void VRender() = 0;

	virtual bool VHandleEvents(const CAppMsg& _krMsg);

	// Sets m_bIsShown to true, allowing the element to handle events and presented to the screen.
	virtual void VShow();
	// Makes the element inactive, disallowing it from handling events and being presented to the screen.
	virtual void VHide();

	// Retrieves the position of the GUI element in relation to the world, instead of in relation to it's anchor.
	CPoint GetWorldPosition() const;

	// Retrieves the bounding box of the GUI element in relation to the world, instead of in relation to it's anchor.
	CRect GetWorldRect() const;

protected:
private:

	// Member Variables
public:
protected:
	CRect m_boundingBox;	// The bounding box of the element. Used in handling events.
							// When width = 0 and height = 0 the box is just a position 
							// on the screen.
	EGUIAnchor m_eAnchor;	// Defines where to anchor the position of the button from.

	bool m_bIsShown;		// True if the element should handle events and be shown.
private:
};

#endif	// __BUTTON_H__