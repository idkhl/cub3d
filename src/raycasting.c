/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 12:58:38 by idakhlao          #+#    #+#             */
/*   Updated: 2024/12/26 14:54:34 by idakhlao         ###   ########.fr       */
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
		mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
		drawStart++;
	}
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

void	raycasting(t_game *game)
{
	double posX = 22, posY = 12;
	double dirX = -1, dirY = 0;
	double planeX = 0, planeY = 0.66;
	double time = 0;
	double oldTime = 0;
	int		w = game->map.screen_w;
	int		h = game->map.screen_h;
	struct timeval tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec + (tv.tv_usec / 1000000.0);
	while (1)
	{
		int x = 0;
		while (x < game->map.screen_w)
		{
			double cameraX = 2 * x / (double)w - 1;
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraX;
			int mapX = (int)posX;
			int mapY = (int)posY;
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
				sideDistX = (posX - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY;
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
		oldTime = time;
        gettimeofday(&tv, NULL);
        time = tv.tv_sec + (tv.tv_usec / 1000000.0);
        double frameTime = time - oldTime;
        printf("FPS = %f\n", 1.0 / frameTime);
		clear_image(game);
		double moveSpeed = frameTime * 5.0;
		double rotSpeed = frameTime * 3.0;
		// break ;
	}
}
