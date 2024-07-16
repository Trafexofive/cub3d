#ifndef MACROS_H
#define MACROS_H

#ifndef __OSX__

typedef enum s_keys {

  W_KEY = 0x77,
  S_KEY = 0x73,
  A_KEY = 0x61,
  D_KEY = 0x64,
  J_KEY = 0x106,
  K_KEY = 0x107,
  ESC_KEY = 0xFF1B,
} t_keys;

#else

typedef enum s_keys {
  W_KEY = 0x0D,
  S_KEY = 0x01,
  A_KEY = 0x00,
  D_KEY = 0x02,
  ESC_KEY = 0x35,
} t_keys;

#endif

#define NIL 0
#define COLOR 0xFF5733
#define GREEN 0x00FF4D
#define VER false
#define HOR true
#define FPS 100000
#define TILE_SIZE 30
#define MOVE_SPEED 2
#define HIT_BOX 10
#define SCALE_FACTOR 0.7
#define SCREEN_WIDTH 1980
#define SCREEN_HEIGHT 1280

#endif
