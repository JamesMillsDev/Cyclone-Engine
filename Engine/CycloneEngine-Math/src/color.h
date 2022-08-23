#ifndef CYCLONE_MATH_COLOR
#define CYCLONE_MATH_COLOR

#include <glm/vec4.hpp>

namespace CycloneEngine
{
    typedef struct color
    {
#define COLOR_SIZE 4
        union
        {
            struct
            {
                float r;
                float g;
                float b;
                float a;
            };

            float asArray[COLOR_SIZE];
        };

        float& operator[](const int _i)
        {
            return asArray[_i];
        }

        color();
        color(float _r, float _g, float _b, float _a);
        color(const glm::vec4& _vector);
        operator glm::vec4 const() const;
    
    } color;
}

#endif //!CYCLONE_MATH_COLOR