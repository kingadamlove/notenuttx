#include <nuttx/config.h>

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/ioctl.h>

#include <nuttx/ioexpander/gpio.h>

void show_usage(FAR const char *progname)
{
  fprintf(stderr, "Usage:\n");
  fprintf(stderr, "  %s -r <driver-path>       # Read pin type and value\n", progname);
  fprintf(stderr, "  %s -s <0|1> <driver-path> # Set pin output value\n", progname);
}

int main(int argc, FAR char *argv[])
{
  int fd, ret;
  FAR const char *devpath;
  enum gpio_pintype_e pintype;
  bool value;

  if (argc < 3)
    {
      show_usage(argv[0]);
      return EXIT_FAILURE;
    }

  /* 读取模式 */
  if (strcmp(argv[1], "-r") == 0)
    {
      devpath = argv[2];
      fd = open(devpath, O_RDWR);
      if (fd < 0)
        {
          fprintf(stderr, "ERROR: Failed to open %s: %d\n", devpath, errno);
          return EXIT_FAILURE;
        }

      ret = ioctl(fd, GPIOC_PINTYPE, (unsigned long)((uintptr_t)&pintype));
      if (ret < 0)
        {
          fprintf(stderr, "ERROR: Failed to read pin type: %d\n", errno);
          close(fd);
          return EXIT_FAILURE;
        }

      ret = ioctl(fd, GPIOC_READ, (unsigned long)((uintptr_t)&value));
      if (ret < 0)
        {
          fprintf(stderr, "ERROR: Failed to read pin value: %d\n", errno);
          close(fd);
          return EXIT_FAILURE;
        }

      printf("GPIO Type:  %d\n", pintype);
      printf("GPIO Value: %u\n", value);
      close(fd);
    }

  /* 设置模式 */
  else if (strcmp(argv[1], "-s") == 0)
    {
      if (argc < 4)
        {
          show_usage(argv[0]);
          return EXIT_FAILURE;
        }

      int val = atoi(argv[2]);
      if (val != 0 && val != 1)
        {
          fprintf(stderr, "ERROR: Invalid value: %s\n", argv[2]);
          return EXIT_FAILURE;
        }

      value = (val != 0);
      devpath = argv[3];

      fd = open(devpath, O_RDWR);
      if (fd < 0)
        {
          fprintf(stderr, "ERROR: Failed to open %s: %d\n", devpath, errno);
          return EXIT_FAILURE;
        }

      ret = ioctl(fd, GPIOC_WRITE, (unsigned long)value);
      if (ret < 0)
        {
          fprintf(stderr, "ERROR: Failed to write pin value: %d\n", errno);
          close(fd);
          return EXIT_FAILURE;
        }

      printf("GPIO value set to: %d\n", value);
      close(fd);
    }

  else
    {
      show_usage(argv[0]);
      return EXIT_FAILURE;
    }

  return EXIT_SUCCESS;
}
