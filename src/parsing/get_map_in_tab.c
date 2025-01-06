/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_in_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 16:12:18 by sben-tay          #+#    #+#             */
/*   Updated: 2025/01/06 17:14:54 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	len_map(t_game *data);
static bool	is_char_map(char c);
static char	**first_line(t_game *data);

int	get_map_in_tab(t_game *data)
{
	int		len;
	char	**src;
	int		i;

	len = len_map(data);
	src = first_line(data);
	data->parsing.map = malloc(sizeof(char *) * (len + 2));
	if (data->parsing.map == NULL)
		return (ERROR);
	i = 0;
	while (*src)
	{
		data->parsing.map[i] = ft_strdup(*src);
		if (!data->parsing.map[i])
			return (ERROR);
		src++;
		i++;
	}
	data->parsing.map[i] = NULL;
	return (SUCCESS);
}

static int	len_map(t_game *data)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	len = 0;
	while (data->file[i])
	{
		j = 0;
		while (ft_isspace(data->file[i][j]))
			j++;
		if (is_char_map(data->file[i][j]))
		{
			break ;
		}
		i++;
	}
	while (data->file[i])
	{
		i++;
		len++;
	}
	return (len);
}

static char	**first_line(t_game *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->file[i])
	{
		j = 0;
		while (ft_isspace(data->file[i][j]))
			j++;
		if (is_char_map(data->file[i][j]))
		{
			break ;
		}
		i++;
	}
	return (data->file + i);
}

static bool	is_char_map(char c)
{
	return (c == '1' || c == '0');
}
