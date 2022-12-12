
// Check splitting and coalescing

#ifndef DEMO_TEST
#include <malloc.h>
#else
#include <stdlib.h>
#endif

#include <stdio.h>
#include <stddef.h>

#include <assert.h>

#define BLOCK_SIZE 16
#define BLOCK_COUNT 100

int main() {


  char *data[BLOCK_COUNT];

  fprintf(stderr, "Checking splitting...");
  data[0] = malloc(BLOCK_SIZE);
  char *start = data[0];

  // check that we are getting pointers within the same page
  for (int i = 1; i < BLOCK_COUNT; ++i) {
    data[i] = malloc(BLOCK_SIZE);
    assert(data[i] >= start);
    assert(data[i] < start + 4096);
  }
  fprintf(stderr, "Seems okay!\n");

  for (int i = 0; i < BLOCK_COUNT; ++i) {
    free(data[i]);
  }

  fprintf(stderr, "Checking coalescing...");
  data[0] = malloc(BLOCK_COUNT * BLOCK_SIZE);
  assert(start == data[0]);
  fprintf(stderr, "Seems okay!\n");
  free(data[0]);

  fprintf(stderr, "Checking splitting again...");
  data[0] = malloc(BLOCK_SIZE);
  assert(start == data[0]);
  for (int i = 1; i < BLOCK_COUNT; ++i) {
    data[i] = malloc(BLOCK_SIZE);
    assert(data[i] < start + 4096);
  }
  fprintf(stderr, "Seems okay!\n");

  for (int i = 0; i < BLOCK_COUNT; ++i) {
    free(data[i]);
  }

  return 0;
}
