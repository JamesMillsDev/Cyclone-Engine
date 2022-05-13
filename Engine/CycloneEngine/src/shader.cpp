#include "Shader.h"

#include <fstream>
#include <streambuf>
#include <string>

#include <GL/glew.h>

namespace CycloneEngine
{
	Shader::Shader(const char* _file, const ShaderType _type) : id(0), type(_type), file(_file)
	{
		load();
	}

	void Shader::load()
	{
		std::ifstream t(file);
		t.seekg(0, std::ios::end);
		size_t size = t.tellg();
		std::string buffer(size, ' ');
		t.seekg(0);
		t.read(&buffer[0], size);

		id = 0;
		switch (type)
		{
		case ShaderType::VERTEX:
			id = glCreateShader(GL_VERTEX_SHADER);
			break;

		case ShaderType::FRAGMENT:
			id = glCreateShader(GL_FRAGMENT_SHADER);
			break;

		case ShaderType::INVALID: 
			return;
		}

		const char* data = buffer.c_str();
		glShaderSource(id, 1, &data, nullptr);
		glCompileShader(id);
	}

	ShaderProgram::ShaderProgram() : id(0)
	{

	}

	void ShaderProgram::append(const Shader* _shader, const bool _autoCompile)
	{
		shaders.push_back(*_shader);

		if(_autoCompile)
			compile();
	}

	void ShaderProgram::compile()
	{
		if(id != 0)
			glDeleteProgram(id);

		id = glCreateProgram();

		for (Shader shader : shaders)
		{
			glAttachShader(id, static_cast<unsigned int>(shader));
		}

		glLinkProgram(id);
	}

	void ShaderProgram::bind() const
	{
		glUseProgram(id);
	}
}