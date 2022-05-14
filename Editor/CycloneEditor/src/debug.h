#ifndef CYCLONE_DEBUG
#define CYCLONE_DEBUG

#include <string>
#include <vector>
#include "imgui/imgui.h"

namespace CycloneEngine
{
	enum class LogLevel
	{
		Info = 0,
		Warning = 1,
		Error = 2,
		Exception = 3
	};

	class std::tm;
	class LogMessage;

	class Debug
	{
	public:
		static void setLevel(LogLevel _level);
		static void log(const char* _message);
		static void logWarning(const char* _message);
		static void logError(const char* _message);
		static void logException(const char* _message);
		static std::vector<LogMessage*> getMessages() { return messages; }

	private:
		static void storeMessage(const char* _message, LogLevel _level);
		static std::string getTime();
		static LogLevel level;
		static std::vector<LogMessage*> messages;

	};

	class LogMessage
	{
	public:
		LogMessage(LogLevel _level, const char* _message, std::string _time);
		void render() const;

	private:
		ImVec4* getColor() const;
		const char* getLevelText() const;
		LogLevel level;
		std::string message;
		std::string time;

	};
}

#endif // !CYCLONE_DEBUG