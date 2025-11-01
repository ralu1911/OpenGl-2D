#include "Font.h"


#include <sstream>
#include <iostream>
#include <fstream>
#include "stb_truetype.h"
#include <stdint.h>


#include <litegfx.h>

Font::Font()
  :m_bufferTextStyle(nullptr), m_texture(nullptr), m_fHeight(0)
{
}

Font::Font(void* _texture, void* _bufferTextStyle, float _height)
  :m_texture(_texture), m_bufferTextStyle(_bufferTextStyle), m_fHeight(_height)
{
}

Font::~Font()
{
  if (m_bufferTextStyle)
  {
    delete[] m_bufferTextStyle;
  }
  ltex_free(static_cast<ltex_t*>(m_texture));
  m_bufferTextStyle = nullptr;
  m_texture = nullptr;

}

Font* Font::Load(const char* _fileName, float _heigt)
{
  Font* font_;
  ltex_t* BufferVRam = ltex_alloc(2048, 2048, 0);
  //"C:/Clase/Master/Programacion 2D/Practica 5/Recursos Practica 1_plantilla/plantilla/project/Orange.ttf"
  std::ifstream stream(_fileName, std::ios::binary);

  if (!stream.bad())
  {

    unsigned char* alphaPixelSize = new unsigned char[BufferVRam->height * BufferVRam->width];
    stbtt_fontinfo info;
    std::filebuf* buffer = stream.rdbuf();
    stream.seekg(0, std::ios::beg);
    unsigned int fileinit = stream.tellg();
    stream.seekg(0, std::ios::end);
    unsigned int fileEnd = stream.tellg();
    unsigned int fileSize = fileEnd - fileinit;
    unsigned char* pbuffer = new unsigned char[fileSize];
    stream.seekg(0, std::ios::beg);
    for (size_t i = 0; i < fileSize; i++)  // copiar el buffer de alpha
    {
      int auxNum = buffer->sbumpc();
      if (auxNum == -1)
      {
        i = fileSize;
      }
      else
      {
        pbuffer[i] = auxNum;
      }

      //for (size_t j = 0; j < sizeof(int); j++)
      //{
      //  char character = reinterpret_cast<char*>(&auxNum)[j];
      //  pbuffer[(i * sizeof(int)) + j] = character;
      //}
    }


    int a = stbtt_InitFont(&info, pbuffer, 0);
    float heigt = stbtt_ScaleForPixelHeight(&info, _heigt);
    int glif = info.numGlyphs;

    stbtt_bakedchar* charStyle = new stbtt_bakedchar[glif];
    stbtt_BakeFontBitmap(pbuffer, 0, _heigt, alphaPixelSize, 2048, 2048, 32, glif, charStyle);

    unsigned int size = 2048 * 2048 * 4;
    unsigned char* pixelchar = new unsigned char[2048 * 2048 * 4];
    unsigned char color = 255;
    for (size_t i = 0; i < size; i++)
    {
      if ((i - 3) % 4 != 0)
      {
        pixelchar[i] = color;
      }
      else
      {
        pixelchar[i] = alphaPixelSize[i/4];
      }
    }

    ltex_setpixels(BufferVRam, pixelchar);
    font_ = new Font(BufferVRam, charStyle, _heigt);
    //for (size_t i = 0; i < size; i++)
    //{
    //  printf("|%c", pixelchar[i]);
    //}


    delete[] pixelchar;
    pixelchar = nullptr;
    delete[] alphaPixelSize;
    alphaPixelSize = nullptr;


    return font_;
  }
  return nullptr;
}

float Font::GetHeight() const
{
  return m_fHeight;
}

Vector2 Font::GetTextSize(const char* _text)
{
  Vector2 size_ = Vector2(0,0);
  for (size_t i = 0; i < m_currentTextSize; i++)
  {
    float sizey = static_cast<stbtt_bakedchar*>(m_bufferTextStyle)[_text[i] - 32].y1 - static_cast<stbtt_bakedchar*>(m_bufferTextStyle)[_text[i] - 32].y0;
    Vector2 Vector = Vector2(static_cast<stbtt_bakedchar*>(m_bufferTextStyle)[_text[i] - 32].x1 - static_cast<stbtt_bakedchar*>(m_bufferTextStyle)[_text[i] - 32].x0
      , sizey > size_.y ? sizey : size_.y);
    size_.x += Vector.x;
    size_.y = Vector.y;
  }
  return size_;
}

void Font::Draw(const char* _text, const Vector2& _pos)
{

  m_currentTextSize = strlen(_text);
  Vector2 pos = _pos;
  stbtt_aligned_quad quad;
  Vector2 Size = GetTextSize(_text);


  

  for (size_t i = 0; i < m_currentTextSize; i++)
  {
    stbtt_GetBakedQuad(static_cast<stbtt_bakedchar*>(m_bufferTextStyle), 2048, 2048, _text[i] - 32, &pos.x, &pos.y, &quad, true);




    float u0 = 0, u1 = 0;
    float v0 = 0, v1 = 0;
    float Height = quad.y1 - quad.y0;
    float Witht = quad.x1 - quad.x0;

    u0 = quad.s0 / static_cast<ltex_t*>(m_texture)->width;
    u1 = quad.s1 / static_cast<ltex_t*>(m_texture)->width;
    v0 = quad.t0 / static_cast<ltex_t*>(m_texture)->height;
    v1 = quad.t1 / static_cast<ltex_t*>(m_texture)->height;

    //ltex_draw(static_cast<ltex_t*>(m_texture), _pos.x, _pos.y);
    ltex_drawrotsized(static_cast<ltex_t*>(m_texture), pos.x, pos.y, 0, 1, 1, quad.x1 - quad.x0, quad.y1 - quad.y0, quad.s0, quad.t0, quad.s1, quad.t1);
    //ltex_drawrotsized(static_cast<ltex_t*>(m_texture), _pos.x, _pos.y, 0, 0, 0, quad.x1 - quad.x0, quad.y1 - quad.y0, quad.s0, quad.t0, quad.s1, quad.t1);
  }


}


