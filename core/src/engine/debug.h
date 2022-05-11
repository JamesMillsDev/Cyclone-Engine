#ifndef CYCLONE_DEBUG
#define CYCLONE_DEBUG

#include <string>
#include <vector>
#include "imgui/imgui.h"

namespace CycloneEngine
{
	enum class log_level
	{
		Info = 0,
		Warning = 1,
		Error = 2,
		Exception = 3
	};

	class std::tm;
	class log_message;

	class debug
	{
	public:
		static void set_level(log_level _level);
		static void log(const char* _message);
		static void log_warning(const char* _message);
		static void log_error(const char* _message);
		static void log_exception(const char* _message);
		static std::vector<log_message*> get_messages() { return messages; }

	private:
		static void store_message(const char* _message, log_level _level);
		static std::string get_time();
		static log_level level;
		static std::vector<log_message*> messages;

	};

	class log_message
	{
	public:
		log_message(log_level _level, const char* _message, std::string _time);
		void render() const;

	private:
		ImVec4* get_color() const;
		const char* get_level_text() const;
		log_level level;
		std::string message;
		std::string time;

	};
}

#endif // !CYCLONE_DEBUG