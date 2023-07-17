#include "lib.h"

int main(int ac, char** av) {

    if (ac < 2) {
        printf("Please valid map name\n");
        return 1;
    }
    if(access(av[1], F_OK) != 0) {
        printf("File doesn't exist\n");
        return 1;
    }
    struct mouse m1 = Mouse.New();
    struct binary_matrix *visited = m1.find_path(av[1], m1.bin, m1.chm);
    if(visited == 0)
        return 1; // road not found

    unsigned all_s = m1.replace(visited, m1.chm);
    m1.print(m1.chm, all_s);
    
    return 0;
}