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

//
//BOOL WINAPI HandlerRoutine(DWORD _dwCtrlType);
//
////==========================================================
//// WinMain() is the entry point to the application.
////
//// It triggers the initialization sequence and enters a 
//// message processing loop. Giving control to the CGameApp.
////==========================================================
//
//int WINAPI WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow)
//{
//	/*#ifdef _DEBUG
//		RedirectIOToConsole();
//
//		std::cout << "========================" << std::endl;
//		std::cout << "Debugging console loaded" << std::endl;
//		std::cout << "========================";
//		std::cout << std::endl << std::endl;
//
//		if(SetConsoleCtrlHandler(HandlerRoutine, TRUE) == FALSE) {
//			std::cout << "Unable to set console ctrl handler!" << std::endl;
//			return 0;
//		}
//	#endif*/
//
//	MSG msg;
//
//	ZeroMemory(&msg, sizeof(msg));
//
//	// Perform the initialization sequence.
//	if(!g_pApp->VInitialize(_hInstance, _lpCmdLine)) {
//	// Failed to initialize.
//		g_pApp->OnClose();
//		return 0;
//	}
//
//	while(msg.message != WM_QUIT && g_pApp->IsRunning()) {
//		if(PeekMessage(&msg, 0, 0, 0, PM_REMOVE)) {
//			// Translate any accelerator keys.
//			TranslateMessage(&msg);
//
//			// Send the message to the window proc.
//			DispatchMessage(&msg);
//		}
//		else {
//			// Update the game.
//			g_pApp->Update();
//		}
//	}
//
//	// Return to windows.
//	return static_cast<int>(msg.wParam);
//}
//
//BOOL WINAPI HandlerRoutine(DWORD _dwCtrlType)
//{
//	switch(_dwCtrlType) {
//		case CTRL_C_EVENT: {
//			std::cout << "CTRL+C event triggered" << std::endl;
//
//			if(g_pApp) {
//				g_pApp->OnClose();
//			}
//
//			break;
//		}
//		case CTRL_BREAK_EVENT: {
//			std::cout << "CTRL+BREAK event triggered" << std::endl;
//
//			if(g_pApp) {
//				g_pApp->OnClose();
//			}
//
//			break;
//	   }
//		case CTRL_CLOSE_EVENT: {
//			std::cout << "Console is being closed" << std::endl;
//
//			if(g_pApp) {
//				g_pApp->OnClose();
//			}
//
//			break;
//		}
//	}
//
//	return TRUE;
//}