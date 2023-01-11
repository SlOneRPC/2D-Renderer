#include "Logging.h"

#ifdef DEBUG

FILE* fStream;
HANDLE hConsole;

void SetConsoleColour(int colour) {
	SetConsoleTextAttribute(hConsole, colour);
}

void CreateConsole() {
	AllocConsole();
	freopen_s(&fStream, "CONOUT$", "w", stdout);
	SetConsoleTitle(L"Renderer DEBUG");
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

void CloseConsole() {
	fclose(fStream);
	FreeConsole();
}

#endif