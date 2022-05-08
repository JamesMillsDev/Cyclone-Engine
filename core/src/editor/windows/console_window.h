#ifndef CYCLONE_CONSOLE
#define CYCLONE_CONSOLE

#include "editor_window.h"

namespace CycloneEditor
{
	class console_window final : public editor_window
	{
	public:
		void render() const override;

	};
}

#endif // !CYCLONE_CONSOLE