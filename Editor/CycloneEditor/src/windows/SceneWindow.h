#ifndef CYCLONE_SCENE_WINDOW
#define CYCLONE_SCENE_WINDOW

#include "EditorWindow.h"

namespace CycloneEditor
{
	class SceneWindow final : public EditorWindow
	{
	public:
		void render() const override;
	};
}

#endif // !CYCLONE_SCENE_WINDOW