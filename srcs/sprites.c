/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:34:08 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/07 17:25:22 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	short_anims(t_sprites *sprite, t_game *game, int cur)
{
	if (game->frame < 35)
		sprite->penny = sprite->penny->next;
	if (game->is_win && sprite->trapdoor->next)
		sprite->trapdoor = sprite->trapdoor->next;
	if (cur == 2 || cur == 3 || cur == 4 || cur == 5)
		game->player->anims[cur] = game->player->anims[cur]->next;
}

t_sprites	*anim(t_sprites *sprite, t_game *game)
{
	int	cur;
	int	ce;
	int	i;

	i = -1;
	cur = game->player->cur;
	if (game->frame % 5 == 0)
		short_anims(sprite, game, cur);
	if (game->frame % 8 == 0)
	{
		while (++i < game->nb_enemies)
		{
			ce = game->enemies[i]->cur;
			game->enemies[i]->anims[ce] = game->enemies[i]->anims[ce]->next;
		}
	}
	game = enemies_move(game);
	if (game->nb_enemies == 0 && game->sprites->door[0]->next
		&& game->frame % 8 == 0)
		anim_doors(game);
	return (sprite);
}

void	anim_doors(t_game *game)
{
	game->sprites->door[0] = game->sprites->door[0]->next;
	game->sprites->door[1] = game->sprites->door[1]->next;
	game->sprites->door[2] = game->sprites->door[2]->next;
	game->sprites->door[3] = game->sprites->door[3]->next;
}

t_anim	*get_anim(t_game *game, char *folder, int nbsprites, int is_loop)
{
	int		i;
	t_anim	*anim;
	t_anim	*first;
	t_anim	*temp;
	t_pos	p;

	i = 0;
	anim = 0;
	while (i < nbsprites)
	{
		temp = malloc(sizeof(t_anim));
		if (anim)
			anim->next = temp;
		else
			first = temp;
		temp->img = mlx_xpm_file_to_image(game->mlx,
				ft_strjoin(ft_strjoin(folder, ft_itoa(i)), ".xpm"), &p.x, &p.y);
		anim = temp;
		i++;
	}
	if (is_loop)
		anim->next = first;
	else
		anim->next = 0;
	return (first);
}
