#include "pa1010d.h"

#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

void print_sentence(char* buf, int len)
{
    for (int i = 0; i < len; ++i) {
        printf("%c", buf[i]);
    }
}

void get_sentence(int fd, char* buf, int *len)
{
    char msg_char;
    while (1) {
        read(fd, &msg_char, 1);
        if (msg_char == '$') {
            *len = 0;
            while (1) {
                read(fd, &msg_char, 1);
                if (*len > 11 && buf[*len - 1] == '\r' && msg_char == '\n') {
                    buf[*len] = msg_char;
                    ++(*len);
                    break;
                } else if (buf[*len - 1] != '\r' && msg_char == '\n') {
                    continue;
                }
                buf[*len] = msg_char;
                ++(*len);
            }
            break;
        }
    }
}
