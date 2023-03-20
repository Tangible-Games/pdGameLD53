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

void Level_TraceRay(PlaydateAPI* playdate, Point* eye, int level_i, int level_j, float ray_x,
                    float ray_y, LevelCollision* level_collision_out) {
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

    playdate->system->logToConsole("d_i: %i, d_j: %i", d_i,
                                   d_j);

    cell_i = cell_i + d_i;
    cell_j = cell_j + d_j;
    int cell_index = cell_j * level_width + cell_i;
    playdate->system->logToConsole("c: %i", level[cell_index]);
    if (level[cell_index] == 1 ||
        level[cell_index] == 2) {
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

    Level_TraceRay(playdate, eye, level_i, level_j, ray_x, ray_y, &level_collision);

    playdate->system->logToConsole("%i %i", level_collision.i,
                                   level_collision.j);
  }
}

Point eye;

static int update(void* userdata) {
  PlaydateAPI* playdate = userdata;

  PDButtons buttons_current;
  PDButtons buttons_pushed;
  PDButtons buttons_released;
  playdate->system->getButtonState(&buttons_current, &buttons_pushed, &buttons_released);

  playdate->graphics->clear(kColorWhite);

  int screen_center_x = screen_width / 2;

  float column_angle = horizontal_fov / (float)screen_width;

  Point seg_0_0;
  seg_0_0.x = 0.0f;
  seg_0_0.y = 100.0f;
  Point seg_0_1;
  seg_0_1.x = 100.0;
  seg_0_1.y = 100.0f;

  Point seg_1_0;
  seg_1_0.x = 0.0f;
  seg_1_0.y = 25.0f;
  Point seg_1_1;
  seg_1_1.x = 0.0;
  seg_1_1.y = 75.0f;

  Point seg_2_0;
  seg_2_0.x = 100.0f;
  seg_2_0.y = 25.0f;
  Point seg_2_1;
  seg_2_1.x = 100.0;
  seg_2_1.y = 75.0f;

  float wall_height = 100.0f;

  float view_x = cosf(Math_DegToRad(playdate->system->getCrankAngle()));
  float view_y = sinf(Math_DegToRad(playdate->system->getCrankAngle()));

  if (buttons_current == kButtonUp) {
    eye.x = eye.x + 2.0f * view_x;
    eye.y = eye.y + 2.0f * view_y;
  } else if (buttons_current == kButtonDown) {
    eye.x = eye.x - 2.0f * view_x;
    eye.y = eye.y - 2.0f * view_y;
  }

  if (buttons_current == kButtonLeft) {
    float side_x;
    float side_y;
    Vector_GetRotated(Math_DegToRad(-90.0f), view_x, view_y, &side_x, &side_y);
    eye.x = eye.x + 2.0f * side_x;
    eye.y = eye.y + 2.0f * side_y;
  } else if (buttons_current == kButtonRight) {
    float side_x;
    float side_y;
    Vector_GetRotated(Math_DegToRad(90.0f), view_x, view_y, &side_x, &side_y);
    eye.x = eye.x + 2.0f * side_x;
    eye.y = eye.y + 2.0f * side_y;
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
    view.x = eye.x + 500.0f * ray_x;
    view.y = eye.y + 500.0f * ray_y;

    Point intersection;
    int result = symIntersectSegments(&seg_0_0, &seg_0_1, &eye, &view, 0.00000001f, &intersection);
    int segment_id = -1;
    if (result != 0) {
      result = symIntersectSegments(&seg_1_0, &seg_1_1, &eye, &view, 0.00000001f, &intersection);
      if (result != 0) {
        result = symIntersectSegments(&seg_2_0, &seg_2_1, &eye, &view, 0.00000001f, &intersection);
        if (result == 0) {
          segment_id = 2;
        }
      } else {
        segment_id = 1;
      }
    } else {
      segment_id = 0;
    }

    int y_0 = -1;
    int y_1 = -1;
    float d = -1.0f;
    if (result == 0) {
      float d_x = intersection.x - eye.x;
      float d_y = intersection.y - eye.y;
      d = sqrtf(d_x * d_x + d_y * d_y);
      float x = d * tanf(vertical_fov) * cosf(Math_DegToRad(angle));

      int wall_size_in_px = (float) screen_height * (wall_height / x);
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
          playdate->graphics->drawLine(i, prev_y_0, i, prev_y_1, 2, kColorBlack);
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

  // Point seg_0;
  // seg_0.x = 20.0f;
  // seg_0.y = 30.0f;
  // Point seg_1;
  // seg_1.x = 350.0f;
  // seg_1.y = 45.0f;

  // Point eye;
  // eye.x = (float) screen_width / 2.0f;
  // eye.y = (float) screen_height / 2.0f;

  // Point view;
  // view.x = eye.x + 500.0f * cosf(Math_DegToRad(playdate->system->getCrankAngle()));
  // view.y = eye.y + 500.0f * sinf(Math_DegToRad(playdate->system->getCrankAngle()));

  // Point intersection;
  // int result = symIntersectSegments(&seg_0, &seg_1, &eye, &view, 0.00000001f, &intersection);

  // playdate->graphics->drawLine((int) seg_0.x, (int) seg_0.y, (int) seg_1.x, (int) seg_1.y, 4, kColorBlack);

  // playdate->graphics->drawLine((int) eye.x, (int) eye.y, (int) view.x, (int) view.y, 1, kColorBlack);

  // if (result == 0) {
  //   playdate->graphics->drawRect((int) intersection.x - 5, (int) intersection.y - 5, 10, 10, kColorBlack);
  // }

  playdate->system->drawFPS(0,0);

  return 0;
}

#ifdef _WINDLL
__declspec(dllexport)
#endif
    int eventHandler(PlaydateAPI* playdate, PDSystemEvent event, uint32_t arg) {
  playdate->system->logToConsole("Event handler.");
  if (event == kEventInit) {
    eye.x = 50.0f;
    eye.y = 0.0f;
    playdate->system->setUpdateCallback(update, playdate);
  }
  return 0;
}
