
SRCS = so_long.c map.c map2.c sprites.c sub.c display.c key_manager.c player.c enemies.c scene_manager.c tears.c lanims.c door.c life.c pickups.c

OBJS = ${SRCS:.c=.o}

NAME = so_long

.c.o:
	gcc -I/usr/include -Imlx_linux -O3 -c $< -o ${<:.c=.o}


${NAME}: ${OBJS}
	gcc ${OBJS} -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o ${NAME}

all:	${NAME}

clean:
	rm -f ${OBJS}

fclean:	clean
	rm -f ${NAME}

re:	fclean all
