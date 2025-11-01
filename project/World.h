#pragma once
#include "Vector2.h"
#include "map"
#include "vector"
#include "RectCollider.h"
#include <litegfx.h>



class Sprite;


struct WorldLayer
{
  WorldLayer();
  WorldLayer(ltex_t* _pTexture, Vector2 _vVelocity, float _fScrollRatio);
  
  ltex_t* m_pTexture;
  Vector2 m_vSpritesSize;
  Vector2 m_cSpriteSheetSize;

  std::vector<RectCollider> m_LayerCollision;
  std::vector<std::vector<int>> m_Grid;
  Vector2 m_vVelocity;
  Vector2 m_vPosition;
  Vector2 m_vSize;
  float m_fScrollRatio;
};

class World
{
public:

  World();
  World(float _fClearRed, float _fClearGreen, float _fClearBlue, ltex_t* _pBack0 = nullptr, ltex_t* _pBack1 = nullptr, ltex_t* _pBack2 = nullptr, ltex_t* _pBack3 = nullptr);


  bool LoadMap(const char* filename, uint16_t firstColId);
    
  float GetClearRed();
  float GetClearGreen();
  float GetClearBlue();

  Vector2 GetMapSize();

  void SetLayer(ltex_t* _layer);

  const ltex_t* GetBackGround(size_t _layer) const;

  float GetScrollRatio(size_t _layer) const;
  void SetScroolRatio(size_t _layer, float _fRatio);

  const Vector2& GetScrollSpeed(size_t _layer) const;
  void SetScrollSpeed(size_t _layer, Vector2& _vSpeed);

  const std::vector<RectCollider>& GetLayerCollision(size_t _layer);

  const Vector2& GetCameraPosition() const;
  void SetCameraPosition(const Vector2& _vPos);

  void AddSprite(Sprite& _pSprite);
  void RemoveSprite(Sprite& _pSprite);

  void SetInput(const Vector2& _input);
  const Vector2& GetInput() const;

  void Update(float _fDeltaTime);
  void Draw(const Vector2& _vScreenSize);

  bool MoveSprite(Sprite& _pSprite, const Vector2& _vPos);

  void DrawBackground(WorldLayer _pTexture, int _iWidth, int _iHeight, const Vector2& _vOriginPos, const Vector2& _vScreenSize);
  void DrawLine(WorldLayer _pTexture, int _iWidth, const Vector2& _vOriginPos);

  void DrawLayer(const WorldLayer& _layer);

  void GetTextureUV(int id, const WorldLayer& _layer, Vector2& UV0_, Vector2& UV1_);

  ltex_t* loadTexture(const char* _filename);

private:

  std::vector<Sprite*> m_pSprites;
  std::vector<WorldLayer> m_layers;


  float m_fClearRed;
  float m_fClearGreen;
  float m_fClearBlue;

  Vector2 m_vInput;
  Vector2 m_vCameraPos;


};




