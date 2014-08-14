#include <stdio.h>
#include <GLM\gtx\rotate_vector.hpp>
#include "camera.h"
#include "input.h"
#include "transform.h"

mat4 Transform::m_projectionMatrix = glm::perspective(FOV, WIDTH / HEIGHT, ZNEAR, ZFAR);

Camera::Camera(vec3 position)
{
	m_position = position;
	m_horizontalAngle = 3.14f;
	m_verticalAngle = 0.0f;

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	m_direction = vec3 (cos(m_verticalAngle) * sin(m_horizontalAngle), sin(m_verticalAngle), cos(m_verticalAngle) * cos(m_horizontalAngle));

	// Right vector
	m_right = vec3(sin(m_horizontalAngle - 3.14f / 2.0f) , 0 , cos(m_horizontalAngle - 3.14f / 2.0f));

	m_up = glm::cross(m_right, m_direction);
}

Camera::~Camera()
{
}

bool mouseLocked = false;

void Camera::Input()
{
	float sensitivity = 0.5f;
	float movAmt = (float)(10 * Time::GetDelta());
	float rotAmt = (float)(1.5f * Time::GetDelta());

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
	if (Input::GetKey(GLFW_KEY_UP))
	{
		RotateX(rotAmt);
	}
	if (Input::GetKey(GLFW_KEY_DOWN))
	{
		RotateX(-rotAmt);
	}
	if (Input::GetKey(GLFW_KEY_LEFT))
	{
		RotateY(rotAmt);
	}
	if (Input::GetKey(GLFW_KEY_RIGHT))
	{
		RotateY(-rotAmt);
	}
}

const mat4& Camera::GetViewMatrix()
{
	m_direction = vec3(cos(m_verticalAngle) * sin(m_horizontalAngle), sin(m_verticalAngle), cos(m_verticalAngle) * cos(m_horizontalAngle));
	m_right = vec3(sin(m_horizontalAngle - 3.14f / 2.0f), 0, cos(m_horizontalAngle - 3.14f / 2.0f));
	m_up = glm::cross(m_right, m_direction);
	m_viewMatrix = glm::lookAt(m_position, m_position + m_direction, m_up);
	return m_viewMatrix;
}

void Camera::MoveUp(float amount)
{
	m_position += m_direction * amount;
}


void Camera::MoveRight(float amount)
{
	m_position += m_right * amount;
}


void Camera::RotateX(float angle)
{
	m_verticalAngle += angle;
}

void Camera::RotateY(float angle)
{
	m_horizontalAngle += angle;
}



