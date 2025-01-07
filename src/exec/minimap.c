/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:29:06 by idakhlao          #+#    #+#             */
/*   Updated: 2025/01/07 09:40:05 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mnmp_draw_floor(t_game *game, int dx, int dy)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.map_h)
	{
		x = 0;
		while (x < game->map.map_w)
		{
			dy = 0;
			while (dy < game->minimap.scale)
			{
				dx = 0;
				while (dx < game->minimap.scale)
				{
					if (is_pos_player(game->map.map[y][x]))
					{
						put_pixel(game, x * game->minimap.scale + dx, \
						y * game->minimap.scale + dy, rgb(207, 207, 207));
					}
					dx++;
				}
				dy++;
			}
			x++;
		}
		y++;
	}
}


void	mnmp_draw_walls(t_game *game, int dx, int dy)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.map_h)
	{
		x = 0;
		while (x < game->map.map_w)
		{
			dy = 0;
			while (dy < game->minimap.scale)
			{
				dx = 0;
				while (dx < game->minimap.scale)
				{
					if (game->map.map[y][x] == '1')
					{
						put_pixel(game, x * game->minimap.scale + dx, \
						y * game->minimap.scale + dy, rgb(48, 24, 24));
					}
					dx++;
				}
				dy++;
			}
			x++;
		}
		y++;
	}
}


int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void	mnmp_draw_player(t_game *game, int dx, int dy)
{
	int	pixel_x;
	int	pixel_y;

	dy = -2;
	while (dy <= 2)
	{
		dx = -2;
		while (dx <= 2)
		{
			pixel_x = (int)((game->player.pos_x * game->minimap.scale) + dx);
			pixel_y = (int)((game->player.pos_y * game->minimap.scale) + dy);
			if (pixel_x >= 0 && pixel_x < game->map.map_h * \
			game->minimap.scale && pixel_y >= 0
				&& pixel_y < game->map.map_w * game->minimap.scale)
				put_pixel(game, pixel_y, pixel_x, rgb(255, 0, 0));
			dx++;
		}
		dy++;
	}
}

void	minimap(t_game *game)
{
	int	minimap_size;
	int	dx;
	int	dy;

	dx = 0;
	dy = 0;
	minimap_size = 428; // 228 
	game->minimap.scale = min(minimap_size / game->map.map_w,\
	minimap_size / game->map.map_h);
	game->minimap.minimap = mlx_new_image(game->mlx, game->map.map_w, \
	game->map.map_w);
	game->minimap.addr = mlx_get_data_addr(game->minimap.minimap, \
	&game->minimap.bpp, &game->minimap.size_line, &game->minimap.endian);
	mnmp_draw_floor(game, dx, dy);
	mnmp_draw_walls(game, dx, dy);
	mnmp_draw_player(game, dx, dy);
	mlx_put_image_to_window(game->mlx, game->win, \
	game->minimap.minimap, game->minimap.scale, game->minimap.scale);
}
