/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 12:32:21 by marvin            #+#    #+#             */
/*   Updated: 2023/06/07 13:59:59 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	**get_hearts(t_game *game)
{
	void	**hearts;
	int		imgh;
	int		imgw;

	hearts = malloc(sizeof(void *) * 3);
	hearts[0] = mlx_xpm_file_to_image(game->mlx,
			"sprite/health/full.xpm", &imgw, &imgh);
	hearts[1] = mlx_xpm_file_to_image(game->mlx,
			"sprite/health/half.xpm", &imgw, &imgh);
	hearts[2] = mlx_xpm_file_to_image(game->mlx,
			"sprite/health/empty.xpm", &imgw, &imgh);
	return (hearts);
}

void	display_life(t_game *game)
{
	int	place;
	int	i;

	place = 0;
	i = 0;
	while (i < game->player->health / 2)
	{
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->sprites->hearts[0], i * 50, 0);
		i ++;
	}
	if (game->player->health % 2 == 1)
	{
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->sprites->hearts[1], i * 50, 0);
		i ++;
	}
	while (i * 2 < game->player->maxhealth)
	{
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->sprites->hearts[2], i * 50, 0);
		i ++;
	}
}
