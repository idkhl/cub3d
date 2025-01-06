/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 06:46:29 by sben-tay          #+#    #+#             */
/*   Updated: 2025/01/06 17:14:54 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_pos_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

static bool	is_char_map(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'W'
		|| c == 'E' || c == ' ')
		return (true);
	if (ft_isspace(c))
		return (true);
	return (false);
}

int	replace_space_by_set(char **str, const char set)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (ft_isspace(str[i][j]))
				str[i][j] = set;
			j++;
		}
		j--;
		str[i][j] = '\n';
		j++;
		str[i][j] = '\0';
		i++;
	}
	return (SUCCESS);
}

int	check_valid_map_char(t_game *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->parsing.map[i])
	{
		j = 0;
		while (data->parsing.map[i][j])
		{
			if (!is_char_map(data->parsing.map[i][j]))
			{
				ft_putendl_fd("Error\nInvalid char in map.", 2);
				return (ERROR);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	check_space_in_map(t_game *data)
{
	int		i;
	int		j;
	char	**map;

	i = 0;
	map = data->parsing.map;
	while (data->parsing.map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_isspace(map[i][j]))
			{
				if (map[i][j] == '\t')
				{
					ft_putendl_fd("Error\nInvalid space in map.", 2);
					return (ERROR);
				}
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}
