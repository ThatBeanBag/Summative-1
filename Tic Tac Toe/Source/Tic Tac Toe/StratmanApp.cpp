
// PCH
#include "StratmanStd.h"

#include "StratmanApp.h"

#include "StratmanLogic.h"

CStratmanApp g_stratmanApp;

CGameLogic* CStratmanApp::VCreateGame()
{
	// TODO: Create a game.
	CGameLogic* pGame = new CStratmanLogic();

	if(pGame->VInit()) {
		return pGame;
	}
	else {
		return NULL;
	}

	return pGame;
}

std::string CStratmanApp::VGetIcon()
{
	// TODO: Make an actual file path to a icon image.
	return std::string("");
}

std::string CStratmanApp::VGetTitle()
{
	return std::string("Stratman");
}

CPoint CStratmanApp::VGetScreenSetupSize()
{
	return CPoint(g_kiSTRATMAN_SCREEN_WIDTH, g_kiSTRATMAN_SCREEN_HEIGHT);
}



