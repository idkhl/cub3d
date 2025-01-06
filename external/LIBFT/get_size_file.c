/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 06:58:06 by sben-tay          #+#    #+#             */
/*   Updated: 2024/12/30 12:29:36 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

size_t	get_size_file(char *file)
{
	size_t	size;
	char	*line;
	int		fd;

	size = 0;
	line = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		ft_free((void **)&line);
		size++;
	}
	close(fd);
	return (size);
}
 