#pragma once
#include <string>

class Shader {
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();

	void Bind();
	void Unbind();

	void SetUniformVec4(const char* name, float r, float g, float b, float a);
private:
	void SetupShader(const std::string& path, unsigned int type);
	unsigned int programId;
};
