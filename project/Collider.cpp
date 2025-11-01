#include "Collider.h"
#include "iostream"
#include <litegfx.h>
#include "math.h"

bool Collider::CheckPixelPixel(const Vector2& _pos1, const Vector2& _size1, const Vector2& _scale1, const unsigned char* _pixel1, unsigned int _textureSize1, const Vector2& _pos2, const Vector2& _size2, const Vector2& _scale2, const unsigned char* _pixel2, unsigned int _textureSize2) const
{
  //DrawCollisionTexture(_pixel1, _size1, _scale1, _pos1, 1);
  //DrawCollisionTexture(_pixel2, _size2, _scale2, _pos2, 1);
  if (CheckRectRect(_pos1, _size1, _pos2, _size2))
  {
    Vector2 EsqSupDer;
    Vector2 EsqInfIzq;
    Vector2 EsqInfDer;
    Vector2 EsqSupIzq;
    Vector2 Max;
    Vector2 Min;

    Max.x = fminf(_pos1.x + (_size1.x / 2), _pos2.x + (_size2.x / 2));
    Max.y = fminf(_pos1.y + (_size1.y / 2), _pos2.y + (_size2.y / 2));
    Min.x = fmaxf(_pos1.x - (_size1.x / 2), _pos2.x - (_size2.x / 2));
    Min.y = fmaxf(_pos1.y - (_size1.y / 2), _pos2.y - (_size2.y / 2));

    //lgfx_setcolor(1, 1, 1, 1);
    //lgfx_drawoval(Max.x - 4, Max.y - 4, 8, 8);
    //lgfx_drawoval(Min.x - 4, Min.y - 4, 8, 8);

    EsqInfDer = Max;
    EsqSupIzq = Min;

    EsqInfIzq.x = Min.x;
    EsqInfIzq.y = Max.y;
    EsqSupDer.x = Max.x;
    EsqSupDer.y = Min.y;

    //lgfx_setcolor(1, 0, 0, 1);
    //lgfx_drawline(EsqInfDer.x, EsqInfDer.y, EsqSupDer.x, EsqSupDer.y);
    //lgfx_drawline(EsqInfDer.x, EsqInfDer.y, EsqInfIzq.x, EsqInfIzq.y);
    //lgfx_drawline(EsqSupIzq.x, EsqSupIzq.y, EsqSupDer.x, EsqSupDer.y);
    //lgfx_drawline(EsqSupIzq.x, EsqSupIzq.y, EsqInfIzq.x, EsqInfIzq.y);


    Vector2 PuntoInicio2;
    Vector2 PuntoInicio1;

    PuntoInicio1.x = _pos1.x - _size1.x / 2;
    PuntoInicio1.y = _pos1.y - _size1.y / 2;
    
    PuntoInicio2.x = _pos2.x - _size2.x / 2;
    PuntoInicio2.y = _pos2.y - _size2.y / 2;

    unsigned int PixelNum1 = (static_cast<unsigned int>(fabsf((EsqSupDer.x - EsqSupIzq.x) / _scale1.x)) * static_cast<unsigned int>(fabsf((EsqSupDer.y - EsqInfDer.y) / _scale1.y))) + 1;
    unsigned int PixelNum2 = (static_cast<unsigned int>(fabsf((EsqSupDer.x - EsqSupIzq.x) / _scale2.x)) * static_cast<unsigned int>(fabsf((EsqSupDer.y - EsqInfDer.y) / _scale2.y))) + 1;

    unsigned int PixelFinal = PixelNum1 > PixelNum2 ? PixelNum1 : PixelNum2;

    

    for (unsigned int i = 0; i < PixelFinal; i++)
    {
      //printf("%c", _pixel1[i]);
      Vector2 pos1 = EsqSupIzq - PuntoInicio1;
      Vector2 pos2 = EsqSupIzq - PuntoInicio2;
      Vector2 fis1 = pos1;
      Vector2 fis2 = pos2;

      fis1.x += i;
      fis2.x += i;
      Vector2 pos = Vector2(0, 0);
      if (fis1.x > (EsqSupDer.x - EsqSupIzq.x) - 1 )
      {

        float filas = (i / (EsqSupDer.x - EsqSupIzq.x)) - 1;
        float valor = fmodf(i, (EsqSupDer.x - EsqSupIzq.x));
        pos.x = static_cast<int>(valor);
        pos.y = static_cast<int>(filas);

        pos1 += pos;
        pos2 += pos;
      }
      else
      {
        pos1.x += fis1.x;
        pos2.x += fis1.x;
      }


      unsigned int pixel1 = (static_cast<unsigned int>(pos1.x) - 1 ) + (static_cast<unsigned int>(pos1.y) * ((_size1.x / _scale1.x) ));
      unsigned int pixel2 = (static_cast<unsigned int>(pos2.x) - 1) + (static_cast<unsigned int>(pos2.y) * ((_size2.x / _scale2.x) ));
      if (roundf(_pixel1[pixel1]) != 0 && _pixel2[pixel2] != 0) 
      {
        //printf("\nposicion en el array personaje 1: %u", pixel1);
        //printf("\nposicion en el array personaje 2: %u", pixel2);
        //lgfx_setcolor(0, 0, 1, 1);
        //lgfx_drawoval(pos.x + EsqSupIzq.x - 4, pos.y + EsqSupIzq.y - 4, 8, 8);
        //lgfx_drawpoint(pos.x + EsqSupIzq.x, pos.y + EsqSupIzq.y);
        return true;
      }
      else
      {
        //lgfx_setcolor(0, 1, 0, 1);
        //lgfx_drawpoint(pos.x + EsqSupIzq.x, pos.y + EsqSupIzq.y);
      }
    }


  }
  return false;
}

void Collider::DrawCollisionTexture(const unsigned char* _Pixeles, Vector2 _size, Vector2 _scale, Vector2 _pos, unsigned int _maxFrame) const
{
  Vector2 trueSize = _size / _scale;
  unsigned int textureSize = trueSize.x * trueSize.y;
  Vector2 InicialPos = _pos - (_size / 2);
  for (unsigned int i = 0; i < textureSize; i++)
  {
    Vector2 DrawPoint = Vector2(0, 0);
    if (i > (trueSize.x * _maxFrame))
    {
      DrawPoint.x = i % static_cast<unsigned int>((trueSize.x * _maxFrame));
      DrawPoint.y = static_cast<unsigned int>(i / static_cast<unsigned int>((trueSize.x * _maxFrame)));
    }
    else
    {
      DrawPoint.x = i;
    }
    Vector2 TempVector = DrawPoint + InicialPos;
    if (_Pixeles[i] != 0)
    {
      lgfx_setcolor(1, 0, 0, 1);
      lgfx_drawpoint(TempVector.x, TempVector.y);
    }
    else
    {
      lgfx_setcolor(0, 0, 1, 1);
      lgfx_drawpoint(TempVector.x, TempVector.y);
    }
  }
}

bool Collider::CheckCircleCircle(const Vector2& _pos1, float _radius1, const Vector2& _pos2, float _radius2) const
{
  //lgfx_setcolor(1, 0, 0, 1);
  //lgfx_drawline(_pos1.x, _pos1.y, _pos2.x, _pos2.y);
  //lgfx_drawoval(_pos1.x - _radius1 / 2, _pos1.y - _radius1 / 2, _radius1, _radius1);
  //lgfx_drawoval(_pos2.x - _radius2 / 2, _pos2.y - _radius2 / 2, _radius2, _radius2);

  if (_pos1.Distance(_pos2) <= _radius1 / 2 + _radius2 / 2)
  {
    return true;
  }
  return false;
}

bool Collider::CheckCircleRect(const Vector2& _pos1, float _radius, const Vector2& _pos2, const Vector2& _size2) const
{
  //lgfx_setcolor(1, 0, 0, 1);
  //
  //lgfx_drawline(_pos1.x, _pos1.y, _pos2.x, _pos2.y);
  //
  //lgfx_setcolor(0, 0, 1, 1);
  //lgfx_drawline(_pos2.x + _size2.x / 2, _pos2.y + _size2.y / 2, _pos2.x + _size2.x / 2, _pos2.y - _size2.y / 2);
  //lgfx_drawline(_pos2.x + _size2.x / 2, _pos2.y + _size2.y / 2, _pos2.x - _size2.x / 2, _pos2.y + _size2.y / 2);
  //lgfx_drawline(_pos2.x - _size2.x / 2, _pos2.y - _size2.y / 2, _pos2.x + _size2.x / 2, _pos2.y - _size2.y / 2);
  //lgfx_drawline(_pos2.x - _size2.x / 2, _pos2.y - _size2.y / 2, _pos2.x - _size2.x / 2, _pos2.y + _size2.y / 2);

  Vector2 PuntoMasCercano = Vector2();
  if (_pos1.x > _pos2.x + (_size2.x / 2))
  {
    PuntoMasCercano.x = _pos2.x + (_size2.x / 2);
  }
  else if(_pos1.x < _pos2.x - (_size2.x / 2))
  {
    PuntoMasCercano.x = _pos2.x - (_size2.x / 2);
  }
  else
  {
    PuntoMasCercano.x = _pos1.x;
  }


  if (_pos1.y > _pos2.y + (_size2.y / 2))
  {
    PuntoMasCercano.y = _pos2.y + (_size2.y / 2);
  }
  else if (_pos1.y < _pos2.y - (_size2.y / 2))
  {
    PuntoMasCercano.y = _pos2.y - (_size2.y / 2);
  }
  else
  {
    PuntoMasCercano.y = _pos1.y;
  }
  //lgfx_setcolor(0, 1, 0, 1);
  //lgfx_drawoval(PuntoMasCercano.x - 2, PuntoMasCercano.y - 2, 4, 4);

  if (PuntoMasCercano.Distance(_pos1) < _radius/2)
  {
    return true;
  }
  
  return false;
}

bool Collider::CheckRectRect(const Vector2& _pos1, const Vector2& _size1, const Vector2& _pos2, const Vector2& _size2) const
{   
  //lgfx_setcolor(0, 0, 1, 1);
  //lgfx_drawline(_pos1.x + _size1.x / 2, _pos1.y + _size1.y / 2, _pos1.x + _size1.x / 2, _pos1.y - _size1.y / 2);
  //lgfx_drawline(_pos1.x + _size1.x / 2, _pos1.y + _size1.y / 2, _pos1.x - _size1.x / 2, _pos1.y + _size1.y / 2);
  //lgfx_drawline(_pos1.x - _size1.x / 2, _pos1.y - _size1.y / 2, _pos1.x + _size1.x / 2, _pos1.y - _size1.y / 2);
  //lgfx_drawline(_pos1.x - _size1.x / 2, _pos1.y - _size1.y / 2, _pos1.x - _size1.x / 2, _pos1.y + _size1.y / 2);
  //
  //lgfx_drawline(_pos2.x + _size2.x / 2, _pos2.y + _size2.y / 2, _pos2.x + _size2.x / 2, _pos2.y - _size2.y / 2);
  //lgfx_drawline(_pos2.x + _size2.x / 2, _pos2.y + _size2.y / 2, _pos2.x - _size2.x / 2, _pos2.y + _size2.y / 2);
  //lgfx_drawline(_pos2.x - _size2.x / 2, _pos2.y - _size2.y / 2, _pos2.x + _size2.x / 2, _pos2.y - _size2.y / 2);
  //lgfx_drawline(_pos2.x - _size2.x / 2, _pos2.y - _size2.y / 2, _pos2.x - _size2.x / 2, _pos2.y + _size2.y / 2);

  if (fabsf((_pos2 - _pos1).x) < _size1.x / 2 + _size2.x / 2 && fabsf((_pos2 - _pos1).y) < _size1.y / 2 + _size2.y / 2)
  {
    return true;
  }
  return false;
}

bool Collider::CheckCirclePixel(const Vector2& _pos1, float _radius1, const Vector2& _pos2, const Vector2& _size2, const Vector2& _scale2, const unsigned char* _pixel2, unsigned int _textureSize) const
{
  if (CheckCircleRect(_pos1, _radius1, _pos2, _size2))
  {



    Vector2 PuntoInicio2;

    PuntoInicio2.x = _pos2.x - _size2.x / 2;
    PuntoInicio2.y = _pos2.y - _size2.y / 2;


    unsigned int PixelNum2 = static_cast<unsigned int>(_size2.x / _scale2.x) * static_cast<unsigned int>(_size2.y / _scale2.y);

    for (unsigned int i = 0; i < PixelNum2; i++)
    {
      //printf("%c", _pixel1[i]);

      Vector2 pos2 = (_pos2 - (_size2 / 2)) - PuntoInicio2;
      Vector2 fis2 = pos2;

      fis2.x += i;

      Vector2 pos = Vector2(0, 0);
      if (fis2.x > (_size2.x / _scale2.x) - 1)
      {

        float filas = (i / ((_size2.x / _scale2.x)));
        float valor = fmodf(i, (_size2.x / _scale2.x) - 1);
        pos.x = static_cast<int>(valor);
        pos.y = static_cast<int>(filas);

        pos2 += pos;
      }
      else
      {
        pos2.x += fis2.x;
      }
      unsigned int pixel2 = static_cast<unsigned int>(pos2.x) + static_cast<unsigned int>(pos2.y) * (_size2.x / _scale2.x) + 1;
      if (_pixel2[pixel2] != 0)
      {
        if (_pos1.Distance((pos2 + (_pos2 - (_size2 / 2)))) < _radius1 / 2)
        {
          return true;
        }
      }
    }
  }
  return false;
  return false;
}

bool Collider::CheckRectPixel(const Vector2& _pos1, const Vector2& _size1, const Vector2& _pos2, const Vector2& _size2, const Vector2& _scale2, const unsigned char* _pixel2, unsigned int _textureSize) const
{
  if (CheckRectRect(_pos1, _size1, _pos2, _size2))
  {
    Vector2 EsqSupDer;
    Vector2 EsqInfIzq;
    Vector2 EsqInfDer;
    Vector2 EsqSupIzq;
    Vector2 Max;
    Vector2 Min;

    Max.x = fminf(_pos1.x + (_size1.x / 2), _pos2.x + (_size2.x / 2));
    Max.y = fminf(_pos1.y + (_size1.y / 2), _pos2.y + (_size2.y / 2));
    Min.x = fmaxf(_pos1.x - (_size1.x / 2), _pos2.x - (_size2.x / 2));
    Min.y = fmaxf(_pos1.y - (_size1.y / 2), _pos2.y - (_size2.y / 2));

    //lgfx_setcolor(1, 1, 1, 1);
    //lgfx_drawoval(Max.x - 4, Max.y - 4, 8, 8);
    //lgfx_drawoval(Min.x - 4, Min.y - 4, 8, 8);

    EsqInfDer = Max;
    EsqSupIzq = Min;

    EsqInfIzq.x = Min.x;
    EsqInfIzq.y = Max.y;
    EsqSupDer.x = Max.x;
    EsqSupDer.y = Min.y;

    //lgfx_setcolor(1, 0, 0, 1);
    //lgfx_drawline(EsqInfDer.x, EsqInfDer.y, EsqSupDer.x, EsqSupDer.y);
    //lgfx_drawline(EsqInfDer.x, EsqInfDer.y, EsqInfIzq.x, EsqInfIzq.y);
    //lgfx_drawline(EsqSupIzq.x, EsqSupIzq.y, EsqSupDer.x, EsqSupDer.y);
    //lgfx_drawline(EsqSupIzq.x, EsqSupIzq.y, EsqInfIzq.x, EsqInfIzq.y);


    Vector2 PuntoInicio2;

    PuntoInicio2.x = _pos2.x - _size2.x / 2;
    PuntoInicio2.y = _pos2.y - _size2.y / 2;

    
    unsigned int PixelNum2 = (static_cast<unsigned int>(fabsf((EsqSupDer.x - EsqSupIzq.x) / _scale2.x)) * static_cast<unsigned int>(fabsf((EsqSupDer.y - EsqInfDer.y) / _scale2.y))) + 1;

    for (unsigned int i = 0; i < PixelNum2; i++)
    {

      Vector2 pos2 = EsqSupIzq - PuntoInicio2;
      Vector2 fis2 = pos2;

      fis2.x += i;

      Vector2 pos = Vector2(0, 0);
      if (fis2.x > (EsqSupDer.x - EsqSupIzq.x) - 1)
      {

        float filas = (i / (EsqSupDer.x - EsqSupIzq.x) - 1);
        float valor = fmodf(i, (EsqSupDer.x - EsqSupIzq.x));
        pos.x = static_cast<int>(valor);
        pos.y = static_cast<int>(filas);

        pos2 += pos;
      }
      else
      {
        pos2.x += fis2.x;
      }

      unsigned int pixel2 = static_cast<unsigned int>(pos2.x) + static_cast<unsigned int>(pos2.y) * (_size2.x / _scale2.x);
      if (_pixel2[pixel2] != 0)
      {
        //lgfx_drawoval((pos.x - 2) + EsqSupIzq.x, (pos.y - 2) + EsqSupIzq.y, 4, 4);
        return true;
      }
    }
  }
  return false;
}
