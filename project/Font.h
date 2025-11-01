#pragma once
#include "Vector2.h"



class Font
{
public:
  Font();
  Font(void* _texture, void* _bufferTextStyle, float _height);
  ~Font();


  static Font* Load(const char* _fileName, float _heigt);

  float GetHeight() const;
  Vector2 GetTextSize(const char* _text);

  void Draw(const char* _text, const Vector2& _pos);

private:

  void* m_texture;
  void* m_bufferTextStyle;

  float m_fHeight;
  int m_currentTextSize;
};

struct GameFont
{

  Font* m_pFont;
  Vector2 m_vCurrentPosition;
  float m_fCurrentVelocity;

  float m_fRed;
  float m_fGreen;
  float m_fBlue;
};

