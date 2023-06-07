/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 14:04:37 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/07 14:56:16 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	fill(t_game *game)
{
	int		cpy;
	int		cpx;
	int		offset;
	int		i;
	t_pos	o;

	i = 0;
	if (game->tears->dir != 0 && game->tears->is_active == 0)
		create_tears(game, game->tears->dir);
	if (game->tears->is_active != 0)
		game->tears->is_active ++;
	if (game->tears->is_active == 5)
		game->tears->is_active = 0;
	move_tears(game);
	reset_tears(game, 0);
	reset_lanims(game, 0);
	reset_picks(game);
	o = game->offset;
	display_game(game);
	if (game->player->dirx == 0 && game->player->diry == 0
		&& game->player->cur != 6
		&& (game->player->invicibility == 0 || game->player->invicibility > 20))
		game->player->cur = 0;
	if (game->nb_enemies == 0)
		game->maps[game->act_pos.y][game->act_pos.x].is_end = 1;
	game->frame ++;
	cpx = game->player->px + 1;
	cpy = game->player->py + 1;
	game->sprites = anim(game->sprites, game);
	if (game->frame == 60)
		game->frame = 0;
	check_picks(game);
	if (game->player->invicibility != 0)
		game->player->invicibility ++;
	if (game->player->invicibility == 40)
		game->player->invicibility = 0;
	if (game->map.map[cpy][cpx] == 'E' - 48 && game->is_win)
		game->player->cine = 2;
	if (game->nbc == game->player->coin)
		game->is_win = 1;
	offset = 0;
	while (i < game->nb_enemies)
	{
		if (game->enemies[i]->px == cpx && game->enemies[i]->py == cpy - 1)
			player_hit(game);
		game->enemies[i]->cx = approach(game->enemies[i]->cx,
				game->enemies[i]->px * 64, 2);
		game->enemies[i]->cy = approach(game->enemies[i]->cy,
				game->enemies[i]->py * 64 + 64, 2);
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->enemies[i]->anims[game->enemies[i]->cur]->img,
			game->enemies[i]->cx + o.x, game->enemies[i]->cy - 5 + o.y);
		if (game->enemies[i]->type == 'G')
			mlx_put_image_to_window(game->mlx, game->mlx_win,
				game->enemies[i]->anims[4]->img,
				game->enemies[i]->cx + o.x, game->enemies[i]->cy + o.y);
		i ++;
	}
	check_enemies(game);
	if ((game->player->invicibility / 4) % 2 == 0)
		display_player(game);
	if (game->map.map[game->player->py + 1][game->player->px + 1] == 'D' - 48
		&& game->nb_enemies == 0)
	{
		if (game->player->py == 7)
			restart(game, choose_map(game, 0, 1), 0);
		else if (game->player->py == -1)
			restart(game, choose_map(game, 0, -1), 0);
		else if (game->player->px == 13)
			restart(game, choose_map(game, 1, 0), 0);
		else if (game->player->px == -1)
			restart(game, choose_map(game, -1, 0), 0);
	}
	if (game->player->dirx == 0 && game->player->diry == 0
		&& game->player->is_moving != 0 && game->frame % 3 == 0)
		slide(game);
	return (1);
}

int	exit_game(t_game *game)
{
	exit (1);
	return (1);
}

t_game	*restart(t_game *game, char *map, int complete)
{
	t_pos	size;
	t_pos	player;

	game->nbc = 0;
	game->player->coin = 0;
	game->player->cur = 0;
	game->nb_enemies = 0;
	game->is_win = 0;
	game->frame = 0;
	game->select = 0;
	game->sprites->trapdoor = get_anim(game, "sprite/trapdoor/tile", 6, 0);
	game->player->anims[6] = get_anim(game, "sprite/isaac/death/tile", 4, 0);
	game->player->anims[7] = get_anim(game, "sprite/isaac/end/tile", 4, 0);
	game->sprites->penny = get_anim(game, "sprite/penny/tile", 6, 1);
	free(game->enemies);
	game->player->cine = 0;
	reset_tears(game, 1);
	if (complete == 1)
		game->player->nbmv = 0;
	else
	{
		player.x = game->player->px;
		player.y = game->player->py;
		if (player.x <= 0)
			player.x = 12;
		else if (player.x >= 12)
			player.x = 0;
		if (player.y <= 0)
			player.y = 6;
		else if (player.y >= 6)
			player.y = 0;
	}
	get_map(map, game);
	size.x = 1088;
	size.y = 704;
	if ((game->map.col + 1) * 64 > size.x)
		size.x = (game->map.col + 1) * 64;
	if (game->map.row * 64 > size.y)
		size.y = game->map.row * 64;
	game->offset.x = (size.x - (game->map.col + 1) * 64) / 2;
	game->offset.y = (size.y - (game->map.row * 64)) / 2;
	if (game->maps[game->act_pos.y][game->act_pos.x].is_end == 1)
		game->nb_enemies = 0;
	game->enemies = malloc(sizeof(t_enemy) * game->nb_enemies + 1);
	game = get_elem(game);
	game->sprites->door = getd_anims(game);
	game->player->py = player.y;
	game->player->px = player.x;
	game = init_pos(game);
	return (game);
}

//game->maps[y][x].type = 1;

int	main(void)
{
	t_game	*game;
	void	*params;
	t_pos	size;

	game = malloc(sizeof(t_game));
	game->mlx = mlx_init();
	game->nbc = 0;
	game = init_player(game);
	game->nb_enemies = 0;
	game->is_win = 0;
	game->frame = 0;
	game->scene = 0;
	game->select = 0;
	game->tears = malloc(sizeof(t_tears));
	game->tears->next = 0;
	game->lanims = malloc(sizeof(t_lanims));
	game->lanims->next = 0;
	game->tears->dir = 0;
	game->act_pos.x = 4;
	game->act_pos.y = 4;
	game->realf = 0;
	get_maps(game);
	choose_map(game, 0, 0);
	get_map(game->map_name, game);
	game->enemies = malloc(sizeof(t_enemy) * game->nb_enemies + 1);
	game = get_elem(game);
	game = init_pos(game);
	size.x = 1088;
	size.y = 704;
	if ((game->map.col + 1) * 64 > size.x)
		size.x = (game->map.col + 1) * 64;
	if (game->map.row * 64 > size.y)
		size.y = game->map.row * 64;
	game->offset.x = (size.x - (game->map.col + 1) * 64) / 2;
	game->offset.y = (size.y - ((game->map.row) * 64)) / 2;
	game->mlx_win = mlx_new_window(game->mlx,
			size.x, size.y, "So Long");
	game->sprites = get_sprites(game);
	mlx_hook(game->mlx_win, 2, (1L << 0), key_manager, game);
	mlx_hook(game->mlx_win, 3, (1L << 1), relinput, game);
	mlx_hook(game->mlx_win, 17, (1L << 0), exit_game, game);
	mlx_loop_hook(game->mlx, scene_manager, game);
	mlx_loop(game->mlx);
}
