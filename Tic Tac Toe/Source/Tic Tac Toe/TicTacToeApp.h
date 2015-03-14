// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2015 Media Design School
//
// File Name	: TicTacToeApp.h
// Desrciption	: TicTacToeApp declaration file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

#pragma once

#ifndef __TICTACTOEAPP_H__
#define __TICTACTOEAPP_H__

// Library Includes

// Local Includes

class CTicTacToeApp : public CGameApp {
	// Member Functions
public:
	CTicTacToeApp();

	// Creates and initializes the CTicTacToeLogic. 
	// This function is called when the app is initialized.
	virtual CGameLogic* VCreateGame();	// This is required so that CTicTacToe is not abstract.

	// Retreives the desired Icon as a file path. 
	// This is used only when the app is initialized.
	virtual std::string VGetIcon();

	// Retreives the title of the application. 
	// This is used only when the app is initialized.
	virtual std::string VGetTitle();

	// Retrieves the initial screen size of the application. 
	// This is used only when the app is initialized.
	virtual CPoint VGetScreenSetupSize();

	// Retrieves the desired style of the window using the various SDL_WindowFlags. 
	// This is used only when the app is initialized.
	virtual Uint32 VGetWindowStyle();
protected:
private:

	// Member Variables
public:
protected:
private:
};

#endif // __TICTACTOEAPP_H__