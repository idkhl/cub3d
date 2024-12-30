/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:58:38 by idakhlao          #+#    #+#             */
/*   Updated: 2024/12/30 17:28:53 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	rgb(int r, int g, int b)
{
    return (0 << 24 | r << 16 | g << 8 | b);
}

void	vertical_line(t_game *game, int x, int color)
{
	if (x > WIDTH || x < 0)
		return ;
	while (game->map.draw_start <= game->map.draw_end)
	{
		put_pixel(game, x, game->map.draw_start, color);
		game->map.draw_start++;
	}
}

void	floor_ceiling(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < HEIGHT / 2)
	{
		j = 0;
		while (j < WIDTH)
		{
			put_pixel(game, j, i, rgb(183, 225, 253));
			j++;
		}
		i++;
	}
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			put_pixel(game, j, i, rgb(61, 61, 61));
			j++;
		}
		i++;
	}
}

void	reset_player_move(t_game *game)
{
	game->player.up = 0;
	game->player.down = 0;
	game->player.left = 0;
	game->player.right = 0;
	game->player.r_right = 0;
	game->player.r_left = 0;
}

void	handle_movement(t_game *game)
{
	double movespeed = 0.08;
	double rotspeed = 0.08;
	if (game->player.up == 1)
	{
		if (game->map.map[(int)(game->player.pos_x + game->player.dir_x * movespeed)][(int)(game->player.pos_y)] == 0)
			game->player.pos_x += game->player.dir_x * movespeed;
		if (game->map.map[(int)(game->player.pos_x)][(int)(game->player.pos_y + game->player.dir_y * movespeed)] == 0)
			game->player.pos_y += game->player.dir_y * movespeed;
	}
	if (game->player.down == 1)
	{
		if (game->map.map[(int)(game->player.pos_x - game->player.dir_x * movespeed)][(int)(game->player.pos_y)] == 0)
			game->player.pos_x -= game->player.dir_x * movespeed;
		if (game->map.map[(int)(game->player.pos_x)][(int)(game->player.pos_y - game->player.dir_y * movespeed)] == 0)
			game->player.pos_y -= game->player.dir_y * movespeed;
	}
	if (game->player.r_right == 1)
	{
		double oldDirX = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(-rotspeed) - game->player.dir_y * sin(-rotspeed);
		game->player.dir_y = oldDirX * sin(-rotspeed) + game->player.dir_y * cos(-rotspeed);

		double oldPlaneX = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(-rotspeed) - game->player.plane_y * sin(-rotspeed);
		game->player.plane_y = oldPlaneX * sin(-rotspeed) + game->player.plane_y * cos(-rotspeed);
	}
	if (game->player.r_left == 1)
	{
		double oldDirX = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(rotspeed) - game->player.dir_y * sin(rotspeed);
		game->player.dir_y = oldDirX * sin(rotspeed) + game->player.dir_y * cos(rotspeed);

		double oldPlaneX = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(rotspeed) - game->player.plane_y * sin(rotspeed);
		game->player.plane_y = oldPlaneX * sin(rotspeed) + game->player.plane_y * cos(rotspeed);
	}
	if (game->player.right == 1)
	{
		if (game->map.map[(int)(game->player.pos_x + game->player.dir_y * (movespeed
				* 2))][(int)game->player.pos_y] == 0)
			game->player.pos_x += game->player.dir_y * movespeed;
		if (game->map.map[(int)game->player.pos_x][(int)(game->player.pos_y - game->player.dir_x
			* (movespeed * 2))] == 0)
			game->player.pos_y -= game->player.dir_x * movespeed;
	}
	if (game->player.left == 1)
	{
		if (game->map.map[(int)(game->player.pos_x - game->player.dir_y * (movespeed
				* 2))][(int)game->player.pos_y] == 0)
			game->player.pos_x -= game->player.dir_y * movespeed;
		if (game->map.map[(int)game->player.pos_x][(int)(game->player.pos_y + game->player.dir_x
			* (movespeed * 2))] == 0)
			game->player.pos_y += game->player.dir_x * movespeed;
	}
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

// void draw_textures(t_game *game, int x)
// {
// 	int	tex_x;
// 	int	tex_y;
// }

void	init_raycasting(t_game *game, int x)
{
	game->map.camera_x = 2 * x / (double)WIDTH - 1;
	game->map.raydir_x = game->player.dir_x + game->player.plane_x * game->map.camera_x;
	game->map.raydir_y = game->player.dir_y + game->player.plane_y * game->map.camera_x;
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
}

void	ray_calc2(t_game *game)
{
	if (game->map.raydir_y < 0)
	{
		game->map.step_y = -1;
		game->map.sidedist_y = (game->player.pos_y - game->map.map_y) * \
		game->map.deltadist_y;
	}
	else
	{
		game->map.step_y = 1;
		game->map.sidedist_y = (game->map.map_y + 1.0 - game->player.pos_y) * \
		game->map.deltadist_y;
	}
}

void	ray_calc(t_game *game)
{
	if (game->map.raydir_x == 0)
		game->map.deltadist_x = 1e30;
	else
		game->map.deltadist_x = fabs(1.0 / game->map.raydir_x);

	if (game->map.raydir_y == 0)
		game->map.deltadist_y = 1e30;
	else
		game->map.deltadist_y = fabs(1.0 / game->map.raydir_y);
	if (game->map.raydir_x < 0)
	{
		game->map.step_x = -1;
		game->map.sidedist_x = (game->player.pos_x - game->map.map_x) \
		* game->map.deltadist_x;
	}
	else
	{
		game->map.step_x = 1;
		game->map.sidedist_x = (game->map.map_x + 1.0 - game->player.pos_x) \
		* game->map.deltadist_x;
	}
	ray_calc2(game);
}

void	dda_loop(t_game *game)
{
	while (game->map.hit == 0)
	{
		if (game->map.sidedist_x < game->map.sidedist_y)
		{
			game->map.sidedist_x += game->map.deltadist_x;
			game->map.map_x += game->map.step_x;
			game->map.side = 0;
		}
		else
		{
			game->map.sidedist_y += game->map.deltadist_y;
			game->map.map_y += game->map.step_y;
			game->map.side = 1;
		}
		if (game->map.map[game->map.map_x][game->map.map_y] > 0)
			game->map.hit = 1;
	}
}

void	dist_height(t_game *game)
{
	if (game->map.side == 0)
		game->map.perpwalldist = (game->map.sidedist_x - game->map.deltadist_x);
	else
		game->map.perpwalldist = (game->map.sidedist_y - game->map.deltadist_y);
	game->map.line_height = (int)(HEIGHT / game->map.perpwalldist);

	game->map.draw_start = -game->map.line_height / 2 + HEIGHT / 2;
	if (game->map.draw_start < 0)
		game->map.draw_start = 0;
	game->map.draw_end = game->map.line_height / 2 + HEIGHT / 2;
	if (game->map.draw_end >= HEIGHT)
		game->map.draw_end = HEIGHT - 1;
}

void	get_rays(t_game *game, int x)
{
	int	h = HEIGHT;

	init_raycasting(game, x);
	ray_calc(game);
	dda_loop(game);
	dist_height(game);

	int texNum = game->map.map[game->map.map_x][game->map.map_y] - 1;
	double wall_x;
	if (game->map.side == 0)
		wall_x = game->player.pos_y + game->map.perpwalldist * game->map.raydir_y;
	else
		wall_x = game->player.pos_x + game->map.perpwalldist * game->map.raydir_x;
	wall_x -= floor(wall_x);
	int tex_x = (int)(wall_x * (double)game->textures->texture_w);
	if (game->map.side == 0 && game->map.raydir_x > 0)
		tex_x = game->textures->texture_w - tex_x - 1;
	if (game->map.side == 1 && game->map.raydir_y < 0)
		tex_x = game->textures->texture_w - tex_x - 1;

	double step = 1.0 * game->textures->texture_h / game->map.line_height;

	double tex_pos = (game->map.draw_start - h / 2 + game->map.line_height / 2) * step;
	int i = game->map.draw_start;
	while (i < game->map.draw_end)
	{
		int tex_y = (int)tex_pos & (game->textures->texture_h - 1);
		tex_pos += step;

		unsigned char *pixel = (unsigned char *)(game->textures[texNum].addr
                            + tex_y * game->textures[texNum].size_line
                            + tex_x * (game->textures[texNum].bpp / 8));

		int r = pixel[2];
		int g = pixel[1];
		int b = pixel[0];

		if (game->map.side == 1)
		{
			r /= 2;
			g /= 2;
			b /= 2;
		}

		int color = rgb(r, g, b);
		put_pixel(game, x, i, color);
		i++;
	}

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
	floor_ceiling(game);
	init_textures(game);
	int x = 0;
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
