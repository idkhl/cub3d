/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 12:49:40 by sben-tay          #+#    #+#             */
/*   Updated: 2025/01/07 18:46:30 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_free_parsing(t_game *data);
static void ft_free_exec(t_game *data);

int	ft_free_all(t_game *data)
{
	ft_free_parsing(data);
	ft_free_exec(data);
	return (SUCCESS)
}


static void	ft_free_parsing(t_game *data)
{
	free_split(data->file);
	ft_free((void **)&data->parsing.no);
	ft_free((void **)&data->parsing.so);
	ft_free((void **)&data->parsing.we);
	ft_free((void **)&data->parsing.ea);
	free_split(data->parsing.map);
}

static void ft_free_exec(t_game *data)
{
	if (data->textures[0].img_data)
		mlx_destroy_image(data->mlx, data->textures[0].img_data);
	if (data->textures[1].img_data)
		mlx_destroy_image(data->mlx, data->textures[1].img_data);
	if (data->textures[2].img_data)
		mlx_destroy_image(data->mlx, data->textures[2].img_data);
	if (data->textures[3].img_data)
		mlx_destroy_image(data->mlx, data->textures[3].img_data);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->minimap.minimap)
		mlx_destroy_image(data->mlx, data->minimap.minimap);
	if (data->win && data->mlx)
	{
		mlx_clear_window(data->mlx, data->win);
		mlx_destroy_window(data->mlx, data->win);
	}
	if (data->mlx)
	{
		mlx_loop_end(data->mlx);
		mlx_destroy_display(data->mlx);
		ft_free((void **)&data->mlx);
	}
}
