#ifndef CAMERA_H
#define CAMERA_H
#include "window.h"
#include <GLM\gtc\matrix_transform.hpp>

#include "../core/common.h"

class Camera
{
public:
	Camera(vec3 position = vec3(0.0f, 0.0f, 1.0f));
	~Camera();

	void Input();
	void MoveUp(float amount);
	void MoveRight(float amount);
	void RotateY(float angle);
	void RotateX(float angle);

	const mat4& GetViewMatrix();

	inline const vec3& GetPosition() { return m_position; };
	inline const vec3& GetDirection() { m_direction = vec3(cos(m_verticalAngle) * sin(m_horizontalAngle), sin(m_verticalAngle), cos(m_verticalAngle) * cos(m_horizontalAngle)); return m_direction; };
	inline const vec3& GetRight() { m_right = vec3(sin(m_horizontalAngle - 3.14f / 2.0f), 0, cos(m_horizontalAngle - 3.14f / 2.0f)); return m_right; }
	inline const vec3& GetUp() {
		m_direction = vec3(cos(m_verticalAngle) * sin(m_horizontalAngle), sin(m_verticalAngle), cos(m_verticalAngle) * cos(m_horizontalAngle));
		m_right = vec3(sin(m_horizontalAngle - 3.14f / 2.0f), 0, cos(m_horizontalAngle - 3.14f / 2.0f));
		return glm::cross(m_right, m_direction);
	};

	inline void SetPosition(const vec3& position){ m_position = position; }
	inline void SetDirection(const vec3& direction){ m_direction = direction; }
	inline void SetUp(const vec3& up){ m_up = up; }
	inline void SetRight(const vec3& right){ m_right = right; }
private:
	vec3 m_position; // Initial position : on +Z 
	float m_horizontalAngle; // Initial horizontal angle : toward -Z
	float m_verticalAngle; // Initial vertical angle 
	vec3 m_direction; // Direction  
	vec3 m_up; //up vector
	vec3 m_right; // Right vector
	mat4 m_viewMatrix;

	static bool mouselocked;
	vec2 m_cursorStoredPos;
};

#endif