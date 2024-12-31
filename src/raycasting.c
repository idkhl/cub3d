/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:58:38 by idakhlao          #+#    #+#             */
/*   Updated: 2024/12/31 16:21:07 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	reset_player_move(t_game *game)
{
	game->player.up = 0;
	game->player.down = 0;
	game->player.left = 0;
	game->player.right = 0;
	game->player.r_right = 0;
	game->player.r_left = 0;
}

void	init_textures(t_game *game)
{
	game->textures->texture_h = 64;
	game->textures->texture_w = 64;
	game->textures[0].img_data = mlx_xpm_file_to_image(game->mlx, "textures/bluestone.xpm", &game->textures[0].texture_w, &game->textures[0].texture_h);
	game->textures[1].img_data = mlx_xpm_file_to_image(game->mlx, "textures/eagle.xpm", &game->textures[1].texture_w, &game->textures[1].texture_h);
	game->textures[2].img_data = mlx_xpm_file_to_image(game->mlx, "textures/purplestone.xpm", &game->textures[2].texture_w, &game->textures[2].texture_h);
	game->textures[3].img_data = mlx_xpm_file_to_image(game->mlx, "textures/redbrick.xpm", &game->textures[3].texture_w, &game->textures[3].texture_h);
	int i = 0;
	while (i < 4)
	{
		if (game->textures[i].img_data == NULL)
		{
			printf("Error loading texture %d\n", i);
			exit(1);
		}
		game->textures[i].addr = mlx_get_data_addr(game->textures[i].img_data, &game->textures[i].bpp, &game->textures[i].size_line, &game->textures[i].endian);
		i++;
	}
}

void	init_raycasting(t_game *game, int x)
{
	game->map.camera_x = 2 * x / (double)WIDTH - 1;
	game->map.raydir_x = game->player.dir_x + game->player.plane_x \
	* game->map.camera_x;
	game->map.raydir_y = game->player.dir_y + game->player.plane_y \
	* game->map.camera_x;
	game->map.map_x = (int)game->player.pos_x;
	game->map.map_y = (int)game->player.pos_y;
	game->map.sidedist_x = 0;
	game->map.sidedist_y = 0;
	game->map.deltadist_x = 0;
	game->map.deltadist_y = 0;
	game->map.perpwalldist = 0;
	game->map.step_x = 0;
	game->map.step_y = 0;
	game->map.hit = 0;
	game->map.side = 0;
	game->map.line_height = 0;
	game->map.draw_start = 0;
	game->map.draw_end = 0;
	game->map.tex_num = 0;
	game->map.wall_x = 0;
	game->map.tex_x = 0;
	game->map.tex_y = 0;
	game->map.step = 0;
	game->map.tex_pos = 0;
}

void	get_rays(t_game *game, int x)
{
	init_raycasting(game, x);
	ray_calc(game);
	dda_loop(game);
	dist_height(game);
	get_textures(game, x);

	// int color = 0;

	// if (game->map.map[game->map.map_x][game->map.map_y] == 1)
	// 	color = rgb(255, 0, 0);
	// else if (game->map.map[game->map.map_x][game->map.map_y] == 2)
	// 	color = rgb(0, 255, 0);
	// else if (game->map.map[game->map.map_x][game->map.map_y] == 3)
	// 	color = rgb(0, 0, 255);
	// else if (game->map.map[game->map.map_x][game->map.map_y] == 4)
	// 	color = rgb(255, 255, 255);
	// else
	// 	color = rgb(255, 255, 0);
	// if (game->map.side == 1)
	// {
	// 	color /= 1.5;
	// }
	// vertical_line(game, x, color);
}

int	raycasting(t_game *game)
{
	int x;

	x = 0;
	floor_ceiling(game);
	while (x < WIDTH)
	{
		get_rays(game, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	handle_movement(game);
	mlx_destroy_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		return (printf("Error\nImage fail\n"), -1);
	game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	reset_player_move(game);
	return (0);
}
