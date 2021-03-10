#include "utility.h"
#include "math.h"
#include "d3dx9.h"

float ToRadians(float v)
{
    return D3DX_PI * v / 180;
}

Vec2 Vec2Add(Vec2 a, Vec2 b)
{
    Vec2 c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
}

Vec3 Vec3Add(Vec3 a, Vec3 b)
{
    Vec3 c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    c.z = a.z + b.z;
    return c;

}

Vec4 Vec4Add(Vec4 a, Vec4 b)
{
    Vec4 c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    c.z = a.z + b.z;
    c.w = a.w + b.w;
    return c;
}

Vec2 Vec2Sub(Vec2 a, Vec2 b)
{
    Vec2 c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    return c;
}

Vec3 Vec3Sub(Vec3 a, Vec3 b)
{
    Vec3 c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    c.z = a.z - b.z;
    return c;
}

Vec4 Vec4Sub(Vec4 a, Vec4 b)
{
    Vec4 c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    c.z = a.z - b.z;
    c.w = a.w - b.w;
    return c;
}

float Vec3Dot(Vec3 a, Vec3 b)
{
    float result = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
    return result;
}

Vec3 Vec3Cross(Vec3 a, Vec3 b)
{
    Vec3 result;
    result.x = (a.y * b.z) - (a.z * b.y);
    result.y = (a.z * b.x) - (a.x * b.z);
    result.z = (a.x * b.y) - (a.y * b.x);
    return result;
}

float Vec3GetLenght(Vec3 v)
{
    return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

Vec3 NormalizaVec3(Vec3 v)
{
    Vec3 result;
    float lenght = Vec3GetLenght(v);
    result.x = v.x / lenght;
    result.y = v.y / lenght;
    result.z = v.z / lenght;
    return result;
}

Vec3 Vec3MultScalar(Vec3 v, float scalar)
{
    Vec3 result;
    result.x = v.x * scalar;
    result.y = v.y * scalar;
    result.z = v.z * scalar;
    return result;
}

Vec3 Vec3RotateY(Vec3 v, float angle)
{
    Vec3 result;
    result.x = v.x * cos(angle) - v.z * sin(angle);
    result.y = v.y;
    result.z = v.x * sin(angle) + v.z * cos(angle);
    return result;
}

Vec3 Vec3RotateX(Vec3 v, float angle)
{
    Vec3 result;
    result.x = v.x;
    result.y = v.y * cos(angle) - v.z * sin(angle);
    result.z = v.y * sin(angle) + v.z * cos(angle);
    return result;
}

Vec3 Vec3RotateZ(Vec3 v, float angle)
{
    Vec3 result;
    result.x = v.x * cos(angle) - v.y * sin(angle);
    result.y = v.x * sin(angle) + v.y * cos(angle);
    result.z = v.z;
    return result;
}

Vec4 Vec4RotateY(Vec4 v, float angle)
{
    Vec4 result;
    result.x = v.x * cos(angle) - v.z * sin(angle);
    result.y = v.y;
    result.z = v.x * sin(angle) + v.z * cos(angle);
    result.w = v.w;
    return result;
}

Vec4 Vec4RotateX(Vec4 v, float angle)
{
    Vec4 result;
    result.x = v.x;
    result.y = v.y * cos(angle) - v.z * sin(angle);
    result.z = v.y * sin(angle) + v.z * cos(angle);
    result.w = v.w;
    return result;
}

Vec4 Vec4RotateZ(Vec4 v, float angle)
{
    Vec4 result;
    result.x = v.x * cos(angle) - v.y * sin(angle);
    result.y = v.x * sin(angle) + v.y * cos(angle);
    result.z = v.z;
    result.w = v.w;
    return result;
}

Matrix MatrixTranspose(Matrix m)
{
    Matrix result = {{
        {m.m[0][0], m.m[1][0], m.m[2][0], m.m[3][0]},
        {m.m[0][1], m.m[1][1], m.m[2][1], m.m[3][1]},
        {m.m[0][2], m.m[1][2], m.m[2][2], m.m[3][2]},
        {m.m[0][3], m.m[1][3], m.m[2][3], m.m[3][3]}
    }};
    return result;
}

Matrix MatrixTranslation(float x, float y, float z)
{
    Matrix result = {{
        {1.0f, 0.0f, 0.0f,    x},
        {0.0f, 1.0f, 0.0f,    y},
        {0.0f, 0.0f, 1.0f,    z},
        {0.0f, 0.0f, 0.0f, 1.0f}
    }};
    result = MatrixTranspose(result);
    return result;
}

Matrix MatrixScale(float x, float y, float z)
{
    Matrix result = {{
        {   x, 0.0f, 0.0f, 0.0f},
        {0.0f,    y, 0.0f, 0.0f},
        {0.0f, 0.0f,    z, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    }};
    return result;
}

Matrix MatrixRotationX(float angle)
{
    Matrix result = {{
        {1.0f,        0.0f,         0.0f, 0.0f},
        {0.0f, cosf(angle), sinf(angle), 0.0f},
        {0.0f, -sinf(angle),  cosf(angle), 0.0f},
        {0.0f,        0.0f,         0.0f, 1.0f}
    }};
    return result;
}

Matrix MatrixRotationY(float angle)
{

    Matrix result = {{
        {cosf(angle), 0.0f, -sinf(angle), 0.0f},
        {       0.0f, 1.0f,         0.0f, 0.0f},
        {sinf(angle), 0.0f,  cosf(angle), 0.0f},
        {       0.0f, 0.0f,         0.0f, 1.0f}
    }};
    return result;
}

Matrix MatrixRotationZ(float angle)
{
    Matrix result = {{
        {cosf(angle),   sinf(angle), 0.0f, 0.0f},
        {-sinf(angle),  cosf(angle), 0.0f, 0.0f},
        {       0.0f,         0.0f, 1.0f, 0.0f},
        {       0.0f,         0.0f, 0.0f, 1.0f}
    }};
    return result;
}


Matrix GetIdentity()
{
    Matrix result = {{
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    }};
    return result;
}

Vec4 Mat4MultVect4(Matrix m, Vec4 v)
{
    Vec4 result;
    result.x = m.m[0][0] * v.x + m.m[0][1] * v.y + m.m[0][2] * v.z + m.m[0][3] * v.w;
    result.y = m.m[1][0] * v.x + m.m[1][1] * v.y + m.m[1][2] * v.z + m.m[1][3] * v.w;
    result.z = m.m[2][0] * v.x + m.m[2][1] * v.y + m.m[2][2] * v.z + m.m[2][3] * v.w;
    result.w = m.m[3][0] * v.x + m.m[3][1] * v.y + m.m[3][2] * v.z + m.m[3][3] * v.w;
    return result;
}

Matrix MatrixMultiply(Matrix a, Matrix b)
{
    Matrix result;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
                result.m[i][j] =
                a.m[i][0] * b.m[0][j] +
                a.m[i][1] * b.m[1][j] +
                a.m[i][2] * b.m[2][j] +
                a.m[i][3] * b.m[3][j];
        }
    }
    return result;
}

Matrix GetViewMatrix(Vec3 eye, Vec3 target, Vec3 up)
{
    Vec3 z = NormalizaVec3(Vec3Sub(target, eye));
    Vec3 x = NormalizaVec3(Vec3Cross(up, z));
    Vec3 y = Vec3Cross(z, x);
    Matrix result = {{
        { x.x,              y.x,              z.x,             0.0f},
        { x.y,              y.y,              z.y,             0.0f},
        { x.z,              y.z,              z.z,             0.0f},
        {-Vec3Dot(x, eye), -Vec3Dot(y, eye), -Vec3Dot(z, eye), 1.0f}
    }};  
    return result; 
}

Matrix GetProjectionMatrix(float fov, float aspect, float znear, float zfar)
{
    float yScale = 1/tanf(fov/2);
    float xScale = yScale / aspect;
    float a = zfar/(zfar-znear);
    float b = -znear*zfar/(zfar-znear);
    Matrix result = {{
        { xScale,   0.0f, 0.0f, 0.0f},
        {   0.0f, yScale, 0.0f, 0.0f},
        {   0.0f,   0.0f,    a, 1.0f},
        {   0.0f,   0.0f,    b, 0.0f}
    }}; 
    return result;
}

D3DXVECTOR3 GetD3DXVector(Vec3 v)
{
    D3DXVECTOR3 result;
    result.x = v.x;
    result.y = v.y;
    result.z = v.z;
    return result;
}

D3DXVECTOR4 GetD3DXVector(Vec4 v)
{
    D3DXVECTOR4 result;
    result.x = v.x;
    result.y = v.y;
    result.z = v.z;
    result.w = v.w;
    return result;
}

D3DXMATRIX GetD3DXMatrix(Matrix m)
{
    D3DXMATRIX result( m.m[0][0], m.m[0][1], m.m[0][2], m.m[0][3],
                       m.m[1][0], m.m[1][1], m.m[1][2], m.m[1][3],
                       m.m[2][0], m.m[2][1], m.m[2][2], m.m[2][3],
                       m.m[3][0], m.m[3][1], m.m[3][2], m.m[3][3]);
    return result;
}

