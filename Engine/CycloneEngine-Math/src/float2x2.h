#ifndef CYCLONE_MATH_FLOAT2X2
#define CYCLONE_MATH_FLOAT2X2

namespace CycloneEngine
{
#define FLOAT2X2_SIZE 2
    
    // ReSharper disable once CppInconsistentNaming
    typedef struct float2x2
    {
        union
        {
            struct
            {
                float m11, m12,
                    m21, m22;
            };

            float asArray[FLOAT2X2_SIZE * FLOAT2X2_SIZE];
        };

        float* operator[](const int _index)
        {
            return &asArray[_index * FLOAT2X2_SIZE];
        }

        float2x2()
        {
            m11 = m22 = 1.0f;
            m12 = m21 = 0.0f;
        }

        float2x2(const float _m11, const float _m12, const float _m21, const float _m22)
        {
            m11 = _m11;
            m12 = _m12;
            m21 = _m21;
            m22 = _m22;
        }

        static float2x2 Transpose(const float2x2& _matrix);
        static float2x2 Inverse(const float2x2& _matrix);
        
    }
    float2x2;

    float2x2 operator*(const float2x2& _matrix, float _scalar);
    float2x2 operator*(const float2x2& _matrix, const float2x2& _other);
}

#endif //!CYCLONE_MATH_FLOAT2X2