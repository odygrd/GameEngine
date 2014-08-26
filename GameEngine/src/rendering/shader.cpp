#include <fstream>
#include <iostream>
#include "shader.h"

using namespace std;

Shader::Shader()
{
	m_program = glCreateProgram();

	if (m_program == 0)
	{
		printf("Failed to create a program id\n");
		exit(EXIT_FAILURE);
	}
}


Shader::~Shader()
{
	for (vector<int>::iterator it = m_shaders.begin(); it != m_shaders.end(); ++it)
	{
		glDetachShader(m_program, *it);
		glDeleteShader(*it);
	}
	glDeleteProgram(m_program);
}

void Shader::AddShader(const string& text, int type)
{
	int shaderId = glCreateShader(type);

	if (shaderId == 0)
	{
		printf("Failed to create a shader type %d\n", type);
		exit(EXIT_FAILURE);
	}

	const GLchar* p[1];
	p[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();//strlen(text.c_str());

	glShaderSource(shaderId, 1,p, lengths);
	glCompileShader(shaderId);

	CheckShaderError(shaderId, GL_COMPILE_STATUS, false);

	glAttachShader(m_program, shaderId);
	m_shaders.push_back(shaderId);
}

void Shader::LinkProgram()
{
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true);

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true);
}

void Shader::Bind()
{
	glUseProgram(m_program);
}

//Load Shaders directly
void Shader::AddVertexShader(const std::string& text)
{
	AddShader(text, GL_VERTEX_SHADER);
}

void Shader::AddGeometryShader(const std::string& text)
{
	AddShader(text, GL_GEOMETRY_SHADER);
}

void Shader::AddFragmentShader(const std::string& text)
{
	AddShader(text, GL_FRAGMENT_SHADER);
}

//Load Shaders from files
void Shader::AddVertexShaderFromFile(const string& text)
{
	AddVertexShader(*LoadShader(text));
}

void Shader::AddGeometryShaderFromFile(const string& text)
{
	AddGeometryShader(*LoadShader(text));
}

void Shader::AddFragmentShaderFromFile(const string& text)
{
	AddFragmentShader(*LoadShader(text));
}

void Shader::SetUniform(const std::string& name, float x, float y, float z)
{
  GLint loc = GetUniformLocation(name);
  glUniform3f(loc,x,y,z);
}

void Shader::SetUniform(const std::string& name, const vec3& v)
{
  this->SetUniform(name,v.x,v.y,v.z);
}

void Shader::SetUniform(const std::string& name, const vec4& v)
{
  GLint loc = GetUniformLocation(name);
  glUniform4f(loc,v.x,v.y,v.z,v.w);
}

void Shader::SetUniform(const std::string& name, const vec2& v)
{
  GLint loc = GetUniformLocation(name);
  glUniform2f(loc,v.x,v.y);
}

void Shader::SetUniform(const std::string& name, const mat4& m)
{
  GLint loc = GetUniformLocation(name);
  glUniformMatrix4fv(loc, 1, GL_FALSE, &m[0][0]);
}

void Shader::SetUniform(const std::string& name, const mat3& m)
{
  GLint loc = GetUniformLocation(name);
  glUniformMatrix3fv(loc, 1, GL_FALSE, &m[0][0]);
}

void Shader::SetUniform(const std::string& name, float val)
{
  GLint loc = GetUniformLocation(name);
  glUniform1f(loc, val);
}

void Shader::SetUniform(const std::string& name, int val)
{
  GLint loc = GetUniformLocation(name);
  glUniform1i(loc, val);
}

void Shader::SetUniform(const std::string& name, GLuint val)
{
  GLint loc = GetUniformLocation(name);
  glUniform1ui(loc, val);
}

void Shader::SetUniform(const std::string& name, bool val)
{
  int loc = GetUniformLocation(name);
  glUniform1i(loc, val);
}

void Shader::CheckShaderError(int shader, int flag, bool isProgram)
{
	GLint success;

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);
	
	
	if (success == GL_FALSE)
	{
		if (isProgram)
		{
			GLint infoLogLength;
			glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar *strInfoLog = new GLchar[infoLogLength + 1];
			glGetProgramInfoLog(shader, infoLogLength, NULL, strInfoLog);
			printf("Program Failure:\n %s\n", strInfoLog);
			delete[] strInfoLog;

		}
		else
		{
			GLint infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar *strInfoLog = new GLchar[infoLogLength + 1];
			glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
			printf("Shader Failure:\n %s\n", strInfoLog);
			delete[] strInfoLog;
		}
	}
}

std::shared_ptr<std::string> Shader::LoadShader(const std::string& fileName)
{
	ifstream file;
	file.open("shaders/" + fileName);

	shared_ptr<string> output(new string());
	string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output->append(line + "\n");
		}
		file.close();
	}
	else
	{
		printf("Unable to load shader: %s\n",  fileName);
	}

	return output;
};

GLint Shader::GetUniformLocation(const std::string& name)
{

	auto pos = m_uniformLocations.find(name);

	if (pos == m_uniformLocations.end()) {
		m_uniformLocations[name] = glGetUniformLocation(m_program, name.c_str());
	}

	return m_uniformLocations[name];
}


void Shader::UpdateUniforms(const mat4& modelViewMatrix, const mat4& projectionMatrix, const vec3& cameraPosition, const Material& material)
{

}