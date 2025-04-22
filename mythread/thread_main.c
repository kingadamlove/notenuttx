#include <nuttx/config.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

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


void* thread_heart()
{
    printf("Success creating thread_heart\n");
}

void* thread_pulse()
{
    printf("Success creating thread_pulse\n");
}


int main(int argc, char* argv[])
{
    //open /dev/adc0123 /dev/serial01
    
    pthread_t heart_tid, pulse_tid;
    int ret;
    // 创建线程1
    ret = pthread_create(&heart_tid, NULL, thread_heart, NULL);
    if (ret != 0)
    {
        printf("Error creating thread_heart\n");
        return -1;
    }



    // 创建线程2
    ret = pthread_create(&pulse_tid, NULL, thread_pulse, NULL);
    if (ret != 0)
    {
        printf("Error creating thread_pulse\n");
        return -1;
    }


    // 等待线程结束
    pthread_join(heart_tid, NULL);
    pthread_join(pulse_tid, NULL);
    return 0;
}