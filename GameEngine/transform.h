#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "common.h"
#include "camera.h"
#include <GLM\gtc\matrix_transform.hpp>

class Transform
{
public:
	Transform(vec3 pos = vec3(0.0f, 0.0f, 0.f), vec3 rot = vec3(0.0f, 0.0f, 0.0f), vec3 scale = vec3(0.0f, 0.0f, 0.0f)):
		m_pos(pos), m_rot(rot), m_scale(scale) {}

	inline void SetTranslation(const vec3& pos){ m_pos = pos; m_translateMatrix = glm::translate(mat4(1.0), m_pos);}
	inline void SetRotation(const float degrees, const vec3& rotAxis){m_degrees = degrees;m_rot = rotAxis;m_rotateMatrix = glm::rotate(mat4(1.0), m_degrees, m_rot);}
	inline void SetScale(const vec3& scale){ m_scale = scale; m_scaleMatrix = glm::scale(mat4(1.0), m_scale);}

	inline const vec3& GetPos(){ return m_pos; }
	inline const vec3& GetRotAxis(){ return m_rot; }
	inline const float GetRotDeg(){ return m_degrees; }
	inline const vec3& GetScale(){ return m_scale; }

	inline static const mat4& GetProjectionMatrix() { return Transform::m_projectionMatrix; };
	inline const mat4& GetTransformMatrix() { m_transformMatrix = m_translateMatrix * m_rotateMatrix * m_scaleMatrix; return m_transformMatrix; }
	inline const mat4& GetModelViewProjectionMatrix(Camera& camera){ m_mvpMatrix = m_projectionMatrix *camera.GetViewMatrix()* GetTransformMatrix(); return m_mvpMatrix; };
	
	static void SetProjection(float fov, float width, float height, float zNear, float zFar){ m_projectionMatrix = glm::perspective(fov, width / height, zNear, zFar); }
	
private:
	float m_degrees;

	vec3 m_pos;
	vec3 m_rot;
	vec3 m_scale;

	mat4 m_translateMatrix;
	mat4 m_rotateMatrix;
	mat4 m_scaleMatrix;

	static mat4 m_projectionMatrix;
	mat4 m_transformMatrix;
	mat4 m_mvpMatrix;
};

#endif