#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <nuttx/analog/adc.h>

int main(int argc, FAR char *argv[])
{
  int fd;
  ssize_t nbytes;
  struct adc_msg_s sample[4];  // 最多读取 4 个样本
  int nsamples;
  int i;

  // 打开 ADC 设备
  fd = open("/dev/adc0", O_RDONLY);
  if (fd < 0)
    {
      printf("Failed to open /dev/adc0\n");
      return -1;
    }

  // 读取数据
  nbytes = read(fd, sample, sizeof(sample));
  if (nbytes < 0)
    {
      printf("ADC read failed\n");
      close(fd);
      return -2;
    }

  // 处理采样结果
  nsamples = nbytes / sizeof(struct adc_msg_s);
  for (i = 0; i < nsamples; i++)
    {
      printf("Channel %d: %d\n", sample[i].am_channel, sample[i].am_data);
    }

  close(fd);
  return 0;
}
