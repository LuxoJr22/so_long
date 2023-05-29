/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:47:30 by mboyer            #+#    #+#             */
/*   Updated: 2023/02/08 18:14:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_enemies(t_game *game)
{
	int 	i;
	int 	enemies;
	int		act_tab;
	t_enemy	**tab;
	t_pos	pos;
	

	i = 0;
	enemies = 0;
	act_tab = 0;
	while (i < game->nb_enemies)
	{
		if (game->enemies[i]->is_dead == 0)
			enemies ++;
		i ++;
	}
	if (enemies != game->nb_enemies)
	{
		tab = malloc(sizeof(t_enemy) * enemies);
		i = 0;
		while (i < game->nb_enemies)
		{
			if (game->enemies[i]->is_dead)
			{
				pos.x = game->enemies[i]->cx;
				pos.y = game->enemies[i]->cy;
				create_lanims(game, get_anim(game, "sprite/death/tile", 10, 0), pos, 1);
				free(game->enemies[i]);
			}
			else
			{
				tab[act_tab] = game->enemies[i];
				act_tab ++;
			}
			i ++;
		}
		game->nb_enemies = enemies;
		game->enemies = tab;
	}
}

int	init_enemies(t_game *game, int i_m, t_pos pos)
{
	game->enemies[i_m] = malloc(sizeof(t_enemy));
	game->enemies[i_m]->py = pos.y - 1;
	game->enemies[i_m]->px = pos.x;
	game->enemies[i_m]->sens = 2;
	game->enemies[i_m]->is_dead = 0;
	game->enemies[i_m]->type = game->map.map[pos.y][pos.x] + 48;
	game->enemies[i_m]->health = 20;
	if (game->map.map[pos.y][pos.x] == 'H' - 48)
		game->enemies[i_m]->sens = 1;
	if (game->enemies[i_m]->type == 'V' || game->enemies[i_m]->type == 'H')
		game->enemies[i_m]->anims = getm_anims(game);
	if (game->enemies[i_m]->type == 'G')
	{
		game->enemies[i_m]->anims = getg_anims(game);
		game->enemies[i_m]->gy = game->enemies[i_m]->py * 64 + 64;
		game->enemies[i_m]->gx = game->enemies[i_m]->px * 64;
		game->enemies[i_m]->health = 10;
	}
	game->enemies[i_m]->dir = 1;
	return (i_m + 1);
}

t_anim	**getg_anims(t_game *game)
{
	t_anim	**ret;

	ret = malloc(sizeof(t_anim) * 5);
	ret[0] = malloc(sizeof(t_anim));
	ret[0] = get_anim(game, "sprite/gaper/left/tile", 4, 1);
	ret[1] = malloc(sizeof(t_anim));
	ret[1] = get_anim(game, "sprite/gaper/right/tile", 4, 1);
	ret[2] = malloc(sizeof(t_anim));
	ret[2] = get_anim(game, "sprite/gaper/down/tile", 4, 1);
	ret[3] = malloc(sizeof(t_anim));
	ret[3] = get_anim(game, "sprite/gaper/up/tile", 4, 1);
	ret[4] = malloc(sizeof(t_anim));
	ret[4] = get_anim(game, "sprite/gaper/head/tile", 1, 0);
	return (ret);
}

void	move_gaper(t_game *game, int i)
{
	int px;
	int py;

	py = game->enemies[i]->py;
	px = game->enemies[i]->px;
	if (game->enemies[i]->cy == game->enemies[i]->py * 64 + 64 && game->enemies[i]->cx == game->enemies[i]->px * 64)
	{
		game->enemies[i]->cur = 1;
		if (game->enemies[i]->py < game->player->py && game->map.map[py + 2][px] != 1)
			game->enemies[i]->py ++;
		else if (game->enemies[i]->py > game->player->py && game->map.map[py][px] != 1)
			game->enemies[i]->py --;
	}
	if (game->enemies[i]->cx == game->enemies[i]->px * 64 && game->enemies[i]->cy == game->enemies[i]->py * 64 + 64)
	{
		game->enemies[i]->cur = 1;
		if (game->enemies[i]->px < game->player->px + 1 && game->map.map[py + 1][px + 1] != 1)
			game->enemies[i]->px ++;
		else if (game->enemies[i]->px > game->player->px + 1 && game->map.map[py + 1][px - 1] != 1)
			game->enemies[i]->px --;
	}
}

t_game	*enemies_move(t_game *game)
{
	int	i;
	int	posx;
	int	posy;

	i = 0;
	while (i < game->nb_enemies)
	{
		posx = game->enemies[i]->px;
		posy = game->enemies[i]->py;
		if (game->enemies[i]->type == 'H' || game->enemies[i]->type == 'V' && game->frame == 1)
		{
			if (game->enemies[i]->sens == 1)
			{
				if (!(game->map.map[posy + 1][posx - 1] == 1
					&& game->map.map[posy + 1][posx + 1] == 1))
				{
					if (game->map.map[posy + 1][posx + game->enemies[i]->dir] == 1)
						game->enemies[i]->dir *= -1;
					game->enemies[i]->px += game->enemies[i]->dir;
					game->enemies[i]->cur = 1;
					if (game->enemies[i]->dir == -1)
						game->enemies[i]->cur = 0;
				}
			}
			if (game->enemies[i]->sens == 2)
			{
				if (!(game->map.map[posy + 2][posx] == 1
					&& game->map.map[posy][posx] == 1))
				{
					if (game->map.map[posy + 1 + game->enemies[i]->dir][posx] == 1)
						game->enemies[i]->dir *= -1;
					game->enemies[i]->py += game->enemies[i]->dir;
					game->enemies[i]->cur = 2;
					if (game->enemies[i]->dir == -1)
						game->enemies[i]->cur = 3;
				}
			}
		}
		if (game->enemies[i]->type == 'G')
			move_gaper(game, i);
		i ++;
	}
	return (game);
}
