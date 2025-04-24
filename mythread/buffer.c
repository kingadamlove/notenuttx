#include "buffer.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>



// 初始化缓冲区
void ringbuffer_init(ringbuffer_t *rb) {
    rb->head = 0;
    rb->tail = 0;
    pthread_mutex_init(&rb->lock, NULL);
}

// 检查缓冲区是否为空
int ringbuffer_is_empty(ringbuffer_t *rb) {
    return rb->head == rb->tail;
}

// 检查缓冲区是否已满
int ringbuffer_is_full(ringbuffer_t *rb) {
    return (rb->head + 1) % RINGBUFFER_SIZE == rb->tail;
}

// 写入数据到缓冲区
void ringbuffer_write(ringbuffer_t *rb, uint8_t data) {
    pthread_mutex_lock(&rb->lock);  // 加锁

    if (!ringbuffer_is_full(rb)) {
        rb->buffer[rb->head] = data;
        rb->head = (rb->head + 1) % RINGBUFFER_SIZE;
    } else {
        printf("Buffer is full, cannot write data\n");
    }

    pthread_mutex_unlock(&rb->lock);  // 解锁
}

// 从缓冲区读取数据
uint8_t ringbuffer_read(ringbuffer_t *rb) {
    pthread_mutex_lock(&rb->lock);  // 加锁

    uint8_t data = 0;
    if (!ringbuffer_is_empty(rb)) {
        data = rb->buffer[rb->tail];
        rb->tail = (rb->tail + 1) % RINGBUFFER_SIZE;
    } else {
        printf("Buffer is empty, cannot read data\n");
    }

    pthread_mutex_unlock(&rb->lock);  // 解锁
    return data;
}

// 写入多个字节
size_t ringbuffer_write_bulk(ringbuffer_t *rb, const uint8_t *data, size_t len) {
    pthread_mutex_lock(&rb->lock);
    size_t i = 0;
    while (i < len && !ringbuffer_is_full(rb)) {
        rb->buffer[rb->head] = data[i++];
        rb->head = (rb->head + 1) % RINGBUFFER_SIZE;
    }
    pthread_mutex_unlock(&rb->lock);
    return i;  // 实际写入的字节数
}

// 读取多个字节
size_t ringbuffer_read_bulk(ringbuffer_t *rb, uint8_t *dest, size_t len) {
    pthread_mutex_lock(&rb->lock);
    size_t i = 0;
    while (i < len && !ringbuffer_is_empty(rb)) {
        dest[i++] = rb->buffer[rb->tail];
        rb->tail = (rb->tail + 1) % RINGBUFFER_SIZE;
    }
    pthread_mutex_unlock(&rb->lock);
    return i;  // 实际读取的字节数
}