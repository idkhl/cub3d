/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_xpm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:24:28 by sben-tay          #+#    #+#             */
/*   Updated: 2025/01/15 14:55:02 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_file_existence(const char *path);

int	check_valid_xpm(t_game *data)
{
	if (check_file_existence(data->parsing.no) == ERROR)
		return (ERROR);
	if (check_file_existence(data->parsing.so) == ERROR)
		return (ERROR);
	if (check_file_existence(data->parsing.we) == ERROR)
		return (ERROR);
	if (check_file_existence(data->parsing.ea) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static int	check_file_existence(const char *path)
{
	int	fd;

	if (ft_strncmp(path + ft_strlen(path) - 4, ".xpm", 4) != 0)
	{
		ft_dprintf(2, "Error\nWrong file extension (.xpm)\n");
		return (ERROR);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_dprintf(2, "Error\n%s", path);
		perror(" ");
		return (ERROR);
	}
	close(fd);
	return (SUCCESS);
}
