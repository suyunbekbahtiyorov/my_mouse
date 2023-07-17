#include "lib.h"

const int sides_col[] = {0, -1, 1, 0};
const int sides_row[] = {-1, 0, 0, 1};

start_target* st_tg = NULL;

struct binary_matrix* new_bin(unsigned width, unsigned height)
{
    struct binary_matrix* visited =
        (struct binary_matrix*)malloc(sizeof(struct binary_matrix));
    visited->matrix = (unsigned**)malloc(sizeof(unsigned*) * height);
    for (unsigned i = 0; i < height; i++)
        visited->matrix[i] = malloc(sizeof(unsigned) * width);
    visited->width = width;
    visited->height = height;
    return visited;
}

bool is_valid(struct binary_matrix* bin, int x, int y)
{
    return (x >= 0 && y >= 0 && x < (int)bin->width && y < (int)bin->height &&
            bin->matrix[y][x] == 1);
}

struct binary_matrix* find_path(const char* filename, struct binary_matrix* bin,
                                struct char_matrix* chm)
{
    int fd = open(filename, O_RDONLY);
    st_tg = parser(fd, bin, chm);
    struct binary_matrix* visited = new_bin(bin->width, bin->height);

    struct queue q1 = Queue.New();
    q1.push_back(&(q1.data),
                 new_linked_list(st_tg->start[1], st_tg->start[0], 0));
    while (!q1.is_empty(&(q1.data)))
    {
        linked_list* curr = q1.data;
        locator* curr_loc = curr->loc;
        if (curr_loc->x == st_tg->target[1] && curr_loc->y == st_tg->target[0])
            return visited;  // if path founded return path
        for (int i = 0; i < 4; i++)
        {
            int x = (int)curr_loc->x + sides_col[i];
            int y = (int)curr_loc->y + sides_row[i];
            /* check is valid index and not visited index */
            if (is_valid(bin, x, y) && visited->matrix[y][x] == 0)
            {
                q1.push_back(&(q1.data),
                             new_linked_list(x, y, curr->num_step + 1));
                visited->matrix[y][x] = curr->num_step + 1;
            }
        }
        q1.pop(&(q1.data));
    }
    // puts("Manzil topilmadi");
    return 0;
}

void get_next_step(struct binary_matrix* bin, locator* curr_loc,
                   unsigned last_step)
{
    for (int i = 0; i < 4; i++)
    {
        int x = (int)curr_loc->x + sides_col[i];
        int y = (int)curr_loc->y + sides_row[i];
        if (bin->matrix[y][x] == last_step - 1 && bin->matrix[y][x] != 0)
        {
            curr_loc->x = x;
            curr_loc->y = y;
            break;
        }
    }
}

unsigned replace(struct binary_matrix* bin, struct char_matrix* chm)
{
    unsigned last_step = bin->matrix[st_tg->target[0]][st_tg->target[1]];
    // printf("%u\n", last_step);
    unsigned all_steps = last_step;
    locator* curr_loc = malloc(sizeof(locator));
    curr_loc->y = st_tg->target[0];
    curr_loc->x = st_tg->target[1];
    while (last_step > 0)
    {
        get_next_step(bin, curr_loc, last_step);
        (chm)->matrix[curr_loc->y][curr_loc->x] = 'o';
        last_step--;  // decrement last step
    }
    free(curr_loc);
    return all_steps - 1;
}

void print(struct char_matrix* chm, unsigned all_s)
{
    if (chm == 0) return;
    for (unsigned y = 0; y < chm->height; y++)
    {
        fprintf(stdout, "%s\n", chm->matrix[y]);
    }
    fprintf(stdout, "%u STEPS!\n", all_s);
}

struct mouse NewMouse()
{
    struct binary_matrix* bin = malloc(sizeof(struct binary_matrix));
    struct char_matrix* chm = malloc(sizeof(struct char_matrix));
    return (struct mouse){
        .bin = bin,
        .chm = chm,

        .find_path = &find_path,
        .replace = &replace,
        .print = &print,
    };
}

const struct MouseClass Mouse = {
    .New = &NewMouse,
};