/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:35:05 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/07 17:28:32 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_rooms(t_game *game, int y, int x, int name)
{
	game->maps[y][x].name = name;
	game->maps[y][x].is_end = 0;
	game->maps[y][x].list = malloc(sizeof(t_pickups));
	game->maps[y][x].list->next = 0;
}

t_game	*init_pos(t_game *game)
{
	int		i_e;

	i_e = 0;
	while (i_e < game->nb_enemies)
	{
		game->enemies[i_e]->cy = game->enemies[i_e]->py * 64 + 64;
		game->enemies[i_e]->cx = game->enemies[i_e]->px * 64;
		i_e ++;
	}
	game->player->cy = game->player->py * 64 + 96;
	game->player->cx = game->player->px * 64 + 96;
	return (game);
}

int	init_enemies(t_game *game, int i_m, t_pos pos)
{
	game->enemies[i_m] = malloc(sizeof(t_enemy));
	game->enemies[i_m]->py = pos.y - 1;
	game->enemies[i_m]->px = pos.x;
	game->enemies[i_m]->sens = 2;
	game->enemies[i_m]->is_dead = 0;
	game->enemies[i_m]->type = game->map.map[pos.y][pos.x] + 48;
	game->enemies[i_m]->health = 20;
	if (game->map.map[pos.y][pos.x] == 'H' - 48)
		game->enemies[i_m]->sens = 1;
	if (game->enemies[i_m]->type == 'V' || game->enemies[i_m]->type == 'H')
		game->enemies[i_m]->anims = getm_anims(game);
	if (game->enemies[i_m]->type == 'G')
	{
		game->enemies[i_m]->anims = getg_anims(game);
		game->enemies[i_m]->gy = game->enemies[i_m]->py * 64 + 64;
		game->enemies[i_m]->gx = game->enemies[i_m]->px * 64;
		game->enemies[i_m]->health = 10;
	}
	game->enemies[i_m]->dir = 1;
	return (i_m + 1);
}

t_game	*init_player(t_game *game)
{
	game->player = malloc(sizeof(t_player));
	init_player_sprites(game);
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
