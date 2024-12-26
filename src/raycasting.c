/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:58:38 by idakhlao          #+#    #+#             */
/*   Updated: 2024/12/26 19:21:18 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	rgb(ColorRGB color)
{
    return (color.red << 16) | (color.green << 8) | color.blue;
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
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

void	clear_image(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->map.screen_h)
	{
		j = 0;
		while (j < game->map.screen_w)
		{
			put_pixel(game, j, i, 0);
			j++;
		}
		i++;
	}
}

void	handle_movement(t_game *game, int keysym)
{
	double oldTime = 0;
	struct timeval tv;

	oldTime = game->player.time;
	gettimeofday(&tv, NULL);
	game->player.time = tv.tv_sec + (tv.tv_usec / 1000000.0);
	double frameTime = game->player.time - oldTime;
	printf("FPS = %f\n", 1.0 / frameTime);
	clear_image(game);
	raycasting(game);
	double moveSpeed = frameTime * 5.0;
	double rotSpeed = frameTime * 3.0;
	if (keysym == XK_Up)
	{
		if (game->map.map[(int)(game->player.pos_x + game->player.dir_x * moveSpeed)][(int)(game->player.pos_y)] == 0)
			game->player.pos_x += game->player.dir_x * moveSpeed;
		if (game->map.map[(int)(game->player.pos_x)][(int)(game->player.pos_y + game->player.dir_y * moveSpeed)] == 0)
			game->player.pos_y += game->player.dir_y * moveSpeed;
	}
	if (keysym == XK_Down)
	{
		if (game->map.map[(int)(game->player.pos_x - game->player.dir_x * moveSpeed)][(int)(game->player.pos_y)] == 0)
			game->player.pos_x -= game->player.dir_x * moveSpeed;
		if (game->map.map[(int)(game->player.pos_x)][(int)(game->player.pos_y - game->player.dir_y * moveSpeed)] == 0)
			game->player.pos_y -= game->player.dir_y * moveSpeed;
	}
	if (keysym == XK_Right)
	{
		double oldDirX = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(-rotSpeed) - game->player.dir_y * sin(-rotSpeed);
		game->player.dir_y = oldDirX * sin(-rotSpeed) + game->player.dir_y * cos(-rotSpeed);

		double oldPlaneX = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(-rotSpeed) - game->player.plane_y * sin(-rotSpeed);
		game->player.plane_y = oldPlaneX * sin(-rotSpeed) + game->player.plane_y * cos(-rotSpeed);
	}
	if (keysym == XK_Left)
	{
		double oldDirX = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(rotSpeed) - game->player.dir_y * sin(rotSpeed);
		game->player.dir_y = oldDirX * sin(rotSpeed) + game->player.dir_y * cos(rotSpeed);

		double oldPlaneX = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(rotSpeed) - game->player.plane_y * sin(rotSpeed);
		game->player.plane_y = oldPlaneX * sin(rotSpeed) + game->player.plane_y * cos(rotSpeed);
	}
}

int	raycasting(t_game *game)
{
	int		w = game->map.screen_w;
	int		h = game->map.screen_h;
	struct timeval tv;

	gettimeofday(&tv, NULL);
	game->player.time = tv.tv_sec + (tv.tv_usec / 1000000.0);
	int x = 0;
	while (x < w)
	{
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
		{
			printf("%d\n", h);
			drawEnd = h - 1;
		}

		ColorRGB color;

		if (game->map.map[mapX][mapY] == 1)
			color = RGB_Red;
		else if (game->map.map[mapX][mapY] == 2)
			color = RGB_Green;
		else if (game->map.map[mapX][mapY] == 3)
			color = RGB_Blue;
		else if (game->map.map[mapX][mapY] == 4)
			color = RGB_White;
		else
			color = RGB_Yellow;

		if (side == 1)
		{
			color.red /= 2;
			color.green /= 2;
			color.blue /= 2;
		}
		int	color_int = rgb(color);
		vertical_line(game, x, drawStart, drawEnd, color_int);
		x++;
	}
	return (0);
}
