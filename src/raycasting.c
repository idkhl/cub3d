/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:58:38 by idakhlao          #+#    #+#             */
/*   Updated: 2024/12/27 16:46:15 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	rgb(int r, int g, int b)
{
    return (0 << 24 | r << 16 | g << 8 | b);
}

void	vertical_line(t_game *game, int x, int drawStart, int drawEnd, int color)
{
	if (x > game->map.screen_w || x < 0)
		return ;
	while (drawStart <= drawEnd)
	{
		put_pixel(game, x, drawStart, color);
		drawStart++;
	}
}

void	floor_ceiling(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->map.screen_h / 2)
	{
		j = 0;
		while (j < game->map.screen_w)
		{
			put_pixel(game, j, i, rgb(218, 218, 218));
			j++;
		}
		i++;
	}
	while (i < game->map.screen_h)
	{
		j = 0;
		while (j < game->map.screen_w)
		{
			put_pixel(game, j, i, rgb(119, 119, 119));
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
	double movespeed = 1;
	double rotspeed = 0.25;
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

void get_rays(t_game *game, int x, int w)
{
	int		h = game->map.screen_h;
	double cameraX = 2 * x / (double)w - 1;
	double rayDirX = game->player.dir_x + game->player.plane_x * cameraX;
	double rayDirY = game->player.dir_y + game->player.plane_y * cameraX;
	int mapX = (int)game->player.pos_x;
	int mapY = (int)game->player.pos_y;
	double sideDistX;
	double sideDistY;

	double deltaDistX;
	double deltaDistY;

	if (rayDirX == 0)
		deltaDistX = 1e30;
	else
		deltaDistX = fabs(1.0 / rayDirX);

	if (rayDirY == 0)
		deltaDistY = 1e30;
	else
		deltaDistY = fabs(1.0 / rayDirY);

	double perpWallDist;

	int stepX;
	int stepY;

	int hit = 0;
	int side;

	if (rayDirX < 0)
	{
		stepX = -1;
		sideDistX = (game->player.pos_x - mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (mapX + 1.0 - game->player.pos_x) * deltaDistX;
	}
	if (rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (game->player.pos_y - mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (mapY + 1.0 - game->player.pos_y) * deltaDistY;
	}
	while(hit == 0)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		if (game->map.map[mapX][mapY] > 0)
			hit = 1;
	}
	if (side == 0)
		perpWallDist = (sideDistX - deltaDistX);
	else
		perpWallDist = (sideDistY - deltaDistY);
	int lineHeight = (int)(h / perpWallDist);
	int drawStart = -lineHeight / 2 + h / 2;
	if (drawStart < 0)
		drawStart = 0;
	int drawEnd = lineHeight / 2 + h / 2;
	if (drawEnd >= h)
		drawEnd = h - 1;

	int color = 0;

	if (game->map.map[mapX][mapY] == 1)
		color = rgb(255, 0, 0);
	else if (game->map.map[mapX][mapY] == 2)
		color = rgb(0, 255, 0);
	else if (game->map.map[mapX][mapY] == 3)
		color = rgb(0, 0, 255);
	else if (game->map.map[mapX][mapY] == 4)
		color = rgb(255, 255, 255);
	else
		color = rgb(255, 255, 0);
	if (side == 1)
	{
		color -= 15;
	}
	vertical_line(game, x, drawStart, drawEnd, color);
}

int	raycasting(t_game *game)
{
	int		w = game->map.screen_w;

	floor_ceiling(game);
	int x = 0;
	while (x < w)
	{
		get_rays(game, x, w);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	handle_movement(game);
	mlx_destroy_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, game->map.screen_w, game->map.screen_h);
	if (!game->img)
		return (printf("Error\nImage fail\n"), -1);
	reset_player_move(game);
	return (0);
}
