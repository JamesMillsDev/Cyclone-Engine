#include "debug.h"

#include <ctime>
#include <iostream>

namespace CycloneEngine
{
	log_level debug::level = INFO;

	void debug::set_level(const log_level _level)
	{
		level = _level;
	}

	void debug::log(const char* _message)
	{
		try_print_message(_message, INFO);
	}

	void debug::log_warning(const char* _message)
	{
		try_print_message(_message, WARNING);
	}

	void debug::log_error(const char* _message)
	{
		try_print_message(_message, ERROR);
	}

	void debug::log_exception(const char* _message)
	{
		try_print_message(_message, EXCEPTION);
	}

	void debug::try_print_message(const string& _message, const log_level _level)
	{
		if (static_cast<int>(_level) >= static_cast<int>(level))
			std::cout << get_message(_message, _level);
	}

	string debug::get_message(const string& _message, const log_level _level)
	{
		switch (_level)
		{
			case INFO: return "[" + get_time_string() + "]\x1B[37m[INFO]\033[0m " + _message + "\n";
			case WARNING: return "[" + get_time_string() + "]\x1B[33m[WARNING]\033[0m " + _message + "\n";
			case ERROR: return "[" + get_time_string() + "]\x1B[31m[ERROR]\033[0m " + _message + "\n";
			case EXCEPTION: return "[" + get_time_string() + "]\x1B[31m[EXCEPTION]\033[0m " + _message + "\n";
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