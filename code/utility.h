#ifndef UTILITY_H
#define UTILITY_H

#include "d3dx9.h"

struct Vec2
{
    float x, y;
};

struct Vec3
{
    float x, y, z;
};

struct Vec4
{
    float x, y, z, w;
};

struct Matrix
{
    float m[4][4];
};

float ToRadians(float v);
Vec2 Vec2Add(Vec2 a, Vec2 b);
Vec3 Vec3Add(Vec3 a, Vec3 b);
Vec4 Vec4Add(Vec4 a, Vec4 b);

Vec2 Vec2Sub(Vec2 a, Vec2 b);
Vec3 Vec3Sub(Vec3 a, Vec3 b);
Vec4 Vec4Sub(Vec4 a, Vec4 b);

float Vec3Dot(Vec3 a, Vec3 b);
Vec3 Vec3Cross(Vec3 a, Vec3 b);
float Vec3GetLenght(Vec3 v);
Vec3 NormalizaVec3(Vec3 v);
Vec3 Vec3MultScalar(Vec3 v, float scalar);

Vec3 Vec3RotateY(Vec3 v, float angle);
Vec3 Vec3RotateX(Vec3 v, float angle);
Vec3 Vec3RotateZ(Vec3 v, float angle);

Vec4 Vec4RotateY(Vec4 v, float angle);
Vec4 Vec4RotateX(Vec4 v, float angle);
Vec4 Vec4RotateZ(Vec4 v, float angle);
Vec4 Mat4MultVect4(Matrix m, Vec4 v);

Matrix MatrixTranspose(Matrix m);
Matrix MatrixTranslation(float x, float y, float z);
Matrix MatrixScale(float x, float y, float z);
Matrix MatrixRotationX(float angle);
Matrix MatrixRotationY(float angle);
Matrix MatrixRotationZ(float angle);

Matrix GetIdentity();
Matrix MatrixMultiply(Matrix a, Matrix b);
Matrix GetViewMatrix(Vec3 eye, Vec3 target, Vec3 up);
Matrix GetProjectionMatrix(float fov, float aspect, float znear, float zfar);

D3DXVECTOR3 GetD3DXVector(Vec3 v);
D3DXVECTOR4 GetD3DXVector(Vec4 v);
D3DXMATRIX GetD3DXMatrix(Matrix m);


#endif
