#ifndef CYCLONE_CONSOLE
#define CYCLONE_CONSOLE

#include "EditorWindow.h"

namespace CycloneEditor
{
	class ConsoleWindow final : public EditorWindow
	{
	public:
		void render() const override;

	};
}

#endif // !CYCLONE_CONSOLE