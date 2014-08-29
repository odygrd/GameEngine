#include <stdio.h>
#include <GLM/gtx/rotate_vector.hpp>
#include "camera.h"
#include "../core/input.h"

Camera::Camera(float fov, float aspect, float zNear, float zFar)
{
	m_projectionMatrix = glm::perspective(fov, aspect, zNear, zFar);

	m_position = vec3(0.0f, 0.0f, 0.0f); 
	m_horizontalAngle = 3.14f;
	m_verticalAngle = 0.0f;
	m_mouselocked = false;
	// Direction : Spherical coordinates to Cartesian coordinates conversion
	m_direction = vec3(cos(m_verticalAngle) * sin(m_horizontalAngle), sin(m_verticalAngle), cos(m_verticalAngle) * cos(m_horizontalAngle));

	// Right vector
	m_right = vec3(sin(m_horizontalAngle - 3.14f / 2.0f), 0, cos(m_horizontalAngle - 3.14f / 2.0f));

	m_up = glm::cross(m_right, m_direction);
}

Camera::~Camera()
{
}

void Camera::Input()
{
	float sensitivity = 0.001f;
	float movAmt = static_cast<float>(10 * Time::GetDelta());
	float rotAmt = static_cast<float>(1.5f * Time::GetDelta());

	if (Input::GetMouseDown(GLFW_MOUSE_BUTTON_1))
	{
		m_cursorStoredPos = Input::GetCursorPosition();
		vec2 centerPos = vec2((float)WIDTH / 2.0f, (float)WIDTH / 2.0f);
		Input::SetCursorPosition(centerPos);
		Input::SetCursorVisibility(false);
		m_mouselocked = true;
	}

	if (Input::GetMouseUp(GLFW_MOUSE_BUTTON_1))
	{
		Input::SetCursorPosition(m_cursorStoredPos);
		Input::SetCursorVisibility(true);
		m_mouselocked = false;
	}

	if (m_mouselocked)
	{
		vec2 centerPos = vec2((float)WIDTH / 2.0f, (float)WIDTH / 2.0f);
		vec2 currentPos = Input::GetCursorPosition();
		vec2 deltaPos = centerPos - currentPos;

		bool rotY = deltaPos.x != 0;
		bool rotX = deltaPos.y != 0;

		if (rotY)
			RotateY(deltaPos.x * sensitivity);
		if (rotX)
			RotateX(deltaPos.y * sensitivity);

		if (rotY || rotX)
			Input::SetCursorPosition(centerPos);
	}

	if (Input::GetKey(GLFW_KEY_W))
	{
		MoveUp(movAmt);
	}
	if (Input::GetKey(GLFW_KEY_S))
	{
		MoveUp(-movAmt);
	}
	if (Input::GetKey(GLFW_KEY_D))
	{
		MoveRight(movAmt);
	}
	if (Input::GetKey(GLFW_KEY_A))
	{
		MoveRight(-movAmt);
	}

}


void Camera::MoveUp(float amount)
{
	m_position += m_direction * amount;
	m_viewMatrix = glm::lookAt(m_position, m_position + m_direction, m_up);
}


void Camera::MoveRight(float amount)
{
	m_position += m_right * amount;
	m_viewMatrix = glm::lookAt(m_position, m_position + m_direction, m_up);
}


void Camera::RotateX(float angle)
{
	m_verticalAngle += angle;
	CalculateDirection();
	m_viewMatrix = glm::lookAt(m_position, m_position + m_direction, m_up);
}

void Camera::RotateY(float angle)
{
	m_horizontalAngle += angle;
	CalculateDirection();
	m_viewMatrix = glm::lookAt(m_position, m_position + m_direction, m_up);
}

void Camera::CalculateDirection()
{
	m_direction = vec3(cos(m_verticalAngle) * sin(m_horizontalAngle), sin(m_verticalAngle), cos(m_verticalAngle) * cos(m_horizontalAngle));
	m_right = vec3(sin(m_horizontalAngle - 3.14f / 2.0f), 0, cos(m_horizontalAngle - 3.14f / 2.0f));
	m_up = glm::cross(m_right, m_direction);
}



