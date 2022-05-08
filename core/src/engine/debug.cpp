#include "debug.h"

#include <string>
#include <ctime>
#include <iostream>

namespace CycloneEngine
{
	log_level debug::level = log_level::Info;
	std::vector<log_message*> debug::messages;

	void debug::set_level(const log_level _level)
	{
		level = _level;
	}

	void debug::log(const char* _message)
	{
		store_message(_message, log_level::Info);
	}

	void debug::log_warning(const char* _message)
	{
		store_message(_message, log_level::Warning);
	}

	void debug::log_error(const char* _message)
	{
		store_message(_message, log_level::Error);
	}

	void debug::log_exception(const char* _message)
	{
		store_message(_message, log_level::Exception);
	}

	void debug::store_message(const char* _message, const log_level _level)
	{
		messages.push_back(new log_message(_level, _message, get_time()));
	}

	std::string debug::get_time()
	{
		std::time_t t = std::time(nullptr);
		std::tm now = std::tm();
		localtime_s(&now, &t);

		int hour = now.tm_hour % 12;
		std::string hourString = std::to_string(hour);
		if (hour < 10)
			hourString = "0" + hourString;

		int min = now.tm_min;
		std::string minString = std::to_string(min);
		if (min < 10)
			minString = "0" + minString;

		int sec = now.tm_sec;
		std::string secString = std::to_string(sec);
		if (sec < 10)
			secString = "0" + secString;

		return "[" + hourString + ":" + minString + ":" + secString + "] ";
	}

	log_message::log_message(const log_level _level, const char* _message, std::string _time)
		: level(_level), message(_message), time(std::move(_time))
	{
		
	}

	void log_message::render() const
	{
		std::string constructedMessage = time;
		constructedMessage += "[";
		constructedMessage += get_level_text();
		constructedMessage += "] ";
		constructedMessage += message;

		ImGui::TextColored(*get_color(), constructedMessage.c_str());
	}

	ImVec4* log_message::get_color() const
	{
		switch (level)
		{
		case log_level::Info: return new ImVec4(1, 1, 1, 1);
		case log_level::Warning: return new ImVec4(1, 1, 0, 1);
		case log_level::Error: return new ImVec4(1, 0, 0, 1);
		case log_level::Exception: return new ImVec4(0.75f, 0, 0.75f, 1);
		}

		return new ImVec4(1, 1, 1, 1);
	}

	const char* log_message::get_level_text() const
	{
		switch (level)
		{
		case log_level::Info: return "INFO";
		case log_level::Warning: return "WARNING";
		case log_level::Error: return "ERROR";
		case log_level::Exception: return "EXCEPTION";
		}

		return "INFO";
	}

}
