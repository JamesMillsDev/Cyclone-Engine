#include "Debug.h"

#include <string>
#include <ctime>
#include <iostream>

namespace CycloneEngine
{
	LogLevel Debug::level = LogLevel::Info;
	std::vector<LogMessage*> Debug::messages;

	void Debug::setLevel(const LogLevel _level)
	{
		level = _level;
	}

	void Debug::log(const char* _message)
	{
		storeMessage(_message, LogLevel::Info);
	}

	void Debug::logWarning(const char* _message)
	{
		storeMessage(_message, LogLevel::Warning);
	}

	void Debug::logError(const char* _message)
	{
		storeMessage(_message, LogLevel::Error);
	}

	void Debug::logException(const char* _message)
	{
		storeMessage(_message, LogLevel::Exception);
	}

	void Debug::storeMessage(const char* _message, const LogLevel _level)
	{
		messages.push_back(new LogMessage(_level, _message, getTime()));
	}

	std::string Debug::getTime()
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

	LogMessage::LogMessage(const LogLevel _level, const char* _message, std::string _time)
		: level(_level), message(_message), time(std::move(_time))
	{
		
	}

	void LogMessage::render() const
	{
		std::string constructedMessage = time;
		constructedMessage += "[";
		constructedMessage += getLevelText();
		constructedMessage += "] ";
		constructedMessage += message;

		ImGui::TextColored(*getColor(), constructedMessage.c_str());
	}

	ImVec4* LogMessage::getColor() const
	{
		switch (level)
		{
		case LogLevel::Info: return new ImVec4(1, 1, 1, 1);
		case LogLevel::Warning: return new ImVec4(1, 1, 0, 1);
		case LogLevel::Error: return new ImVec4(1, 0, 0, 1);
		case LogLevel::Exception: return new ImVec4(0.75f, 0, 0.75f, 1);
		}

		return new ImVec4(1, 1, 1, 1);
	}

	const char* LogMessage::getLevelText() const
	{
		switch (level)
		{
		case LogLevel::Info: return "INFO";
		case LogLevel::Warning: return "WARNING";
		case LogLevel::Error: return "ERROR";
		case LogLevel::Exception: return "EXCEPTION";
		}

		return "INFO";
	}

}
