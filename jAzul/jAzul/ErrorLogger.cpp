#include "ErrorLogger.h"

#include "StringConverter.h"
#include <comdef.h>

void ErrorLogger::Log(std::string message)
{
	std::string e_str = "Error: " + message;
	MessageBoxA(NULL, e_str.c_str(), "Error!!", MB_ICONERROR);
}

void ErrorLogger::Log(HRESULT hr, std::string message)
{
	_com_error error(hr);
	std::string e_str = "Error: " + message + "\n" + error.ErrorMessage();	
	MessageBoxW(NULL, StringConverter::StringToWide(e_str).c_str(), L"Error!!", MB_ICONERROR);
}

void ErrorLogger::Log(HRESULT hr, std::wstring message)
{
	_com_error error(hr);
	// std::string e_str = "Error: " + message + "\n" + error.ErrorMessage();
	MessageBoxW(NULL, message.c_str(), L"Error!!", MB_ICONERROR);
}
