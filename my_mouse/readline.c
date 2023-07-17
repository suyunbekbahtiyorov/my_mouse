#include "lib.h"

char* readline(int fd)
{
    if (fd < 0) return NULL;
    char buff[1000] = {0};
    int res, index = 0;
    char c;
    while ((res = read(fd, &c, 1)) > -1)
    {
        if (res == 0 && index == 0)  // check end of file
            return NULL;
        else if (c == '\n' || res == 0)  // checking newline or end of file
            break;
        else if (index == 999)  // checking index out of range
            break;
        else
            buff[index++] = c;
    }
    char* line = (char*)malloc(index);
    strncpy(line, buff, index);
    return line;
}