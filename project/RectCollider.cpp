#include "RectCollider.h"
#include "iostream"

RectCollider::RectCollider(const Vector2& _pos, const Vector2& _size)
  :m_Position(_pos), m_Size(_size)
{

}

bool RectCollider::Collides(const Collider& _collider) const
{
  return _collider.Collides(m_Position, m_Size);
}

bool RectCollider::Collides(const Vector2& _pos, float _radius) const
{
  return CheckCircleRect(_pos, _radius, m_Position, m_Size);
}

bool RectCollider::Collides(const Vector2& _pos, const Vector2& _size) const
{
  return CheckRectRect(m_Position, m_Size, _pos, _size);
}

bool RectCollider::Collides(const Vector2& _pos, const Vector2& _size, const Vector2& _scale, const unsigned char* _pixel, unsigned int _textureSize) const
{
  return CheckRectPixel(m_Position, m_Size, _pos, _size, _scale, _pixel, _textureSize);
}

void RectCollider::SetPos(const Vector2& _pos)
{
  m_Position = _pos;
}

void RectCollider::SetSize(const Vector2& _size) 
{
  m_Size = _size;
}

const Vector2 RectCollider::GetPos() const
{
  return m_Position;
}

const Vector2 RectCollider::GetSize() const
{
  return m_Size;
}
