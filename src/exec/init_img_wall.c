/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img_wall.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:58:58 by sben-tay          #+#    #+#             */
/*   Updated: 2025/01/07 17:26:37 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	init_texture_nord(t_game *data);
static int	init_texture_south(t_game *data);
static int	init_texture_west(t_game *data);
static int	init_texture_east(t_game *data);

int	init_textures_wall(t_game *game)
{
	game->textures->texture_h = 64;
	game->textures->texture_w = 64;
	if (init_texture_nord(game) == ERROR)
		return (ERROR);
	if (init_texture_south(game) == ERROR)
		return (ERROR);
	if (init_texture_west(game) == ERROR)
		return (ERROR);
	if (init_texture_east(game) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static int	init_texture_nord(t_game *data)
{
	data->textures[0].img_data = mlx_xpm_file_to_image(data->mlx, \
			data->parsing.no, &data->textures[0].texture_w, \
			&data->textures[0].texture_h);
	if (!data->textures[0].img_data)
	{
		ft_dprintf(2, "Error\n Loading %s failed!\n", data->parsing.no);
		return (ERROR);
	}
	data->textures[0].addr = mlx_get_data_addr(data->textures[0].img_data, \
			&data->textures[0].bpp, &data->textures[0].size_line, \
			&data->textures[0].endian);
	return (SUCCESS);
}

static int	init_texture_south(t_game *data)
{
	data->textures[1].img_data = mlx_xpm_file_to_image(data->mlx, \
			data->parsing.so, &data->textures[1].texture_w, \
			&data->textures[1].texture_h);
	if (!data->textures[1].img_data)
	{
		ft_dprintf(2, "Error\n Loading %s failed!\n", data->parsing.so);
		return (ERROR);
	}
	data->textures[1].addr = mlx_get_data_addr(data->textures[1].img_data, \
			&data->textures[1].bpp, &data->textures[1].size_line, \
			&data->textures[1].endian);
	return (SUCCESS);
}

static int	init_texture_west(t_game *data)
{
	data->textures[2].img_data = mlx_xpm_file_to_image(data->mlx, \
			data->parsing.we, &data->textures[2].texture_w, \
			&data->textures[2].texture_h);
	if (!data->textures[2].img_data)
	{
		ft_dprintf(2, "Error\n Loading %s failed!\n", data->parsing.we);
		return (ERROR);
	}
	data->textures[2].addr = mlx_get_data_addr(data->textures[2].img_data, \
			&data->textures[2].bpp, &data->textures[2].size_line, \
			&data->textures[2].endian);
	return (SUCCESS);
}

static int	init_texture_east(t_game *data)
{
	data->textures[3].img_data = mlx_xpm_file_to_image(data->mlx, \
			data->parsing.ea, &data->textures[3].texture_w, \
			&data->textures[3].texture_h);
	if (!data->textures[3].img_data)
	{
		ft_dprintf(2, "Error\n Loading %s failed!\n", data->parsing.ea);
		return (ERROR);
	}
	data->textures[3].addr = mlx_get_data_addr(data->textures[3].img_data, \
			&data->textures[3].bpp, &data->textures[3].size_line, \
			&data->textures[3].endian);
	return (SUCCESS);
}
