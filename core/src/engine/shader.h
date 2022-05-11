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

	class shader
	{
	public:
		shader(const char* _file, ShaderType _type);

		explicit operator unsigned int() const { return id; }

	private:
		void load();
		unsigned int id;
		ShaderType type;
		const char* file;

	};

	class shader_program
	{
	public:
		shader_program();
		void append(const shader* _shader, bool _autoCompile = true);
		void compile();
		void bind() const;

	private:
		unsigned int id;
		std::vector<shader> shaders;

	};
}

#endif //!CYCLONE_SHADER