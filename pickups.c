/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickups.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 17:39:24 by marvin            #+#    #+#             */
/*   Updated: 2023/02/05 17:39:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	display_picks(t_game *game)
{
	t_pickups *picks;
	t_pos	o;

	o = game->offset;
	picks = game->maps[game->act_pos.y][game->act_pos.x].list->next;
	while (picks)
	{
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->sprites->penny->img, picks->cx + 16 + o.x , picks->cy + 20 + o.y);
		picks = picks->next;
	}
}

void	reset_picks(t_game *game)
{
	t_pickups	*picks;
	t_pickups	*next;
	int cpx;
	int cpy;

	cpx = game->player->px + 1;
	cpy = game->player->py + 1;
	picks = game->maps[game->act_pos.y][game->act_pos.x].list;
	next = picks->next;
	while (next)
	{
		if (next->is_pick == 1 )
		{
			picks->next = next->next;
			create_lanims(game, get_anim(game, "sprite/penny/pick/tile", 9, 0), c_pos(cpx * 64, cpy * 64), 1);
			free(next);
			next = picks->next;
		}
		else
		{
			picks = picks->next;
			next = next->next;
		}
	}	
}

void	check_picks(t_game *game)
{
	t_pickups *picks;

	int x;
	int y;

	y = game->player->cy;
	x = game->player->cx;
	picks = game->maps[game->act_pos.y][game->act_pos.x].list->next;
	while (picks)
	{
		if ((y >= picks->cy + 32 - 20 && y <= picks->cy + 32 + 20) && (x >= picks->cx + 32 - 20 && x <= picks->cx + 32 + 20))
		{
			picks->is_pick = 1;
			game->player->coin ++;
		}
		picks = picks->next;
	}
}

void    init_pickups(t_game *game, int y, int x, int type)
{
	t_pickups	*picks;
	t_pickups	*last;

    picks = malloc(sizeof(t_pickups));
	last = game->maps[game->act_pos.y][game->act_pos.x].list;
	picks->cx = x;
	picks->cy = y;
	picks->type = type;
	picks->next = 0;
	if (last)
	{
		while (last->next)
			last = last->next;
		last->next = picks;
	}
	else
		game->maps[game->act_pos.y][game->act_pos.x].list->next = picks;
}