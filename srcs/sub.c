/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 12:10:04 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/07 17:02:56 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_pos	a_pos(t_pos act, int x, int y)
{
	t_pos	pos;

	free(&act);
	pos.x = x;
	pos.y = y;
	return (pos);
}

t_pos	c_pos(int x, int y)
{
	t_pos	pos;

	pos.x = x;
	pos.y = y;
	return (pos);
}

int	approach(int current, int goal, int delta)
{
	int	sign;

	sign = 1;
	if (current - goal > 0)
		sign = -1;
	if (current != goal)
	{
		if ((goal - current) * sign < delta)
			return (goal);
		return (current + (delta * sign));
	}
	else
		return (goal);
}

void	*get_img(t_game *game, char *file)
{
	int	imgw;
	int	imgh;

	return (mlx_xpm_file_to_image(game->mlx, file, &imgw, &imgh));
}
