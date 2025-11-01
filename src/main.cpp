#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION
#define STB_TRUETYPE_IMPLEMENTATION



#include <sstream>
#include <iostream>
#include "cmath"
#include "stb_image.h"
#include <stb_truetype.h>
#include <fstream>
#include "vector"

#include "../lib/glfw3.h"

#include "../project/Vector2.h"
#include "../project/Sprite.h"
#include "../project/Font.h"
#include "../project/World.h"




#define LITE_GFX_IMPLEMENTATION

#include <litegfx.h>



using namespace std;
double mouseX;
double mouseY;
int Height;
int Widht;
int state = 0;
World world;



void MouseCallBack(GLFWwindow* _window, double _x, double _y)
{

  mouseX = _x;
  mouseY = _y;
}
void MouseButtonCallBack(GLFWwindow* _window, int _key, int _scancode, int _Action)
{
  if (_key == GLFW_MOUSE_BUTTON_LEFT)
  {
    state = 1;
  }
  else if (_key == GLFW_MOUSE_BUTTON_RIGHT)
  {
    state = 2;
  }
  else if (_key == GLFW_MOUSE_BUTTON_MIDDLE)
  {
    state = 3;
  }
}

void InputCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
{
  if (_key == GLFW_KEY_ESCAPE)
  {
    glfwTerminate();
  }
  else if (_key == GLFW_KEY_B)
  {
    state = 3;
  }
  else if (_key == GLFW_KEY_RIGHT && (_action == GLFW_REPEAT || _action == GLFW_PRESS))
  {
    Vector2 baseInput = world.GetInput();
    baseInput.x = 1;
    world.SetInput(baseInput);
  }
  else if(_key == GLFW_KEY_RIGHT && _action == GLFW_RELEASE)
  {
    Vector2 baseInput = world.GetInput();
    baseInput.x = 0;
    world.SetInput(baseInput);
  }
  else if (_key == GLFW_KEY_LEFT && (_action == GLFW_REPEAT || _action == GLFW_PRESS))
  {
    Vector2 baseInput = world.GetInput();
    baseInput.x = -1;
    world.SetInput(baseInput);
  }
  else if (_key == GLFW_KEY_LEFT && _action == GLFW_RELEASE)
  {
    Vector2 baseInput = world.GetInput();
    baseInput.x = 0;
    world.SetInput(baseInput);
  }
  else if (_key == GLFW_KEY_UP && (_action == GLFW_REPEAT || _action == GLFW_PRESS))
  {
    Vector2 baseInput = world.GetInput();
    baseInput.y = -1;
    world.SetInput(baseInput);
  }
  else if (_key == GLFW_KEY_UP &&_action == GLFW_RELEASE)
  {
    Vector2 baseInput = world.GetInput();
    baseInput.y = 0;
    world.SetInput(baseInput);
  }
  else if (_key == GLFW_KEY_DOWN && (_action == GLFW_REPEAT || _action == GLFW_PRESS))
  {
    Vector2 baseInput = world.GetInput();
    baseInput.y = 1;
    world.SetInput(baseInput);
  }
  else if (_key == GLFW_KEY_DOWN && _action == GLFW_RELEASE)
  {
    Vector2 baseInput = world.GetInput();
    baseInput.y = 0;
    world.SetInput(baseInput);
  }

}
ltex_t* loadTexture(const char* _filename)
{
  int height;
  int width;
  unsigned char* image = stbi_load(_filename, &width, &height, nullptr, 4);
  ltex_t* BufferVRam = ltex_alloc(width, height, 1);
  ltex_setpixels(BufferVRam, image);
  stbi_image_free(image);
  return BufferVRam;
}



template <typename T>
std::string stringFromNumber(T val)
{
  std::ostringstream stream;
  stream << std::fixed << val;
  return stream.str();
}

void SetSpriteOnScreen(Sprite* _sprite, Vector2 _pos, float angle)
{
  _sprite->SetPosition(_pos);
  _sprite->SetAngle(angle);

}

void DrawBackground(ltex_t* _texture, int _Width, int _height)
{
  bool isCompleat = false;
  int horizontal = 0;
  int vertical = 0;
  while (isCompleat == false)
  {
    ltex_draw(_texture, static_cast<float>(horizontal), static_cast<float>(vertical));
    horizontal += _texture->width;
    if ((horizontal - _texture->width / 2) > _Width)
    {
      horizontal = 0;
      vertical += _texture->height;
    }
    if ((vertical - _texture->height / 2) > _height)
    {
      isCompleat = true;
    }
  }
}

void MoveTo(Sprite& _sprite, float _deltaTime)
{
  Vector2 mouse = Vector2(static_cast<float>(mouseX), static_cast<float>(mouseY));
  Vector2 camera = world.GetCameraPosition();

  mouse += camera;

  float angle = _sprite.GetAngle();
  Vector2 vBeePos = _sprite.GetPos();
  Vector2 vSpritePosition = _sprite.GetPos();
  Vector2 vBeeDirection = mouse - _sprite.GetPos();

  if (static_cast<int>(mouse.x - vSpritePosition.x) > 0) //Right
  {
    _sprite.SetScale(Vector2(1, 1));
    angle -= 32 * _deltaTime;
    vBeePos.x += 128.f * _deltaTime;
    vBeePos.y += 128.f * _deltaTime * vBeeDirection.Abs().y / vBeeDirection.y;
    if (angle < -15)
    {
      angle = -15;
    }
  }
  else if (static_cast<int>(mouse.x - vSpritePosition.x) < 0) //Left
  {
    _sprite.SetScale(Vector2(-1, 1));
    angle += 32 * _deltaTime;
    vBeePos.x -= 128 * _deltaTime;
    vBeePos.y += 128 * _deltaTime * vBeeDirection.Abs().y / vBeeDirection.y;
    if (angle > 15)
    {
      angle = 15;
    }
  }
  else if (angle != 0)
  {
    vBeePos.y += 128 * _deltaTime * vBeeDirection.Abs().y / vBeeDirection.y;
    angle -= 32 * _deltaTime * (_sprite.GetAngle() / fabsf(_sprite.GetAngle()));
  }

  SetSpriteOnScreen(&_sprite, vBeePos, angle);
}


void MakeSmaller(Sprite&, float);

void MakeBigger(Sprite& _sprite, float _deltaTime)
{
  if (_sprite.GetScale().x > 1.1f)
  {
    _sprite.SetCallback(&MakeSmaller);
  }
  _sprite.SetScale(_sprite.GetScale() + (0.25f * _deltaTime));
}
void MakeSmaller(Sprite& _sprite, float _deltaTime)
{
  if (_sprite.GetScale().x < 0.9f)
  {
    _sprite.SetCallback(&MakeBigger);
  }
  _sprite.SetScale(_sprite.GetScale() - (0.25f * _deltaTime));
}

void UpdateGameFont(GameFont* _font, float _deltaTime)
{
  Vector2 newPos = _font->m_vCurrentPosition;

  newPos.x += _font->m_fCurrentVelocity * _deltaTime;
  _font->m_vCurrentPosition = newPos;
  float red = _font->m_fRed;
  float green = _font->m_fGreen;
  float blue = _font->m_fBlue;

  lgfx_setcolor(red, green, blue, 1);
  lgfx_setblend(BLEND_ALPHA);
  _font->m_pFont->Draw("Hello World", newPos);
}

void TeleportInEnd(Sprite& _sprite, float _deltaTime)
{
  if (_sprite.GetVFrames() * _sprite.GetHFrames() <= roundf(_sprite.GetCurrentFrame()))
  {
    int x = rand() % Widht;
    int y = rand() % Height;
    _sprite.SetPosition(Vector2(static_cast<float>(x), static_cast<float>(y)));
  }
}



int main() {

  double lastTime = 0;
  Height = 700;
  Widht = 900;




  glfwInit();
  GLFWmonitor* monitor = glfwGetPrimaryMonitor();

  GLFWwindow* window = glfwCreateWindow(Widht, Height, "main", nullptr, nullptr);
  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, InputCallback);
  glfwSetCursorPosCallback(window, MouseCallBack);
  glfwSetMouseButtonCallback(window, MouseButtonCallBack);
  lgfx_setup2d(900, 700);

  //ltex_t* pBackground0 = loadTexture("./data/level.png");
  //ltex_t* pBackground1 = loadTexture("./data/trees1.png");
  //ltex_t* pBackground2 = loadTexture("./data/trees2.png");
  ltex_t* pBackground3 = loadTexture("./data/clouds.png");


  ltex_t* pPlayerRun = loadTexture("./data/run.png");
  ltex_t* pPlayerIdle = loadTexture("./data/idle.png");
  Sprite pPlayerSpriteRun = Sprite(pPlayerRun, 6, 1);
  pPlayerSpriteRun.SetFps(3);
  pPlayerSpriteRun.SetPosition(Vector2(176, 400));
  pPlayerSpriteRun.SetCollisionType(COLLISION_RECT);

  Sprite pPlayerSpriteIdle = Sprite(pPlayerIdle, 1, 1);
  pPlayerSpriteIdle.SetPosition(Vector2(176, 400));
  pPlayerSpriteIdle.SetCollisionType(COLLISION_RECT);

  world.LoadMap("./data/map.xml", 10);


  world.AddSprite(pPlayerSpriteIdle);
  world.AddSprite(pPlayerSpriteRun);

  //world = World(0, 0, 0, pBackground0, pBackground1, pBackground2, pBackground3);
  world.SetLayer(pBackground3);
  world.SetScroolRatio(1, 0.4f);
  world.SetScrollSpeed(1, Vector2(-16, -8));
  //world.SetScroolRatio(2, 0.6f);
  //world.SetScroolRatio(1, 0.8f);
  //world.SetScroolRatio(0, 1);
  //
  //world.AddSprite(pPlayerSprite);

  do
  {
    //system("cls");
    lgfx_clearcolorbuffer(0, 0, 0);

    double actualTime = glfwGetTime();
    double deltaTime = actualTime - lastTime;
    lastTime = actualTime;
    Vector2 mouse = Vector2(static_cast<float>(mouseX), static_cast<float>(mouseY));



    world.Update(deltaTime);
    world.Draw(Vector2(Widht, Height));



    glfwPollEvents();
    glfwSwapBuffers(window);
  } while (!static_cast<bool>(glfwWindowShouldClose(window)));


  //ltex_free(pBackground0);
  //ltex_free(pBackground1);
  //ltex_free(pBackground2);
  //ltex_free(pBackground3);
  ltex_free(pPlayerRun);
  ltex_free(pPlayerIdle);

  glfwTerminate();

  return 0;
}
