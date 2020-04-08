#include <stdio.h>

#include "simplest_h264_parser.h"

int main(int argc, char **argv)
{
    printf("Hello World!\n");
    printf("argc:%d, argv[0]:%s, argv[1]:%s, argv[2]:%s", argc, argv[0],argv[1],argv[2]);

    if(argc < 2)
        return 0;

    simplest_h264_parser(argv[1]);


    return 0;
}
