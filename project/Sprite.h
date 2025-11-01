#pragma once
#include <litegfx.h>
#include "Vector2.h"
#include "Collider.h"

enum CollisionType
{
  COLLISION_NULL,
  COLLISION_RECT,
  COLLISION_CIRCLE,
  COLLISION_PIXEL
};
class Sprite
{
public:
  Sprite(const ltex_t*, int, int);
  ~Sprite();
  typedef void (*CallbackFunc)(Sprite&, float);
  void SetCallback(CallbackFunc);


                                 
  const ltex_t*  GetTexture      () const;
  const lblend_t GetBlend        () const;
  const float    GetRed          () const;
  const float    GetGreen        () const;
  const float    GetBlue         () const;
  const float    GetAlpha        () const;
  const Vector2  GetPos          () const;
  const float    GetAngle        () const;
  const Vector2  GetScale        () const;
  const Vector2  GetSize         () const;
  const Vector2  GetPivot        () const;
  const int      GetHFrames      () const;
  const int      GetVFrames      () const;
  const int      GetFps          () const;
  const float    GetCurrentFrame () const;
  CollisionType  GetCollisionType() const;
  const Collider* GetCollider    () const;
  


  void SetTexture      (const ltex_t*, int, int);
  void SetBlend        (lblend_t);
  void SetColor        (float, float, float, float);
  void SetPosition     (const Vector2&);
  void SetAngle        (float);
  void SetScale        (const Vector2&);
  void SetPivot        (const Vector2&);
  void SetHFrames      (int);
  void SetVFrames      (int);
  void SetFps          (int);
  void SetCurrentFrame (float);
  void SetCollisionType(CollisionType);
  void UpdateCollision();
  

  bool Collides(Sprite&);
  void Update(float);
  void Draw() const;



private:
  CallbackFunc m_func;
  const ltex_t* m_TexturaGeneral;
  lblend_t m_blend;

  float m_fr;
  float m_fg;
  float m_fb;
  float m_fa;

  Vector2 m_vPos;
  float m_fAngle;
  Vector2 m_vScale;
  Vector2 m_vPivot;

  int m_iHFrames;
  int m_iVFrames;
  int m_iFps;
  
  float m_fCurrentFrame;

  CollisionType m_type;
  Collider* m_pColider;
};

