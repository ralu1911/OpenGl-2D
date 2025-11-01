#pragma once
#include "Collider.h"
class PixelCollider :
    public Collider
{
public:
  PixelCollider(const Vector2&, const Vector2&, unsigned char*, unsigned int, unsigned int);

  virtual bool Collides(const Collider&) const override;
  virtual bool Collides(const Vector2&, float) const override;
  virtual bool Collides(const Vector2&, const Vector2&) const override;
  virtual bool Collides(const Vector2&, const Vector2&, const Vector2&, const unsigned char*, unsigned int) const override;

  void SetPos(const Vector2&);
  void SetSize(const Vector2&);
  void SetScale(const Vector2&);
  void SetCurrentFrame(unsigned int);

  const Vector2 GetPos() const;
  const Vector2 GetSize() const;
  const Vector2 GetScale() const;
  unsigned int GetCurrentFrame() const;



private:
  Vector2 m_pos;
  Vector2 m_size;
  Vector2 m_scale;
  unsigned int m_maxFrame;
  unsigned int m_uiCurrentFrame;
  
  unsigned char* m_pPixeles;
  unsigned int m_textureSize;
};

