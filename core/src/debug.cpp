#include "debug.h"

#include <ctime>
#include <iostream>
#include <cstdio>


namespace CycloneEngine
{
	log_level debug::level = Info;
	HANDLE debug::consoleHandle;

	void debug::init()
	{
		consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	void debug::set_level(const log_level _level)
	{
		level = _level;
	}

	void debug::log(const char* _message)
	{
		try_print_message(_message, Info);
	}

	void debug::log_warning(const char* _message)
	{
		try_print_message(_message, Warning);
	}

	void debug::log_error(const char* _message)
	{
		try_print_message(_message, Error);
	}

	void debug::log_exception(const char* _message)
	{
		try_print_message(_message, Exception);
	}

	void debug::try_print_message(const string& _message, const log_level _level)
	{
		if (static_cast<int>(_level) >= static_cast<int>(level))
			printf(get_message(_message, _level).c_str());
	}

	string debug::get_message(const string& _message, const log_level _level)
	{
		switch (_level)
		{
			case Info:
				SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
				return "[" + get_time_string() + "][INFO] " + _message + "\n";

			case Warning:
				SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED | FOREGROUND_GREEN);
				return "[" + get_time_string() + "][WARNING] " + _message + "\n";

			case Error:
				SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
				return "[" + get_time_string() + "][ERROR] " + _message + "\n";

			case Exception: 
				SetConsoleTextAttribute(consoleHandle, FOREGROUND_RED);
				return "[" + get_time_string() + "][EXCEPTION] " + _message + "\n";
		}

		return "";
	}

	string debug::get_time_string()
	{
		std::time_t t = std::time(nullptr);
		std::tm* now = std::localtime(&t);

		int hour = now->tm_hour % 12;
		string hourString = std::to_string(hour);
		if (hour < 10)
			hourString = "0" + hourString;

		int min = now->tm_min;
		string minString = std::to_string(min);
		if (min < 10)
			minString = "0" + minString;

		int sec = now->tm_sec;
		string secString = std::to_string(sec);
		if (sec < 10)
			secString = "0" + secString;
		
		return hourString + ":" + minString + ":" + secString;
	}

}