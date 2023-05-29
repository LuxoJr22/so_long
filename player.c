/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 14:05:52 by mboyer            #+#    #+#             */
/*   Updated: 2023/02/08 23:33:35 by marvin           ###   ########.fr       */
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
		game->player->anims[cur]->img, game->player->cx + o.x, game->player->cy + offset + o.y);
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
		//change_pos(game, game->player->adirx * game->player->is_moving, game->player->adiry * game->player->is_moving, 0);
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

t_game	*init_player(t_game *game)
{
	int	imgh;
	int	imgw;

	game->player = malloc(sizeof(t_player));
	game->player->anims = malloc(sizeof(t_anim) * 10);
	game->player->head = malloc(sizeof(t_head));
	game->player->anims[0] = get_anim(game, "sprite/isaac/idle/tile", 1, 0);
	game->player->anims[1] = get_anim(game, "sprite/isaac/thumb/tile", 1, 0);
	game->player->anims[2] = get_anim(game, "sprite/isaac/up/tile", 10, 1);
	game->player->anims[3] = get_anim(game, "sprite/isaac/left/tile", 10, 1);
	game->player->anims[4] = get_anim(game, "sprite/isaac/right/tile", 10, 1);
	game->player->anims[5] = get_anim(game, "sprite/isaac/down/tile", 10, 1);
	game->player->anims[6] = get_anim(game, "sprite/isaac/death/tile", 4, 0);
	game->player->anims[7] = get_anim(game, "sprite/isaac/end/tile", 4, 0);
	game->player->anims[8] = get_anim(game, "sprite/isaac/hit/tile", 1, 0);
	game->player->head->up = mlx_xpm_file_to_image(game->mlx,
			"sprite/isaac/head/up.xpm", &imgw, &imgh);
	game->player->head->down = mlx_xpm_file_to_image(game->mlx,
			"sprite/isaac/head/down.xpm", &imgw, &imgh);
	game->player->head->left = mlx_xpm_file_to_image(game->mlx,
			"sprite/isaac/head/left.xpm", &imgw, &imgh);
	game->player->head->right = mlx_xpm_file_to_image(game->mlx,
			"sprite/isaac/head/right.xpm", &imgw, &imgh);
	game->player->coin = 0;
	game->player->nbmv = 0;
	game->player->cur = 0;
	game->player->cine = 0;
	game->player->dirx = 0;
	game->player->diry = 0;
	game->player->invicibility = 0;
	game->player->health = 6;
	game->player->maxhealth = 6;
	game->player->is_moving = 0;
	game->player->adirx = 0;
	game->player->adiry = 0;
	game->player->dmg = 50;
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