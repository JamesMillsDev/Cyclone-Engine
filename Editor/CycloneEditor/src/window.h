#ifndef CYCLONE_WINDOW
#define CYCLONE_WINDOW
#include "editor.h"

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
	CycloneEditor::editor* editorInstance;

};

#endif // !CYCLONE_WINDOW