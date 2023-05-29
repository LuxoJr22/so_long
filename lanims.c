/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lanims.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:24:33 by marvin            #+#    #+#             */
/*   Updated: 2023/01/23 12:24:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void reset_lanims(t_game *game, int force)
{
	t_lanims *first;
	t_lanims *next;

	first = game->lanims;
	next = first->next;
	while(next)
	{
		if (next->anim->next == 0 || force)
		{
			first->next = next->next;
			free(next);
			next = first->next;
		}
		else
		{
			first = first->next;
			next = next->next;
		}
	}
	if (force)
		game->lanims->next = 0;
}

void	display_lanims(t_game *game)
{
	t_lanims *lanims;

	lanims = game->lanims->next;
	while (lanims)
	{
        mlx_put_image_to_window(game->mlx, game->mlx_win,
                lanims->anim->img, lanims->pos.x + 64, lanims->pos.y + 80);
        if (game->frame % lanims->frames == 0)
            lanims->anim = lanims->anim->next;
        lanims = lanims->next;
	}
}

void	create_lanims(t_game *game, t_anim *anims, t_pos pos, int f)
{
	t_lanims	*lanim;
    t_lanims    *last;

	lanim = malloc(sizeof(t_lanims));
	lanim->next = 0;
    lanim->frames = f;
	lanim->pos = pos;
    lanim->anim = anims;
    last = game->lanims->next;
    if (last)
    {
        while (last->next)
            last = last->next;
	    last->next = lanim;
    }
    else
        game->lanims->next = lanim;
}