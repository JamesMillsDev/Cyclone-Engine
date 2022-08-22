#ifndef CYCLONE_MATH_COLOR
#define CYCLONE_MATH_COLOR

#include <glm/vec4.hpp>

#include "CycloneMath.h"

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

        CYCLONE_DLL color();
        CYCLONE_DLL color(float _r, float _g, float _b, float _a);
        CYCLONE_DLL color(const glm::vec4& _vector);
        CYCLONE_DLL operator glm::vec4 const() const;
    
    } color;
}

#endif //!CYCLONE_MATH_COLOR