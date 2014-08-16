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

void Shader::AddUniform(const string& uniform)
{
	int location = glGetUniformLocation(m_program, uniform.c_str());
	if (location == INVALID_VALUE)
	{
		printf("Error finding %s uniform location\n\n", uniform.c_str());
	}
	m_uniforms.emplace(uniform, location);
}

void Shader::SetUniformi(const string& uniform, int value)
{
	glUniform1i(m_uniforms.at(uniform), value);
}

void Shader::SetUniformf(const string& uniform, float value)
{
	glUniform1f(m_uniforms.at(uniform), value);
}

void Shader::SetUniform(const string& uniform, const vec3& value)
{
	glUniform3f(m_uniforms.at(uniform), value.x, value.y, value.z);
}

void Shader::SetUniform(const string& uniform, const mat4& value)
{
	glUniformMatrix4fv(m_uniforms.at(uniform), 1, GL_FALSE, &(value[0][0]));
}

void Shader::UpdateUniforms(const mat4& MVPMatrix, Material material)
{

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