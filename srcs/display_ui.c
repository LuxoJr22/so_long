/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_ui.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:22:50 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/07 14:25:16 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	display_numbers(t_game *game, int nb, void **numbers, t_pos pos)
{
	if (nb < 10)
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			numbers[nb], pos.x, pos.y);
	else if (nb <= 99)
	{
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			numbers[nb % 10], pos.x + 30, pos.y);
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			numbers[nb / 10], pos.x, pos.y);
	}
	else
	{
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			numbers[9], pos.x + 30, pos.y);
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			numbers[9], pos.x, pos.y);
	}
}

void	display_finish(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 0, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 480, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 960, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 0, 270);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 480, 270);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 960, 270);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 0, 540);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 480, 540);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 960, 540);
}

void	display_death(t_game *game)
{
	t_pos	nbpos;

	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 0, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 480, 0);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 0, 270);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->menu, 480, 270);
	mlx_put_image_to_window(game->mlx, game->mlx_win,
		game->sprites->menu->death, 150, 0);
	nbpos.x = 400;
	nbpos.y = 310;
}

//display_numbers(game, game->player->score, game->sprites->numbersb, nbpos);