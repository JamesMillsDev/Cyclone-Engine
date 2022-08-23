#include "SceneCamera.h"

#include <glm/vec3.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Input.h"
using namespace CycloneEngine;

namespace CycloneEditor
{
    SceneCamera::SceneCamera(float _windowWidth, float _windowHeight)
    {
        m_viewMatrix = glm::lookAt(glm::vec3(10), glm::vec3(0), glm::vec3(0, 1, 0));
        m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f,
                                          _windowWidth / _windowHeight,
                                          0.1f, 1000.f);

    }

    void SceneCamera::Draw()
    {
    }

    void SceneCamera::Update(const float _dt)
    {
        m_input = Input::GetInstance();
        
        const float frameSpeed = m_input->IsKeyDown(Keycode::LeftShift) ? _dt * 2.0f : _dt;
        if(m_input->IsKeyDown(Keycode::W))
            m_viewMatrix = m_viewMatrix * float4x4::Translation(0, 0, frameSpeed);
    }
}
