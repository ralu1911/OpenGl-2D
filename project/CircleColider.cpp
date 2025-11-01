#include "CircleColider.h"

CircleColider::CircleColider(const Vector2& _pos, float _radius)
  : m_pos(_pos), m_fRadius(_radius)
{
  
}

bool CircleColider::Collides(const Collider& _collider) const
{
  return _collider.Collides(m_pos, m_fRadius);
}

bool CircleColider::Collides(const Vector2& _pos, float _radius) const
{
  return CheckCircleCircle(m_pos , m_fRadius, _pos, _radius);
}

bool CircleColider::Collides(const Vector2& _pos, const Vector2& _size) const
{
  return CheckCircleRect(m_pos, m_fRadius, _pos, _size);
}

bool CircleColider::Collides(const Vector2& _pos, const Vector2& _size, const Vector2& _scale, const unsigned char* _pixel, unsigned int _textureSize) const
{
  return CheckCirclePixel(m_pos, m_fRadius, _pos, _size, _scale , _pixel, _textureSize);
}

void CircleColider::SetPos(const Vector2& _pos)
{
  m_pos = _pos;
}

void CircleColider::SetRadius(float _radius)
{
  m_fRadius = _radius;
}

const Vector2 CircleColider::GetPos() const
{
    return m_pos;
}

float CircleColider::GetRadius() const
{
    return m_fRadius;
}


