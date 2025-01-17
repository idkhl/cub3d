/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 14:27:37 by idakhlao          #+#    #+#             */
/*   Updated: 2025/01/17 11:06:53 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	up_down(t_game *game, double movespeed);
void	right_left(t_game *game, double movespeed);
void	rotate(t_game *game, double rotspeed, int x);
void	rotate_right(t_game *game, double olddirx, double oldplane, \
		double rotspeed);

void	handle_movement(t_game *game)
{
	double	movespeed;
	double	rotspeed;
	int		x;

	movespeed = 1;
	rotspeed = 0.025;
	x = 0;
	if (game->player.mouse == 1)
	{
		mlx_mouse_get_pos(game->mlx, game->win, &game->mouse_x, &game->mouse_y);
		if (game->mouse_x > WIDTH / 2 + 5)
			game->player.mr_right = 1;
		if (game->mouse_x < WIDTH / 2 - 5)
			game->player.mr_left = 1;
		if (game->player.mouse == 1)
			mlx_mouse_move(game->mlx, game->win, WIDTH / 2, HEIGHT / 2);
		x = game->mouse_x;
	}
	up_down(game, movespeed);
	right_left(game, movespeed);
	rotate(game, rotspeed, x);
}

void	up_down(t_game *game, double movespeed)
{
	if (game->player.up == 1)
	{
		if (is_pos_player(game->map.map[(int)(game->player.pos_x \
		+ game->player.dir_x * movespeed)][(int)(game->player.pos_y)]))
			game->player.pos_x += game->player.dir_x * movespeed;
		if (is_pos_player(game->map.map[(int)(game->player.pos_x)][(int) \
		(game->player.pos_y + game->player.dir_y * movespeed)]))
			game->player.pos_y += game->player.dir_y * movespeed;
	}
	if (game->player.down == 1)
	{
		if (is_pos_player(game->map.map[(int)(game->player.pos_x - \
		game->player.dir_x * movespeed)][(int)(game->player.pos_y)]))
			game->player.pos_x -= game->player.dir_x * movespeed;
		if (is_pos_player(game->map.map[(int)(game->player.pos_x)][(int) \
		(game->player.pos_y - game->player.dir_y * movespeed)]))
			game->player.pos_y -= game->player.dir_y * movespeed;
	}
}

void	right_left(t_game *game, double movespeed)
{
	if (game->player.right == 1)
	{
		if (is_pos_player(game->map.map[(int)(game->player.pos_x + \
		game->player.dir_y * (movespeed * 2))][(int)game->player.pos_y]))
			game->player.pos_x += game->player.dir_y * movespeed;
		if (is_pos_player(game->map.map[(int)game->player.pos_x][(int) \
		(game->player.pos_y - game->player.dir_x * (movespeed * 2))]))
			game->player.pos_y -= game->player.dir_x * movespeed;
	}
	if (game->player.left == 1)
	{
		if (is_pos_player(game->map.map[(int)(game->player.pos_x - \
		game->player.dir_y * (movespeed * 2))][(int)game->player.pos_y]))
			game->player.pos_x -= game->player.dir_y * movespeed;
		if (is_pos_player(game->map.map[(int)game->player.pos_x][(int) \
		(game->player.pos_y + game->player.dir_x * (movespeed * 2))]))
			game->player.pos_y += game->player.dir_x * movespeed;
	}
}

void	rotate_right(t_game *game, double olddirx, double oldplane, \
		double rotspeed)
{
	int	x;

	if (game->player.mr_right == 1)
		rotspeed = 0.05;
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
	x = game->mouse_x;
	if (game->mouse_x == x)
		game->player.mr_right = 0;
}

void	rotate(t_game *game, double rotspeed, int x)
{
	double	olddirx;
	double	oldplane;

	olddirx = 0;
	oldplane = 0;
	if (game->player.r_right == 1 || game->player.mr_right == 1)
		rotate_right(game, olddirx, oldplane, rotspeed);
	if (game->player.r_left == 1 || game->player.mr_left == 1)
	{
		if (game->player.mr_left == 1)
			rotspeed = 0.05;
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
		if (game->mouse_x == x)
			game->player.mr_left = 0;
	}
}
