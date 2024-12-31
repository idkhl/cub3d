/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:22:43 by idakhlao          #+#    #+#             */
/*   Updated: 2024/12/31 16:37:07 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
