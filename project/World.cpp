#include "World.h"
#include "Sprite.h"
#include "stb_image.h"
#include "pugixml.hpp"

World::World()
  : m_fClearRed(0),
  m_fClearGreen(0),
  m_fClearBlue(0),
  m_vCameraPos(Vector2::Zero()),
  m_vInput(Vector2(0,0))
{
}

World::World(float _fClearRed, float _fClearGreen, float _fClearBlue, ltex_t* _pBack0, ltex_t* _pBack1, ltex_t* _pBack2, ltex_t* _pBack3)
  : m_fClearRed(_fClearRed),
  m_fClearGreen(_fClearGreen),
  m_fClearBlue(_fClearBlue),
  m_vCameraPos(Vector2::Zero()),
  m_vInput(Vector2(0, 0))
{
  WorldLayer oLeyer0 = WorldLayer(_pBack0, Vector2(0, 0), 0);
  WorldLayer oLeyer1 = WorldLayer(_pBack1, Vector2(0, 0), 0);
  WorldLayer oLeyer2 = WorldLayer(_pBack2, Vector2(0, 0), 0);
  WorldLayer oLeyer3 = WorldLayer(_pBack3, Vector2(0, 0), 0);

  m_layers.push_back(oLeyer0);
  m_layers.push_back(oLeyer1);
  m_layers.push_back(oLeyer2);
  m_layers.push_back(oLeyer3);
}

bool World::LoadMap(const char* filename, uint16_t firstColId)
{
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(filename);
  
  if (!result) {
    return false;
  }
  WorldLayer oLayer;
  
  pugi::xml_node map = doc.child("map");
  
  int width = map.attribute("width").as_int();
  int height = map.attribute("height").as_int();
  int tileWidth = map.attribute("tilewidth").as_int();
  int tileHeight = map.attribute("tileheight").as_int();
  
  
  
  pugi::xml_node tileset = map.child("tileset");
  std::string tilesetName = tileset.attribute("name").as_string();
  int tilecount = tileset.attribute("tilecount").as_int();
  int columns = tileset.attribute("columns").as_int();
  
  int rows = tilecount / columns;
  Vector2 vSpriteSheetSize = Vector2(columns, rows);
  

  
  std::string imageSource = tileset.child("image").attribute("source").as_string();
  int imageWidth = tileset.child("image").attribute("width").as_int();
  int imageHeight = tileset.child("image").attribute("height").as_int();

  std::string path = "./data/";
  std::string sCompleatPath = path + imageSource;
  ltex_t* pTexture = loadTexture(sCompleatPath.c_str());

  Vector2 vTextureSize = Vector2(tileWidth, tileHeight);
  
  pugi::xml_node layer = map.child("layer");
  
  
  int Widht = layer.attribute("width").as_int();
  int Height = layer.attribute("height").as_int();
  
  Vector2 vSize = Vector2(Widht * tileWidth, Height * tileHeight);
  
  
  int count = 0;
  pugi::xml_node data = layer.child("data");
  for (pugi::xml_node tile : data.children("tile")) {
    int gid = tile.attribute("gid").as_int();
    int row = count / width;
    int colum = count % width;
    if (oLayer.m_Grid.size() <= row)
    {
      std::vector<int> vector;
      oLayer.m_Grid.push_back(vector);
    }

    if (gid != 0)
    {
      RectCollider collision(Vector2(colum * tileWidth, row * tileHeight), Vector2(tileWidth, tileHeight));
      oLayer.m_LayerCollision.push_back(collision);
    }
    oLayer.m_Grid[row].push_back(gid);
    count++;
  }
  oLayer.m_cSpriteSheetSize = vSpriteSheetSize;
  oLayer.m_pTexture = pTexture;
  oLayer.m_vSize = vSize;
  oLayer.m_vSpritesSize = vTextureSize;
  
  
  m_layers.push_back(oLayer);
  
  return true;
}

float World::GetClearRed()
{
  return m_fClearRed;
}

float World::GetClearGreen()
{
  return m_fClearGreen;
}

float World::GetClearBlue()
{
  return m_fClearBlue;
}

Vector2 World::GetMapSize()
{
  return m_layers[0].m_vSize;
}

void World::SetLayer(ltex_t* _layer)
{
  WorldLayer oLeyer3 = WorldLayer(_layer, Vector2(0, 0), 0);

  m_layers.push_back(oLeyer3);
}

const ltex_t* World::GetBackGround(size_t _layer) const
{
  auto it = m_layers[_layer];

  ltex_t* value_ = it.m_pTexture;

  return value_;
}

float World::GetScrollRatio(size_t _layer) const
{
  auto it = m_layers[_layer];

  float value_ = it.m_fScrollRatio;

  return value_;
}

void World::SetScroolRatio(size_t _layer, float _fRatio)
{

  m_layers[_layer].m_fScrollRatio = _fRatio;
}

const Vector2& World::GetScrollSpeed(size_t _layer) const
{
  auto it = m_layers[_layer];

  Vector2 value_ = it.m_vVelocity;

  return value_;
}

void World::SetScrollSpeed(size_t _layer, Vector2& _vSpeed)
{
  m_layers[_layer].m_vVelocity = _vSpeed;
}

const std::vector<RectCollider>& World::GetLayerCollision(size_t _layer)
{
  return m_layers[_layer].m_LayerCollision;
}

const Vector2& World::GetCameraPosition() const
{
  return m_vCameraPos;
}

void World::SetCameraPosition(const Vector2& _vPos)
{
  m_vCameraPos = _vPos;
  lgfx_setorigin(_vPos.x, _vPos.y);
}

void World::AddSprite(Sprite& _pSprite)
{
  Sprite* pSeach;

  if (std::find(m_pSprites.begin(), m_pSprites.end(), pSeach) == m_pSprites.end())
  {
    m_pSprites.push_back(&_pSprite);
  }
}

void World::RemoveSprite(Sprite& _pSprite)
{
  Sprite* pSeach;

  if (std::find(m_pSprites.begin(), m_pSprites.end(), pSeach) != m_pSprites.end())
  {
    m_pSprites.erase(std::find(m_pSprites.begin(), m_pSprites.end(), pSeach));
  }
}

void World::SetInput(const Vector2& _input)
{
  m_vInput = _input;
}

const Vector2& World::GetInput() const
{
  return m_vInput;
}

void World::Update(float _fDeltaTime)
{
  for (auto it = m_layers.begin(); it != m_layers.end(); it++)
  {
    (*it).m_vPosition += (*it).m_vVelocity * _fDeltaTime;
  }

  for (auto it = m_pSprites.begin(); it != m_pSprites.end(); it++)
  {
    (*it)->Update(_fDeltaTime);
  }
}

void World::Draw(const Vector2& _vScreenSize)
{



  lgfx_setcolor(1, 1, 1, 1);

  lgfx_setblend(BLEND_ALPHA);
  
  float fHorizontalLogitud = _vScreenSize.x + GetCameraPosition().x;
  float fVerticalLogitud = _vScreenSize.y + GetCameraPosition().y;
  
  WorldLayer oLayer3 = m_layers[1];
  Vector2 vLayer3Pos = GetCameraPosition() * (-(oLayer3.m_fScrollRatio - 1));
  vLayer3Pos += oLayer3.m_vPosition;
  DrawBackground(oLayer3, fHorizontalLogitud, fVerticalLogitud, vLayer3Pos, _vScreenSize);

  //WorldLayer oLayer2 = (m_layers[2]);
  //Vector2 vLayer2Pos = GetCameraPosition() * (-(oLayer2.m_fScrollRatio - 1));
  //DrawLine(oLayer2, fHorizontalLogitud, vLayer2Pos);

  //WorldLayer oLayer1 = (m_layers[1]);
  //Vector2 vLayer1Pos = GetCameraPosition() * (-(oLayer1.m_fScrollRatio - 1));
  //DrawLine(oLayer1, fHorizontalLogitud, vLayer1Pos);



  //ltex_draw(oLayer0.m_pTexture, vLayer0Pos.x, 0);


  DrawLayer(m_layers[0]);

  for (auto it = m_pSprites.begin(); it != m_pSprites.end(); it++)
  {
    Vector2 pos = (*it)->GetPos();
    pos.y -= _vScreenSize.y / 2;
    pos.x -= _vScreenSize.x / 2;


    Vector2 NewPos = GetCameraPosition();
    if (m_layers.size() > 0)
    {
      WorldLayer oLayer0 = (m_layers[0]);
      Vector2 vLayer0Pos = GetCameraPosition() * (-(oLayer0.m_fScrollRatio - 1));


      if (pos.x > 0 && vLayer0Pos.x + oLayer0.m_vSize.x > pos.x + _vScreenSize.x && pos.y > 0 && vLayer0Pos.y + oLayer0.m_vSize.y > pos.y + _vScreenSize.y)
      {
        NewPos.x = pos.x;
        NewPos.y = pos.y;

        SetCameraPosition(NewPos);
      }
      else if (pos.x > 0 && vLayer0Pos.x + oLayer0.m_vSize.x > pos.x + _vScreenSize.x)
      {
        NewPos.x = pos.x;
        SetCameraPosition(NewPos);
      }
      else if(pos.y > 0 && vLayer0Pos.y + oLayer0.m_vSize.y > pos.y + _vScreenSize.y)
      {
        NewPos.y = pos.y;
        SetCameraPosition(NewPos);
      }

    }

  }

  MoveSprite(*(m_pSprites[1]), m_vInput);

  //for (auto it = m_pSprites.begin(); it != m_pSprites.end(); it++)
  //{
  //  (*it)->Draw();
  //}

}

bool World::MoveSprite(Sprite& _pSprite, const Vector2& _vPos)
{
  if (_vPos.x == 0 && _vPos.y == 0)
  {
    m_pSprites[0]->Draw();
    return false;
  }
  Vector2 vSpriteOriginal = _pSprite.GetPos();
  Vector2 vNextPositionY = vSpriteOriginal;
  vNextPositionY.y += _vPos.y;

  Vector2 vNextPositionX = vSpriteOriginal;
  vNextPositionX.x += _vPos.x;

  _pSprite.SetPosition(vNextPositionX);
  bool bCollisionX = false;
  bool bCollisionY = false;
  for (auto it = m_layers[0].m_LayerCollision.begin(); it != m_layers[0].m_LayerCollision.end(); it++)
  {
    _pSprite.UpdateCollision();
    bool bHasCollide = _pSprite.GetCollider()->Collides(*it);
    if (bHasCollide)
    {
      const RectCollider* collider = static_cast<const RectCollider*>(_pSprite.GetCollider());
      const RectCollider* otherCollider = static_cast<const RectCollider*>(it._Ptr);
      collider->GetPos();

      //lgfx_setcolor(0, 1, 0, 1);
      //lgfx_drawrect(collider->GetPos().x, collider->GetPos().y, collider->GetSize().x, collider->GetSize().y);
      //
      //lgfx_setcolor(1, 0, 0, 1);
      //lgfx_drawrect(otherCollider->GetPos().x, otherCollider->GetPos().y, otherCollider->GetSize().x, otherCollider->GetSize().y);

      bCollisionX = true;
    }
  }
  _pSprite.SetPosition(vNextPositionY);
  for (auto it = m_layers[0].m_LayerCollision.begin(); it != m_layers[0].m_LayerCollision.end(); it++)
  {
    _pSprite.UpdateCollision();
    bool bHasCollide = _pSprite.GetCollider()->Collides(*it);
    if (bHasCollide)
    {
      const RectCollider* collider = static_cast<const RectCollider*>(_pSprite.GetCollider());
      const RectCollider* otherCollider = static_cast<const RectCollider*>(it._Ptr);
      collider->GetPos();

      //lgfx_setcolor(0, 1, 0, 1);
      //lgfx_drawrect(collider->GetPos().x, collider->GetPos().y, collider->GetSize().x, collider->GetSize().y);
      //
      //lgfx_setcolor(1, 0, 0, 1);
      //lgfx_drawrect(otherCollider->GetPos().x, otherCollider->GetPos().y, otherCollider->GetSize().x, otherCollider->GetSize().y);

      bCollisionY = true;
    }
  }

  _pSprite.SetPosition(vSpriteOriginal);

  if (bCollisionX && bCollisionY)
  {
    _pSprite.SetPosition(vSpriteOriginal);
    m_pSprites[0]->SetPosition(vSpriteOriginal);
    m_pSprites[0]->Draw();
    return true;
  }
  else if(bCollisionX)
  {
    _pSprite.SetPosition(vNextPositionY);
    m_pSprites[0]->SetPosition(vNextPositionY);
    m_pSprites[0]->Draw();
    return true;
  }
  else if (bCollisionY)
  {

    _pSprite.SetPosition(vNextPositionX);
    m_pSprites[0]->SetPosition(vNextPositionX);
  }
  else
  {
    _pSprite.SetPosition(vSpriteOriginal + _vPos);
    m_pSprites[0]->SetPosition(vSpriteOriginal + _vPos);
  }

  _pSprite.Draw();
  return false;
}

void World::DrawBackground(WorldLayer _pLayer, int _iWidth, int _iHeight, const Vector2& _vOriginPos, const Vector2& _vScreenSize)
{
  bool isCompleat = false;
  int horizontal = _vOriginPos.x;
  int vertical = _vOriginPos.y;
  Vector2 textureSize = Vector2(_pLayer.m_pTexture->width, _pLayer.m_pTexture->height);
  Vector2 vScreenPos = _vScreenSize + GetCameraPosition();
  
  if(_pLayer.m_pTexture)
  while (isCompleat == false)
  {
    if (horizontal < vScreenPos.x && horizontal + textureSize.x > GetCameraPosition().x && vertical < vScreenPos.y && vertical + textureSize.y > GetCameraPosition().y)
    {
      ltex_draw(_pLayer.m_pTexture, static_cast<float>(horizontal), static_cast<float>(vertical));
    }
    horizontal += _pLayer.m_pTexture->width;
    if ((horizontal - _pLayer.m_pTexture->width / 2) > _iWidth)
    {
      horizontal = _vOriginPos.x;
      vertical += _pLayer.m_pTexture->height;

    }
    if ((vertical - _pLayer.m_pTexture->height / 2) > _iHeight)
    {
      isCompleat = true;
    }
  }
}

void World::DrawLine(WorldLayer _pLayer, int _iWidth, const Vector2& _vOriginPos)
{
  bool isCompleat = false;
  int horizontal = _vOriginPos.x;
  int vertical = _vOriginPos.y;
  while (isCompleat == false)
  {
    ltex_draw(_pLayer.m_pTexture, static_cast<float>(horizontal), static_cast<float>(vertical));
    horizontal += _pLayer.m_pTexture->width;
    if ((horizontal - _pLayer.m_pTexture->width / 2) > _iWidth)
    {
      horizontal = 0;
      isCompleat = true;
    }
  }
}

void World::DrawLayer(const WorldLayer& _layer)
{
  for (size_t i = 0; i < _layer.m_Grid.size(); i++)
  {
    std::vector<int> row = _layer.m_Grid[i];
    for (size_t j = 0; j < row.size(); j++)
    {
      int id = row[j];
      if (id != 0)
      {
        Vector2 vUV0;
        Vector2 vUV1;

        Vector2 vSpritePosition = _layer.m_vPosition;
        vSpritePosition.y += i * _layer.m_vSpritesSize.y;
        vSpritePosition.x += j * _layer.m_vSpritesSize.x;
        GetTextureUV(id, _layer, vUV0, vUV1);
        ltex_drawrotsized(_layer.m_pTexture, vSpritePosition.x, vSpritePosition.y, 0, 0, 0, _layer.m_vSpritesSize.x, _layer.m_vSpritesSize.y, vUV0.x, vUV0.y, vUV1.x, vUV1.y);
      }
    }
  }
}

void World::GetTextureUV(int id, const WorldLayer& _layer, Vector2& UV0_, Vector2& UV1_)
{
  Vector2 vTextureSize = Vector2(_layer.m_pTexture->width, _layer.m_pTexture->height);
  int row = id / _layer.m_cSpriteSheetSize.x;
  int colum = id % static_cast<int>(_layer.m_cSpriteSheetSize.x);

  UV0_.x = _layer.m_vSpritesSize.x * colum;
  UV0_.y = _layer.m_vSpritesSize.y * row;

  UV1_.x = _layer.m_vSpritesSize.x * (colum + 1);
  UV1_.y = _layer.m_vSpritesSize.y * (row + 1);

  UV0_.x = UV0_.x / static_cast<float>(_layer.m_pTexture->width);
  UV1_.x = UV1_.x / static_cast<float>(_layer.m_pTexture->width);

  UV0_.y = UV0_.y / static_cast<float>(_layer.m_pTexture->height);
  UV1_.y = UV1_.y / static_cast<float>(_layer.m_pTexture->height);
}

ltex_t* World::loadTexture(const char* _filename)
{
  int height;
  int width;
  unsigned char* image = stbi_load(_filename, &width, &height, nullptr, 4);
  ltex_t* BufferVRam = ltex_alloc(width, height, 1);
  ltex_setpixels(BufferVRam, image);
  stbi_image_free(image);
  return BufferVRam;
}


WorldLayer::WorldLayer()
  : m_pTexture(nullptr),
  m_fScrollRatio(1),
  m_vPosition(Vector2(0,0)),
  m_vVelocity(Vector2(0,0)),
  m_vSize(Vector2(0,0))
{
}

WorldLayer::WorldLayer(ltex_t* _pTexture, Vector2 _vVelocity, float _fScrollRatio)
  :m_pTexture(_pTexture),
  m_vVelocity(_vVelocity),
  m_fScrollRatio(_fScrollRatio)
{
  
}
