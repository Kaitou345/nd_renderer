#include <pch.h>
#include "Camera.h"

Camera::Camera(glm::vec3 initialPosition, glm::vec3 WorldUp, float pitch, float yaw, float moveSpeed, float turnSpeed)
{
    m_Position = initialPosition;
    m_WorldUp = WorldUp;
    m_Pitch = pitch;
    m_Yaw = yaw;

    m_Front = glm::vec3(0.f, 0.f,-1.f);
    
    m_MoveSpeed = moveSpeed;
    m_TurnSpeed = turnSpeed;
    Update();
}

void Camera::Update()
{
    m_Front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch)) ;
    m_Front.y = sin(glm::radians(m_Pitch));
    m_Front.z = cos(glm::radians(m_Pitch)) * sin(glm::radians(m_Yaw));
    m_Front = glm::normalize(m_Front);

    m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
    m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}

glm::mat4 Camera::CalculateViewMatrix()
{
    return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
}

#include <iostream>
void Camera::KeyPressUpdate(bool* Keys, float deltaTime)
{
    //if (Keys[GLFW_KEY_1])
    //{
    //    if(m_MoveSpeed > 0.f )
    //        m_MoveSpeed -= 1.f;
    //
    //    std::cout << m_MoveSpeed << std::endl;
    //}
    //if (Keys[GLFW_KEY_3])
    //{
    //    if (m_MoveSpeed < 100.f)
    //        m_MoveSpeed += 1.f;
    //    std::cout << m_MoveSpeed << std::endl;
    //
    //}

    if (Keys[GLFW_KEY_W])
    {
        m_Position += m_Front * m_MoveSpeed * deltaTime;
    }
    if (Keys[GLFW_KEY_S])
    {
        m_Position -= m_Front * m_MoveSpeed * deltaTime;
    }                                      
    if (Keys[GLFW_KEY_A])                  
    {                                      
        m_Position -= m_Right * m_MoveSpeed * deltaTime;
    }                                      
    if (Keys[GLFW_KEY_D])                  
    {                                      
        m_Position += m_Right * m_MoveSpeed * deltaTime;
    }
    if (Keys[GLFW_KEY_Q])
    {
        m_Position += m_WorldUp * m_MoveSpeed * 1.5f * deltaTime;
    }
    if (Keys[GLFW_KEY_E])
    {
        m_Position -= m_WorldUp * m_MoveSpeed * 1.5f * deltaTime;
    }

}

void Camera::MouseMoveUpdate(float xChange, float yChange)
{
    m_Yaw -= xChange * m_TurnSpeed;
    m_Pitch += yChange * m_TurnSpeed;
    
    //m_Pitch = m_Pitch >= 89.f ? 89.f : m_Pitch;

    if (m_Pitch >= 89.f)
        m_Pitch = 89.f;
    if (m_Pitch <= -89.f)
        m_Pitch = -89.f;

    if (m_Yaw > 360.f)
        m_Yaw -= 360.f;
    

    Update();
}
