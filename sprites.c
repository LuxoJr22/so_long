/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 10:34:08 by mboyer            #+#    #+#             */
/*   Updated: 2023/01/28 23:57:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_sprites	*anim(t_sprites *sprite, t_game *game)
{
	int	cur;
	int	ce;
	int	i;

	i = -1;
	cur = game->player->cur;
	if (game->frame % 5 == 0)
	{
		if (game->frame < 35)
			sprite->penny = sprite->penny->next;
		if (game->is_win && sprite->trapdoor->next)
			sprite->trapdoor = sprite->trapdoor->next;
		if (cur == 2 || cur == 3 || cur == 4 || cur == 5)
			game->player->anims[cur] = game->player->anims[cur]->next;
	}
	if (game->frame % 8 == 0)
	{
		while (++i < game->nb_enemies)
		{
			ce = game->enemies[i]->cur;
			game->enemies[i]->anims[ce] = game->enemies[i]->anims[ce]->next;
		}
	}
	//if (game->frame == 1)
	game = enemies_move(game);
	if (game->nb_enemies == 0 && game->sprites->door[0]->next && game->frame % 8 == 0)
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

void	**get_number(t_game *game, char *folder)
{
	int		i;
	void	**imgs;
	int		ih;
	int		iw;

	i = 0;
	imgs = malloc(sizeof(void *) * 10);
	while (i < 10)
	{
		imgs[i] = mlx_xpm_file_to_image(game->mlx,
				ft_strjoin(ft_strjoin(folder, ft_itoa(i)), ".xpm"), &iw, &ih);
		i++;
	}
	return (imgs);
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

t_anim	**getm_anims(t_game *game)
{
	t_anim	**ret;

	ret = malloc(sizeof(t_anim) * 5);
	ret[0] = malloc(sizeof(t_anim));
	ret[0] = get_anim(game, "sprite/charger/left/tile", 4, 1);
	ret[1] = malloc(sizeof(t_anim));
	ret[1] = get_anim(game, "sprite/charger/right/tile", 4, 1);
	ret[2] = malloc(sizeof(t_anim));
	ret[2] = get_anim(game, "sprite/charger/down/tile", 4, 1);
	ret[3] = malloc(sizeof(t_anim));
	ret[3] = get_anim(game, "sprite/charger/up/tile", 4, 1);
	ret[4] = malloc(sizeof(t_anim));
	ret[4] = get_anim(game, "sprite/death/tile", 4, 0);
	return (ret);
}

t_menu	*get_menu(t_game *game)
{
	t_menu	*menu;
	int		imgh;
	int		imgw;

	menu = malloc(sizeof(t_menu));
	menu->menu = mlx_xpm_file_to_image(game->mlx,
			"sprite/menu/menu.xpm", &imgw, &imgh);
	menu->ui = mlx_xpm_file_to_image(game->mlx,
			"sprite/menu/ui.xpm", &imgw, &imgh);
	menu->continues = mlx_xpm_file_to_image(game->mlx,
			"sprite/menu/continue.xpm", &imgw, &imgh);
	menu->leaderboard = mlx_xpm_file_to_image(game->mlx,
			"sprite/menu/leaderboard.xpm", &imgw, &imgh);
	menu->select = mlx_xpm_file_to_image(game->mlx,
			"sprite/menu/select.xpm", &imgw, &imgh);
	menu->options = mlx_xpm_file_to_image(game->mlx,
			"sprite/menu/options.xpm", &imgw, &imgh);
	menu->exit = mlx_xpm_file_to_image(game->mlx,
			"sprite/menu/exit.xpm", &imgw, &imgh);
	menu->leaderpage = mlx_xpm_file_to_image(game->mlx,
			"sprite/menu/leaderpage.xpm", &imgw, &imgh);
	menu->death = mlx_xpm_file_to_image(game->mlx,
			"sprite/menu/death.xpm", &imgw, &imgh);
	menu->map_text = mlx_xpm_file_to_image(game->mlx,
			"sprite/menu/map.xpm", &imgh, &imgw);
	menu->back_select = mlx_xpm_file_to_image(game->mlx,
			"sprite/menu/keyconfigmenue.xpm", &imgh, &imgw);
	menu->challenge = mlx_xpm_file_to_image(game->mlx,
			"sprite/menu/challenge.xpm", &imgh, &imgw);
	menu->optionsmenu = mlx_xpm_file_to_image(game->mlx,
			"sprite/menu/optionsmenu.xpm", &imgh, &imgw);
	return (menu);
}

t_sprites	*get_sprites(t_game *game)
{
	int			imgw;
	int			imgh;
	t_sprites	*sprite;

	sprite = malloc(sizeof(t_sprites));
	sprite->black = mlx_xpm_file_to_image(game->mlx,
			"sprite/black.xpm", &imgw, &imgh);
	sprite->ground = mlx_xpm_file_to_image(game->mlx,
			"sprite/walls/map1.xpm", &imgw, &imgh);
	sprite->rock = mlx_xpm_file_to_image(game->mlx,
			"sprite/rocks/tile001.xpm", &imgw, &imgh);
	sprite->score = mlx_xpm_file_to_image(game->mlx,
			"sprite/ui/score.xpm", &imgh, &imgw);
	sprite->coin = mlx_xpm_file_to_image(game->mlx,
			"sprite/ui/coin.xpm", &imgh, &imgw);
	sprite->door = getd_anims(game);
	sprite->tears = mlx_xpm_file_to_image(game->mlx,
			"sprite/tears/tears.xpm", &imgh, &imgw);
	sprite->penny = get_anim(game, "sprite/penny/tile", 6, 1);
	sprite->trapdoor = get_anim(game, "sprite/trapdoor/tile", 6, 0);
	sprite->menu = get_menu(game);
	sprite->numbers = get_number(game, "sprite/number/white/");
	sprite->numbersb = get_number(game, "sprite/number/black/");
	sprite->hearts = get_hearts(game);
	return (sprite);
}
