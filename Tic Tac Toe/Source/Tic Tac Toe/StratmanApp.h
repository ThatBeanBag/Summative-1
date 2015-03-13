#pragma once

#ifndef __STRATMANAPP_H__
#define __STRATMANAPP_H__

class CStratmanApp : public CGameApp {
	// Member Functions
public:
	virtual CGameLogic* VCreateGame();
	virtual std::string VGetIcon();
	virtual std::string VGetTitle();
	virtual CPoint VGetScreenSetupSize();
protected:
private:

	// Member Variables
public:
protected:
private:
};

#endif