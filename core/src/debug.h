#ifndef CYCLONE_DEBUG
#define CYCLONE_DEBUG

#include <string>

using std::string;

namespace CycloneEngine
{
	enum log_level
	{
		INFO,
		WARNING,
		ERROR,
		EXCEPTION
	};

	class debug
	{
	public:
		static void set_level(log_level _level);
		static void log(const char* _message);
		static void log_warning(const char* _message);
		static void log_error(const char* _message);
		static void log_exception(const char* _message);

	private:
		static void try_print_message(const string& _message, log_level _level);
		static string get_message(const string& _message, log_level _level);
		static string get_time_string();
		static log_level level;

	};
}

#endif // !CYCLONE_DEBUG