/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 08:40:45 by sben-tay          #+#    #+#             */
/*   Updated: 2025/01/06 17:14:54 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**map_duplicate(char **map)
{
	char	**map_cpy;
	int		i;
	int		x;

	i = 0;
	x = 0;
	while (map[x])
		x++;
	map_cpy = (char **)malloc(sizeof(char *) * (x + 1));
	if (!map_cpy)
	{
		free_split(map);
		return (NULL);
	}
	while (map[i])
	{
		map_cpy[i] = ft_strdup((const char *)map[i]);
		i++;
	}
	map_cpy[i] = NULL;
	return (map_cpy);
}

int	count_zero(char **str)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] == '0')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

void	init_pos_s_n(t_game *data, char **map, int x, int y)
{
	if (map[x][y] == 'N')
	{
		data->parsing.pos_x = x;
		data->parsing.pos_y = y;
		data->parsing.direction = 'N';
		data->parsing.nb_pos++;
	}
	if (map[x][y] == 'S')
	{
		data->parsing.pos_x = x;
		data->parsing.pos_y = y;
		data->parsing.direction = 'S';
		data->parsing.nb_pos++;
	}
}

void	init_pos_e_w(t_game *data, char **map, int x, int y)
{
	if (map[x][y] == 'E')
	{
		data->parsing.pos_x = x;
		data->parsing.pos_y = y;
		data->parsing.direction = 'E';
		data->parsing.nb_pos++;
	}
	if (map[x][y] == 'W')
	{
		data->parsing.pos_x = x;
		data->parsing.pos_y = y;
		data->parsing.direction = 'W';
		data->parsing.nb_pos++;
	}
}
