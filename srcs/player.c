/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 14:05:52 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/07 17:24:27 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	display_player(t_game *game)
{
	int		offset;
	int		cur;
	t_pos	o;

	offset = 0;
	o = game->offset;
	o.y -= 64;
	o.x -= 32;
	cur = game->player->cur;
	if (cur >= 2 && cur <= 5)
		offset = 16;
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->player->anims[cur]->img, game->player->cx + o.x,
		game->player->cy + offset + o.y);
	if (game->tears->dir == 1 || (game->tears->dir == 0 && cur == 2))
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->player->head->up, game->player->cx + o.x,
			game->player->cy - 5 + o.y);
	if (game->tears->dir == 4 || (game->tears->dir == 0 && cur == 4))
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->player->head->left, game->player->cx + o.x,
			game->player->cy - 5 + o.y);
	if (game->tears->dir == 2 || (game->tears->dir == 0 && cur == 3))
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->player->head->right, game->player->cx + o.x,
			game->player->cy - 5 + o.y);
	if (game->tears->dir == 3 || (game->tears->dir == 0 && cur == 5))
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->player->head->down, game->player->cx + o.x,
			game->player->cy - 5 + o.y);
}

void	slide(t_game *game)
{
	int		y;
	int		x;
	t_pos	max;
	t_pos	min;

	y = game->player->py + 1;
	x = game->player->px + 1;
	max.x = (game->player->cx + 20) / 64;
	max.y = (game->player->cy + 10) / 64;
	min.x = (game->player->cx - 20) / 64;
	min.y = (game->player->cy - 20) / 64;
	if (game->map.map[y + game->player->adiry][x + game->player->adirx] != 1)
	{
		change_pos(game, game->player->adirx, game->player->adiry, 0);
		game->player->is_moving --;
	}
}

t_game	*change_pos(t_game *game, int x, int y, int cur)
{
	t_pos	o;

	o = game->offset;
	if (game->player->dirx != 0 || game->player->diry != 0)
	{
		game->player->is_moving = 3;
		game->player->adirx = x;
		game->player->adiry = y;
	}
	game->player->cx += x * 5;
	game->player->cy += y * 5;
	game->player->py = (game->player->cy) / 64 - 1;
	game->player->px = (game->player->cx) / 64 - 1;
	if (game->player->invicibility == 0 || game->player->invicibility > 20)
		game->player->cur = cur;
	return (game);
}

void	player_hit(t_game *game)
{
	if (game->player->invicibility == 0)
	{
		game->player->cur = 8;
		game->player->health --;
		if (game->player->health == 0)
			game->player->cine = 1;
		game->player->invicibility = 1;
	}
}
