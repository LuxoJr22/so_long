/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:04:51 by marvin            #+#    #+#             */
/*   Updated: 2023/06/07 14:00:17 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	display_door(t_game *game, int y, int x)
{
	t_pos	o;

	o = game->offset;
	if (y == 0)
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->sprites->door[0]->img, x * 64 - 32 + o.x, y * 64 + o.y - 10);
	if (y == 8)
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->sprites->door[2]->img, x * 64 - 32 + o.x, y * 64 + o.y - 10);
	if (x == 0)
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->sprites->door[1]->img, x * 64 - 32 + o.x, y * 64 + o.y - 10);
	if (x == 14)
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->sprites->door[3]->img, x * 64 - 32 + o.x, y * 64 + o.y - 10);
}

t_anim	**getd_anims(t_game *game)
{
	t_anim	**ret;

	ret = malloc(sizeof(t_anim) * 4);
	ret[0] = malloc(sizeof(t_anim));
	ret[0] = get_anim(game, "sprite/door/up/tile", 5, 0);
	ret[1] = malloc(sizeof(t_anim));
	ret[1] = get_anim(game, "sprite/door/left/tile", 5, 0);
	ret[2] = malloc(sizeof(t_anim));
	ret[2] = get_anim(game, "sprite/door/down/tile", 5, 0);
	ret[3] = malloc(sizeof(t_anim));
	ret[3] = get_anim(game, "sprite/door/right/tile", 5, 0);
	if (game->nb_enemies == 0)
	{
		while (ret[0]->next)
		{
			ret[0] = ret[0]->next;
			ret[1] = ret[1]->next;
			ret[2] = ret[2]->next;
			ret[3] = ret[3]->next;
		}
	}
	return (ret);
}
