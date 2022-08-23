#ifndef CYCLONE_SHADER
#define CYCLONE_SHADER

#include "CycloneEngine.h"

#include <vector>

namespace CycloneEngine
{
	enum class ShaderType
	{
		Invalid = -1,
		Vertex,
		Fragment
	};

	class Shader
	{
	public:
		Shader(const char* _file, ShaderType _type);

		explicit operator unsigned int() const { return id; }

	private:
		void Load();
		unsigned int id;
		ShaderType type;
		const char* file;

	};

	class ShaderProgram
	{
	public:
		ShaderProgram();
		void Append(const Shader* _shader, bool _autoCompile = true);
		void Compile();
		void Bind() const;

	private:
		unsigned int id;
		std::vector<Shader> shaders;

	};
}

#endif //!CYCLONE_SHADER