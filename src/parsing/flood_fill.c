/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 08:20:41 by sben-tay          #+#    #+#             */
/*   Updated: 2025/01/15 16:34:02 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	flood_fill(char **map, int x, int y, t_game *data);

int	flood_fill_map_and_island(t_game *data)
{
	char	**map;
	int		x;
	int		y;

	x = 0;
	map = map_duplicate(data->parsing.map);
	if (!map)
		return (ERROR);
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == '0' || is_pos_char(map[x][y]))
			{
				if (flood_fill(map, x, y, data))
					return (free_split(map), ERROR);
			}
			y++;
		}
		x++;
	}
	free_split(map);
	return (SUCCESS);
}

bool	flood_fill(char **map, int x, int y, t_game *data)
{
	int	res;

	res = 0;
	if (map[x][y] == '1' || map[x][y] == '*')
		return (0);
	init_pos_s_n(data, map, x, y);
	init_pos_e_w(data, map, x, y);
	if (data->parsing.nb_pos > 1)
		return (ft_putendl_fd("Error\nToo many starting positions.", 2), 1);
	if (map[x][y] == '0' || is_pos_char(map[x][y]) || !map[x][y])
		map[x][y] = '*';
	if (map[x][y] == ' ' || map[x][y] == '\n' || map[x][y] == '\0')
		return (ft_putendl_fd("Error\nMap is not closed.", 2), 1);
	res = flood_fill(map, x - 1, y, data);
	if (res)
		return (res);
	res = flood_fill(map, x + 1, y, data);
	if (res)
		return (res);
	res = flood_fill(map, x, y - 1, data);
	if (res)
		return (res);
	res = flood_fill(map, x, y + 1, data);
	return (res);
}
