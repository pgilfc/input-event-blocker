
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>

#define INPUT_EVENT_DIR "/dev/input/"

int main (int argc, char **argv) {
    int fd;
    char input[50] = INPUT_EVENT_DIR;

    if (getuid() != 0){
		printf("Not running as root!");
        return -1;
    }

    if(argc < 2){
        printf("Missing input event!");
        return -2;
    }

	strcat(input, argv[1]);

    if(access(input, F_OK) != 0) {
        printf("No such input event!");
        return -3;
    }

    fd = open(input, O_RDONLY);

    if(ioctl(fd, EVIOCGRAB, 1)){
        printf("Couldn't grab input event!");
        return -4;
    }

    while(1){}
}

