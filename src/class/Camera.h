#ifndef CAMERA
#define CAMERA

#include <pch.h>

class Camera
{
public:
	Camera(glm::vec3 initialPosition, glm::vec3 WorldUp, float pitch, float yaw, float moveSpeed, float turnSpeed);
	~Camera() {};

	void Update();
	glm::mat4 CalculateViewMatrix();

	glm::vec3 GetPosition() { return m_Position; }

	void KeyPressUpdate(bool* Keys, float deltaTime);
	void MouseMoveUpdate(float xChange, float yChange);



private:
	glm::vec3 m_Position;
	glm::vec3 m_Front;
	glm::vec3 m_WorldUp;
	glm::vec3 m_Up;
	glm::vec3 m_Right;
	
	float m_Pitch;
	float m_Yaw;



	float m_MoveSpeed;
	float m_TurnSpeed;

};

#endif