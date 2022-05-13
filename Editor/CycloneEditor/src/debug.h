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
		static void set_level(LogLevel _level);
		static void log(const char* _message);
		static void log_warning(const char* _message);
		static void log_error(const char* _message);
		static void log_exception(const char* _message);
		static std::vector<LogMessage*> get_messages() { return messages; }

	private:
		static void store_message(const char* _message, LogLevel _level);
		static std::string get_time();
		static LogLevel level;
		static std::vector<LogMessage*> messages;

	};

	class LogMessage
	{
	public:
		LogMessage(LogLevel _level, const char* _message, std::string _time);
		void render() const;

	private:
		ImVec4* get_color() const;
		const char* get_level_text() const;
		LogLevel level;
		std::string message;
		std::string time;

	};
}

#endif // !CYCLONE_DEBUG