CFAGS = -Wall -Wextra -Werror

SRC = queue.c readline.c map_parser.c mouse.c main.c

OUT = my_mouse

my_mouse: $(SRC)
	gcc ${CFAGS} -o ${OUT} $(SRC)

fclean:
	rm -f ${OUT} *.o