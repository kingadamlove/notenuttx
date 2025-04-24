#ifndef __APPS_EXAMPLES_BUFFER_H
#define __APPS_EXAMPLES_BUFFER_H

#include <nuttx/config.h>
#include <stdint.h>
#include <stddef.h>
#include <stdio.h> 
#define RINGBUFFER_SIZE 512

// 定义环形缓冲区结构体
typedef struct {
    uint8_t buffer[RINGBUFFER_SIZE];  // 缓冲区
    size_t head;                      // 写指针
    size_t tail;                      // 读指针
    pthread_mutex_t lock;             // 锁，确保线程安全
} ringbuffer_t;


void ringbuffer_init(ringbuffer_t *rb) ;
int ringbuffer_is_empty(ringbuffer_t *rb);
int ringbuffer_is_full(ringbuffer_t *rb) ;
void ringbuffer_write(ringbuffer_t *rb, uint8_t data) ;
uint8_t ringbuffer_read(ringbuffer_t *rb) ;

#endif
