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
  if (argc != 3) {
    fprintf(stderr, "Expected 2 arguments, got %d.\n", argc - 1);
    fprintf(stderr, "Usage: %s INFILE1 INFILE2 OUTFILE\n", argv[0]);
    return 1;
  }

  int rc = 0;

  const char* infile1 = argv[1];
  const char* infile2 = argv[2];

  int infile1_width, infile1_height, infile1_channel;
  int infile2_width, infile2_height, infile2_channel;
  uint8_t* infile1_data = NULL;
  uint8_t* infile2_data = NULL;
  uint64_t diff         = 0;

  clock_t start;
  clock_t end;
  double time_spent;

  infile1_data = stbi_load(infile1, &infile1_width, &infile1_height, &infile1_channel, 4);
  if (infile1_data == NULL) {
    fprintf(stderr, "Failed to open infile1 '%s'.\n", infile1);
    DEFER_END(rc, 1);
  }

  infile2_data = stbi_load(infile2, &infile2_width, &infile2_height, &infile2_channel, 4);
  if (infile2_data == NULL) {
    fprintf(stderr, "Failed to open infile2 '%s'.\n", infile2);
    DEFER_END(rc, 1);
  }

  if (infile1_width != infile2_width) {
    fprintf(stderr, "'%s' width != '%s' width.\n", infile1, infile2);
    DEFER_END(rc, 1);
  }
  if (infile1_height != infile2_height) {
    fprintf(stderr, "'%s' height != '%s' height.\n", infile1, infile2);
    DEFER_END(rc, 1);
  }

  start = clock();

  diff = pixelmatch(infile1_data, infile2_data, infile1_width, infile1_height, 0.1, true);

  end        = clock();
  time_spent = (double)(end - start) / CLOCKS_PER_SEC;

end:

  if (rc == 0) {
    printf("Differences: %lu\n", diff);
    printf("Time taken for pixelmatch: %f seconds\n", time_spent);
  }

  stbi_image_free(infile1_data);
  stbi_image_free(infile2_data);

  return rc;
}
