#pragma once
#include "Collider.h"
class RectCollider :
    public Collider
{
public:
  RectCollider(const Vector2&, const Vector2&);
  virtual bool Collides(const Collider&) const override;
  virtual bool Collides(const Vector2&, float) const override;
  virtual bool Collides(const Vector2&, const Vector2&) const override;
  virtual bool Collides(const Vector2&, const Vector2&, const Vector2&, const unsigned char*, unsigned int) const override;

  void SetPos(const Vector2&);
  void SetSize(const Vector2&);

  const Vector2 GetPos() const;
  const Vector2 GetSize() const;
private:
  Vector2 m_Size;
  Vector2 m_Position;

};

