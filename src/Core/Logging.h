#pragma once

#include <Windows.h>

#ifdef DEBUG
#include <iostream>
#include <Windows.h>  

void SetConsoleColour(int colour);
void CreateConsole();
void CloseConsole();

#define LOG_INFO(info) SetConsoleColour(15); std::cout << "INFO:  " << info << std::endl
#define LOG_ERROR(error) SetConsoleColour(12); std::cout << "ERROR:  " << error << std::endl
#define LOG_WARN(warning) SetConsoleColour(14); std::cout << "WARN: " << warning << std::endl

#define ALLOC_CONSOLE() CreateConsole()
#define CLOSE_CONSOLE() CloseConsole()

#else

#define LOG_INFO(info)
#define LOG_ERROR(error)
#define LOG_Warm(warning) 

#define ALLOC_CONSOLE() FreeConsole();
#define CLOSE_CONSOLE()

#endif // DEBUG