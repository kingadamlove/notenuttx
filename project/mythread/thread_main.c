#include <nuttx/config.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <nuttx/analog/adc.h>
#include <sched.h>

#include "buffer.h"
#include "machinestudy.h"
// // 全局变量
// pthread_t data_analysis_thread;
// sem_t data_analysis_sem;

// // 按键中断回调函数
// static void key_interrupt_handler(int irq, void *context, void *arg) {
//     int sval;
//     sem_getvalue(&data_analysis_sem, &sval);

//     if (sval == 0) {
//         // 线程挂起，唤醒它
//         printf("Waking up data analysis thread...\n");
//         sem_post(&data_analysis_sem);
//     } else {
//         // 线程在运行，取消它并重新创建
//         printf("Restarting data analysis thread...\n");

//         pthread_cancel(data_analysis_thread);             // 异步取消线程
//         pthread_join(data_analysis_thread, NULL);         // 等待线程回收资源

//         sem_init(&data_analysis_sem, 0, 0);                // 重新初始化信号量
//         pthread_create(&data_analysis_thread, NULL, data_analysis_func, NULL);
//     }
// }
#define samplesSize 4

typedef struct {
    int adc_fd;
    int uart_fd;
    ringbuffer_t rb;
} shared_dev_t;

static int pulse = 0;

// 声明线程函数
void* thread_heart(void *arg);
void* thread_pulse(void *arg);

int main(int argc, char* argv[])
{
    pthread_t heart_tid, pulse_tid;
    pthread_attr_t heart_attr, pulse_attr;
    struct sched_param heart_param, pulse_param;
    int ret;
    shared_dev_t devs;
    
    
     // 初始化环形缓冲区
    ringbuffer_init(&devs.rb);

    //open /dev/adc0 /dev/ttyS1
    devs.uart_fd  = open("/dev/ttyS1", O_RDWR);
    if (devs.uart_fd  < 0) {
      printf("Failed to open /dev/ttyS1\n");
      return -1;
    }
    
    // 打开 ADC
    devs.adc_fd = open("/dev/adc0", O_RDONLY);
    if (devs.adc_fd < 0) {
      printf("Failed to open /dev/adc0\n");
      return -1;
    }
   
    // // 初始化线程属性
    // pthread_attr_init(&heart_attr);
    // pthread_attr_init(&pulse_attr);


    // // 设置线程调度策略为 SCHED_FIFO（NuttX 实时调度）
    // pthread_attr_setschedpolicy(&heart_attr, SCHED_FIFO);
    // pthread_attr_setschedpolicy(&pulse_attr, SCHED_FIFO);

    // // 设置线程优先级
    // heart_param.sched_priority = 100;  // 采集线程优先级
    // pulse_param.sched_priority = 80;  // 分析发送线程优先级更高

    // pthread_attr_setschedparam(&heart_attr, &heart_param);
    // pthread_attr_setschedparam(&pulse_attr, &pulse_param);

    // // 使用我们设置的优先级
    // pthread_attr_setinheritsched(&heart_attr, PTHREAD_EXPLICIT_SCHED);
    // pthread_attr_setinheritsched(&pulse_attr, PTHREAD_EXPLICIT_SCHED);

    // 创建采集线程
    ret = pthread_create(&heart_tid,  NULL, thread_heart, NULL);

    //ret = pthread_create(&heart_tid,  &heart_attr, thread_heart, &devs);
    if (ret != 0)
    {
        printf("Error creating thread_heart\n");
        return -1;
    }
    printf("Success creating thread_heart\n");


    // 创建线程2
    ret = pthread_create(&pulse_tid, NULL, thread_pulse,NULL);

    //ret = pthread_create(&pulse_tid, &pulse_attr, thread_pulse, &devs);
    if (ret != 0)
    {
        printf("Error creating thread_pulse\n");
        return -1;
    }
    printf("Success creating thread_pulse\n");


    // 等待线程结束
    pthread_join(heart_tid, NULL);
    pthread_join(pulse_tid, NULL);
    return 0;
}

void* thread_heart(void *arg)
{
    // printf("Success creating thread_heart\n");
    // shared_dev_t *devs = (shared_dev_t *)arg;

    // ssize_t nbytes;
    // struct adc_msg_s sample[samplesSize];  // 最多读取 4 个样本
    // int nsamples;

    // while (1) {

    //     // 读取数据
    //     nbytes = read(devs->adc_fd, sample, sizeof(sample));
    //     if (nbytes < 0) {
    //         printf("ADC read failed\n");
    //         break;
    //     }

    //     // 处理采样结果
    //     nsamples = nbytes / sizeof(struct adc_msg_s);
    //     for (int i = 0; i < nsamples; i++) {
    //         uint16_t data = sample[i].am_data;
    //         printf("Channel %d: %d\n", sample[i].am_channel, data);
            
    //         if (pulse == 1) {
    //             ringbuffer_write(&devs->rb, (uint8_t)data);
    //         }
    //         else{
    //             char buf[16];
    //             int len = snprintf(buf, sizeof(buf), "%d\n", data);
    //             write(devs->uart_fd, buf, len);
    //         }
    //     }
    // }

    return NULL; 
}

void* thread_pulse(void *arg)
{
    printf("Success creating thread_pulse\n");
    // shared_dev_t *devs = (shared_dev_t *)arg;
    
    // while (1) {
    //     uint8_t data = ringbuffer_read(&devs->rb);

    //     // 串口发送格式化字符串（可改成更复杂逻辑）
    //     char buf[16];
    //     int len = snprintf(buf, sizeof(buf), "%d\n", data);
    //     write(devs->uart_fd, buf, len);

    //     // 模拟数据处理逻辑
    //     dataprocesser((char *)&data);
    // }
    
    return NULL;
}
