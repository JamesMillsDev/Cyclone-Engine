#include "Debug.h"

#include <string>
#include <ctime>
#include <iostream>

namespace CycloneEngine
{
	LogLevel Debug::m_level = LogLevel::Info;
	std::vector<LogMessage*> Debug::m_messages;

	void Debug::SetLevel(const LogLevel _level)
	{
		m_level = _level;
	}

	void Debug::Log(const char* _message)
	{
		StoreMessage(_message, LogLevel::Info);
	}

	void Debug::LogWarning(const char* _message)
	{
		StoreMessage(_message, LogLevel::Warning);
	}

	void Debug::LogError(const char* _message)
	{
		StoreMessage(_message, LogLevel::Error);
	}

	void Debug::LogException(const char* _message)
	{
		StoreMessage(_message, LogLevel::Exception);
	}

	void Debug::StoreMessage(const char* _message, const LogLevel _level)
	{
		m_messages.push_back(new LogMessage(_level, _message, GetTime()));
	}

	std::string Debug::GetTime()
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
		: m_level(_level), m_message(_message), m_time(std::move(_time))
	{
		
	}

	void LogMessage::Render() const
	{
		std::string constructedMessage = m_time;
		constructedMessage += "[";
		constructedMessage += GetLevelText();
		constructedMessage += "] ";
		constructedMessage += m_message;

		ImGui::TextColored(*GetColor(), constructedMessage.c_str());
	}

	ImVec4* LogMessage::GetColor() const
	{
		switch (m_level)
		{
		case LogLevel::Info: return new ImVec4(1, 1, 1, 1);
		case LogLevel::Warning: return new ImVec4(1, 1, 0, 1);
		case LogLevel::Error: return new ImVec4(1, 0, 0, 1);
		case LogLevel::Exception: return new ImVec4(0.75f, 0, 0.75f, 1);
		}

		return new ImVec4(1, 1, 1, 1);
	}

	const char* LogMessage::GetLevelText() const
	{
		switch (m_level)
		{
		case LogLevel::Info: return "INFO";
		case LogLevel::Warning: return "WARNING";
		case LogLevel::Error: return "ERROR";
		case LogLevel::Exception: return "EXCEPTION";
		}

		return "INFO";
	}

}
