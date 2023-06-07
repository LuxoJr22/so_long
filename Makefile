
SRCS = srcs/so_long.c srcs/map.c srcs/map2.c srcs/sprites.c srcs/sub.c srcs/display.c srcs/key_manager.c srcs/player.c srcs/enemies.c srcs/scene_manager.c\
		srcs/tears.c srcs/lanims.c srcs/door.c srcs/life.c srcs/pickups.c srcs/scene.c srcs/display_ui.c srcs/init.c srcs/get_sprites.c srcs/lib.c

OBJS = ${SRCS:.c=.o}

NAME = so_long

.c.o:
	gcc -I/usr/include -Imlx_linux -O3 -c $< -o ${<:.c=.o}


${NAME}: ${OBJS}
	gcc ${OBJS} -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit -o ${NAME}



all:	${NAME}

clean:
	rm -f ${OBJS}

fclean:	clean
	rm -f ${NAME}

re:	fclean all
