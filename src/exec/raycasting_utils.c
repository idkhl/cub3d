/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 15:52:08 by idakhlao          #+#    #+#             */
/*   Updated: 2025/01/09 11:09:45 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;

	i = 0;
	str = (unsigned char *)s;
	while (i < n)
	{
		*str++ = (unsigned char)c;
		i++;
	}
	return (s);
}

int	rgb(int r, int g, int b)
{
	return (0 << 24 | r << 16 | g << 8 | b);
}

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
	{
		fprintf(stderr, "Error\nPixel out of bounds: (%d, %d)\n", x, y);
		return ;
	}
	dst = game->addr + (y * game->size_line + x * (game->bpp / 8));
	*(unsigned int *)dst = color;
}

void	floor_ceiling(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < HEIGHT / 2)
	{
		j = -1;
		while (++j < WIDTH)
		{
			put_pixel(game, j, i, rgb(game->parsing.r_c, game->parsing.g_c, \
					game->parsing.b_c));
		}
		i++;
	}
	while (i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
		{
			put_pixel(game, j, i, rgb(game->parsing.r_f, game->parsing.g_f, \
					game->parsing.b_f));
		}
		i++;
	}
}

// void	vertical_line(t_game *game, int x, int color)
// {
// 	if (x > WIDTH || x < 0)
// 		return ;
// 	while (game->map.draw_start <= game->map.draw_end)
// 	{
// 		put_pixel(game, x, game->map.draw_start, color);
// 		game->map.draw_start++;
// 	}
// }