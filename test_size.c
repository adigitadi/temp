#ifndef DEMO_TEST
#include <malloc.h>
#else
#include <stdlib.h>
#endif

#include <stdio.h>

int main() {

  // Allocate several different uniquely sized blocks. Ideally your
  // allocator will be able to fit all requests smaller than a page in
  // the same block. Requests larger than a page should allocate
  // separate new blocks

  
  for (int i = 0; i < 5; i++) {
    // these should fit in a single page
    int *data = (int *) malloc(8);
    int *data1 = (int *) malloc(16);
    int *data2 = (int *) malloc(32);
    int *data3 = (int *) malloc(64);
    int *data4 = (int *) malloc(128);
    int *data5 = (int *) malloc(256);
    int *data6 = (int *) malloc(512);

    // these will require multiple pages
    int *data7 = (int *) malloc(5400);    // 2 pages 
    int *data8 = (int *) malloc(12800);   // 4 pages
    int *data9 = (int *) malloc(192000);  // 47 pages

    free(data);
    free(data1);
    free(data2);
    free(data3);
    free(data4);
    free(data5);
    free(data6);
    free(data7);
    free(data8);
    free(data9);
  }

  return 0;
}
