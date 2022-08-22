#include "color.h"

namespace CycloneEngine
{
    color::color()
    {
        r = 255.0f;
        g = 255.0f;
        b = 255.0f;
        a = 255.0f;
    }

    color::color(const float _r, const float _g, const float _b, const float _a)
    {
        r = _r;
        g = _g;
        b = _b;
        a = _a;
    }

    color::color(const glm::vec4& _vector)
    {
        r = _vector.r;
        g = _vector.g;
        b = _vector.b;
        a = _vector.a;
    }

    color::operator glm::vec<4, float, glm::defaultp> const() const
    {
        return glm::vec4(r, g, b, a);
    }
}
