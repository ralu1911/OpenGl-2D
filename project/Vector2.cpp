#include "Vector2.h"


Vector2::Vector2()
  :x(0), y(0)
{

}
Vector2::Vector2(float _x, float _y)
  :x(_x), y(_y)
{

}
Vector2::Vector2(const Vector2& _vector)
  :x(_vector.x), y(_vector.y)
{

}
Vector2::~Vector2()
{

}
Vector2 Vector2::operator=(const Vector2& _vector)
{
  this->x = _vector.x;
  this->y = _vector.y;
  return *this;
}

Vector2 Vector2::operator +(const Vector2& _other) const
{
  float auxX = x + _other.x;
  float auxY = y + _other.y;
  Vector2 result_ = Vector2(auxX, auxY);
  return result_;
}
Vector2 Vector2::operator +=(const Vector2& _other)
{
  this->x += _other.x;
  this->y += _other.y;
  return *this;
}
Vector2 Vector2::operator -(const Vector2& _other) const
{
  float auxX = x - _other.x;
  float auxY = y - _other.y;
  Vector2 result_ = Vector2(auxX, auxY);
  return result_;
}
Vector2 Vector2::operator -=(const Vector2& _other)
{
  this->x -= _other.x;
  this->y -= _other.y;
  return *this;
}
Vector2 Vector2::operator *(const Vector2& _other) const
{
  float auxX = x * _other.x;
  float auxY = y * _other.y;
  Vector2 result_ = Vector2(auxX, auxY);
  return result_;
}
Vector2 Vector2::operator *=(const Vector2& _other)
{
  this->x *= _other.x;
  this->y *= _other.y;
  return *this;
}
Vector2 Vector2::operator /(const Vector2& _other) const
{
  float auxX = x / _other.x;
  float auxY = y / _other.y;
  Vector2 result_ = Vector2(auxX, auxY);
  return result_;
}
Vector2 Vector2::operator /=(const Vector2& _other)
{
  this->x /= _other.x;
  this->y /= _other.y;
  return *this;
}

Vector2 Vector2::operator +(const float& _other) const
{
  float auxX = x + _other;
  float auxY = y + _other;
  Vector2 result_ = Vector2(auxX, auxY);
  return result_;
}
Vector2 Vector2::operator +=(const float& _other)
{
  this->x += _other;
  this->y += _other;
  return *this;
}
Vector2 Vector2::operator -(const float& _other) const
{
  float auxX = x - _other;
  float auxY = y - _other;
  Vector2 result_ = Vector2(auxX, auxY);
  return result_;
}
Vector2 Vector2::operator -=(const float& _other)
{
  this->x -= _other;
  this->y -= _other;
  return *this;
}
Vector2 Vector2::operator *(const float& _other) const
{
  float auxX = this->x * _other;
  float auxY = this->y * _other;
  Vector2 result_ = Vector2(auxX, auxY);
  return result_;
}
Vector2 Vector2::operator *=(const float& _other)
{
  this->y *= _other;
  this->x *= _other;
  return *this;
}
Vector2 Vector2::operator /(const float& _other) const
{
  float auxX = x / _other;
  float auxY = y / _other;
  Vector2 result_ = Vector2(auxX, auxY);
  return result_;
}
Vector2 Vector2::operator /=(const float& _other)
{
  this->x /= _other;
  this->y /= _other;
  return *this;
}

Vector2 Vector2::Abs() const
{
  Vector2 result_ = *this;
  result_.x = fabsf(result_.x);
  result_.y = fabsf(result_.y);
  return result_;
}
float Vector2::Lenght() const
{
  float result_ = sqrtf(powf(this->x, 2) + powf(this->y, 2));
  return result_;
}
Vector2 Vector2::Normalize() const
{
  Vector2 result_ = (*this) / this->Lenght();
  return result_;
}
float Vector2::Dot(const Vector2& _vector) const
{
  float result_ = (this->x * _vector.x) + (this->y * _vector.y);
  return result_;
}
float Vector2::Angle(const Vector2& _vector) const
{
  float result_ = acosf(this->Dot(_vector) / (this->Lenght() * _vector.Lenght()));
  return result_;
}
float Vector2::Distance(const Vector2& _vector) const
{
  Vector2 aux = _vector - *this;
  return aux.Lenght();
}

Vector2 Vector2::Right()
{
  return Vector2(1, 0);
}

Vector2 Vector2::Up()
{
  return Vector2(0, 1);
}

Vector2 Vector2::Down()
{
  return Vector2(0, -1);
}

Vector2 Vector2::Left()
{
  return Vector2(-1, 0);
}

Vector2 Vector2::Zero()
{
  return Vector2(0, 0);
}



