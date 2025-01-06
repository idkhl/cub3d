/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_fd_utils3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 15:12:25 by sben-tay          #+#    #+#             */
/*   Updated: 2025/01/06 17:14:54 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_and_mark(char **file, int i, int j, bool *dejavu);
static int	mark_dejavu(bool *dejavu, int index);

bool	valid_char_map(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i + 1] && str[i] == 'E' && str[i + 1] == 'A')
			return (false);
		if (str[i + 1] && str[i] == 'W' && str[i + 1] == 'E')
			return (false);
		if (str[i + 1] && str[i] == 'S' && str[i + 1] == 'O')
			return (false);
		if (str[i + 1] && str[i] == 'N' && str[i + 1] == 'O')
			return (false);
		if (str[i] == 'F')
			return (false);
		if (str[i] == 'C')
			return (false);
		if (str[i] == '1' || str[i] == '0' || str[i] == '\0'
			|| ft_isspace(str[i]))
			return (true);
		i++;
	}
	if (!str[i] || str[i] == ft_isspace(str[i]))
		return (true);
	return (false);
}

int	check_double_param(t_game *data)
{
	static bool	dejavu[6] = {false};
	int			i;
	int			j;

	i = 0;
	while (data->file[i])
	{
		j = 0;
		while (data->file[i][j] && ft_isspace(data->file[i][j]))
			j++;
		if (check_and_mark(data->file, i, j, dejavu) == ERROR)
			return (ft_putendl_fd("Error\nDouble param detected!", 2),
				ERROR);
		i++;
	}
	return (SUCCESS);
}

static int	check_and_mark(char **file, int i, int j, bool *dejavu)
{
	if (file[i][j] == 'N' && file[i][j + 1] == 'O')
		return (mark_dejavu(dejavu, 0));
	if (file[i][j] == 'S' && file[i][j + 1] == 'O')
		return (mark_dejavu(dejavu, 1));
	if (file[i][j] == 'W' && file[i][j + 1] == 'E')
		return (mark_dejavu(dejavu, 2));
	if (file[i][j] == 'E' && file[i][j + 1] == 'A')
		return (mark_dejavu(dejavu, 3));
	if (file[i][j] == 'F' && file[i][j + 1] == ' ')
		return (mark_dejavu(dejavu, 4));
	if (file[i][j] == 'C' && file[i][j + 1] == ' ')
		return (mark_dejavu(dejavu, 5));
	return (SUCCESS);
}

static int	mark_dejavu(bool *dejavu, int index)
{
	if (dejavu[index])
		return (ERROR);
	dejavu[index] = true;
	return (SUCCESS);
}
