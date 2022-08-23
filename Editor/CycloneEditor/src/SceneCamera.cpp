#include "SceneCamera.h"

#include <glm/vec3.hpp>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "Input.h"
using namespace CycloneEngine;

namespace CycloneEditor
{
    SceneCamera::SceneCamera()
    {
        m_theta = 0;
        m_phi = 0;
        SetPosition(float3(-10, 2, 0));
        SetRotation(float3(0, 0, 0));

        m_input = Input::GetInstance();
    }

    SceneCamera::~SceneCamera() = default;

    void SceneCamera::Update(const float _dt)
    {
        // if the right button us down, increment theta and phi
        if(m_input->IsMouseButtonDown(1))
        {
            const float thetaR = glm::radians(m_theta);
            const float phiR = glm::radians(m_phi);

            // Calculate the forwards and right axis and up axis for the camera
            const float3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
            const float3 right(-sin(thetaR), 0, cos(thetaR));
            const float3 up(0, 1, 0);

            // use WASD, ZX keys to move camera around
            if(m_input->IsKeyDown(Keycode::W))
                m_position += forward * _dt * .5f;
            if(m_input->IsKeyDown(Keycode::S))
                m_position -= forward * _dt * .5f;
            if(m_input->IsKeyDown(Keycode::A))
                m_position -= right * _dt * .5f;
            if(m_input->IsKeyDown(Keycode::D))
                m_position += right * _dt * .5f;

            if(m_input->IsKeyDown(Keycode::E))
                m_position += up * _dt;
            if(m_input->IsKeyDown(Keycode::Q))
                m_position -= up * _dt;

            // get current mouse coordinates
            const float mx = m_input->GetMouseX();
            const float my = m_input->GetMouseY();
            const float turnSpeed = .1f;

            m_theta += turnSpeed * (mx - m_lastMouseX);
            m_phi += turnSpeed * (my - m_lastMouseY);

            m_lastMouseX = mx;
            m_lastMouseY = my;
        }
    }

    void SceneCamera::SetPosition(float3 _position)
    {
        m_position = _position;
    }

    void SceneCamera::SetRotation(float3 _rotation)
    {
        m_rotation = _rotation;
    }

    float3 SceneCamera::GetPosition() const
    {
        return m_position;
    }

    float3 SceneCamera::GetRotation() const
    {
        return m_rotation;
    }

    float4x4 SceneCamera::GetView() const
    {
        const float thetaR = glm::radians(m_theta);
        const float phiR = glm::radians(m_phi);
        const float3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
        return lookAt((glm::vec3)m_position, (glm::vec3)(m_position + forward), glm::vec3(0, 1, 0));
    }

    float4x4 SceneCamera::GetProjection() const
    {
        return glm::perspective(glm::pi<float>() * 0.25f, m_screenWidth / m_screenHeight, 0.1f, 1000.f);
    }

    float4x4 SceneCamera::GetProjectionView() const
    {
        return GetView() * GetProjection();
    }

    void SceneCamera::UpdateScreenSize(const float _w, const float _h)
    {
        m_screenWidth = _w;
        m_screenHeight = _h;
    }
}
