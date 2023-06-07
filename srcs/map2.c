/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboyer <mboyer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:29:40 by mboyer            #+#    #+#             */
/*   Updated: 2023/06/07 14:58:38 by mboyer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_game	*get_elem(t_game *game)
{
	int	x;
	int	y;
	int	i_m;

	y = 0;
	i_m = 0;
	while (y < game->map.row)
	{
		x = 0;
		while (x < game->map.col)
		{
			if ((game->map.map[y][x] == 38 || game->map.map[y][x] == 24
				|| game->map.map[y][x] == 23)
				&& game->maps[game->act_pos.y][game->act_pos.x].is_end == 0)
				i_m = init_enemies(game, i_m, c_pos(x, y));
			if (game->map.map[y][x] == 'P' - 48)
			{
				game->player->py = y - 1;
				game->player->px = x - 1;
			}
			if (game->map.map[y][x] == 'C' - 48 && game->maps[game->act_pos.y]
				[game->act_pos.x].is_end == 0)
			{
				init_pickups(game, y * 64, x * 64, game->map.map[y][x] + 48);
				game->nbc ++;
			}
			x ++;
		}
		y ++;
	}
	return (game);
}

t_map	map_fill(char buf[2], int fd, int ret, t_game *game)
{
	t_map	map;

	map = game->map;
	while (ret)
	{
		map.col = -1;
		while (ret && buf[0] != '\n')
		{
			if (buf[0] == 'H' || buf[0] == 'V' || buf[0] == 'G')
				game->nb_enemies ++;
			map.col ++;
			map.map[map.row][map.col] = buf[0] - 48;
			ret = read(fd, buf, 1);
		}
		ret = read(fd, buf, 1);
		map.row ++;
	}
	return (map);
}

void	get_map(char *file, t_game *game)
{
	int		fd;
	char	buf[2];
	int		ret;
	t_map	map;

	map = game->map;
	map.row = 0;
	fd = open(file, O_RDONLY);
	map.map = ft_malloc_map(map.map, fd, buf);
	close(fd);
	fd = open(file, O_RDONLY);
	ret = read(fd, buf, 1);
	game->map = map;
	game->map = map_fill(buf, fd, ret, game);
	close(fd);
	check_map(map);
}

void	get_maps(t_game *game)
{
	int		i;

	i = 0;
	game->maps = malloc(sizeof(t_room *) * 7);
	while (i < 7)
	{
		game->maps[i] = malloc(sizeof(t_room) * 7);
		i ++;
	}
	init_rooms(game, 4, 4, 1);
	init_rooms(game, 3, 4, 4);
	init_rooms(game, 2, 4, 2);
	init_rooms(game, 2, 5, 3);
}

char	*choose_map(t_game *game, int x, int y)
{
	game->act_pos.x += x;
	game->act_pos.y += y;
	game->map_name = ft_strjoin("maps/map",
			ft_itoa(game->maps[game->act_pos.y][game->act_pos.x].name));
	game->map_name = ft_strjoin(game->map_name, ".ber");
	return (game->map_name);
}
