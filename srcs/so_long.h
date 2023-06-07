/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:05:19 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/07 17:29:00 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <mlx.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>

typedef struct s_pos {
	int	x;
	int	y;
}				t_pos;

typedef struct s_anim {
	void			*img;
	struct s_anim	*next;
}				t_anim;

typedef struct s_head {
	void	*up;
	void	*down;
	void	*left;
	void	*right;
}		t_head;

typedef struct s_enemy {
	t_anim	**anims;
	int		cur;
	int		sens;
	int		dir;
	int		gy;
	int		gx;
	int		px;
	int		py;
	int		cy;
	int		cx;
	int		is_dead;
	int		type;
	float	health;
}		t_enemy;

typedef struct s_pickups {
	t_anim				*anims;
	int					type;
	int					cy;
	int					cx;
	int					is_pick;
	struct s_pickups	*next;
}			t_pickups;

typedef struct s_player {
	t_anim		**anims;
	int			coin;
	int			nbmv;
	int			cy;
	int			cx;
	int			gy;
	int			gx;
	int			px;
	int			py;
	int			cur;
	t_head		*head;
	int			cine;
	int			diry;
	int			dirx;
	int			health;
	int			maxhealth;
	int			invicibility;
	int			is_moving;
	int			adirx;
	int			adiry;
	float		dmg;
}				t_player;

typedef struct s_map {
	int	**map;
	int	row;
	int	col;
}				t_map;

typedef struct s_menu {
	void	*menu;
	void	*options;
	void	*continues;
	void	*leaderboard;
	void	*select;
	void	*exit;
	void	*ui;
	void	*leaderpage;
	void	*death;
	void	*map_text;
	void	*back_select;
	void	*challenge;
	void	*optionsmenu;
}				t_menu;

typedef struct s_sprites {
	void	*black;
	void	*ground;
	void	*wall;
	void	*wallc;
	void	*wallb;
	void	*wallr;
	void	*wall1;
	void	*wallctl;
	void	*wallcbl;
	void	*wallcbr;
	void	*rock;
	t_menu	*menu;
	t_anim	*trapdoor;
	t_anim	*penny;
	void	*score;
	void	*coin;
	void	**numbers;
	void	**numbersb;
	t_anim	**door;
	void	*tears;
	void	**hearts;
}				t_sprites;

typedef struct s_collec {
	int		py;
	int		px;
	int		lx;
	int		ly;
	int		is_active;
}				t_collec;

typedef struct s_room {
	int			is_end;
	int			name;
	t_pickups	*list;
}				t_room;

typedef struct s_tears {
	t_pos			pos;
	t_pos			inertia;
	int				is_active;
	int				dir;
	struct s_tears	*next;
}				t_tears;

typedef struct s_lanims {
	t_anim			*anim;
	t_pos			pos;
	int				frames;
	struct s_lanims	*next;
}				t_lanims;

typedef struct s_game {
	t_enemy		**enemies;
	int			scene;
	t_player	*player;
	t_collec	*collec;
	t_sprites	*sprites;
	int			is_win;
	int			nbc;
	void		*mlx;
	void		*mlx_win;
	int			frame;
	t_map		map;
	int			nb_enemies;
	int			select;
	t_pos		offset;
	char		*map_name;
	t_tears		*tears;
	t_room		**maps;
	t_pos		act_pos;
	int			realf;
	t_lanims	*lanims;
}			t_game;

char		*ft_itoa(int nb);
void		get_map(char *file, t_game *game);
t_sprites	*get_sprites(t_game *game);
char		*ft_strjoin(char *s1, char *s2);
t_sprites	*anim(t_sprites *sprite, t_game *game);
t_anim		*get_anim(t_game *game, char *folder, int nbsprites, int is_loop);
t_game		*get_elem(t_game *game);
t_anim		**getm_anims(t_game *game);
t_game		*enemies_move(t_game *game);
int			move(t_game *game, int diry, int dirx);
t_game		*change_pos(t_game *game, int x, int y, int cur);
int			menu_select(int keycode, t_game *game);
int			key_manager(int keycode, t_game *game);
t_game		*enemies_move(t_game *game);
int			approach(int current, int goal, int delta);
t_game		*init_player(t_game *game);
void		display_game(t_game *game);
void		display_menu(t_game *game);
void		display_finish(t_game *game);
void		display_death(t_game *game);
t_game		*restart(t_game *game, char *map, int complete);
void		display_select(t_game *game);
int			scene_manager(t_game *game);
int			fill(t_game *game);
int			**ft_malloc_map(int **map, int fd, char buf[2]);
void		check_map(t_map map);
int			input(int keycode, t_game *game);
int			input(int keycode, t_game *game);
int			relinput(int keycode, t_game *game);
void		reset_tears(t_game *game, int force);
void		move_tears(t_game *game);
void		create_tears(t_game *game, int dir);
void		check_enemies(t_game *game);
int			init_enemies(t_game *game, int i_m, t_pos pos);
void		display_tears(t_game *game);
void		display_player(t_game *game);
char		*choose_map(t_game *game, int x, int y);
void		reset_tears(t_game *game, int force);
void		display_lanims(t_game *game);
void		create_lanims(t_game *game, t_anim *anim, t_pos pos, int f);
void		reset_lanims(t_game *game, int force);
t_pos		c_pos(int x, int y);
t_anim		**getd_anims(t_game *game);
t_anim		**getg_anims(t_game *game);
void		anim_doors(t_game *game);
void		**get_hearts(t_game *game);
void		display_life(t_game *game);
void		player_hit(t_game *game);
void		display_door(t_game *game, int y, int x);
void		slide(t_game *game);
void		init_pickups(t_game *game, int y, int x, int type);
void		display_picks(t_game *game);
void		check_picks(t_game *game);
void		reset_picks(t_game *game);
void		menu(t_game *game);
void		finish(t_game *game);
void		death(t_game *game);
void		select_map(t_game *game);
void		display_numbers(t_game *game, int nb, void **numbers, t_pos pos);
void		display_finish(t_game *game);
void		display_death(t_game *game);
void		get_maps(t_game *game);
char		*choose_map(t_game *game, int x, int y);
void		init_rooms(t_game *game, int y, int x, int name);
t_game		*init_pos(t_game *game);
t_sprites	*get_sprites(t_game *game);
t_menu		*get_menu(t_game *game);
t_anim		**getm_anims(t_game *game);
t_anim		*get_anim(t_game *game, char *folder, int nbsprites, int is_loop);
void		**get_number(t_game *game, char *folder);
t_pos		a_pos(t_pos act, int x, int y);
void		display_back(t_game *game, t_pos o);
void		*get_img(t_game *game, char *file);
void		init_player_sprites(t_game *game);

#endif
