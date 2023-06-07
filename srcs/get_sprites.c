/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:42:33 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/07 17:28:10 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	menu->menu = get_img(game, "sprite/menu/menu.xpm");
	menu->ui = get_img(game, "sprite/menu/ui.xpm");
	menu->continues = get_img(game, "sprite/menu/continue.xpm");
	menu->leaderboard = get_img(game, "sprite/menu/leaderboard.xpm");
	menu->select = get_img(game, "sprite/menu/select.xpm");
	menu->options = get_img(game, "sprite/menu/options.xpm");
	menu->exit = get_img(game, "sprite/menu/exit.xpm");
	menu->leaderpage = get_img(game, "sprite/menu/leaderpage.xpm");
	menu->death = get_img(game, "sprite/menu/death.xpm");
	menu->map_text = get_img(game, "sprite/menu/map.xpm");
	menu->back_select = get_img(game, "sprite/menu/keyconfigmenue.xpm");
	menu->challenge = get_img(game, "sprite/menu/challenge.xpm");
	menu->optionsmenu = get_img(game, "sprite/menu/optionsmenu.xpm");
	return (menu);
}

t_sprites	*get_sprites(t_game *game)
{
	t_sprites	*sprite;

	sprite = malloc(sizeof(t_sprites));
	sprite->black = get_img(game, "sprite/black.xpm");
	sprite->ground = get_img(game, "sprite/walls/map1.xpm");
	sprite->rock = get_img(game, "sprite/rocks/tile001.xpm");
	sprite->score = get_img(game, "sprite/ui/score.xpm");
	sprite->coin = get_img(game, "sprite/ui/coin.xpm");
	sprite->door = getd_anims(game);
	sprite->tears = get_img(game, "sprite/tears/tears.xpm");
	sprite->penny = get_anim(game, "sprite/penny/tile", 6, 1);
	sprite->trapdoor = get_anim(game, "sprite/trapdoor/tile", 6, 0);
	sprite->menu = get_menu(game);
	sprite->numbers = get_number(game, "sprite/number/white/");
	sprite->numbersb = get_number(game, "sprite/number/black/");
	sprite->hearts = get_hearts(game);
	return (sprite);
}

void	**get_number(t_game *game, char *folder)
{
	int		i;
	void	**imgs;

	i = 0;
	imgs = malloc(sizeof(void *) * 10);
	while (i < 10)
	{
		imgs[i] = get_img(game,
				ft_strjoin(ft_strjoin(folder, ft_itoa(i)), ".xpm"));
		i++;
	}
	return (imgs);
}

void	init_player_sprites(t_game *game)
{
	game->player->anims = malloc(sizeof(t_anim) * 10);
	game->player->head = malloc(sizeof(t_head));
	game->player->anims[0] = get_anim(game, "sprite/isaac/idle/tile", 1, 0);
	game->player->anims[1] = get_anim(game, "sprite/isaac/thumb/tile", 1, 0);
	game->player->anims[2] = get_anim(game, "sprite/isaac/up/tile", 10, 1);
	game->player->anims[3] = get_anim(game, "sprite/isaac/left/tile", 10, 1);
	game->player->anims[4] = get_anim(game, "sprite/isaac/right/tile", 10, 1);
	game->player->anims[5] = get_anim(game, "sprite/isaac/down/tile", 10, 1);
	game->player->anims[6] = get_anim(game, "sprite/isaac/death/tile", 4, 0);
	game->player->anims[7] = get_anim(game, "sprite/isaac/end/tile", 4, 0);
	game->player->anims[8] = get_anim(game, "sprite/isaac/hit/tile", 1, 0);
	game->player->head->up = get_img(game, "sprite/isaac/head/up.xpm");
	game->player->head->down = get_img(game, "sprite/isaac/head/down.xpm");
	game->player->head->left = get_img(game, "sprite/isaac/head/left.xpm");
	game->player->head->right = get_img(game, "sprite/isaac/head/right.xpm");
}
