
#include "lib.h"

char sepatator = '*';
unsigned* get_width_height(int fd)
{
    char* line = readline(fd);
    if (strlen(line) < 3)
    {
        fprintf(stderr, "MAP ERROR");
        return 0;
    }
    static unsigned widht_height[2];
    if (sscanf(line, "%ux%u%c", &widht_height[1], &widht_height[0],
               &sepatator) == 3)
    {
        printf("%s\n", line);
        return widht_height;
    }
    else
    {
        fprintf(stderr, "MAP ERROR");
        return 0;
    }
}

int s_index(char* str, char c)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == c) return i;
    }
    return -1;
}

void convert_binary(struct binary_matrix** bin, char* row, int row_index)
{
    // static int index = 0;
    (*bin)->matrix[row_index] =
        (unsigned*)malloc(sizeof(unsigned) * strlen(row));
    for (unsigned i = 0; i < (*bin)->width; i++)
        (*bin)->matrix[row_index][i] = (row[i] != sepatator);
}

start_target* parser(int fd, struct binary_matrix* bin, struct char_matrix* chm)
{
    if (fd < 0) return 0;

    unsigned* width_height = get_width_height(fd);

    bin->height = width_height[1];  // height 0th index
    bin->width = width_height[0];   // width 1st index
    chm->height = width_height[1];
    chm->width = width_height[0];

    bin->matrix = malloc(sizeof(unsigned*) *
                         bin->height); /* allocate memory to matrixs */
    chm->matrix = malloc(sizeof(char*) * chm->height);

    start_target* st_tg = (start_target*)malloc(
        sizeof(start_target)); /* start and target initialize */

    unsigned curr_row = 0;
    char* line = NULL;
    bool is_start_founded = 0,
         is_target_founded = 0; /* to find two points (start and target) */
    while ((line = readline(fd)) != NULL)
    { /* while lines is exist add it to matrixs */
        if (!is_start_founded)
        {
            int i;
            if ((i = s_index(line, START)) != -1)
            {
                st_tg->start[0] = curr_row; /* set start position */
                st_tg->start[1] = i;
                is_start_founded = true;
            }
        }
        if (!is_target_founded)
        {
            int i;
            if ((i = s_index(line, TARGET)) != -1)
            {
                st_tg->target[0] = curr_row; /* set target position */
                st_tg->target[1] = i;
                is_target_founded = true;
            }
        }

        chm->matrix[curr_row] = strndup(line, chm->width);  // add line to map
        convert_binary(&bin, line, curr_row);  // convert line to binary array
        curr_row++;
        free(line);
    }
    if (!(is_start_founded & is_target_founded))
    {
        fprintf(stderr, "MAP ERROR");
        exit(1);
    }
    return st_tg;
}
