/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_fd_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 10:12:03 by sben-tay          #+#    #+#             */
/*   Updated: 2025/01/06 17:14:54 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_f(t_game *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->file[i])
	{
		j = 0;
		while (data->file[i][j] && ft_isspace(data->file[i][j]))
			j++;
		if (data->file[i][j] == 'F')
		{
			j++;
			while (data->file[i][j] && ft_isspace(data->file[i][j]))
				j++;
			if (check_format_rgb(data->file[i] + j) == ERROR)
				return (ft_putendl_fd("Error\nParam F need RGB format.",
						2), ERROR);
			return (SUCCESS);
		}
		i++;
	}
	return (ft_putendl_fd("Error\nParam F not found.", 2), ERROR);
}

int	check_c(t_game *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->file[i])
	{
		j = 0;
		while (data->file[i][j] && ft_isspace(data->file[i][j]))
			j++;
		if (data->file[i][j] == 'C')
		{
			j++;
			while (data->file[i][j] && ft_isspace(data->file[i][j]))
				j++;
			if (check_format_rgb(data->file[i] + j) == ERROR)
				return (ft_putendl_fd("Error\nParam C need RGB format.",
						2), ERROR);
			return (SUCCESS);
		}
		i++;
	}
	return (ft_putendl_fd("Error\nParam C not found.", 2), ERROR);
}

int	check_map_is_last_param(t_game *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->file[i])
	{
		j = 0;
		while (data->file[i][j] && ft_isspace(data->file[i][j]))
			j++;
		if (data->file[i][j] == '1' || data->file[i][j] == '0')
			break ;
		i++;
	}
	while (data->file[i])
	{
		j = 0;
		while (data->file[i][j] && ft_isspace(data->file[i][j]))
			j++;
		if (!(valid_char_map(data->file[i] + j)))
			return (ft_putendl_fd \
			("Error\nMap is missing or not last param.", \
			2), ERROR);
		i++;
	}
	return (SUCCESS);
}

int	check_format_rgb(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != ',' && !ft_isspace(str[i]))
		{
			if (!ft_isdigit(str[i]))
				return (ERROR);
		}
		if (str[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		return (ERROR);
	return (SUCCESS);
}

int	check_invalid_param(t_game *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->file[i])
	{
		j = 0;
		while (data->file[i][j] && ft_isspace(data->file[i][j]))
			j++;
		if (!valid_char(data->file[i][j]))
			return (ft_putendl_fd("Error\nInvalid param in file", 2),
				ERROR);
		i++;
	}
	return (SUCCESS);
}
