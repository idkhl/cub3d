/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:24:19 by idakhlao          #+#    #+#             */
/*   Updated: 2025/01/06 19:07:49 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	texture_color(t_game *game, int x, int i, unsigned char *pixel)
{
	int	r;
	int	g;
	int	b;
	int	color;

	r = pixel[2];
	g = pixel[1];
	b = pixel[0];
	if (game->map.side == 1)
	{
		r /= 1.5;
		g /= 1.5;
		b /= 1.5;
	}
	color = rgb(r, g, b);
	put_pixel(game, x, i, color);
}

void	texture_loop(t_game *game, int x)
{
	int				i;
	unsigned char	*pixel;

	if (game->map.side == 0 && game->map.raydir_x > 0)
		game->map.tex_x = game->textures->texture_w - game->map.tex_x - 1;
	if (game->map.side == 1 && game->map.raydir_y < 0)
		game->map.tex_x = game->textures->texture_w - game->map.tex_x - 1;
	pixel = NULL;
	game->map.step = 1.0 * game->textures->texture_h / game->map.line_height;
	i = game->map.draw_start;
	game->map.tex_pos = (game->map.draw_start - HEIGHT / 2 \
	+ game->map.line_height / 2) * game->map.step;
	while (i < game->map.draw_end)
	{
		game->map.tex_y = (int)game->map.tex_pos & (game->textures->texture_h \
		- 1);
		game->map.tex_pos += game->map.step;
		pixel = (unsigned char *)(game->textures[game->map.tex_num].addr \
		+ game->map.tex_y * game->textures[game->map.tex_num].size_line \
		+ game->map.tex_x * (game->textures[game->map.tex_num].bpp / 8));
		texture_color(game, x, i, pixel);
		i++;
	}
}

void	get_textures(t_game *game, int x)
{
	if (game->map.side == 0)
	{
		if (game->map.raydir_x < 0)
			game->map.tex_num = 0;
		else
			game->map.tex_num = 1;
	}
	else
	{
		if (game->map.raydir_y < 0)
			game->map.tex_num = 2;
		else
			game->map.tex_num = 3;
	}
	if (game->map.side == 0)
		game->map.wall_x = game->player.pos_y + game->map.perpwalldist \
		* game->map.raydir_y;
	else
		game->map.wall_x = game->player.pos_x + game->map.perpwalldist \
		* game->map.raydir_x;
	game->map.wall_x -= floor(game->map.wall_x);
	game->map.tex_x = (int)(game->map.wall_x * \
	(double)game->textures->texture_w);
	texture_loop(game, x);
}
