// PCH
#include"StratmanStd.h"

#include "StratmanHumanView.h"
#include "StratmanLogic.h"

CStratmanHumanView::CStratmanHumanView()
{

}

CStratmanHumanView::~CStratmanHumanView()
{

}

void CStratmanHumanView::VOnBeginDragging()
{
	if(g_pApp->m_pGame) {
		// Cast the logic to stratman logic.
		CStratmanLogic* stratmanLogic = dynamic_cast<CStratmanLogic*>(g_pApp->m_pGame);

		if(stratmanLogic) {
			stratmanLogic->OnBeginDragging();
		}
	}
	else {
	// There is no game logic.
	}
}

void CStratmanHumanView::VOnEndDragging()
{
	if(g_pApp->m_pGame) {
		// Cast the logic to stratman logic.
		CStratmanLogic* stratmanLogic = dynamic_cast<CStratmanLogic*>(g_pApp->m_pGame);

		if(stratmanLogic) {
			stratmanLogic->OnEndDragging();
		}
	}
	else {
	// There is no game logic.
	}
}