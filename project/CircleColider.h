#pragma once
#include "Collider.h"
class CircleColider :
    public Collider
{
public:
  CircleColider(const Vector2&, float);

  virtual bool Collides(const Collider&) const override;
  virtual bool Collides(const Vector2&, float) const override;
  virtual bool Collides(const Vector2&, const Vector2&) const override;
  virtual bool Collides(const Vector2&, const Vector2&, const Vector2&, const unsigned char*, unsigned int) const override;
  
  void SetPos(const Vector2&);
  void SetRadius(float);

  const Vector2 GetPos() const;
  float GetRadius() const;

private:
  Vector2 m_pos;
  float m_fRadius;

};

