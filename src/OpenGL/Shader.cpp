#include "Shader.h"
#include "CommonRender.h"
#include <fstream>
#include "Core/Logging.h"

#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
	: programId(glCreateProgram())
{
	if (SetupShader(vertexPath, GL_VERTEX_SHADER) &&
		SetupShader(fragmentPath, GL_FRAGMENT_SHADER))
	{
		glLinkProgram(programId);
		glValidateProgram(programId);
	}
}

Shader::~Shader()
{
	glDeleteProgram(programId);
}

void Shader::Bind()
{
	glUseProgram(programId);
}

void Shader::Unbind()
{
	glUseProgram(0);
}

void Shader::SetUniform1i(const char* name, float value)
{
	int location = glGetUniformLocation(programId, name);
	glUniform1i(location, value);
}

void Shader::SetUniformVec4(const char* name, float r, float g, float b, float a)
{
	int location = glGetUniformLocation(programId, name);
	glUniform4f(location, r, g, b, a);
}

void Shader::SetUniformMat4(const char* name, const glm::mat4& pos)
{
	int location = glGetUniformLocation(programId, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(pos));
}

bool Shader::SetupShader(const std::string& path, unsigned int type)
{
	std::ifstream file(path, std::ios::in | std::ios::binary);

	std::string data;
	if (file) 
	{
		file.seekg(0, std::ios::end);
		size_t size = file.tellg();

		if (size != -1)
		{
			data.resize(size);
			file.seekg(0, std::ios::beg);
			file.read(&data[0], size);
		}
		else
		{
			LOG_ERROR("Shader file is invalid -> " + path);
			_ASSERT(false);
			return false;
		}
	}
	else	
	{
		LOG_ERROR("Cannot find shader -> " + path);
		_ASSERT(false);
		return false;
	}


	unsigned int shader = glCreateShader(type);
	const char* shaderSource = data.c_str();
	glShaderSource(shader, 1, &shaderSource, nullptr);
	glCompileShader(shader);

	int result;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE) 
	{
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(shader, length, &length, message);
		LOG_ERROR("Cannot compile shader -> " + std::string(message));
		glDeleteShader(shader);
		_ASSERT(false);
		return false;
	}

	LOG_INFO("Successfully compiled shader -> " + path);

	glAttachShader(programId, shader);
	return true;
}
