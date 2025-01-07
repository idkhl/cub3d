/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 06:19:45 by sben-tay          #+#    #+#             */
/*   Updated: 2025/01/07 17:27:28 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	handle_parsing(int argc, char **argv, t_game *data)
{
	if (argc != 2)
	{
		ft_dprintf(2, "Error\nWrong number of arguments\n");
		return (ERROR);
	}
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4) != 0)
	{
		ft_dprintf(2, "Error\nWrong file extension\n");
		return (ERROR);
	}
	if (get_fd_in_tab(argv[1], data) == ERROR)
		return (ERROR);
	if (check_valid_fd(data) == ERROR)
		return (ERROR);
	if (get_value_fd(data) == ERROR)
		return (ERROR);
	if (get_map_in_tab(data) == ERROR)
		return (ERROR);
	if (check_valid_xpm(data) == ERROR)
		return (ERROR);
	if (check_valid_map(data) == ERROR)
		return (ERROR);
	return (SUCCESS);
}


int	check_file_existence(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0) // Échec d'ouverture
	{
		perror("Error opening file");
		return (0); // Le fichier n'existe pas ou n'est pas accessible
	}
	close(fd); // Ferme le fichier
	return (1); // Le fichier existe
}