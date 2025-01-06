/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_first_last_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 13:25:44 by sben-tay          #+#    #+#             */
/*   Updated: 2025/01/06 17:14:54 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_good_char(char c);

int	check_first_last_line(t_game *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->parsing.map[0][j])
	{
		if (!is_good_char(data->parsing.map[0][j]))
		{
			printf("ici ?\n");
			return (ft_putendl_fd("Error\nMap is not closed.", 2), ERROR);
		}
		j++;
	}
	j = 0;
	while (data->parsing.map[i])
		i++;
	while (data->parsing.map[i - 1][j])
	{
		if (!is_good_char(data->parsing.map[i - 1][j]))
		{
			printf("ici ?\n");
			return (ft_putendl_fd("Error\nMap is not closed.", 2), ERROR);
		}
		j++;
	}
	return (SUCCESS);
}

static bool	is_good_char(char c)
{
	return (c == '1' || c == ' ' || c == '\n' || c == '\0');
}
