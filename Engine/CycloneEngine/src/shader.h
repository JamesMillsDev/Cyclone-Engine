#ifndef CYCLONE_SHADER
#define CYCLONE_SHADER

#include <vector>

namespace CycloneEngine
{
	enum class ShaderType
	{
		INVALID = -1,
		VERTEX,
		FRAGMENT
	};

	class Shader
	{
	public:
		Shader(const char* _file, ShaderType _type);

		explicit operator unsigned int() const { return id; }

	private:
		void load();
		unsigned int id;
		ShaderType type;
		const char* file;

	};

	class ShaderProgram
	{
	public:
		ShaderProgram();
		void append(const Shader* _shader, bool _autoCompile = true);
		void compile();
		void bind() const;

	private:
		unsigned int id;
		std::vector<Shader> shaders;

	};
}

#endif //!CYCLONE_SHADER