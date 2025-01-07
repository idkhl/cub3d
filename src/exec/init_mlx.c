/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:05:22 by sben-tay          #+#    #+#             */
/*   Updated: 2025/01/07 10:16:42 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		return (ft_dprintf(2, "Error\nMLX failed\n"), ERROR);
	}
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	if (!game->win)
	{
		return (ft_dprintf(2, "Error\nWindow fail\n"), ERROR);
	}
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
	{
		return (ft_dprintf(2, "Error\nImage fail\n"), ERROR);
	}
	game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, \
			&game->endian);
	if (!game->addr)
	{
		return (ft_dprintf(2, "Error\nData_addr fail\n"), ERROR);
	}
	return (0);
}
