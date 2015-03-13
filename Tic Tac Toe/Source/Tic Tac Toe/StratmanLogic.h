#pragma once

#ifndef __STRATMANLOGIC_H__
#define __STRATMANLOGIC_H__

// Library Includes

// Local Includes
#include "StratmanHumanView.h"
#include "WireGraph.h"


class CStratmanLogic : public CGameLogic {
	// Member Functions
public:
	CStratmanLogic();
	virtual ~CStratmanLogic();

	virtual bool VInit();
	virtual void VUpdate(float _fDeltaTime);

	void OnBeginDragging();
	void OnEndDragging();
protected:
private:
	// Member Variables
public:
protected:
private:
	CSprite m_sprite;
	CStratmanHumanView* m_pHumanView;

	int m_iDraggingNode;
	CWireGraph m_wireGraph;
};



#endif