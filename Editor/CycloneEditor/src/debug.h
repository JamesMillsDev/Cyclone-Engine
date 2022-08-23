#ifndef CYCLONE_DEBUG
#define CYCLONE_DEBUG

#include <string>
#include <vector>
#include "imgui/imgui.h"

using std::string;
using std::vector;

namespace CycloneEngine
{
	
	enum class LogLevel
	{
		Info = 0,
		Warning = 1,
		Error = 2,
		Exception = 3
	};

	struct std::tm;
	class LogMessage;
	
	typedef vector<LogMessage*> LogMessages;

	class Debug
	{
	public:
		static void SetLevel(LogLevel _level);
		static void Log(const char* _message);
		static void LogWarning(const char* _message);
		static void LogError(const char* _message);
		static void LogException(const char* _message);
		static LogMessages GetMessages() { return m_messages; }

	private:
		static void StoreMessage(const char* _message, LogLevel _level);
		static string GetTime();
		static LogLevel m_level;
		static LogMessages m_messages;

	};

	class LogMessage
	{
	public:
		LogMessage(LogLevel _level, const char* _message, string _time);
		void Render() const;

	private:
		ImVec4* GetColor() const;
		const char* GetLevelText() const;
		LogLevel m_level;
		string m_message;
		string m_time;

	};
}

#endif // !CYCLONE_DEBUG