#include "PixelCollider.h"
#include "iostream"
#include <litegfx.h>

PixelCollider::PixelCollider(const Vector2& _pos, const Vector2& _size, unsigned char* _pixeles, unsigned int _maxFrame, unsigned int _textureSize)
  :m_pos(_pos), m_size(_size), m_pPixeles(_pixeles), m_maxFrame(_maxFrame), m_textureSize(_textureSize), m_uiCurrentFrame(1), m_scale(Vector2(1,1))
{

}

bool PixelCollider::Collides(const Collider& _collider) const
{
  
  Vector2 TrueSize = (m_size / m_scale);
  unsigned char* newTexture = new unsigned char[(m_size.x / m_scale.x) * (m_size.y / m_scale.y) + 1];
  unsigned int timer = (TrueSize.x * (TrueSize.y - 1)) + (m_uiCurrentFrame - 1) * TrueSize.x;

  timer = 0;
  printf("Abeja 1 \nMin = %f\nMax = %u", ((m_uiCurrentFrame - 1) * (TrueSize.x)) - 1, m_uiCurrentFrame * static_cast<unsigned int>(TrueSize.x));
  for (unsigned int i = 0; i < m_textureSize; i++)
  {
    
    if (i % static_cast<unsigned int>(TrueSize.x) * m_maxFrame > ((m_uiCurrentFrame - 1) * (TrueSize.x)) - 1
      && i % static_cast<unsigned int>(TrueSize.x) * m_maxFrame < m_uiCurrentFrame * static_cast<unsigned int>(TrueSize.x))
    {
      newTexture[timer] = m_pPixeles[i];
      timer++;
    }
  }
  bool valor = _collider.Collides(m_pos, m_size, m_scale, newTexture, (m_size.x / m_scale.x) * (m_size.y / m_scale.y) + 1);
  delete[] newTexture;
  return valor;
}

bool PixelCollider::Collides(const Vector2& _pos, float _radius) const
{
  Vector2 TrueSize = (m_size / m_scale);
  unsigned char* newTexture = new unsigned char[(m_size.x / m_scale.x) * (m_size.y / m_scale.y) + 1];
  unsigned int timer = (TrueSize.x * (TrueSize.y - 1)) + (m_uiCurrentFrame - 1) * TrueSize.x;

  timer = 0;
  for (unsigned int i = 0; i < m_textureSize; i++)
  {
    if (i % static_cast<unsigned int>(TrueSize.x) * m_maxFrame > ((m_uiCurrentFrame - 1) * (TrueSize.x)) - 1 && i % static_cast<unsigned int>(TrueSize.x) * m_maxFrame < m_uiCurrentFrame * static_cast<unsigned int>(TrueSize.x))
    {
      newTexture[timer] = m_pPixeles[i];
      timer++;
    }
  }
  bool valor = CheckCirclePixel(_pos, _radius, m_pos, m_size, m_scale, newTexture, (m_size.x / m_scale.x) * (m_size.y / m_scale.y) + 1);
  delete[] newTexture;
  return valor;
}

bool PixelCollider::Collides(const Vector2& _pos, const Vector2& _size) const
{
  Vector2 TrueSize = (m_size / m_scale);
  unsigned char* newTexture = new unsigned char[(m_size.x / m_scale.x) * (m_size.y / m_scale.y) + 1];
  unsigned int timer = (TrueSize.x * (TrueSize.y - 1)) + (m_uiCurrentFrame - 1) * TrueSize.x;

  timer = 0;
  for (unsigned int i = 0; i < m_textureSize; i++)
  {
    if (i % static_cast<unsigned int>(TrueSize.x) * m_maxFrame > ((m_uiCurrentFrame - 1) * (TrueSize.x)) - 1 
      && i % static_cast<unsigned int>(TrueSize.x) * m_maxFrame < m_uiCurrentFrame * static_cast<unsigned int>(TrueSize.x))
    {
      newTexture[timer] = m_pPixeles[i];
      timer++;
    }
  }
  bool valor = CheckRectPixel(_pos, _size, m_pos, m_size, m_scale, newTexture, (m_size.x / m_scale.x) * (m_size.y / m_scale.y) + 1);
  delete[] newTexture;
  return valor;
}


bool PixelCollider::Collides(const Vector2& _pos, const Vector2& _size, const Vector2& _scale, const unsigned char* _pixel, unsigned int _textureSize) const
{
  Vector2 TrueSize = (m_size / m_scale);
  unsigned char* newTexture = new unsigned char[(m_size.x / m_scale.x) * (m_size.y / m_scale.y) + 1];
  unsigned int timer = (TrueSize.x * (TrueSize.y - 1)) + (m_uiCurrentFrame - 1) * TrueSize.x;

  timer = 0;
  printf("\nAbeja 2 \nMin = %f\nMax = %u", ((m_uiCurrentFrame - 1) * (TrueSize.x)) - 1, m_uiCurrentFrame * static_cast<unsigned int>(TrueSize.x));
  for (unsigned int i = 0; i < m_textureSize; i++)
  {
    if (i % static_cast<unsigned int>(TrueSize.x) * m_maxFrame > ((m_uiCurrentFrame - 1) * (TrueSize.x)) - 1 
      && i % static_cast<unsigned int>(TrueSize.x) * m_maxFrame < m_uiCurrentFrame * static_cast<unsigned int>(TrueSize.x))
    {
      newTexture[timer] = m_pPixeles[i];
      timer++;
    }
  }

  bool valor = CheckPixelPixel(m_pos, m_size, m_scale,  newTexture, (m_size.x / m_scale.x) * (m_size.y / m_scale.y) + 1, _pos, _size, _scale, &_pixel[0], _textureSize);
  delete[] newTexture;
  return valor;
}



void PixelCollider::SetPos(const Vector2& _pos)
{
  m_pos = _pos;
}

void PixelCollider::SetSize(const Vector2& _size)
{
  m_size = _size;
}

void PixelCollider::SetScale(const Vector2& _scale) 
{
  m_scale = _scale;
}

void PixelCollider::SetCurrentFrame(unsigned int _currentFrame)
{
  m_uiCurrentFrame = _currentFrame;
}

const Vector2 PixelCollider::GetPos() const
{
  return m_pos;
}

const Vector2 PixelCollider::GetSize() const
{
  return m_size;
}

const Vector2 PixelCollider::GetScale() const
{
  return m_scale;
}

unsigned int PixelCollider::GetCurrentFrame() const
{
  return m_uiCurrentFrame;
}

