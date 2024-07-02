#ifndef ERRORLOGGER_H
#define ERRORLOGGER_H

class ErrorLogger
{
private:
	ErrorLogger() = default;
	ErrorLogger(const ErrorLogger&) = delete;
	ErrorLogger(ErrorLogger&&) = delete;
	ErrorLogger& operator=(const ErrorLogger&) = delete;
	ErrorLogger& operator=(ErrorLogger&&) = delete;
	~ErrorLogger() = default;
	
public:
	static void Log(std::string message);
	static void Log(HRESULT hr, std::string message);
	static void Log(HRESULT hr, std::wstring message);
};

#endif // ERRORLOGGER_H