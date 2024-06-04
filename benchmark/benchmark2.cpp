#include <stdio.h>
#include <time.h>

#include "../pixelmatch.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define DEFER_END(rc, val) \
  do {                     \
    rc = val;              \
    goto end;              \
  } while (0)

int main(int argc, char** argv) {
  int frames = 310;

  char current_frame_path[256];
  char next_frame_path[256];
  uint8_t* current_frame_data;
  int current_frame_width;
  int current_frame_height;
  int current_frame_channel;
  uint8_t* next_frame_data;
  int next_frame_width;
  int next_frame_height;
  int next_frame_channel;
  uint64_t diff = 0;
  clock_t start;
  clock_t end;
  double total_time_spent = 0;

  snprintf(current_frame_path, 255, "../assets/frames/%08d.png", 1);
  snprintf(next_frame_path, 255, "../assets/frames/%08d.png", 2);

  int rc = 0;

  current_frame_data = stbi_load(current_frame_path, &current_frame_width, &current_frame_height, &current_frame_channel, 4);
  if (current_frame_data == NULL) {
    fprintf(stderr, "Failed to open current_frame_path '%s'.\n", current_frame_path);
    DEFER_END(rc, 1);
  }

  next_frame_data = stbi_load(next_frame_path, &next_frame_width, &next_frame_height, &next_frame_channel, 4);
  if (current_frame_data == NULL) {
    fprintf(stderr, "Failed to open next_frame_path '%s'.\n", next_frame_path);
    DEFER_END(rc, 1);
  }

  for (int i = 3; i < frames; i++) {
    if (current_frame_width != next_frame_width) {
      fprintf(stderr, "'%s' width != '%s' width.\n", current_frame_path, next_frame_path);
      DEFER_END(rc, 1);
    }
    if (current_frame_height != next_frame_height) {
      fprintf(stderr, "'%s' height != '%s' height.\n", current_frame_path, next_frame_path);
      DEFER_END(rc, 1);
    }

    start = clock();

    diff = pixelmatch(current_frame_data, next_frame_data, current_frame_width, current_frame_height, 0.1, true);

    end = clock();
    total_time_spent += (double)(end - start) / CLOCKS_PER_SEC;

    printf("%s - %s = %lu\n", current_frame_path, next_frame_path, diff);

    stbi_image_free(current_frame_data);

    current_frame_data   = next_frame_data;
    current_frame_width  = next_frame_width;
    current_frame_height = next_frame_height;
    strncpy(current_frame_path, next_frame_path, 255);

    snprintf(next_frame_path, 255, "../assets/frames/%08d.png", i);

    next_frame_data = stbi_load(next_frame_path, &next_frame_width, &next_frame_height, &next_frame_channel, 4);
    if (next_frame_data == NULL) {
      fprintf(stderr, "Failed to open next_frame_data '%s'.\n", next_frame_data);
      DEFER_END(rc, 1);
    }
  }

end:

  if (rc == 0) {
    printf("Time taken for pixelmatch: %f seconds\n", total_time_spent);
  }

  stbi_image_free(current_frame_data);
  stbi_image_free(next_frame_data);

  return rc;
}
