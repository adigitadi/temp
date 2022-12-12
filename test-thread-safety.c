// test-thread-safety.c
// thread-safety tester for Better Memory Allocator
// 

#ifndef DEMO_TEST
#include <malloc.h>
#else
#include <stdlib.h>
#endif

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <assert.h>

void *thread(void *vargp) {
  pthread_t id = pthread_self();
  int step = sizeof(pthread_t);
  // create an array of sizes based on sizeof(pthread_t)
  // size[] = {8, 5200, 32, 9000, 128};
  int size[] = {step, 650*step, 4*step, 1125*step, 16*step};
  pthread_t *data[5];
  
  // Allocate different uniquely sized blocks (some within a page,
  // others needing a more than a single page). 
  // Ideally your allocator will use one block for the requests
  // smaller than a page (using splitting) and multiple blocks
  // for requests larger than a page.

  for (int k=0; k<5; k++) {
    data[k] = (pthread_t *) malloc(size[k]);
    for ( int i=0; i<(size[k]/step); i++) {
      // set each element to the thread's ID
      data[k][i] = id;
    }
  }
    
  sleep(1);  // sleep for 1 sec

  for (int k=0; k<5; k++) {
    for ( int i=0; i<(size[k]/step); i++) {
      // assert that every element equals the thread's ID
      // catches if another thread was given the same chunk
      assert(pthread_equal(data[k][i], id));
    }
    free(data[k]);
  }

  return NULL;
}

int main() {
  pthread_t tid[100];
  for (int i = 0; i < 100; i++) {
    pthread_create(&tid[i], NULL, thread, NULL);
  }
  for (int i = 0; i < 100; i++) {
    pthread_join(tid[i], NULL);
  }

  return 0;
}
