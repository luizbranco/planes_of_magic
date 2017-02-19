#include "camera.h"

#include <math.h>
#include <stdio.h>

#include "../math/math.h"

namespace camera {
void Camera::MoveUp() { y = math::Clamp(y - speed, 0, max_h); }
void Camera::MoveDown() { y = math::Clamp(y + speed, 0, max_h); }
void Camera::MoveLeft() { x = math::Clamp(x - speed, 0, max_w); }
void Camera::MoveRight() { x = math::Clamp(x + speed, 0, max_w); }
void Camera::ZoomIn() { ChangeZoom(zoom - 1); }
void Camera::ZoomOut() { ChangeZoom(zoom + 1); }

int Camera::Clip(int* width, int* height) {
  double size = ceil(tile_size / zoom);

  int map_width = *width;
  int map_height = *height;

  // camera tile-based size
  int cam_w = math::Clamp(ceil(w / size), 0, map_width);
  int cam_h = math::Clamp(ceil(h / size), 0, map_height);

  // camera tile-based position
  int cam_x = math::Clamp(floor(x / size), 0, map_width - cam_w);
  int cam_y = math::Clamp(floor(y / size), 0, map_height - cam_h);

  *width = cam_w;
  *height = cam_h;

  return cam_x + (cam_y * map_width);
}

void Camera::ChangeZoom(int new_zoom) {
  int old_size = tile_size / zoom;

  zoom = math::Clamp(new_zoom, min_zoom, max_zoom);

  int mid_x = x + w / 2;
  int mid_y = y + h / 2;

  int new_size = tile_size / zoom;

  int new_w = map_w * new_size;
  int new_h = map_h * new_size;

  int new_x = (mid_x * new_size / old_size) - w / 2;
  int new_y = (mid_y * new_size / old_size) - h / 2;

  x = math::Clamp(new_x, 0, new_w - w);
  y = math::Clamp(new_y, 0, new_h - h);
}
}
