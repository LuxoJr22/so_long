/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tears.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 08:57:28 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/07 16:38:29 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	display_tears(t_game *game)
{
	t_tears	*tears;

	tears = game->tears->next;
	while (tears)
	{
		mlx_put_image_to_window(game->mlx, game->mlx_win,
			game->sprites->tears, tears->pos.x + 64, tears->pos.y + 80);
		tears = tears->next;
	}
}

void	reset_tears(t_game *game, int force)
{
	t_tears	*first;
	t_tears	*next;

	first = game->tears;
	next = first->next;
	while (next)
	{
		if (next->is_active == 0 || force)
		{
			first->next = next->next;
			next->pos = a_pos(next->pos, next->pos.x - 30, next->pos.y - 30);
			if (!force)
				create_lanims(game, get_anim(game,
						"sprite/tears/splash/tile", 14, 0), next->pos, 1);
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
		game->tears->next = 0;
}

void	change_tears_pos(t_tears *tears)
{
	if (tears->dir == 1)
		tears->pos.y -= 5;
	if (tears->dir == 2)
		tears->pos.x += 5;
	if (tears->dir == 3)
		tears->pos.y += 5;
	if (tears->dir == 4)
		tears->pos.x -= 5;
	tears->pos.x += tears->inertia.x;
	tears->pos.y += tears->inertia.y;
}

void	move_tears(t_game *game)
{
	t_tears	*tears;
	int		i;

	tears = game->tears->next;
	while (tears)
	{
		i = 0;
		change_tears_pos(tears);
		if (tears->pos.x > 900 || tears->pos.x < 32
			|| tears->pos.y > 500 || tears->pos.y < 32)
			tears->is_active = 0;
		while (i < game->nb_enemies && tears->is_active)
		{
			if (tears->pos.x / 64 == game->enemies[i]->px
				&& tears->pos.y / 64 == game->enemies[i]->py)
			{
				game->enemies[i]->health -= game->player->dmg;
				if (game->enemies[i]->health <= 0)
					game->enemies[i]->is_dead = 1;
				tears->is_active = 0;
			}
			i ++;
		}
		tears = tears->next;
	}
}

void	create_tears(t_game *game, int dir)
{
	t_tears	*tear;
	t_tears	*last;

	tear = malloc(sizeof(t_tears));
	tear->next = 0;
	tear->is_active = 1;
	tear->dir = dir;
	tear->pos.x = game->player->cx;
	tear->pos.y = game->player->cy - 64;
	tear->inertia.y = game->player->diry;
	tear->inertia.x = game->player->dirx;
	last = game->tears->next;
	if (last)
	{
		while (last->next)
			last = last->next;
		last->next = tear;
	}
	else
		game->tears->next = tear;
	game->tears->is_active = 1;
}
