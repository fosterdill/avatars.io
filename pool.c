#include "pool.h"

threadpool_t *create_threadpool() {
  return threadpool_create(THREAD_COUNT, QUEUE_SIZE, 0);
}
