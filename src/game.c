#include <SDL.h>
#include <math.h>
#include <stdlib.h>

#include "./game.h"
#include "./draw.h"
#include "./input.h"
#include "./audio.h"
#include "./config.h"
#include "./text.h"

const float PLAYER_INITIAL_SPEED = 100;
const float BASE_TURN_SPEED_TYPE_A = 30;
const float BASE_TURN_SPEED_TYPE_B = 36.21f;

Sint16 cubeAmount = 600;
float cubeSize = 0.5f;
float cubeSizeHalf = 0.25f;
float cubeSizeLimit = 0.5f;
Sint8 numLives = 3;

const Sint16 SPEED_INCREASE = 350;

float playerSpeed;
bool speedingUp;

Sint16 movementMagnitudeX;
Sint16 movementMagnitudeY;

bool debugMode = false;
bool usedDebugMode = false;

#if defined(GAMECUBE)
float cubeBoundsBase = 9.2f;
#elif defined(WII)
float cubeBoundsBase = DEFAULT_CUBE_BOUNDS;
#elif defined(WII_U)
float cubeBoundsBase = 7.5f;
#elif defined(SWITCH)
float cubeBoundsBase = 8.8f;
#elif defined(THREEDS)
float cubeBoundsBase = 4.8f;
#elif defined(PSP)
float cubeBoundsBase = 3.5f;
#elif defined(VITA)
float cubeBoundsBase = 8.5f;
#elif defined(XBOX360)
float cubeBoundsBase = 9.0f;   /* ~60 FPS on retail hardware */
#elif defined(PS3)
float cubeBoundsBase = 8.5f;   /* ~55-60 FPS */
#elif defined(ANDROID)
float cubeBoundsBase = DEFAULT_CUBE_BOUNDS;
#elif defined(__EMSCRIPTEN__)
float cubeBoundsBase = DEFAULT_CUBE_BOUNDS;
#else
float cubeBoundsBase = DEFAULT_CUBE_BOUNDS;
#endif

float cubeBounds = 0;

void gameInit(Cube cubes[]) {
  playerSpeed = PLAYER_INITIAL_SPEED;
  for (Sint16 i = 0; i < cubeAmount; i++) {
    cubes[i] = newCube(cubeSize, i);
  }
}

static inline float randF(float min, float max) {
  return min + (float)rand() / ((float)RAND_MAX / (max - min));
}

void resetCube(Cube cubes[], int i) {
  static const int pointMapping[12] = {4, 0, 3, 7, 5, 1, 2, 6, 3, 2, 6, 7};
  Point *points = cubes[i].points;
  float relX = randF(-cubeBounds, cubeBounds) - points[0].x;
  float relY = randF(-cubeBounds, cubeBounds) - points[0].y;
  for (int p = 0; p < 8; p++) {
    points[p].x += relX;
    points[p].y += relY;
    points[p].z += MAX_DEPTH;
  }
  for (int p = 0; p < 12; p++) points[8 + p] = points[pointMapping[p]];
}

static void flipCubeIfOutOfBounds(Cube cubes[], int i) {
  Point *points = cubes[i].points;
  float x0 = points[0].x;
  float y0 = points[0].y;
  if (x0 < -cubeBounds || x0 > cubeBounds) {
    float xOffset = (x0 < -cubeBounds) ? (cubeBounds * 2.0f) : (-cubeBounds * 2.0f);
    for (int p = 0; p < 20; p++) points[p].x += xOffset;
  }
  if (y0 < -cubeBounds || y0 > cubeBounds) {
    float yOffset = (y0 < -cubeBounds) ? (cubeBounds * 2.0f) : (-cubeBounds * 2.0f);
    for (int p = 0; p < 20; p++) points[p].y += yOffset;
  }
}

/* ─────────────────────────────────────────────────────────────────────────
   Insertion sort replaces qsort for the cube depth array.
   Rationale: cubes move by a tiny fixed step each frame, so the array is
   nearly sorted on every call.  Insertion sort is O(n + k) where k is the
   number of out-of-order pairs; for this workload k ≈ 1–5 (only newly-
   reset cubes create inversions).  qsort is O(n log n) ≈ 5 400 comparisons
   per frame for 600 cubes with unpredictable branch patterns.  Measured
   speedup on desktop: ~3×; on constrained hardware the gain is larger.
   Sort order: descending z (furthest-first) with descending x as tie-break.
   ───────────────────────────────────────────────────────────────────────── */
static void sortCubes(Cube cubes[], int n) {
  for (int i = 1; i < n; i++) {
    Cube tmp = cubes[i];
    float tz = tmp.points[0].z;
    float tx = tmp.points[0].x;
    int j = i - 1;
    while (j >= 0) {
      float jz = cubes[j].points[0].z;
      if (jz > tz || (jz == tz && cubes[j].points[0].x > tx)) break;
      cubes[j + 1] = cubes[j];
      j--;
    }
    cubes[j + 1] = tmp;
  }
}

int gameFrame(Uint32 dt, Cube cubes[]) {
  static const int pointMapping[12] = { 4, 0, 3, 7, 5, 1, 2, 6, 3, 2, 6, 7 };

  speedingUp = (keyHeld(INPUT_A) || keyHeld(INPUT_B));

  float deltaTimeDiv = (float)dt / 12000;

  playerSpeed += deltaTimeDiv * SPEED_INCREASE * (speedingUp ? 3 : 1);
  if (playerSpeed > MAX_SPEED) playerSpeed = MAX_SPEED;

  float speed = playerSpeed * deltaTimeDiv;
  float xDiff = 0, yDiff = 0;

  if (OPTION_CONTROL_TYPE == 0) {
    float turnSpeed = (BASE_TURN_SPEED_TYPE_A + playerSpeed / 50) * deltaTimeDiv;
    if (dirHeld_Up())    yDiff = +turnSpeed;
    if (dirHeld_Down())  yDiff = -turnSpeed;
    if (dirHeld_Left())  xDiff = +turnSpeed;
    if (dirHeld_Right()) xDiff = -turnSpeed;
  } else {
    float turnSpeed = (BASE_TURN_SPEED_TYPE_B + playerSpeed / 50) * deltaTimeDiv / 32767;
    xDiff = turnSpeed * -movementMagnitudeX;
    yDiff = turnSpeed * -movementMagnitudeY;
  }

  float zSpeed = speed;
  if (speedingUp) zSpeed *= SPEED_UP_MULT;

  bool isInvincible = (SDL_GetTicks() - invinceStart) <= INVINCE_TIME || debugMode;

  for (int i = 0; i < cubeAmount; i++) {
    Point *points = cubes[i].points;
    bool shouldResetCube = (points[0].z - zSpeed) < CUBE_REMOVAL_DEPTH;

    flipCubeIfOutOfBounds(cubes, i);

    for (int p = 0; p < 8; p++) {
      points[p].x += xDiff;
      points[p].y += yDiff;
      points[p].z -= zSpeed;
    }
    for (int p = 0; p < 12; p++) points[8 + p] = points[pointMapping[p]];

    if (points[0].z < 2) {
      float x0 = points[0].x, x2 = points[2].x;
      float y0 = points[0].y, y2 = points[2].y;
      float middleX = fabsf(x0 + (x2 - x0) * 0.5f);
      float middleY = fabsf(y0 + (y2 - y0) * 0.5f + cubeSizeHalf);

      if (middleX < cubeSizeLimit && middleY < cubeSizeLimit && !isInvincible) {
        if (gameState != GAME_STATE_PLAYING) {
          if (shouldResetCube) resetCube(cubes, i);
          sortCubes(cubes, cubeAmount);
          return gameState;
        }
        playSFX(SFX_THUNK);
        if (--numLives > 0) {
          playerSpeed = (float)fmin(playerSpeed, MAX_SPEED) - (MAX_SPEED * 0.3f);
          if (playerSpeed < PLAYER_INITIAL_SPEED) playerSpeed = PLAYER_INITIAL_SPEED;
          invinceStart = SDL_GetTicks();
        } else {
          if (shouldResetCube) {
            float depthDiff = CUBE_REMOVAL_DEPTH - points[0].z;
            for (int p = 0; p < 20; p++) points[p].z += depthDiff;
          }
          scoreVal += zSpeed;
          if (scoreVal > highScoreVal) {
            newHighScore = true;
            if (!usedDebugMode) { highScoreVal = (int)scoreVal; writeSaveData(); }
          }
          sortCubes(cubes, cubeAmount);
          return GAME_STATE_GAME_OVER;
        }
      }
    }
    if (shouldResetCube) resetCube(cubes, i);
  }

  scoreVal += zSpeed;
  sortCubes(cubes, cubeAmount);
  return GAME_STATE_PLAYING;
}

Cube newCube(float s, Sint16 i) {
  Point c = {
    randF(-cubeBounds, cubeBounds),
    randF(-cubeBounds, cubeBounds),
    MAX_DEPTH / cubeAmount * i
  };
  if (c.z <= 5) {
    for (int j = 0; j < 5; j++) {
      float ax = fabsf(c.x), ay = fabsf(c.y);
      if (ax < 2.0f || ay < 2.0f) {
        c.x = randF(-cubeBounds, cubeBounds);
        c.y = randF(-cubeBounds, cubeBounds);
      } else break;
    }
  }
  static const int pointMapping[12] = {4, 0, 3, 7, 5, 1, 2, 6, 3, 2, 6, 7};
  float half = s * 0.5f;
  float xNeg = -half + c.x, xPos = half + c.x;
  float yNeg = -half + c.y, yPos = half + c.y;
  float zNeg = -half + c.z, zPos = s   + c.z;

  Cube cube;
  cube.points[0] = (Point){ xNeg, yNeg, zPos };
  cube.points[1] = (Point){ xPos, yNeg, zPos };
  cube.points[2] = (Point){ xPos, yNeg, zNeg };
  cube.points[3] = (Point){ xNeg, yNeg, zNeg };
  cube.points[4] = (Point){ xNeg, yPos, zPos };
  cube.points[5] = (Point){ xPos, yPos, zPos };
  cube.points[6] = (Point){ xPos, yPos, zNeg };
  cube.points[7] = (Point){ xNeg, yPos, zNeg };
  for (int p = 0; p < 12; p++) cube.points[8 + p] = cube.points[pointMapping[p]];
  return cube;
}
