/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd_in_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 07:37:10 by sben-tay          #+#    #+#             */
/*   Updated: 2025/01/06 18:12:43 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	alloc_tab_fd(t_game *param, char *file);
static int	get_file_in_tab(t_game *param, int fd);

int	get_fd_in_tab(char *file, t_game *data)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_dprintf(2, "Error\nCould not open map_file\n");
		return (ERROR);
	}
	if (alloc_tab_fd(data, file) == ERROR)
	{
		ft_dprintf(2, "Error\nCould not allocate memory\n");
		close(fd);
		return (ERROR);
	}
	get_file_in_tab(data, fd);
	close(fd);
	return (SUCCESS);
}

static int	alloc_tab_fd(t_game *param, char *file)
{
	size_t	len;

	len = get_size_file(file);
	param->file = malloc(sizeof(char *) * (len + 1));
	if (param->file == NULL)
		return (ERROR);
	return (SUCCESS);
}

static int	get_file_in_tab(t_game *param, int fd)
{
	int	i;

	i = 0;
	while (1)
	{
		param->file[i] = get_next_line(fd);
		if (param->file[i] == NULL)
			break ;
		i++;
	}
	return (SUCCESS);
}
