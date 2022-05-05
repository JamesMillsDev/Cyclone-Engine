#ifndef CYCLONE_WINDOW
#define CYCLONE_WINDOW

class GLFWwindow;

namespace CycloneEngine
{
	class window
	{
	public:
		window(const char* _name);
		bool init();
		void run() const;
		void cleanup() const;

	private:
		GLFWwindow* windowInstance;
		const char* name;

	};
}

#endif // !CYCLONE_WINDOW