#include "Shader.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <glad.h>
#include "Renderer.h"

Shader::Shader(const std::string& myFilepath) : filepath(myFilepath), rendererID(0)
{
	ShaderProgramSource source{ ParseShader(myFilepath) };
	rendererID = CreateShader(source.VertexSource, source.FragmentSource);
	//CompileShader();
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(rendererID));

}

void Shader::Bind() const
{
	GLCall(glUseProgram(rendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];

	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << std::endl;
		}
	}

	/*std::cout << "vertex: " << ss[0].str() <<std::endl;
	std::cout << "fragment: " << ss[1].str() <<std::endl;*/

	return { ss[0].str(), ss[1].str() };
}
unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	GLCall(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

	if (result == GL_FALSE)
	{
		int lenght;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght));
		char* message = (char*)_malloca(lenght * sizeof(char));
		GLCall(glGetShaderInfoLog(id, lenght, &lenght, message));
		std::cout << "Failed to compite " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
		std::cout << message << std::endl;
		free(message);
		GLCall(glDeleteShader(id));
		return 0;

	}

	return id;
}
unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLCall(unsigned int program = glCreateProgram());

	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glValidateProgram(program));
	GLCall(glLinkProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}

/////////// Uniforms ///////////////

int Shader::GetUniformLocation(const std::string& name)
{
	if (uniformLocationCache.find(name) != uniformLocationCache.end())
	{
		return uniformLocationCache[name];
	}

	GLCall(int location = glGetUniformLocation(rendererID, name.c_str()));

	if (location == -1)
	{
		std::cout << " Warning: uniform '" << name << "' doesn't exist!" << std::endl;
	}

	uniformLocationCache[name] = location;

	return location;
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	GLuint location = GetUniformLocation(name);
	if (location != -1)
		GLCall(glUniform1i(location, value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	GLuint location = GetUniformLocation(name);
	if (location != -1)
		GLCall(glUniform1f(location, value));
}

void Shader::SetUniform2f(const std::string& name, float v0, float v1)
{
	GLuint location = GetUniformLocation(name);
	if (location != -1)
		GLCall(glUniform2f(location, v0, v1));
}

void Shader::SetUniform3f(const std::string& name, float v0, float v1, float v2)
{
	GLuint location = GetUniformLocation(name);
	if (location != -1)
		GLCall(glUniform3f(location, v0, v1, v2));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLuint location = GetUniformLocation(name);
	if (location != -1)
		GLCall(glUniform4f(location, v0, v1, v2, v3));
}

void Shader::SetUniformMat3f(const std::string& name, const glm::mat3& matrix)
{
	GLuint location = GetUniformLocation(name);
	if (location != -1)
		GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]));
}

void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
	GLuint location = GetUniformLocation(name);
	if (location != -1)
		GLCall(glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]));
}
