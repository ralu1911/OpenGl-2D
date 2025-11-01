#include "Sprite.h"
#include "iostream"
#include "RectCollider.h"
#include "CircleColider.h"
#include "PixelCollider.h"


Sprite::Sprite(const ltex_t* _texture, int _hframe, int _vframe)
  :m_TexturaGeneral(_texture), m_iHFrames(_hframe), m_iVFrames(_vframe),
  m_blend(BLEND_ALPHA), m_fr(1), m_fb(1), m_fg(1), m_fa(1), m_fAngle(0),
  m_fCurrentFrame(0), m_iFps(0), m_vPivot(Vector2(0, 0)), m_vPos(Vector2(0, 0)),
  m_vScale(Vector2(1, 1)), m_func(nullptr), m_pColider(nullptr), m_type(CollisionType::COLLISION_NULL)
{
  
}

Sprite::~Sprite()
{

}


void Sprite::SetCallback(CallbackFunc _func)
{
  m_func = _func;
}

const ltex_t* Sprite::GetTexture() const
{
  return m_TexturaGeneral;
}
const lblend_t Sprite::GetBlend() const
{
  return m_blend;
}
const float Sprite::GetRed() const
{
  return m_fr;
}
const float Sprite::GetGreen() const
{
  return m_fg;
}
const float Sprite::GetBlue() const
{
  return m_fb;
}
const float Sprite::GetAlpha() const
{
  return m_fa;
}
const Vector2 Sprite::GetPos() const
{
  return m_vPos;
}
const float Sprite::GetAngle() const
{
  return m_fAngle;
}
const Vector2 Sprite::GetScale() const
{
  return m_vScale;
}
const Vector2 Sprite::GetSize() const
{
  Vector2 Size = Vector2(m_TexturaGeneral->width, m_TexturaGeneral->height);
  Size = Size * m_vScale;
  return Size;
}
const Vector2 Sprite::GetPivot() const
{
  return m_vPivot;
}
const int Sprite::GetHFrames() const
{
  return m_iHFrames;
}
const int Sprite::GetVFrames() const
{
  return m_iVFrames;
}
const int Sprite::GetFps() const
{
  return m_iFps;
}
const float Sprite::GetCurrentFrame() const
{
  return m_fCurrentFrame;
}

CollisionType Sprite::GetCollisionType() const
{
  return m_type;
}

const Collider* Sprite::GetCollider() const
{
  return m_pColider;
}

void Sprite::SetTexture(const ltex_t* _textura, int _hFrames, int _vFrames)
{
  m_TexturaGeneral = _textura;
  m_iHFrames = _hFrames;
  m_iVFrames = _vFrames;

}
void Sprite::SetBlend(lblend_t _blend)
{
  m_blend = _blend;
}
void Sprite::SetColor(float _r, float _g, float _b, float _a)
{
  m_fr = _r;
  m_fg = _g;
  m_fb = _b;
  m_fa = _a;
}
void Sprite::SetPosition(const Vector2& _position)
{
  m_vPos = _position;
}
void Sprite::SetAngle(float _angle)
{
  m_fAngle = _angle;
}
void Sprite::SetScale(const Vector2& _scale)
{
  m_vScale = _scale;
}
void Sprite::SetPivot(const Vector2& _pivot)
{
  m_vPivot = _pivot;
}
void Sprite::SetHFrames(int _hframes)
{
  m_iHFrames = _hframes;
}
void Sprite::SetVFrames(int _vframes)
{
  m_iVFrames = _vframes;
}
void Sprite::SetFps(int _fps)
{
  m_iFps = _fps;
}
void Sprite::SetCurrentFrame(float _currentFrame)
{
  m_fCurrentFrame = _currentFrame;
  if (m_fCurrentFrame > GetHFrames() * GetVFrames())
  {
    m_fCurrentFrame = 0;
  }
 
}

void Sprite::SetCollisionType(CollisionType _type)
{
  m_type = _type;
  switch (m_type)
  {
  case COLLISION_NULL:
  {
    if (m_pColider != nullptr)
    {
      delete m_pColider;
      m_pColider = nullptr;
    }

    break;
  }
  case COLLISION_RECT:
  {
    if (m_pColider != nullptr)
    {
      delete m_pColider;
      m_pColider = nullptr;
    }

    RectCollider* collider = new RectCollider(GetPos(), GetSize());

    m_pColider = static_cast<Collider*>(collider);
    break;
  }
  case COLLISION_CIRCLE:
  {
    if (m_pColider != nullptr)
    {
      delete m_pColider;
      m_pColider = nullptr;
    }
    float radius = GetSize().x > GetSize().y ? GetSize().x : GetSize().y;
    CircleColider* collider = new CircleColider(m_vPos, radius);
    m_pColider = static_cast<Collider*>(collider);
    break;
  }
  case COLLISION_PIXEL:
  {
    if (m_pColider != nullptr)
    {
      delete m_pColider;
      m_pColider = nullptr;
    }

    unsigned int size = m_TexturaGeneral->width * m_TexturaGeneral->height * 4;

    unsigned char* buffer = new unsigned char[size];
    unsigned char* mask = new unsigned char[size / 4];
    ltex_getpixels(m_TexturaGeneral, buffer);
    
    for (unsigned int i = 0; i < size/4; i++)
    {
      mask[i] = buffer[(4 * i) + 3];
      //printf("|%c", mask[i]);
    }
    unsigned int fixedSize = size / 4;
    //printf("\nInicia Mask \n");
    for (unsigned int i = 0; i < fixedSize; i++)
    {
     // printf("|%c", mask[i]);
    }
    delete[] buffer;
    PixelCollider* collider = new PixelCollider(GetPos(), GetSize(), mask, GetHFrames() * GetVFrames(), m_TexturaGeneral->height * m_TexturaGeneral->width);
    m_pColider = static_cast<Collider*>(collider);
    break;
  }
  default:
  {

    break;
  }
  }
}

void Sprite::UpdateCollision()
{
  switch (m_type)
  {
  case CollisionType::COLLISION_CIRCLE:
  {
    static_cast<CircleColider*>(m_pColider)->SetPos(GetPos());
    printf("radio en sprite %f: ", GetSize().x > GetSize().y ? GetSize().x : GetSize().y);
    printf("escala en sprite %f: ", GetScale().x);
    static_cast<CircleColider*>(m_pColider)->SetRadius(GetSize().x > GetSize().y ? GetSize().x : GetSize().y);
    break;
  }
  case CollisionType::COLLISION_RECT:
  {
    static_cast<RectCollider*>(m_pColider)->SetPos(GetPos());
    Vector2 vTrueSize;
    vTrueSize.x = GetSize().x / GetHFrames();
    vTrueSize.y = GetSize().y / GetVFrames();
    static_cast<RectCollider*>(m_pColider)->SetSize(vTrueSize);
    break;
  }
  case CollisionType::COLLISION_PIXEL:
  {
    static_cast<PixelCollider*>(m_pColider)->SetPos(GetPos());
    static_cast<PixelCollider*>(m_pColider)->SetScale(GetScale());
    static_cast<PixelCollider*>(m_pColider)->SetSize(GetSize());
    static_cast<PixelCollider*>(m_pColider)->SetCurrentFrame(static_cast<unsigned int>(GetCurrentFrame() + 1));
  } 
  default:
    break;
  }
}

bool Sprite::Collides(Sprite& _other)
{ 
  UpdateCollision();
  _other.UpdateCollision();

  return m_pColider->Collides(*_other.GetCollider());
}

void Sprite::Update(float _deltatime)
{
  SetCurrentFrame((static_cast<float>(GetFps()) * _deltatime) + GetCurrentFrame());

  UpdateCollision();


  if(m_func != nullptr)
  {
    (m_func)(*this, _deltatime);
  }
}

void Sprite::Draw() const
{
  Vector2 spriteSize = Vector2(m_TexturaGeneral->width / GetHFrames(), m_TexturaGeneral->height / GetVFrames());

  Vector2 sprite = Vector2(static_cast<int>(GetCurrentFrame()) % (GetHFrames()) + 1, static_cast<int>(GetCurrentFrame()) / (GetHFrames()) + 1);
  
  Vector2 UV0 = Vector2(((sprite.x - 1) * (spriteSize.x)) / m_TexturaGeneral->width, ((sprite.y - 1) * (spriteSize.y))/ m_TexturaGeneral->height);
  Vector2 UV1 = Vector2((sprite.x * spriteSize.x) / m_TexturaGeneral->width, (sprite.y * spriteSize.y) / m_TexturaGeneral->height);

  spriteSize = spriteSize * GetScale();

  lgfx_setcolor(m_fr, m_fg, m_fb, m_fa);
  lgfx_setblend(GetBlend());
  ltex_drawrotsized(m_TexturaGeneral, GetPos().x, GetPos().y, GetAngle(),
    GetPivot().x, GetPivot().y, spriteSize.x, spriteSize.y, UV0.x, UV0.y, UV1.x, UV1.y);
}




