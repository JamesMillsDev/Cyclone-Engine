#pragma once

#define GLM_SWIZZLE
#include <glm/glm.hpp>

namespace CycloneEditor
{
    class SceneCamera;
    
    class Gizmos
    {
    public:
        static void Create(unsigned int _maxLines = 0xffff, unsigned int _maxTris = 0xffff, unsigned int _max2DLines = 0xff, unsigned int _max2DTris = 0xff);
        static void Destroy();

        // removes all Gizmos
        static void Clear();

        // draws current Gizmo buffers, either using a combined (projection * view) matrix, or separate matrices
        static void Draw(const SceneCamera& _camera);

        // the projection matrix here should ideally be orthographic with a near of -1 and far of 1
        static void Draw2D(const glm::mat4& _projection);

        // Adds a single debug line
        static void AddLine(const glm::vec3& _rv0, const glm::vec3& _rv1, const glm::vec4& _color);

        // Adds a single debug line
        static void AddLine(const glm::vec3& _rv0, const glm::vec3& _rv1, const glm::vec4& _color0, const glm::vec4& _color1);

        // Adds a triangle.
        static void AddTri(const glm::vec3& _rv0, const glm::vec3& _rv1, const glm::vec3& _rv2, const glm::vec4& _color);

        // Adds 3 unit-length lines (red,green,blue) representing the 3 axis of a transform, 
        // at the transform's translation. Optional scale available.
        static void AddTransform(const glm::mat4& _transform, float _fScale = 1.0f);

        // Adds a wireframe Axis-Aligned Bounding-Box with optional transform for rotation/translation.
        static void AddAabb(const glm::vec3& _center, const glm::vec3& _extents, const glm::vec4& _color, const glm::mat4* _transform = nullptr);

        // Adds an Axis-Aligned Bounding-Box with optional transform for rotation.
        static void AddAabbFilled(const glm::vec3& _center, const glm::vec3& _extents, const glm::vec4& _fillColor, const glm::mat4* _transform = nullptr);

        // Adds a cylinder aligned to the Y-axis with optional transform for rotation.
        static void AddCylinderFilled(const glm::vec3& _center, float _radius, float _fHalfLength, unsigned int _segments, const glm::vec4& _fillColor, const glm::mat4* _transform = nullptr);

        // Adds a double-sided hollow ring in the XZ axis with optional transform for rotation.
        // If _rvFilLColour.w == 0 then only an outer and inner line is drawn.
        static void AddRing(const glm::vec3& _center, float _innerRadius, float _outerRadius, unsigned int _segments, const glm::vec4& _fillColor, const glm::mat4* _transform = nullptr);

        // Adds a double-sided disk in the XZ axis with optional transform for rotation.
        // If _rvFilLColour.w == 0 then only an outer line is drawn.
        static void AddDisk(const glm::vec3& _center, float _radius, unsigned int _segments, const glm::vec4& _fillColor, const glm::mat4* _transform = nullptr);

        // Adds an arc, around the Y-axis
        // If _rvFilLColour.w == 0 then only an outer line is drawn.
        static void AddArc(const glm::vec3& _center, float _rotation, float _radius, float _arcHalfAngle, unsigned int _segments, const glm::vec4& _fillColor, const glm::mat4* _transform = nullptr);

        // Adds an arc, around the Y-axis, starting at the inner radius and extending to the outer radius
        // If _rvFilLColour.w == 0 then only an outer line is drawn.
        static void AddArcRing(const glm::vec3& _center, float _rotation, float _innerRadius, float _outerRadius, float _arcHalfAngle, unsigned int _segments, const glm::vec4& _fillColor, const glm::mat4* _transform = nullptr);

        // Adds a Sphere at a given position, with a given number of rows, and columns, radius and a max and min long and latitude
        static void AddSphere(const glm::vec3& _center, float _radius, int _rows, int _columns, const glm::vec4& _fillColor, const glm::mat4* _transform = nullptr, float _longMin = 0.f, float _longMax = 360, float _latMin = -90, float _latMax = 90);

        // Adds a single Hermite spline curve
        static void AddHermiteSpline(const glm::vec3& _start, const glm::vec3& _end, const glm::vec3& _tangentStart, const glm::vec3& _tangentEnd, unsigned int _segments, const glm::vec4& _color);

        // 2-dimensional gizmos
        static void Add2DLine(const glm::vec2& _start, const glm::vec2& _end, const glm::vec4& _color);
        static void Add2DLine(const glm::vec2& _start, const glm::vec2& _end, const glm::vec4& _color0, const glm::vec4& _color1);
        static void Add2DTri(const glm::vec2& _rv0, const glm::vec2& _rv1, const glm::vec2& _rv2, const glm::vec4& _color);
        static void Add2DAabb(const glm::vec2& _center, const glm::vec2& _extents, const glm::vec4& _color, const glm::mat4* _transform = nullptr);
        static void Add2DAabbFilled(const glm::vec2& _center, const glm::vec2& _extents, const glm::vec4& _color, const glm::mat4* _transform = nullptr);
        static void Add2DCircle(const glm::vec2& _center, float _radius, unsigned int _segments, const glm::vec4& _color, const glm::mat4* _transform = nullptr);

    private:
        Gizmos(unsigned int _maxLines, unsigned int _maxTris, unsigned int _max2DLines, unsigned int _max2DTris);
        ~Gizmos();

        struct GizmoVertex
        {
            glm::vec4 position;
            glm::vec4 color;
        };

        struct GizmoLine
        {
            GizmoVertex v0;
            GizmoVertex v1;
        };

        struct GizmoTri
        {
            GizmoVertex v0;
            GizmoVertex v1;
            GizmoVertex v2;
        };

        unsigned int m_shader;

        // line data
        unsigned int m_maxLines;
        unsigned int m_lineCount;
        GizmoLine* m_lines;

        unsigned int m_lineVao;
        unsigned int m_lineVbo;

        // triangle data
        unsigned int m_maxTris;
        unsigned int m_triCount;
        GizmoTri* m_tris;

        unsigned int m_triVao;
        unsigned int m_triVbo;

        unsigned int m_transparentTriCount;
        GizmoTri* m_transparentTris;

        unsigned int m_transparentTriVao;
        unsigned int m_transparentTriVbo;

        // 2D line data
        unsigned int m_max2DLines;
        unsigned int m_2dLineCount;
        GizmoLine* m_2dLines;

        unsigned int m_2dLineVao;
        unsigned int m_2dLineVbo;

        // 2D triangle data
        unsigned int m_max2DTris;
        unsigned int m_2dTriCount;
        GizmoTri* m_2dTris;

        unsigned int m_2dTriVao;
        unsigned int m_2dTriVbo;

        static Gizmos* m_singleton;
    };
}
