/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:19:41 by idakhlao          #+#    #+#             */
/*   Updated: 2025/01/15 15:57:30 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (main_parser(argc, argv, &game) == ERROR)
	{
		ft_free_all(&game);
		return (1);
	}
	if (init_game(&game) == ERROR)
	{
		ft_free_all(&game);
		return (1);
	}
	mlx_hook(game.win, KeyPress, KeyPressMask, &handle_keypress, &game);
	mlx_hook(game.win, 17, 0, &ft_free_all, &game);
	if (game.player.mouse == 1)
		mlx_mouse_move(game.mlx, game.win, WIDTH / 2, HEIGHT / 2);
	mlx_mouse_hide(game.mlx, game.win);
	mlx_loop_hook(game.mlx, raycasting, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, &handle_keyrelease, &game);
	mlx_loop(game.mlx);
	minimap(&game);
	ft_free_all(&game);
}
