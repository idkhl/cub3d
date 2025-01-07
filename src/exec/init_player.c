/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:59:14 by sben-tay          #+#    #+#             */
/*   Updated: 2025/01/07 10:24:53 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_pos_nord(t_game *data);
static void	init_pos_south(t_game *data);
static void	init_pos_east(t_game *data);
static void	init_pos_west(t_game *data);

int	init_player(t_game *game)
{
	game->player.pos_x = game->parsing.pos_x;
	game->player.pos_y = game->parsing.pos_y;
	if (game->parsing.direction == 'N')
	{
		init_pos_nord(game);
	}
	if (game->parsing.direction == 'S')
	{
		init_pos_south(game);
	}
	if (game->parsing.direction == 'E')
	{
		init_pos_east(game);
	}
	if (game->parsing.direction == 'W')
	{
		init_pos_west(game);
	}
	return (SUCCESS);
}

static void	init_pos_nord(t_game *data)
{
	data->player.dir_x = -1.0;
	data->player.dir_y = 0.0;
	data->player.plane_x = 0.0;
	data->player.plane_y = 0.66;
}

static void	init_pos_south(t_game *data)
{
	data->player.dir_x = 1.0;
	data->player.dir_y = 0.0;
	data->player.plane_x = 0.0;
	data->player.plane_y = -0.66;
}

static void	init_pos_east(t_game *data)
{
	data->player.dir_x = 0.0;
	data->player.dir_y = 1.0;
	data->player.plane_x = 0.66;
	data->player.plane_y = 0.0;
}

static void	init_pos_west(t_game *data)
{
	data->player.dir_x = 0.0;
	data->player.dir_y = -1.0;
	data->player.plane_x = -0.66;
	data->player.plane_y = 0.0;
}
