#ifndef CYCLONE_MATH_VECTORS
#define CYCLONE_MATH_VECTORS

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

using glm::vec2;
using glm::vec3;
using glm::vec4;

namespace CycloneEngine
{
	struct Vector2
	{
	public:
		Vector2();
		Vector2(float _x, float _y);
		~Vector2();

		float x;
		float y;

		operator vec2() const { return vec2(x, y); }

	};

	struct Vector3
	{
	public:
		Vector3();
		Vector3(float _x, float _y, float _z);
		~Vector3();

		float x;
		float y;
		float z;

		operator vec3() const { return vec3(x, y, z); }

	};

	struct Vector4
	{
	public:
		Vector4();
		Vector4(float _x, float _y, float _z, float _w);
		~Vector4();

		float x;
		float y;
		float z;
		float w;

		operator vec4() const { return vec4(x, y, z, w); }

	};
}

#endif // !CYCLONE_MATH_VECTORS