#include <windows.h>
#include "Platform/Windows/WindowsApplication.h"

_Use_decl_annotations_
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, PSTR cmdline, int cmdshow) {
	hInstancePrev;
	cmdline;

	WindowsApplication application;
	return application.Run(hInstance, cmdshow);
}
