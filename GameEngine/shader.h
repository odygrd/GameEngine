#ifndef SHADER_H
#define SHADER_H
#include <GL\glew.h>

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include "material.h"
#include "common.h"

class Shader
{
public:
	Shader();
	virtual ~Shader();

	void AddVertexShaderFromFile(const std::string& text);
	void AddGeometryShaderFromFile(const std::string& text);
	void AddFragmentShaderFromFile(const std::string& text);
	void AddVertexShader(const std::string& text);
	void AddGeometryShader(const std::string& text);
	void AddFragmentShader(const std::string& text);
	void AddUniform(const std::string& uniform);

	void Bind();
	void LinkProgram();

	void SetUniformi(const std::string& name, int value);
	void SetUniformf(const std::string& name, float value);
	void SetUniform(const std::string& name, const vec3& value);
	void SetUniform(const std::string& name, const mat4& value);
	void SetUniform(const std::string& name, const mat3& value);

	virtual void UpdateUniforms(const mat4& modelViewMatrix, const mat4& projectionMatrix, Material material);
private:
	int m_program;
	std::vector<int> m_shaders;

	static void CheckShaderError(int shader, int flag, bool isProgram);
	static std::shared_ptr<std::string> LoadShader(const std::string& fileName);
	std::unordered_map<std::string, int> m_uniforms; //hash table
	void AddShader(const std::string& text, int type);
};

#endif