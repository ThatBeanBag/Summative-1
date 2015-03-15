// 
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2005 - 2014 Media Design School
//
// File Name	: main.cpp
// Desrciption	: main implementation file.
// Author		: Hayden Asplet.
// Mail			: hayden.asplet@mediadesignschool.com
//

// PCH
#include "GameStd.h"

// Library Includes

// Local Includes
//#include "Console\Console.h"

int main(int argc, char* args[])
{
	// Initailize the application.
	if(!g_pApp->VInitialize()) {
		g_pApp->OnClose();
	}

	SDL_Event event;

	// Clear the memory block of event.
	memset(&event, 0, sizeof(event));

	while(event.type != SDL_QUIT && g_pApp->IsRunning()) {
		if(SDL_PollEvent(&event)) {
			// Handle the event.
			g_pApp->MsgProc(event);
		}
		else {
			g_pApp->Update();
		}
	}

	SDL_Quit();

	return 0;
}