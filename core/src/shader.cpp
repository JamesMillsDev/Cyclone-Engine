#include "shader.h"

#include <fstream>
#include <streambuf>
#include <string>

#include <GL/glew.h>

#include "debug.h"

namespace CycloneEngine
{
	shader::shader(const char* _file, const ShaderType _type) : id(0), type(_type), file(_file)
	{
		load();
	}

	void shader::load()
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
			debug::log_exception("Shader type of INVALID was attempted to be loaded.");
			return;
		}

		const char* data = buffer.c_str();
		glShaderSource(id, 1, &data, nullptr);
		glCompileShader(id);
	}

	shader_program::shader_program() : id(0)
	{

	}

	void shader_program::append(const shader* _shader, const bool _autoCompile)
	{
		shaders.push_back(*_shader);

		if(_autoCompile)
			compile();
	}

	void shader_program::compile()
	{
		if(id != 0)
			glDeleteProgram(id);

		id = glCreateProgram();

		for (shader shader : shaders)
		{
			glAttachShader(id, static_cast<unsigned int>(shader));
		}

		glLinkProgram(id);
	}

	void shader_program::bind() const
	{
		glUseProgram(id);
	}
}