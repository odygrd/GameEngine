#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "common.h"
#include <GLM\gtc\matrix_transform.hpp>

class Transform
{
public:
	Transform(vec3 pos = vec3(0.0f, 0.0f, 0.f), vec3 rot = vec3(0.0f, 0.0f, 0.0f), vec3 scale = vec3(0.0f, 0.0f, 0.0f)):
		m_pos(pos), m_rot(rot), m_scale(scale) {}

	inline void SetTranslation(const vec3& pos){ m_pos = pos; m_translateMatrix = glm::translate(mat4(1.0), m_pos); CalculateTransMatrix(); }
	inline void SetRotation(const float degrees, const vec3& rotAxis){ m_degrees = degrees; m_rot = rotAxis; m_rotateMatrix = glm::rotate(mat4(1.0), m_degrees, m_rot); CalculateTransMatrix(); }
	inline void SetScale(const vec3& scale){ m_scale = scale; m_scaleMatrix = glm::scale(mat4(1.0), m_scale); CalculateTransMatrix(); }

	inline const vec3& GetPos(){ return m_pos; }
	inline const vec3& GetRotAxis(){ return m_rot; }
	inline float GetRotDeg(){ return m_degrees; }
	inline const vec3& GetScale(){ return m_scale; }

	inline const mat4& GetTransformMatrix() const { return m_transformMatrix; }
	
private:
	float m_degrees;

	vec3 m_pos;
	vec3 m_rot;
	vec3 m_scale;

	mat4 m_translateMatrix;
	mat4 m_rotateMatrix;
	mat4 m_scaleMatrix;

	mat4 m_transformMatrix;

	inline void CalculateTransMatrix(){ m_transformMatrix = m_translateMatrix * m_rotateMatrix * m_scaleMatrix; }

};

#endif