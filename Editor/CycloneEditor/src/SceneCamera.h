#ifndef CYCLONE_SCENE_CAMERA
#define CYCLONE_SCENE_CAMERA

#include <float3.h>
#include <float4x4.h>

namespace CycloneEngine
{
	class Input;
}

using CycloneEngine::float3;
using CycloneEngine::float4x4;

namespace CycloneEditor
{
	class Gizmos;
	
	class SceneCamera
	{
	public:
		SceneCamera();
		~SceneCamera();

		void Update(float _dt);
		void SetPosition(float3 _position);
		void SetRotation(float3 _rotation);
		float3 GetPosition() const;
		float3 GetRotation() const;
		float4x4 GetView() const;
		float4x4 GetProjection() const;
		float4x4 GetProjectionView() const;
		void UpdateScreenSize(float _w, float _h);

	private:
		float4x4 m_worldTransform;
		float4x4 m_viewTransform;
		float4x4 m_projectionTransform;
		float4x4 m_projectionViewTransform;

		float m_theta; // z rotation
		float m_phi; // x rotation

		float m_lastMouseX = 0.f;
		float m_lastMouseY = 0.f;

		float3 m_position; // local
		float3 m_rotation; // local

		float m_screenWidth;
		float m_screenHeight;

		friend Gizmos;

		CycloneEngine::Input* m_input;
		
	};
}

#endif // !CYCLONE_SCENE_CAMERA