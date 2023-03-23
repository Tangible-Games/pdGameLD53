#include "game.h"
#include "math_intersect.h"
#include "pd_api.h"

#define Math_Pi 3.141592653589793f

float Math_DegToRad(float a) { return a * (Math_Pi * 0.00555555555555f); }

int level_width = 8;
int level_height = 8;
// clang-format off
int8_t level[] = {
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 0, 0, 0, 0, 0, 0, 2,
    2, 0, 1, 0, 1, 0, 1, 2,
    2, 1, 1, 0, 1, 0, 0, 2,
    2, 0, 0, 0, 1, 0, 0, 2,
    2, 0, 0, 0, 0, 0, 0, 2,
    2, 2, 2, 2, 2, 2, 2, 2,
};
// clang-format on
const float level_cell_size = 20.0f;

const int screen_width = 400;
const int screen_height = 240;
const float horizontal_fov = 45.0f;
const float vertical_fov =
    ((float)screen_height / (float)screen_width) * horizontal_fov;

void Vector_GetRotated(float angle_rad, float ray_x, float ray_y,
                       float* ray_x_out, float* ray_y_out) {
  float c = cosf(angle_rad);
  float s = sinf(angle_rad);
  *ray_x_out = c * ray_x - s * ray_y;
  *ray_y_out = s * ray_x + c * ray_y;
}

typedef struct LevelCollision {
  int i;
  int j;
  float d_2;
  Point p;
} LevelCollision;

void Level_GetCell(Point* eye, int* level_i_out, int* level_j_out) {
  *level_i_out = (int)(eye->x / level_cell_size);
  *level_j_out = (int)(eye->y / level_cell_size);
}

void Level_TraceRay(PlaydateAPI* playdate, Point* eye, int level_i, int level_j,
                    float ray_x, float ray_y,
                    LevelCollision* level_collision_out) {
  int cell_i = level_i;
  int cell_j = level_j;

  int CC = 10;
  while (1) {
    Point eye_in_cell;
    eye_in_cell.x = eye->x - level_cell_size * level_i;
    eye_in_cell.y = eye->y - level_cell_size * level_j;

    int d_i = 0;
    int d_j = 0;
    Point intersection;
    symIntersectSquareFromInside(eye_in_cell.x, eye_in_cell.y, ray_x, ray_y,
                                 level_cell_size, level_cell_size, &d_i, &d_j,
                                 &intersection.x, &intersection.y);

    playdate->system->logToConsole("d_i: %i, d_j: %i", d_i, d_j);

    cell_i = cell_i + d_i;
    cell_j = cell_j + d_j;
    int cell_index = cell_j * level_width + cell_i;
    playdate->system->logToConsole("c: %i", level[cell_index]);
    if (level[cell_index] == 1 || level[cell_index] == 2) {
      float p_x = level_cell_size * cell_i + intersection.x;
      float p_y = level_cell_size * cell_j + intersection.y;
      float d_x = p_x - eye->x;
      float d_y = p_y - eye->y;
      level_collision_out->i = cell_i;
      level_collision_out->j = cell_j;
      level_collision_out->d_2 = d_x * d_x + d_y * d_y;
      level_collision_out->p.x = p_x;
      level_collision_out->p.y = p_y;
      break;
    }

    --CC;
    if (CC < 0) {
      break;
    }
  }
}

void Level_Rasterize(PlaydateAPI* playdate, Point* eye, float view_x,
                     float view_y, uint8_t* screen_bits_out) {
  int screen_center_x = screen_width / 2;

  int level_i = 0;
  int level_j = 0;
  Level_GetCell(eye, &level_i, &level_j);

  float column_angle = horizontal_fov / (float)screen_width;

  for (int i = 0; i < screen_width; ++i) {
    float angle = column_angle * (i - screen_center_x);

    float ray_x;
    float ray_y;
    Vector_GetRotated(Math_DegToRad(angle), view_x, view_y, &ray_x, &ray_y);

    LevelCollision level_collision;

    Level_TraceRay(playdate, eye, level_i, level_j, ray_x, ray_y,
                   &level_collision);

    playdate->system->logToConsole("%i %i", level_collision.i,
                                   level_collision.j);
  }
}

Point eye;
float view_x;
float view_y;

typedef struct Wall {
  Point p_0;
  Point p_1;
} Wall;

Wall walls[3];

float prev_time = 0.0f;

int update(void* userdata) {
  PlaydateAPI* playdate = userdata;

  float cur_time = playdate->system->getElapsedTime();
  float dt = cur_time - prev_time;
  prev_time = cur_time;

  PDButtons buttons_current;
  PDButtons buttons_pushed;
  PDButtons buttons_released;
  playdate->system->getButtonState(&buttons_current, &buttons_pushed,
                                   &buttons_released);

  playdate->graphics->clear(kColorWhite);

  int screen_center_x = screen_width / 2;

  float column_angle = horizontal_fov / (float)screen_width;

  float wall_height = 100.0f;

  if (buttons_current == kButtonUp) {
    eye.x = eye.x + 100.0f * dt * view_x;
    eye.y = eye.y + 100.0f * dt * view_y;
  } else if (buttons_current == kButtonDown) {
    eye.x = eye.x - 100.0f * dt * view_x;
    eye.y = eye.y - 100.0f * dt * view_y;
  }

  if (buttons_current == kButtonLeft) {
    float new_view_x;
    float new_view_y;
    Vector_GetRotated(Math_DegToRad(-270.0f) * dt, view_x, view_y, &new_view_x,
                      &new_view_y);
    view_x = new_view_x;
    view_y = new_view_y;
  } else if (buttons_current == kButtonRight) {
    float new_view_x;
    float new_view_y;
    Vector_GetRotated(Math_DegToRad(270.0f) * dt, view_x, view_y, &new_view_x,
                      &new_view_y);
    view_x = new_view_x;
    view_y = new_view_y;
  }

  int prev_segment_id = -1;
  int prev_y_0 = -1;
  int prev_y_1 = 1000;
  float prev_d = -1.0f;

  for (int i = 0; i < screen_width; ++i) {
    float angle = column_angle * (i - screen_center_x);

    float ray_x;
    float ray_y;
    Vector_GetRotated(Math_DegToRad(angle), view_x, view_y, &ray_x, &ray_y);

    Point view;
    view.x = eye.x + 1000.0f * ray_x;
    view.y = eye.y + 1000.0f * ray_y;

    int result = -1;
    int segment_id = -1;
    float d = 1000000.0f;
    for (int i = 0; i < 3; ++i) {
      Point intersection;
      int new_result = symIntersectSegments(&walls[i].p_0, &walls[i].p_1, &eye,
                                            &view, 0.00000001f, &intersection);
      if (new_result == 0) {
        float d_x = intersection.x - eye.x;
        float d_y = intersection.y - eye.y;
        float new_d = sqrtf(d_x * d_x + d_y * d_y);
        if (new_d < d) {
          d = new_d;
          segment_id = i;
        }

        result = 0;
      }
    }

    int y_0 = -1;
    int y_1 = -1;
    if (result == 0) {
      float x = d * tanf(vertical_fov) * cosf(Math_DegToRad(angle));

      int wall_size_in_px = (float)screen_height * (wall_height / x);
      y_0 = (screen_height - wall_size_in_px) / 2;
      y_1 = y_0 + wall_size_in_px;
    }

    if (segment_id != prev_segment_id) {
      if (prev_segment_id == -1) {
        playdate->graphics->drawLine(i, y_0, i, y_1, 2, kColorBlack);
      } else if (segment_id == -1) {
        playdate->graphics->drawLine(i, prev_y_0, i, prev_y_1, 2, kColorBlack);
      } else {
        if (d < prev_d) {
          playdate->graphics->drawLine(i, y_0, i, y_1, 2, kColorBlack);
        } else {
          playdate->graphics->drawLine(i, prev_y_0, i, prev_y_1, 2,
                                       kColorBlack);
        }
      }
    } else if (segment_id != -1) {
      playdate->graphics->drawLine(i, y_0, i, y_0 - 2, 1, kColorBlack);
      playdate->graphics->drawLine(i, y_1, i, y_1 + 2, 1, kColorBlack);
    }

    prev_segment_id = segment_id;
    prev_y_0 = y_0;
    prev_y_1 = y_1;
    prev_d = d;
  }

  playdate->system->drawFPS(0, 0);

  return 0;
}

#ifdef _WINDLL
__declspec(dllexport)
#endif
    int eventHandler(PlaydateAPI* playdate, PDSystemEvent event, uint32_t arg) {
  playdate->system->logToConsole("Event handler.");
  if (event == kEventInit) {
    void* userdata = SetupGame(playdate);
    playdate->system->setUpdateCallback(Update, userdata);

    eye.x = 50.0f;
    eye.y = 0.0f;
    view_x = 0.0f;
    view_y = 1.0f;

    walls[0].p_0.x = 0.0f;
    walls[0].p_0.y = 100.0f;
    walls[0].p_1.x = 100.0;
    walls[0].p_1.y = 100.0f;

    walls[1].p_0.x = 0.0f;
    walls[1].p_0.y = 25.0f;
    walls[1].p_1.x = 0.0;
    walls[1].p_1.y = 75.0f;

    walls[2].p_0.x = 100.0f;
    walls[2].p_0.y = 25.0f;
    walls[2].p_1.x = 100.0;
    walls[2].p_1.y = 75.0f;

    playdate->display->setRefreshRate(60);
    prev_time = playdate->system->getElapsedTime();
    playdate->system->setUpdateCallback(update, playdate);
  }
  return 0;
}
