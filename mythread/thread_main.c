#include <nuttx/config.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define STACK_SIZE 1024

// 线程1：打印 "Hello"
void *thread_hello(void *arg)
{
  while (1)
  {
    printf("Hello\n");
    usleep(500000);  // 睡眠500ms
  }
  return NULL;
}

// 线程2：打印 "World"
void *thread_world(void *arg)
{
  while (1)
  {
    printf("World\n");
    usleep(500000);  // 睡眠500ms
  }
  return NULL;
}

int main(int argc, char *argv[])
{
  pthread_t tid1, tid2;
  int ret;

  // 创建线程1
  ret = pthread_create(&tid1, NULL, thread_hello, NULL);
  if (ret != 0)
  {
    printf("Error creating thread_hello\n");
    return -1;
  }

  // 创建线程2
  ret = pthread_create(&tid2, NULL, thread_world, NULL);
  if (ret != 0)
  {
    printf("Error creating thread_world\n");
    return -1;
  }

  // 等待线程结束
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);

  return 0;
}
