#pragma once

#include "raylib.h"
#include <cmath>

class Mat3
{
public:
  float m[3][3];

  Mat3()
  {
    // Initialize to identity matrix
    m[0][0] = 1.0f;
    m[0][1] = 0.0f;
    m[0][2] = 0.0f;
    m[1][0] = 0.0f;
    m[1][1] = 1.0f;
    m[1][2] = 0.0f;
    m[2][0] = 0.0f;
    m[2][1] = 0.0f;
    m[2][2] = 1.0f;
  }

  Mat3 operator*(const Mat3 &other) const
  {
    Mat3 result;
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j)
      {
        result.m[i][j] = 0;
        for (int k = 0; k < 3; ++k)
          result.m[i][j] += m[i][k] * other.m[k][j];
      }
    return result;
  }

  // Multiply matrix with vector
  Vector2 multiply(const Vector2 &v) const
  {
    Vector2 result;
    result.x = m[0][0] * v.x + m[0][1] * v.y + m[0][2];
    result.y = m[1][0] * v.x + m[1][1] * v.y + m[1][2];
    return result;
  }

  // Static constructors
  static Mat3 translation(float tx, float ty)
  {
    Mat3 mat;
    mat.m[0][2] = tx;
    mat.m[1][2] = ty;
    return mat;
  }

  static Mat3 rotation(float angleRadians)
  {
    Mat3 mat;
    float c = cos(angleRadians);
    float s = sin(angleRadians);
    mat.m[0][0] = c;
    mat.m[0][1] = -s;
    mat.m[1][0] = s;
    mat.m[1][1] = c;
    return mat;
  }

  static Mat3 scale(float sx, float sy)
  {
    Mat3 mat;
    mat.m[0][0] = sx;
    mat.m[1][1] = sy;
    return mat;
  }

  static Mat3 inverseAffine(const Mat3 &mat)
  {
    Mat3 inv;
    float m[3][3];
    for (int i = 0; i < 3; ++i)
      for (int j = 0; j < 3; ++j)
        m[i][j] = mat.m[i][j];

    float det = m[0][0] * m[1][1] - m[0][1] * m[1][0];
    if (std::fabs(det) < 1e-6f)
      return Mat3();

    float invDet = 1.0f / det;

    // Invert 2x2 rotation/scale part
    inv.m[0][0] = m[1][1] * invDet;
    inv.m[0][1] = -m[0][1] * invDet;
    inv.m[1][0] = -m[1][0] * invDet;
    inv.m[1][1] = m[0][0] * invDet;

    // Invert translation
    inv.m[0][2] = -(inv.m[0][0] * m[0][2] + inv.m[0][1] * m[1][2]);
    inv.m[1][2] = -(inv.m[1][0] * m[0][2] + inv.m[1][1] * m[1][2]);

    inv.m[2][0] = 0;
    inv.m[2][1] = 0;
    inv.m[2][2] = 1;

    return inv;
  }
};