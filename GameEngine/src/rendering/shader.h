#ifndef SHADER_H
#define SHADER_H
#include <GL\glew.h>

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "renderEngine.h"

class Material;

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

	void Bind();
	void LinkProgram();

	void SetUniform(const std::string& name, float x, float y, float z);
	void SetUniform(const std::string& name, const vec3& v);
	void SetUniform(const std::string& name, const vec4& v);
	void SetUniform(const std::string& name, const vec2& v);
	void SetUniform(const std::string& name, const mat4& m);
	void SetUniform(const std::string& name, const mat3& m);
	void SetUniform(const std::string& name, float val);
	void SetUniform(const std::string& name, int val);
	void SetUniform(const std::string& name, GLuint val);
	void SetUniform(const std::string& name, bool val);

	inline void SetRenderEngine(RenderEngine* renderEngine){ m_renderEngine = renderEngine; };
	inline RenderEngine* GetRenderEngine(){ return m_renderEngine; };
	
	virtual void UpdateUniforms(const mat4& modelMatrix, const Material& material);
private:
	int m_program;
	std::vector<int> m_shaders;
	std::unordered_map<std::string, GLint> m_uniformLocations;
	static std::shared_ptr<std::string> LoadShader(const std::string& fileName);
	
	static void CheckShaderError(int shader, int flag, bool isProgram);
	void AddShader(const std::string& text, int type);
	GLint Shader::GetUniformLocation(const std::string& name);

	RenderEngine* m_renderEngine;
};

#endif