#ifndef MOUSE_LIB_H
#define MOUSE_LIB_H

/* struct for binary matrix */
struct binary_matrix {
    unsigned width, height;
    unsigned** matrix;
};

// struct for char matrix
struct char_matrix {
    unsigned width, height;
    char** matrix;
};


/*  OOP for my_mouse 'Solving algorithm' */
struct mouse {
    struct binary_matrix* bin;
    struct char_matrix* chm;

    struct binary_matrix* (*const find_path) (const char* filename, struct binary_matrix* , struct char_matrix*);
    unsigned (*const replace) (struct binary_matrix* , struct char_matrix*);
    void (*const print) (struct char_matrix*, unsigned);
};

extern const struct MouseClass {
    struct mouse (*New) ();
} Mouse;

#endif // MOUSE_LIB_H