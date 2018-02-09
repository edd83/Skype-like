#pragma once

#include <string>
#include "eErrorCode.h"
#include "eCommandId.h"

class Debug
{
public:
	static void Log(std::string const&);
	static void LogError(std::string const&);

	static void LogCommandId(std::string const&, int, std::string const& = "");
	static void LogErrorCode(std::string const&, int, std::string const& = "");

	static void enableDebug(bool);

private:
	static bool _debugEnabled;

};
