#pragma once

#include <iostream>
#include <string>

// REFERENCE FROM CHERNO LOG.H
//#define LOG_TRACE(...)         ::GLCore::Log::GetLogger()->trace(__VA_ARGS__)
//#define LOG_INFO(...)          ::GLCore::Log::GetLogger()->info(__VA_ARGS__)
//#define LOG_WARN(...)          ::GLCore::Log::GetLogger()->warn(__VA_ARGS__)
//#define LOG_ERROR(...)         ::GLCore::Log::GetLogger()->error(__VA_ARGS__)
//#define LOG_CRITICAL(...)      ::GLCore::Log::GetLogger()->critical(__VA_ARGS__)

//#define LOG(...) Logger::Log(__VA_ARGS__)
#define LOG(x) Logger::Log(x)

class Logger {

// FUNCTIONS
public:
	// Delete default copy constructor by setting the function = delete
	Logger(const Logger&) = delete;

	// Better Log implementation 1/2
	static void Log(const char* message)
	{
		std::cout << "LOG_MSG: " << message << "\n" << std::endl;
	}

private:
	// Hidden constructor
	Logger() {}

// VARIABLES
public:

private:
	static Logger s_Instance;
};

// THE SINGLETON vvv aka:
// This is the lone Logger instance that is the referenced when using the Logger singleton
Logger Logger::s_Instance;
