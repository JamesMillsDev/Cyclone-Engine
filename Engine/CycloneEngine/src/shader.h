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
		CYCLONE_DLL Shader(const char* _file, ShaderType _type);

		CYCLONE_DLL explicit operator unsigned int() const { return id; }

	private:
		CYCLONE_DLL void Load();
		unsigned int id;
		ShaderType type;
		const char* file;

	};

	class ShaderProgram
	{
	public:
		CYCLONE_DLL ShaderProgram();
		CYCLONE_DLL void Append(const Shader* _shader, bool _autoCompile = true);
		CYCLONE_DLL void Compile();
		CYCLONE_DLL void Bind() const;

	private:
		unsigned int id;
		std::vector<Shader> shaders;

	};
}

#endif //!CYCLONE_SHADER