/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:58:38 by idakhlao          #+#    #+#             */
/*   Updated: 2025/01/09 10:27:21 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_raycasting(t_game *game, int x)
{
	game->map.camera_x = 2 * x / (double)WIDTH - 1;
	game->map.raydir_x = game->player.dir_x + game->player.plane_x \
	* game->map.camera_x;
	game->map.raydir_y = game->player.dir_y + game->player.plane_y \
	* game->map.camera_x;
	game->map.map_x = (int)game->player.pos_x;
	game->map.map_y = (int)game->player.pos_y;
}

void	get_rays(t_game *game, int x)
{
	init_raycasting(game, x);
	ray_calc(game);
	dda_loop(game);
	dist_height(game);
	get_textures(game, x);
}

int	raycasting(t_game *game)
{
	int	x;

	x = 0;
	floor_ceiling(game);
	while (x < WIDTH)
	{
		get_rays(game, x);
		x++;
	}
	minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	handle_movement(game);
	mlx_destroy_image(game->mlx, game->img);
	mlx_destroy_image(game->mlx, game->minimap.minimap);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		return (printf("Error\nImage fail\n"), -1);
	game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, \
	&game->endian);
	return (0);
}
