/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:18:39 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/07 14:26:16 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	menu(t_game *game)
{
	display_menu(game);
}

void	finish(t_game *game)
{
	restart(game, game->map_name, 1);
	game->scene = 0;
	display_finish(game);
}

void	death(t_game *game)
{
	display_death(game);
}

void	select_map(t_game *game)
{
	display_select(game);
}
