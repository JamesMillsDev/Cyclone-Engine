#include "Gizmos.h"

#include <cstdio>
#include <GL/glew.h>
#include <glm/ext.hpp>

namespace CycloneEngine
{
    Gizmos* Gizmos::m_singleton;
    
    Gizmos::Gizmos(const unsigned int _maxLines, const unsigned int _maxTris, const unsigned int _max2DLines, const unsigned int _max2DTris)
        : m_maxLines(_maxLines), m_lineCount(0), m_lines(new GizmoLine[_maxLines]), m_maxTris(_maxTris), m_triCount(0),
          m_tris(new GizmoTri[_maxTris]), m_transparentTriCount(0), m_transparentTris(new GizmoTri[_maxTris]), m_max2DLines(_max2DLines),
          m_2dLineCount(0), m_2dLines(new GizmoLine[_max2DLines]), m_max2DTris(_max2DTris), m_2dTriCount(0), m_2dTris(new GizmoTri[_max2DTris])
    {
        // create shaders
        const char* vsSource = "#version 150\n \
					 in vec4 Position; \
					 in vec4 color; \
					 out vec4 vcolor; \
					 uniform mat4 ProjectionView; \
					 void main() { vcolor = color; gl_Position = ProjectionView * Position; }";

        const char* fsSource = "#version 150\n \
					 in vec4 vcolor; \
                     out vec4 FragColor; \
					 void main()	{ FragColor = vcolor; }";


        const unsigned int vs = glCreateShader(GL_VERTEX_SHADER);
        const unsigned int fs = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(vs, 1, &vsSource, nullptr);
        glCompileShader(vs);

        glShaderSource(fs, 1, &fsSource, nullptr);
        glCompileShader(fs);

        m_shader = glCreateProgram();
        glAttachShader(m_shader, vs);
        glAttachShader(m_shader, fs);
        glBindAttribLocation(m_shader, 0, "Position");
        glBindAttribLocation(m_shader, 1, "color");
        glLinkProgram(m_shader);

        int success = GL_FALSE;
        glGetProgramiv(m_shader, GL_LINK_STATUS, &success);
        if(success == GL_FALSE)
        {
            int infoLogLength = 0;
            glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &infoLogLength);
            char* infoLog = new char[infoLogLength];

            glGetShaderInfoLog(m_shader, infoLogLength, nullptr, infoLog);
            printf("Error: Failed to link Gizmo shader program!\n");
            printf("%s", infoLog);
            printf("\n");
            delete[] infoLog;
        }

        glDeleteShader(vs);
        glDeleteShader(fs);

        // create VBOs
        glGenBuffers(1, &m_lineVbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_lineVbo);
        glBufferData(GL_ARRAY_BUFFER, m_maxLines * sizeof(GizmoLine), m_lines, GL_DYNAMIC_DRAW);

        glGenBuffers(1, &m_triVbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_triVbo);
        glBufferData(GL_ARRAY_BUFFER, m_maxTris * sizeof(GizmoTri), m_tris, GL_DYNAMIC_DRAW);

        glGenBuffers(1, &m_transparentTriVbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_transparentTriVbo);
        glBufferData(GL_ARRAY_BUFFER, m_maxTris * sizeof(GizmoTri), m_transparentTris, GL_DYNAMIC_DRAW);

        glGenBuffers(1, &m_2dLineVbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_2dLineVbo);
        glBufferData(GL_ARRAY_BUFFER, m_max2DLines * sizeof(GizmoLine), m_2dLines, GL_DYNAMIC_DRAW);

        glGenBuffers(1, &m_2dTriVbo);
        glBindBuffer(GL_ARRAY_BUFFER, m_2dTriVbo);
        glBufferData(GL_ARRAY_BUFFER, m_max2DTris * sizeof(GizmoTri), m_2dTris, GL_DYNAMIC_DRAW);

        glGenVertexArrays(1, &m_lineVao);
        glBindVertexArray(m_lineVao);
        glBindBuffer(GL_ARRAY_BUFFER, m_lineVbo);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GizmoVertex), nullptr);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(GizmoVertex), (char*) nullptr + 16);

        glGenVertexArrays(1, &m_triVao);
        glBindVertexArray(m_triVao);
        glBindBuffer(GL_ARRAY_BUFFER, m_triVbo);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GizmoVertex), nullptr);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(GizmoVertex), (char*) nullptr + 16);

        glGenVertexArrays(1, &m_transparentTriVao);
        glBindVertexArray(m_transparentTriVao);
        glBindBuffer(GL_ARRAY_BUFFER, m_transparentTriVbo);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GizmoVertex), nullptr);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(GizmoVertex), (char*) nullptr + 16);

        glGenVertexArrays(1, &m_2dLineVao);
        glBindVertexArray(m_2dLineVao);
        glBindBuffer(GL_ARRAY_BUFFER, m_2dLineVbo);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GizmoVertex), nullptr);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(GizmoVertex), (char*) nullptr + 16);

        glGenVertexArrays(1, &m_2dTriVao);
        glBindVertexArray(m_2dTriVao);
        glBindBuffer(GL_ARRAY_BUFFER, m_2dTriVbo);
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(GizmoVertex), nullptr);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_TRUE, sizeof(GizmoVertex), (char*) nullptr + 16);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    Gizmos::~Gizmos()
    {
        delete[] m_lines;
        delete[] m_tris;
        delete[] m_transparentTris;
        glDeleteBuffers(1, &m_lineVbo);
        glDeleteBuffers(1, &m_triVbo);
        glDeleteBuffers(1, &m_transparentTriVbo);
        glDeleteVertexArrays(1, &m_lineVao);
        glDeleteVertexArrays(1, &m_triVao);
        glDeleteVertexArrays(1, &m_transparentTriVao);
        delete[] m_2dLines;
        delete[] m_2dTris;
        glDeleteBuffers(1, &m_2dLineVbo);
        glDeleteBuffers(1, &m_2dTriVbo);
        glDeleteVertexArrays(1, &m_2dLineVao);
        glDeleteVertexArrays(1, &m_2dTriVao);
        glDeleteProgram(m_shader);
    }

    void Gizmos::Create(const unsigned int _maxLines, const unsigned int _maxTris, const unsigned int _max2DLines, const unsigned int _max2DTris)
    {
        if(m_singleton == nullptr)
            m_singleton = new Gizmos(_maxLines, _maxTris, _max2DLines, _max2DTris);
    }

    void Gizmos::Destroy()
    {
        delete m_singleton;
        m_singleton = nullptr;
    }

    void Gizmos::Clear()
    {
        m_singleton->m_lineCount = 0;
        m_singleton->m_triCount = 0;
        m_singleton->m_transparentTriCount = 0;
        m_singleton->m_2dLineCount = 0;
        m_singleton->m_2dTriCount = 0;
    }

    // Adds 3 unit-length lines (red,green,blue) representing the 3 axis of a transform, 
    // at the transform's translation. Optional scale available.
    void Gizmos::AddTransform(const glm::mat4& _transform, float _fScale /* = 1.0f */)
    {
        glm::vec4 vXAxis = _transform[3] + _transform[0] * _fScale;
        glm::vec4 vYAxis = _transform[3] + _transform[1] * _fScale;
        glm::vec4 vZAxis = _transform[3] + _transform[2] * _fScale;

        glm::vec4 vRed(1, 0, 0, 1);
        glm::vec4 vGreen(0, 1, 0, 1);
        glm::vec4 vBlue(0, 0, 1, 1);

        AddLine(_transform[3].xyz, vXAxis.xyz, vRed, vRed);
        AddLine(_transform[3].xyz, vYAxis.xyz, vGreen, vGreen);
        AddLine(_transform[3].xyz, vZAxis.xyz, vBlue, vBlue);
    }

    void Gizmos::AddAabb(const glm::vec3& _center, const glm::vec3& _extents, const glm::vec4& _color, const glm::mat4* _transform /* = nullptr */)
    {
        glm::vec3 vVerts[8];
        glm::vec3 vX(_extents.x, 0, 0);
        glm::vec3 vY(0, _extents.y, 0);
        glm::vec3 vZ(0, 0, _extents.z);

        if(_transform != nullptr)
        {
            vX = (*_transform * glm::vec4(vX, 0)).xyz;
            vY = (*_transform * glm::vec4(vY, 0)).xyz;
            vZ = (*_transform * glm::vec4(vZ, 0)).xyz;
        }

        // top verts
        vVerts[0] = _center - vX - vZ - vY;
        vVerts[1] = _center - vX + vZ - vY;
        vVerts[2] = _center + vX + vZ - vY;
        vVerts[3] = _center + vX - vZ - vY;

        // bottom verts
        vVerts[4] = _center - vX - vZ + vY;
        vVerts[5] = _center - vX + vZ + vY;
        vVerts[6] = _center + vX + vZ + vY;
        vVerts[7] = _center + vX - vZ + vY;

        AddLine(vVerts[0], vVerts[1], _color, _color);
        AddLine(vVerts[1], vVerts[2], _color, _color);
        AddLine(vVerts[2], vVerts[3], _color, _color);
        AddLine(vVerts[3], vVerts[0], _color, _color);

        AddLine(vVerts[4], vVerts[5], _color, _color);
        AddLine(vVerts[5], vVerts[6], _color, _color);
        AddLine(vVerts[6], vVerts[7], _color, _color);
        AddLine(vVerts[7], vVerts[4], _color, _color);

        AddLine(vVerts[0], vVerts[4], _color, _color);
        AddLine(vVerts[1], vVerts[5], _color, _color);
        AddLine(vVerts[2], vVerts[6], _color, _color);
        AddLine(vVerts[3], vVerts[7], _color, _color);
    }

    void Gizmos::AddAabbFilled(const glm::vec3& _center, const glm::vec3& _extents, const glm::vec4& _fillColor, const glm::mat4* _transform /* = nullptr */)
    {
        glm::vec3 vVerts[8];
        glm::vec3 vX(_extents.x, 0, 0);
        glm::vec3 vY(0, _extents.y, 0);
        glm::vec3 vZ(0, 0, _extents.z);

        if(_transform != nullptr)
        {
            vX = (*_transform * glm::vec4(vX, 0)).xyz;
            vY = (*_transform * glm::vec4(vY, 0)).xyz;
            vZ = (*_transform * glm::vec4(vZ, 0)).xyz;
        }

        // top verts
        vVerts[0] = _center - vX - vZ - vY;
        vVerts[1] = _center - vX + vZ - vY;
        vVerts[2] = _center + vX + vZ - vY;
        vVerts[3] = _center + vX - vZ - vY;

        // bottom verts
        vVerts[4] = _center - vX - vZ + vY;
        vVerts[5] = _center - vX + vZ + vY;
        vVerts[6] = _center + vX + vZ + vY;
        vVerts[7] = _center + vX - vZ + vY;

        glm::vec4 vWhite(1, 1, 1, 1);

        AddLine(vVerts[0], vVerts[1], vWhite, vWhite);
        AddLine(vVerts[1], vVerts[2], vWhite, vWhite);
        AddLine(vVerts[2], vVerts[3], vWhite, vWhite);
        AddLine(vVerts[3], vVerts[0], vWhite, vWhite);

        AddLine(vVerts[4], vVerts[5], vWhite, vWhite);
        AddLine(vVerts[5], vVerts[6], vWhite, vWhite);
        AddLine(vVerts[6], vVerts[7], vWhite, vWhite);
        AddLine(vVerts[7], vVerts[4], vWhite, vWhite);

        AddLine(vVerts[0], vVerts[4], vWhite, vWhite);
        AddLine(vVerts[1], vVerts[5], vWhite, vWhite);
        AddLine(vVerts[2], vVerts[6], vWhite, vWhite);
        AddLine(vVerts[3], vVerts[7], vWhite, vWhite);

        // top
        AddTri(vVerts[2], vVerts[1], vVerts[0], _fillColor);
        AddTri(vVerts[3], vVerts[2], vVerts[0], _fillColor);

        // bottom
        AddTri(vVerts[5], vVerts[6], vVerts[4], _fillColor);
        AddTri(vVerts[6], vVerts[7], vVerts[4], _fillColor);

        // front
        AddTri(vVerts[4], vVerts[3], vVerts[0], _fillColor);
        AddTri(vVerts[7], vVerts[3], vVerts[4], _fillColor);

        // back
        AddTri(vVerts[1], vVerts[2], vVerts[5], _fillColor);
        AddTri(vVerts[2], vVerts[6], vVerts[5], _fillColor);

        // left
        AddTri(vVerts[0], vVerts[1], vVerts[4], _fillColor);
        AddTri(vVerts[1], vVerts[5], vVerts[4], _fillColor);

        // right
        AddTri(vVerts[2], vVerts[3], vVerts[7], _fillColor);
        AddTri(vVerts[6], vVerts[2], vVerts[7], _fillColor);
    }

    void Gizmos::AddCylinderFilled(const glm::vec3& _center, float _radius, float _fHalfLength, unsigned int _segments, const glm::vec4& _fillColor, const glm::mat4* _transform /* = nullptr */)
    {
        glm::vec4 white(1, 1, 1, 1);

        float segmentSize = 2 * glm::pi<float>() / (float)_segments;

        for(unsigned int i = 0; i < _segments; ++i)
        {
            glm::vec3 v0Top(0, _fHalfLength, 0);
            glm::vec3 v1Top(sinf(i * segmentSize) * _radius, _fHalfLength, cosf(i * segmentSize) * _radius);
            glm::vec3 v2Top(sinf((i + 1) * segmentSize) * _radius, _fHalfLength, cosf((i + 1) * segmentSize) * _radius);
            glm::vec3 v0Bottom(0, -_fHalfLength, 0);
            glm::vec3 v1Bottom(sinf(i * segmentSize) * _radius, -_fHalfLength, cosf(i * segmentSize) * _radius);
            glm::vec3 v2Bottom(sinf((i + 1) * segmentSize) * _radius, -_fHalfLength, cosf((i + 1) * segmentSize) * _radius);

            if(_transform != nullptr)
            {
                v0Top = (*_transform * glm::vec4(v0Top, 0)).xyz;
                v1Top = (*_transform * glm::vec4(v1Top, 0)).xyz;
                v2Top = (*_transform * glm::vec4(v2Top, 0)).xyz;
                v0Bottom = (*_transform * glm::vec4(v0Bottom, 0)).xyz;
                v1Bottom = (*_transform * glm::vec4(v1Bottom, 0)).xyz;
                v2Bottom = (*_transform * glm::vec4(v2Bottom, 0)).xyz;
            }

            // triangles
            AddTri(_center + v0Top, _center + v1Top, _center + v2Top, _fillColor);
            AddTri(_center + v0Bottom, _center + v2Bottom, _center + v1Bottom, _fillColor);
            AddTri(_center + v2Top, _center + v1Top, _center + v1Bottom, _fillColor);
            AddTri(_center + v1Bottom, _center + v2Bottom, _center + v2Top, _fillColor);

            // lines
            AddLine(_center + v1Top, _center + v2Top, white, white);
            AddLine(_center + v1Top, _center + v1Bottom, white, white);
            AddLine(_center + v1Bottom, _center + v2Bottom, white, white);
        }
    }

    void Gizmos::AddRing(const glm::vec3& _center, float _innerRadius, float _outerRadius, unsigned int _segments, const glm::vec4& _fillColor, const glm::mat4* _transform)
    {
        glm::vec4 vSolid = _fillColor;
        vSolid.w = 1;

        float fSegmentSize = 2 * glm::pi<float>() / (float)_segments;

        for(unsigned int i = 0; i < _segments; ++i)
        {
            glm::vec3 v1Outer(sinf(i * fSegmentSize) * _outerRadius, 0, cosf(i * fSegmentSize) * _outerRadius);
            glm::vec3 v2Outer(sinf((i + 1) * fSegmentSize) * _outerRadius, 0, cosf((i + 1) * fSegmentSize) * _outerRadius);
            glm::vec3 v1Inner(sinf(i * fSegmentSize) * _innerRadius, 0, cosf(i * fSegmentSize) * _innerRadius);
            glm::vec3 v2Inner(sinf((i + 1) * fSegmentSize) * _innerRadius, 0, cosf((i + 1) * fSegmentSize) * _innerRadius);

            if(_transform != nullptr)
            {
                v1Outer = (*_transform * glm::vec4(v1Outer, 0)).xyz;
                v2Outer = (*_transform * glm::vec4(v2Outer, 0)).xyz;
                v1Inner = (*_transform * glm::vec4(v1Inner, 0)).xyz;
                v2Inner = (*_transform * glm::vec4(v2Inner, 0)).xyz;
            }

            if(_fillColor.w != 0)
            {
                AddTri(_center + v2Outer, _center + v1Outer, _center + v1Inner, _fillColor);
                AddTri(_center + v1Inner, _center + v2Inner, _center + v2Outer, _fillColor);

                AddTri(_center + v1Inner, _center + v1Outer, _center + v2Outer, _fillColor);
                AddTri(_center + v2Outer, _center + v2Inner, _center + v1Inner, _fillColor);
            }
            else
            {
                // line
                AddLine(_center + v1Inner + _center, _center + v2Inner + _center, vSolid, vSolid);
                AddLine(_center + v1Outer + _center, _center + v2Outer + _center, vSolid, vSolid);
            }
        }
    }

    void Gizmos::AddDisk(const glm::vec3& _center, float _radius, unsigned int _segments, const glm::vec4& _fillColor, const glm::mat4* _transform)
    {
        glm::vec4 vSolid = _fillColor;
        vSolid.w = 1;

        float fSegmentSize = 2 * glm::pi<float>() / (float)_segments;

        for(unsigned int i = 0; i < _segments; ++i)
        {
            glm::vec3 v1Outer(sinf(i * fSegmentSize) * _radius, 0, cosf(i * fSegmentSize) * _radius);
            glm::vec3 v2Outer(sinf((i + 1) * fSegmentSize) * _radius, 0, cosf((i + 1) * fSegmentSize) * _radius);

            if(_transform != nullptr)
            {
                v1Outer = (*_transform * glm::vec4(v1Outer, 0)).xyz;
                v2Outer = (*_transform * glm::vec4(v2Outer, 0)).xyz;
            }

            if(_fillColor.w != 0)
            {
                AddTri(_center, _center + v1Outer, _center + v2Outer, _fillColor);
                AddTri(_center + v2Outer, _center + v1Outer, _center, _fillColor);
            }
            else
            {
                // line
                AddLine(_center + v1Outer, _center + v2Outer, vSolid, vSolid);
            }
        }
    }

    void Gizmos::AddArc(const glm::vec3& _center, float _rotation, float _radius, float _arcHalfAngle, unsigned int _segments, const glm::vec4& _fillColor, const glm::mat4* _transform)
    {
        glm::vec4 vSolid = _fillColor;
        vSolid.w = 1;

        float fSegmentSize = 2 * _arcHalfAngle / (float)_segments;

        for(unsigned int i = 0; i < _segments; ++i)
        {
            glm::vec3 v1Outer(sinf(i * fSegmentSize - _arcHalfAngle + _rotation) * _radius, 0, cosf(i * fSegmentSize - _arcHalfAngle + _rotation) * _radius);
            glm::vec3 v2Outer(sinf((i + 1) * fSegmentSize - _arcHalfAngle + _rotation) * _radius, 0, cosf((i + 1) * fSegmentSize - _arcHalfAngle + _rotation) * _radius);

            if(_transform != nullptr)
            {
                v1Outer = (*_transform * glm::vec4(v1Outer, 0)).xyz;
                v2Outer = (*_transform * glm::vec4(v2Outer, 0)).xyz;
            }

            if(_fillColor.w != 0)
            {
                AddTri(_center, _center + v1Outer, _center + v2Outer, _fillColor);
                AddTri(_center + v2Outer, _center + v1Outer, _center, _fillColor);
            }
            else
            {
                // line
                AddLine(_center + v1Outer, _center + v2Outer, vSolid, vSolid);
            }
        }

        // edge lines
        if(_fillColor.w == 0)
        {
            glm::vec3 v1outer(sinf(-_arcHalfAngle + _rotation) * _radius, 0, cosf(-_arcHalfAngle + _rotation) * _radius);
            glm::vec3 v2outer(sinf(_arcHalfAngle + _rotation) * _radius, 0, cosf(_arcHalfAngle + _rotation) * _radius);

            if(_transform != nullptr)
            {
                v1outer = (*_transform * glm::vec4(v1outer, 0)).xyz;
                v2outer = (*_transform * glm::vec4(v2outer, 0)).xyz;
            }

            AddLine(_center, _center + v1outer, vSolid, vSolid);
            AddLine(_center, _center + v2outer, vSolid, vSolid);
        }
    }

    void Gizmos::AddArcRing(const glm::vec3& _center, float _rotation, float _innerRadius, float _outerRadius, float _arcHalfAngle, unsigned int _segments, const glm::vec4& _fillColor, const glm::mat4* _transform)
    {
        glm::vec4 vSolid = _fillColor;
        vSolid.w = 1;

        float fSegmentSize = (2 * _arcHalfAngle) / _segments;

        for(unsigned int i = 0; i < _segments; ++i)
        {
            glm::vec3 v1Outer(sinf(i * fSegmentSize - _arcHalfAngle + _rotation) * _outerRadius, 0, cosf(i * fSegmentSize - _arcHalfAngle + _rotation) * _outerRadius);
            glm::vec3 v2Outer(sinf((i + 1) * fSegmentSize - _arcHalfAngle + _rotation) * _outerRadius, 0, cosf((i + 1) * fSegmentSize - _arcHalfAngle + _rotation) * _outerRadius);
            glm::vec3 v1Inner(sinf(i * fSegmentSize - _arcHalfAngle + _rotation) * _innerRadius, 0, cosf(i * fSegmentSize - _arcHalfAngle + _rotation) * _innerRadius);
            glm::vec3 v2Inner(sinf((i + 1) * fSegmentSize - _arcHalfAngle + _rotation) * _innerRadius, 0, cosf((i + 1) * fSegmentSize - _arcHalfAngle + _rotation) * _innerRadius);

            if(_transform != nullptr)
            {
                v1Outer = (*_transform * glm::vec4(v1Outer, 0)).xyz;
                v2Outer = (*_transform * glm::vec4(v2Outer, 0)).xyz;
                v1Inner = (*_transform * glm::vec4(v1Inner, 0)).xyz;
                v2Inner = (*_transform * glm::vec4(v2Inner, 0)).xyz;
            }

            if(_fillColor.w != 0)
            {
                AddTri(_center + v2Outer, _center + v1Outer, _center + v1Inner, _fillColor);
                AddTri(_center + v1Inner, _center + v2Inner, _center + v2Outer, _fillColor);

                AddTri(_center + v1Inner, _center + v1Outer, _center + v2Outer, _fillColor);
                AddTri(_center + v2Outer, _center + v2Inner, _center + v1Inner, _fillColor);
            }
            else
            {
                // line
                AddLine(_center + v1Inner, _center + v2Inner, vSolid, vSolid);
                AddLine(_center + v1Outer, _center + v2Outer, vSolid, vSolid);
            }
        }

        // edge lines
        if(_fillColor.w == 0)
        {
            glm::vec3 v1Outer(sinf(-_arcHalfAngle + _rotation) * _outerRadius, 0, cosf(-_arcHalfAngle + _rotation) * _outerRadius);
            glm::vec3 v2Outer(sinf(_arcHalfAngle + _rotation) * _outerRadius, 0, cosf(_arcHalfAngle + _rotation) * _outerRadius);
            glm::vec3 v1Inner(sinf(-_arcHalfAngle + _rotation) * _innerRadius, 0, cosf(-_arcHalfAngle + _rotation) * _innerRadius);
            glm::vec3 v2Inner(sinf(_arcHalfAngle + _rotation) * _innerRadius, 0, cosf(_arcHalfAngle + _rotation) * _innerRadius);

            if(_transform != nullptr)
            {
                v1Outer = (*_transform * glm::vec4(v1Outer, 0)).xyz;
                v2Outer = (*_transform * glm::vec4(v2Outer, 0)).xyz;
                v1Inner = (*_transform * glm::vec4(v1Inner, 0)).xyz;
                v2Inner = (*_transform * glm::vec4(v2Inner, 0)).xyz;
            }

            AddLine(_center + v1Inner, _center + v1Outer, vSolid, vSolid);
            AddLine(_center + v2Inner, _center + v2Outer, vSolid, vSolid);
        }
    }

    void Gizmos::AddSphere(const glm::vec3& _center, float _radius, int _rows, int _columns, const glm::vec4& _fillColor, const glm::mat4* _transform, float _longMin, float _longMax, float _latMin, float _latMax)
    {
        float inverseRadius = 1 / _radius;
        //Invert these first as the multiply is slightly quicker
        float invColumns = 1.0f / static_cast<float>(_columns);
        float invRows = 1.0f / static_cast<float>(_rows);

        float deg2Rad = glm::pi<float>() / 180;

        //Lets put everything in radians first
        float latitiudinalRange = (_latMax - _latMin) * deg2Rad;
        float longitudinalRange = (_longMax - _longMin) * deg2Rad;
        // for each row of the mesh
        glm::vec3* v4Array = new glm::vec3[_rows * _columns + _columns];

        for(int row = 0; row <= _rows; ++row)
        {
            // y ordinates this may be a little confusing but here we are navigating around the xAxis in GL
            float ratioAroundXAxis = static_cast<float>(row) * invRows;
            float radiansAboutXAxis = ratioAroundXAxis * latitiudinalRange + (_latMin * deg2Rad);
            float y = _radius * sin(radiansAboutXAxis);
            float z = _radius * cos(radiansAboutXAxis);

            for(int col = 0; col <= _columns; ++col)
            {
                float ratioAroundYAxis = static_cast<float>(col) * invColumns;
                float theta = ratioAroundYAxis * longitudinalRange + (_longMin * deg2Rad);
                glm::vec3 v4Point(-z * sinf(theta), y, -z * cosf(theta));
                glm::vec3 v4Normal(inverseRadius * v4Point.x, inverseRadius * v4Point.y, inverseRadius * v4Point.z);

                if(_transform != nullptr)
                {
                    v4Point = (*_transform * glm::vec4(v4Point, 0)).xyz;
                    v4Normal = (*_transform * glm::vec4(v4Normal, 0)).xyz;
                }

                int index = row * _columns + (col % _columns);
                v4Array[index] = v4Point;
            }
        }

        for(int face = 0; face < (_rows) * (_columns); ++face)
        {
            int iNextFace = face + 1;

            if(iNextFace % _columns == 0)
            {
                iNextFace = iNextFace - (_columns);
            }

            AddLine(_center + v4Array[face], _center + v4Array[face + _columns], glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f));

            if(face % _columns == 0 && longitudinalRange < (glm::pi<float>() * 2))
            {
                continue;
            }
            AddLine(_center + v4Array[iNextFace + _columns], _center + v4Array[face + _columns], glm::vec4(1.f, 1.f, 1.f, 1.f), glm::vec4(1.f, 1.f, 1.f, 1.f));

            AddTri(_center + v4Array[iNextFace + _columns], _center + v4Array[face], _center + v4Array[iNextFace], _fillColor);
            AddTri(_center + v4Array[iNextFace + _columns], _center + v4Array[face + _columns], _center + v4Array[face], _fillColor);
        }

        delete[] v4Array;
    }

    void Gizmos::AddHermiteSpline(const glm::vec3& _start, const glm::vec3& _end, const glm::vec3& _tangentStart, const glm::vec3& _tangentEnd, unsigned int _segments, const glm::vec4& _color)
    {
        _segments = _segments > 1 ? _segments : 1;

        glm::vec3 prev = _start;

        for(unsigned int i = 1; i <= _segments; ++i)
        {
            float s = i / (float) _segments;

            float s2 = s * s;
            float s3 = s2 * s;
            float h1 = (2.0f * s3) - (3.0f * s2) + 1.0f;
            float h2 = (-2.0f * s3) + (3.0f * s2);
            float h3 = s3 - (2.0f * s2) + s;
            float h4 = s3 - s2;
            glm::vec3 p = (_start * h1) + (_end * h2) + (_tangentStart * h3) + (_tangentEnd * h4);

            AddLine(prev, p, _color, _color);
            prev = p;
        }
    }

    void Gizmos::AddLine(const glm::vec3& _rv0, const glm::vec3& _rv1, const glm::vec4& _color)
    {
        AddLine(_rv0, _rv1, _color, _color);
    }

    void Gizmos::AddLine(const glm::vec3& _rv0, const glm::vec3& _rv1, const glm::vec4& _color0, const glm::vec4& _color1)
    {
        if(m_singleton != nullptr &&
            m_singleton->m_lineCount < m_singleton->m_maxLines)
        {
            m_singleton->m_lines[m_singleton->m_lineCount].v0.position = glm::vec4(_rv0, 1);
            m_singleton->m_lines[m_singleton->m_lineCount].v0.color = _color0;
            m_singleton->m_lines[m_singleton->m_lineCount].v1.position = glm::vec4(_rv1, 1);
            m_singleton->m_lines[m_singleton->m_lineCount].v1.color = _color1;

            m_singleton->m_lineCount++;
        }
    }

    void Gizmos::AddTri(const glm::vec3& _rv0, const glm::vec3& _rv1, const glm::vec3& _rv2, const glm::vec4& _color)
    {
        if(m_singleton != nullptr)
        {
            if(_color.w == 1)
            {
                if(m_singleton->m_triCount < m_singleton->m_maxTris)
                {
                    m_singleton->m_tris[m_singleton->m_triCount].v0.position = glm::vec4(_rv0, 1);
                    m_singleton->m_tris[m_singleton->m_triCount].v1.position = glm::vec4(_rv1, 1);
                    m_singleton->m_tris[m_singleton->m_triCount].v2.position = glm::vec4(_rv2, 1);
                    m_singleton->m_tris[m_singleton->m_triCount].v0.color = _color;
                    m_singleton->m_tris[m_singleton->m_triCount].v1.color = _color;
                    m_singleton->m_tris[m_singleton->m_triCount].v2.color = _color;

                    m_singleton->m_triCount++;
                }
            }
            else
            {
                if(m_singleton->m_transparentTriCount < m_singleton->m_maxTris)
                {
                    m_singleton->m_transparentTris[m_singleton->m_transparentTriCount].v0.position = glm::vec4(_rv0, 1);
                    m_singleton->m_transparentTris[m_singleton->m_transparentTriCount].v1.position = glm::vec4(_rv1, 1);
                    m_singleton->m_transparentTris[m_singleton->m_transparentTriCount].v2.position = glm::vec4(_rv2, 1);
                    m_singleton->m_transparentTris[m_singleton->m_transparentTriCount].v0.color = _color;
                    m_singleton->m_transparentTris[m_singleton->m_transparentTriCount].v1.color = _color;
                    m_singleton->m_transparentTris[m_singleton->m_transparentTriCount].v2.color = _color;

                    m_singleton->m_transparentTriCount++;
                }
            }
        }
    }

    void Gizmos::Add2DAabb(const glm::vec2& _center, const glm::vec2& _extents, const glm::vec4& _color, const glm::mat4* _transform)
    {
        glm::vec2 verts[4];
        glm::vec2 vX(_extents.x, 0);
        glm::vec2 vY(0, _extents.y);

        if(_transform != nullptr)
        {
            vX = (*_transform * glm::vec4(vX, 0, 0)).xy();
            vY = (*_transform * glm::vec4(vY, 0, 0)).xy();
        }

        verts[0] = _center - vX - vY;
        verts[1] = _center + vX - vY;
        verts[2] = _center - vX + vY;
        verts[3] = _center + vX + vY;

        Add2DLine(verts[0], verts[1], _color, _color);
        Add2DLine(verts[1], verts[2], _color, _color);
        Add2DLine(verts[2], verts[3], _color, _color);
        Add2DLine(verts[3], verts[0], _color, _color);
    }

    void Gizmos::Add2DAabbFilled(const glm::vec2& _center, const glm::vec2& _extents, const glm::vec4& _color, const glm::mat4* _transform)
    {
        glm::vec2 verts[4];
        glm::vec2 vX(_extents.x, 0);
        glm::vec2 vY(0, _extents.y);

        if(_transform != nullptr)
        {
            vX = (*_transform * glm::vec4(vX, 0, 0)).xy();
            vY = (*_transform * glm::vec4(vY, 0, 0)).xy();
        }

        verts[0] = _center - vX - vY;
        verts[1] = _center + vX - vY;
        verts[2] = _center + vX + vY;
        verts[3] = _center - vX + vY;

        Add2DTri(verts[0], verts[1], verts[2], _color);
        Add2DTri(verts[0], verts[2], verts[3], _color);
    }

    auto Gizmos::Add2DCircle(const glm::vec2& _center, float _radius, unsigned int _segments, const glm::vec4& _color, const glm::mat4* _transform) -> void
    {
        glm::vec4 solidColor = _color;
        solidColor.w = 1;

        float segmentSize = 2 * glm::pi<float>() / _segments;

        for(unsigned int i = 0; i < _segments; ++i)
        {
            glm::vec2 v1Outer(sinf(i * segmentSize) * _radius, cosf(i * segmentSize) * _radius);
            glm::vec2 v2Outer(sinf((i + 1) * segmentSize) * _radius, cosf((i + 1) * segmentSize) * _radius);

            if(_transform != nullptr)
            {
                v1Outer = (*_transform * glm::vec4(v1Outer, 0, 0)).xy();
                v2Outer = (*_transform * glm::vec4(v2Outer, 0, 0)).xy();
            }

            if(_color.w != 0)
            {
                Add2DTri(_center, _center + v1Outer, _center + v2Outer, _color);
                Add2DTri(_center + v2Outer, _center + v1Outer, _center, _color);
            }
            else
            {
                // line
                Add2DLine(_center + v1Outer, _center + v2Outer, solidColor, solidColor);
            }
        }
    }

    void Gizmos::Add2DLine(const glm::vec2& _start, const glm::vec2& _end, const glm::vec4& _color)
    {
        Add2DLine(_start, _end, _color, _color);
    }

    void Gizmos::Add2DLine(const glm::vec2& _start, const glm::vec2& _end, const glm::vec4& _color0, const glm::vec4& _color1)
    {
        if(m_singleton != nullptr && m_singleton->m_2dLineCount < m_singleton->m_max2DLines)
        {
            m_singleton->m_2dLines[m_singleton->m_2dLineCount].v0.position = glm::vec4(_start, 1, 1);
            m_singleton->m_2dLines[m_singleton->m_2dLineCount].v0.color = _color0;
            m_singleton->m_2dLines[m_singleton->m_2dLineCount].v1.position = glm::vec4(_end, 1, 1);
            m_singleton->m_2dLines[m_singleton->m_2dLineCount].v1.color = _color1;

            m_singleton->m_2dLineCount++;
        }
    }

    void Gizmos::Add2DTri(const glm::vec2& _rv0, const glm::vec2& _rv1, const glm::vec2& _rv2, const glm::vec4& _color)
    {
        if(m_singleton != nullptr)
        {
            if(m_singleton->m_2dTriCount < m_singleton->m_max2DTris)
            {
                m_singleton->m_2dTris[m_singleton->m_2dTriCount].v0.position = glm::vec4(_rv0, 1, 1);
                m_singleton->m_2dTris[m_singleton->m_2dTriCount].v1.position = glm::vec4(_rv1, 1, 1);
                m_singleton->m_2dTris[m_singleton->m_2dTriCount].v2.position = glm::vec4(_rv2, 1, 1);
                m_singleton->m_2dTris[m_singleton->m_2dTriCount].v0.color = _color;
                m_singleton->m_2dTris[m_singleton->m_2dTriCount].v1.color = _color;
                m_singleton->m_2dTris[m_singleton->m_2dTriCount].v2.color = _color;

                m_singleton->m_2dTriCount++;
            }
        }
    }

    void Gizmos::Draw(const glm::mat4& _projectionView)
    {
        if(m_singleton != nullptr && (m_singleton->m_lineCount > 0 || m_singleton->m_triCount > 0 || m_singleton->m_transparentTriCount > 0))
        {
            glUseProgram(m_singleton->m_shader);

            const unsigned int projectionViewUniform = glGetUniformLocation(m_singleton->m_shader, "ProjectionView");
            glUniformMatrix4fv(projectionViewUniform, 1, false, glm::value_ptr(_projectionView));

            if(m_singleton->m_lineCount > 0)
            {
                glBindBuffer(GL_ARRAY_BUFFER, m_singleton->m_lineVbo);
                glBufferSubData(GL_ARRAY_BUFFER, 0, m_singleton->m_lineCount * sizeof(GizmoLine), m_singleton->m_lines);

                glBindVertexArray(m_singleton->m_lineVao);
                glDrawArrays(GL_LINES, 0, m_singleton->m_lineCount * 2);
            }

            if(m_singleton->m_triCount > 0)
            {
                glBindBuffer(GL_ARRAY_BUFFER, m_singleton->m_triVbo);
                glBufferSubData(GL_ARRAY_BUFFER, 0, m_singleton->m_triCount * sizeof(GizmoTri), m_singleton->m_tris);

                glBindVertexArray(m_singleton->m_triVao);
                glDrawArrays(GL_TRIANGLES, 0, m_singleton->m_triCount * 3);
            }

            if(m_singleton->m_transparentTriCount > 0)
            {
                // not ideal to store these, but Gizmos must work stand-alone
                const GLboolean blendEnabled = glIsEnabled(GL_BLEND);
                GLboolean depthMask = GL_TRUE;
                glGetBooleanv(GL_DEPTH_WRITEMASK, &depthMask);
                int src, dst;
                glGetIntegerv(GL_BLEND_SRC, &src);
                glGetIntegerv(GL_BLEND_DST, &dst);

                // setup blend states
                if(blendEnabled == GL_FALSE)
                    glEnable(GL_BLEND);
                
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glDepthMask(GL_FALSE);

                glBindBuffer(GL_ARRAY_BUFFER, m_singleton->m_transparentTriVbo);
                glBufferSubData(GL_ARRAY_BUFFER, 0, m_singleton->m_transparentTriCount * sizeof(GizmoTri), m_singleton->m_transparentTris);

                glBindVertexArray(m_singleton->m_transparentTriVao);
                glDrawArrays(GL_TRIANGLES, 0, m_singleton->m_transparentTriCount * 3);

                // reset state
                glDepthMask(depthMask);
                glBlendFunc(src, dst);
                
                if(blendEnabled == GL_FALSE)
                    glDisable(GL_BLEND);
            }

            glUseProgram(0);
        }
    }

    void Gizmos::Draw(const glm::mat4& _projection, const glm::mat4& _view)
    {
        Draw(_projection * _view);
    }

    void Gizmos::Draw2D(const glm::mat4& _projection)
    {
        if(m_singleton != nullptr && (m_singleton->m_2dLineCount > 0 || m_singleton->m_2dTriCount > 0))
        {
            glUseProgram(m_singleton->m_shader);

            const unsigned int projectionViewUniform = glGetUniformLocation(m_singleton->m_shader, "ProjectionView");
            glUniformMatrix4fv(projectionViewUniform, 1, false, glm::value_ptr(_projection));

            if(m_singleton->m_2dLineCount > 0)
            {
                glBindBuffer(GL_ARRAY_BUFFER, m_singleton->m_2dLineVbo);
                glBufferSubData(GL_ARRAY_BUFFER, 0, m_singleton->m_2dLineCount * sizeof(GizmoLine), m_singleton->m_2dLines);

                glBindVertexArray(m_singleton->m_2dLineVao);
                glDrawArrays(GL_LINES, 0, m_singleton->m_2dLineCount * 2);
            }

            if(m_singleton->m_2dTriCount > 0)
            {
                const GLboolean blendEnabled = glIsEnabled(GL_BLEND);

                GLboolean depthMask = GL_TRUE;
                glGetBooleanv(GL_DEPTH_WRITEMASK, &depthMask);

                int src, dst;
                glGetIntegerv(GL_BLEND_SRC, &src);
                glGetIntegerv(GL_BLEND_DST, &dst);

                if(blendEnabled == GL_FALSE)
                    glEnable(GL_BLEND);

                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                glDepthMask(GL_FALSE);

                glBindBuffer(GL_ARRAY_BUFFER, m_singleton->m_2dTriVbo);
                glBufferSubData(GL_ARRAY_BUFFER, 0, m_singleton->m_2dTriCount * sizeof(GizmoTri), m_singleton->m_2dTris);

                glBindVertexArray(m_singleton->m_2dTriVao);
                glDrawArrays(GL_TRIANGLES, 0, m_singleton->m_2dTriCount * 3);

                glDepthMask(depthMask);

                glBlendFunc(src, dst);

                if(blendEnabled == GL_FALSE)
                    glDisable(GL_BLEND);
            }

            glUseProgram(0);
        }
    }
}
