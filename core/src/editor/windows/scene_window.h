#ifndef CYCLONE_SCENE_WINDOW
#define CYCLONE_SCENE_WINDOW

#include "editor_window.h"

namespace CycloneEditor
{
	class scene_window final : public editor_window
	{
	public:
		void render() const override;
	};
}

#endif // !CYCLONE_SCENE_WINDOW