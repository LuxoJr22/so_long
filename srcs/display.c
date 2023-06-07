/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 14:10:28 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/07 16:53:50 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	display_map(t_game *game, int x, int y, t_pos o)
{
	while (x <= game->map.col)
	{
		while (y < game->map.row)
		{
			if (game->map.map[y][x] == 1 || game->map.map[y][x] == 'D' - 48)
			{
				if (x != 0 && y != 0 && y != game->map.row - 1
					&& x != game->map.col)
					mlx_put_image_to_window(game->mlx, game->mlx_win,
						game->sprites->rock, x * 64 + o.x, y * 64 + o.y);
			}
			if (game->map.map[y][x] == 'D' - 48)
				display_door(game, y, x);
			if (game->map.map[y][x] == 'E' - 48)
				mlx_put_image_to_window(game->mlx, game->mlx_win,
					game->sprites->trapdoor->img, (x * 64) - 20 + o.x,
					(y * 64) - 20 + o.y);
		y += 1;
		}
	x += 1;
	y = 0;
	}
}

void	display_game(t_game *game)
{
	int		x;
	int		y;
	t_pos	nbpos;
	t_pos	o;

	o = game->offset;
	x = 0;
	y = 0;
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->black, 0, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->black, 350, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->ground, x * 64, y * 64);
	display_map(game, x, y, o);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->score, 280, 0);
	display_picks(game);
	display_tears(game);
	display_lanims(game);
	display_life(game);
	nbpos.x = 410;
	nbpos.y = 10;
	display_numbers(game, game->player->nbmv, game->sprites->numbers, nbpos);
}

void	display_menu(t_game *game)
{
	t_pos	o;

	o.x = 100;
	o.y = 100;
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->ui, -100 + o.x, -50 + o.y);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->continues, 320 + o.x, 60 + o.y);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->challenge, 320 + o.x, 120 + o.y);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->options, 340 + o.x, 220 + o.y);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->select, 300 + o.x, game->select * 80 + 90 + o.y);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->exit, 340 + o.x, 320 + o.y);
}

void	display_select(t_game *game)
{
	int		i;
	t_pos	nbpos;
	t_pos	o;

	o.x = 150;
	o.y = 150;
	i = 0;
	display_back(game, o);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->back_select, 100 + o.x, 50 + o.y);
	while (i < 12)
	{
		nbpos.x = 150 + (i % 4) * 130 + o.x;
		nbpos.y = 100 + (i / 4) * 80 + o.y;
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->sprites->menu->map_text, nbpos.x, nbpos.y);
		nbpos.x += 70;
		i ++;
		display_numbers(game, i, game->sprites->numbersb, nbpos);
	}
}

void	display_back(t_game *game, t_pos o)
{
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 0 + o.x, 0 + o.y);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 480 + o.x, 0 + o.y);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 0 + o.x, 270 + o.y);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 480 + o.x, 270 + o.y);
}
