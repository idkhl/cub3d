/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:27:37 by idakhlao          #+#    #+#             */
/*   Updated: 2025/01/01 15:37:21 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	up_down(t_game *game, double movespeed)
{
	if (game->player.up == 1)
	{
		if (game->map.map[(int)(game->player.pos_x \
		+ game->player.dir_x * movespeed)][(int)(game->player.pos_y)] == 0)
			game->player.pos_x += game->player.dir_x * movespeed;
		if (game->map.map[(int)(game->player.pos_x)][(int)(game->player.pos_y \
		+ game->player.dir_y * movespeed)] == 0)
			game->player.pos_y += game->player.dir_y * movespeed;
	}
	if (game->player.down == 1)
	{
		if (game->map.map[(int)(game->player.pos_x - game->player.dir_x \
		* movespeed)][(int)(game->player.pos_y)] == 0)
			game->player.pos_x -= game->player.dir_x * movespeed;
		if (game->map.map[(int)(game->player.pos_x)][(int)(game->player.pos_y \
		- game->player.dir_y * movespeed)] == 0)
			game->player.pos_y -= game->player.dir_y * movespeed;
	}
}

void	right_left(t_game *game, double movespeed)
{
	if (game->player.right == 1)
	{
		if (game->map.map[(int)(game->player.pos_x + game->player.dir_y \
		* (movespeed * 2))][(int)game->player.pos_y] == 0)
			game->player.pos_x += game->player.dir_y * movespeed;
		if (game->map.map[(int)game->player.pos_x][(int)(game->player.pos_y \
		- game->player.dir_x * (movespeed * 2))] == 0)
			game->player.pos_y -= game->player.dir_x * movespeed;
	}
	if (game->player.left == 1)
	{
		if (game->map.map[(int)(game->player.pos_x - game->player.dir_y \
		* (movespeed * 2))][(int)game->player.pos_y] == 0)
			game->player.pos_x -= game->player.dir_y * movespeed;
		if (game->map.map[(int)game->player.pos_x][(int)(game->player.pos_y \
		+ game->player.dir_x * (movespeed * 2))] == 0)
			game->player.pos_y += game->player.dir_x * movespeed;
	}
}

void	rotate_right(t_game *game, double olddirx, double oldplane, \
		double rotspeed)
{
	olddirx = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(-rotspeed) - \
	game->player.dir_y * sin(-rotspeed);
	game->player.dir_y = olddirx * sin(-rotspeed) + game->player.dir_y \
	* cos(-rotspeed);
	oldplane = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(-rotspeed) - \
	game->player.plane_y * sin(-rotspeed);
	game->player.plane_y = oldplane * sin(-rotspeed) + game->player.plane_y \
	* cos(-rotspeed);
}

void	rotate(t_game *game, double rotspeed)
{
	double	olddirx;
	double	oldplane;

	olddirx = 0;
	oldplane = 0;
	if (game->player.r_right == 1)
		rotate_right(game, olddirx, oldplane, rotspeed);
	if (game->player.r_left == 1)
	{
		olddirx = game->player.dir_x;
		game->player.dir_x = game->player.dir_x * cos(rotspeed) \
		- game->player.dir_y * sin(rotspeed);
		game->player.dir_y = olddirx * sin(rotspeed) + game->player.dir_y \
		* cos(rotspeed);
		oldplane = game->player.plane_x;
		game->player.plane_x = game->player.plane_x * cos(rotspeed) \
		- game->player.plane_y * sin(rotspeed);
		game->player.plane_y = oldplane * sin(rotspeed) + game->player.plane_y \
		* cos(rotspeed);
	}
}

void	handle_movement(t_game *game)
{
	double	movespeed;
	double	rotspeed;

	movespeed = 0.08;
	rotspeed = 0.017;
	up_down(game, movespeed);
	right_left(game, movespeed);
	rotate(game, rotspeed);
}
