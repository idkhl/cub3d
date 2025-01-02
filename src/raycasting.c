/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:58:38 by idakhlao          #+#    #+#             */
/*   Updated: 2025/01/02 14:01:40 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_textures(t_game *game)
{
	int	i;

	game->textures->texture_h = 64;
	game->textures->texture_w = 64;
	game->textures[0].img_data = mlx_xpm_file_to_image(game->mlx, \
	"textures/bluestone.xpm", &game->textures[0].texture_w, \
	&game->textures[0].texture_h); //NO
	game->textures[1].img_data = mlx_xpm_file_to_image(game->mlx, \
	"textures/eagle.xpm", &game->textures[1].texture_w, \
	&game->textures[1].texture_h); //SO
	game->textures[2].img_data = mlx_xpm_file_to_image(game->mlx, \
	"textures/purplestone.xpm", &game->textures[2].texture_w, \
	&game->textures[2].texture_h); //WE
	game->textures[3].img_data = mlx_xpm_file_to_image(game->mlx, \
	"textures/redbrick.xpm", &game->textures[3].texture_w, \
	&game->textures[3].texture_h); //EA
	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img_data == NULL)
		{
			printf("Error loading texture %d\n", i);
			exit(1);
		}
		game->textures[i].addr = mlx_get_data_addr(game->textures[i].img_data, \
		&game->textures[i].bpp, &game->textures[i].size_line, \
		&game->textures[i].endian);
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
	// game->map.hit = 0;
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
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	handle_movement(game);
	mlx_destroy_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		return (printf("Error\nImage fail\n"), -1);
	game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, \
	&game->endian);
	return (0);
}
