/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_fd_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 10:12:03 by sben-tay          #+#    #+#             */
/*   Updated: 2025/01/15 15:27:53 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool check_valid_param(char *str);

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
		if (!check_valid_param(data->file[i] + j))
			return (ft_putendl_fd("Error\nInvalid param in file", 2),
				ERROR);
		i++;
	}
	return (SUCCESS);
}

static bool check_valid_param(char *str)
{
		if (*str == '\0')
		return (true);
	if (*str == 'N' && !ft_strncmp(str, "NO", 2))
		return (true);
	if (*str == 'S' && !ft_strncmp(str, "SO", 2))
		return (true);
	if (*str == 'W' && !ft_strncmp(str, "WE", 2))
		return (true);
	if (*str == 'E' && !ft_strncmp(str, "EA", 2))
		return (true);
	if (*str == 'F' && !ft_strncmp(str, "F", 1))
		return (true);
	if (*str == 'C'&& !ft_strncmp(str, "C", 1))
		return (true);
	if (*str == '1' && !ft_strncmp(str, "1", 1))
		return (true);
	if (*str ==  '0' && !ft_strncmp(str, "0", 1))
		return (true);
	return (false);
}
