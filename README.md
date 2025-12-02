# OpenGl-2D

## Resume
This is a 2D proto Game Engine, that uses OpenGL, it is compose of this elements:
- Vector
- Sprites
- Collision
- Fonts
- World

## Sprites
The sprite class uses stb_image to load textures, and with the method update and draw.

## Collision
The engine has 3 types of colisions:
- RectCollider, a rectangular size collider.
- CircleColider, a Circular size collider.
- PixelColider, a collider that detect the pixels.

## Font
Load fonts with stb_truetype.

## World
Load the world reading a XML file using pugiXML.
