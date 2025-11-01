#pragma once
#include "stdint.h"
#include "Vector2.h"

class Collider
{
public:
  virtual bool Collides(const Collider&) const = 0;
  virtual bool Collides(const Vector2&, float ) const = 0;
  virtual bool Collides(const Vector2&, const Vector2&) const = 0;
  virtual bool Collides(const Vector2&, const Vector2&, const Vector2&, const unsigned char*, unsigned int) const = 0;
  void DrawCollisionTexture(const unsigned char* _Pixeles, Vector2 _size, Vector2 _scale, Vector2 _pos, unsigned int _maxFrame) const;

  bool CheckCircleCircle(const Vector2&, float, const Vector2&, float) const;
  bool CheckCircleRect(const Vector2&, float, const Vector2&, const Vector2&) const;
  bool CheckRectRect(const Vector2&, const Vector2&, const Vector2&, const Vector2&) const;
  bool CheckCirclePixel(const Vector2&, float, const Vector2&, const Vector2&, const Vector2&, const unsigned char*, unsigned int) const;
  bool CheckRectPixel(const Vector2&, const Vector2&, const Vector2&, const Vector2&, const Vector2&, const unsigned char*, unsigned int) const;
  bool CheckPixelPixel(const Vector2&, const Vector2&, const Vector2&, const unsigned char*, unsigned int, const Vector2&, const Vector2&, const Vector2&, const unsigned char*, unsigned int) const;
};

