#include "pa1010d.h"

#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define I2C_DEV "/dev/i2c-1"
#define I2C_ADDR 0x10
#define MAX_NMEA 82

int main()
{
    int fd;
    char gps_buffer[MAX_NMEA];  // max NMEA message size

    if ((fd = open(I2C_DEV, O_RDWR)) < 0) {
        perror("Failed to open I2C bus");
        return 1;
    }
    if (ioctl(fd, I2C_SLAVE_FORCE, I2C_ADDR) < 0) {
        perror("Failed to set slave addreess");
        close(fd);
        return 1;
    }

    int msg_len;
    while (1) {
        get_sentence(fd, gps_buffer, &msg_len);
        print_sentence(gps_buffer, msg_len);
    }

    printf("Starting reads\n");
    return 0;
}
