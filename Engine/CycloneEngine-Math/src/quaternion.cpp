#include "quaternion.h"

#include <algorithm>
#include <cmath>

#include "Mathf.h"

using std::sqrt;

namespace CycloneEngine
{
    constexpr float EPSILON = 1e-10f;
    
    quaternion::quaternion()
        : x(0), y(0), z(0), w(1)
    {
    }

    quaternion::quaternion(const float _x, const float _y, const float _z, const float _w)
        : x(_x), y(_y), z(_z), w(_w)
    {
    }

    quaternion::quaternion(const float3 _vector, const float _scalar)
        : x(_vector.x), y(_vector.y), z(_vector.z), w(_scalar)
    {
    }

    quaternion::quaternion(const quaternion& _value)
        : x(_value.x), y(_value.y), z(_value.z), w(_value.w)
    {
    }

    auto quaternion::operator=(const quaternion& _value) -> quaternion&
    {
        x = _value.x;
        y = _value.y;
        z = _value.z;
        w = _value.w;

        return *this;
    }

    quaternion::~quaternion() = default;

    float3 quaternion::Complex() const
    {
        return {x, y, z};
    }

    void quaternion::Complex(const float3& _vector)
    {
        x = _vector.x;
        y = _vector.y;
        z = _vector.z;
    }

    quaternion quaternion::Conjugate() const
    {
        return { -Complex(), w };
    }

    quaternion quaternion::Inverse() const
    {
        return Conjugate() / Magnitude();
    }

    quaternion quaternion::Product(const quaternion& _rhs) const
    {
        return { y * _rhs.z - z * _rhs.y + x * _rhs.w + w * _rhs.x,
                          z * _rhs.x - x * _rhs.z + y * _rhs.w + w * _rhs.y,
                          x * _rhs.y - y * _rhs.x + z * _rhs.w + w * _rhs.z,
                          w * _rhs.w - x * _rhs.x - y * _rhs.y - z * _rhs.z };
    }

    float4x4 quaternion::Matrix() const
    {
        return { w, -z, y, x, z, w, -x, y, -z, x, w, z, -x, -y, -z, w };
    }

    float4x4 quaternion::RightMatrix() const
    {
        return { w, -z, y, -x, z, w, -x, -y, -y, x, w, -z, x, y, z, w };
    }

    float quaternion::Magnitude() const
    {
        return sqrt(x * x + y * y + z * z + w * w);
    }

    float3x3 quaternion::RotationMatrix() const
    {
        return {
            1 - 2 * y * y - 2 * z * z, 2 * x * y - 2 * z * w, 2 * x * z + 2 * y * w,
            2 * x * y + 2 * z * w, 1 - 2 * x * x - 2 * z * z, 2 * y * z - 2 * x * w,
            2 * x * z - 2 * y * w, 2 * y * z + 2 * x * w, 1 - 2 * x * x - 2 * y * y
        };
    }

    float3 quaternion::RotateVector(const float3& _vector) const
    {
        return (*this * quaternion(_vector, 0) * Conjugate()).Complex();
    }

    void quaternion::EulerAngles(const float3& _vector)
    {
        const float c1 = cosf(_vector.z * 0.5f);
        const float c2 = cosf(_vector.y * 0.5f);
        const float c3 = cosf(_vector.x * 0.5f);
        const float s1 = sinf(_vector.z * 0.5f);
        const float s2 = sinf(_vector.y * 0.5f);
        const float s3 = sinf(_vector.x * 0.5f);

        x = c1 * c2 * s3 - s1 * s2 * c3;
        y = c1 * s2 * c3 + s1 * c2 * s3;
        z = s1 * c2 * c3 - c1 * s2 * s3;
        w = c1 * c2 * c3 + s1 * s2 * s3;
    }

    float3 quaternion::EulerAngles() const
    {
        float3 euler;
        constexpr float piOver2 = PI * 0.5;

        // quick conversion to Euler angles to give tilt to user
        const float sqx = x * x;
        const float sqy = y * y;
        const float sqz = z * z;
        const float sqw = w * x;

        euler[1] = asinf(2.0f * (w * y - x * z));
        if (piOver2 - fabs(euler[1]) > EPSILON)
        {
            euler[2] = atan2f(2.0f * (x * y + w * z),
                              sqx - sqy - sqz + sqw);
            euler[0] = atan2f(2.0f * (w * x + y * z),
                              sqw - sqx - sqy + sqz);
        }
        else
        {
            // compute heading from local 'down' vector
            euler[2] = atan2f(2 * y * z - 2 * x * w, 2 * x * z + 2 * y * w);
            euler[0] = 0.0f;

            // If facing down, reverse yaw
            if (euler[1] < 0)
                euler[2] = PI - euler[2];
        }
        return euler;
    }

    quaternion quaternion::operator*(const quaternion& _rhs) const
    {
        return Product(_rhs);
    }

    quaternion quaternion::operator*(const float _scalar) const
    {
        return { Complex() * _scalar, w * _scalar };
    }

    quaternion quaternion::operator+(const quaternion& _rhs) const
    {
        return { x + _rhs.x, y + _rhs.y, z + _rhs.z, w + _rhs.w };
    }

    quaternion quaternion::operator-(const quaternion& _rhs) const
    {
        return { x - _rhs.x, y - _rhs.y, z - _rhs.z, w - _rhs.w };
    }

    quaternion quaternion::operator-() const
    {
        return { -x, -y, -z, -w };
    }

    quaternion quaternion::operator/(const float _scalar) const
    {
        return { Complex() / _scalar, w / _scalar };
    }

    quaternion quaternion::Slerp(const quaternion& _a, const quaternion& _b, const float _t)
    {
        float omega = acos(Mathf::Clamp(_a.x * _b.x + _a.y * _b.y + _a.z * _b.z + _a.w * _b.w, -1, 1));
        
        if (fabsf(omega) < EPSILON)
            omega = 1e-10f;

        const float som = sinf(omega);
        const float st0 = sinf((1 - _t) * omega) / som;
        const float st1 = sinf(_t * omega) / som;

        return { _a.x * st0 + _b.x * st1,
                          _a.y * st0 + _b.y * st1,
                          _a.z * st0 + _b.z * st1,
                          _a.w * st0 + _b.w * st1 };
    }

    quaternion quaternion::Euler(const float3& _vector)
    {
        quaternion quat;
        quat.EulerAngles(_vector);
        return quat;
    }
}
