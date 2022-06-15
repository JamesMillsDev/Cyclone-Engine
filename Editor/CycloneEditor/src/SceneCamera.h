#ifndef CYCLONE_SCENE_CAMERA
#define CYCLONE_SCENE_CAMERA

#include <float3.h>
#include <float4x4.h>

using CycloneEngine::float3;
using CycloneEngine::float4x4;

namespace CycloneEditor
{
	class Gizmos;
	
	class SceneCamera
	{
	public:
		SceneCamera(float _windowWidth, float _windowHeight);
		void Draw();
		void Update(float _dt);

	private:
		float4x4 m_viewMatrix;
		float4x4 m_projectionMatrix;

		friend Gizmos;
		
	};
}

#endif // !CYCLONE_SCENE_CAMERA