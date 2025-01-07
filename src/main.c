/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:19:41 by idakhlao          #+#    #+#             */
/*   Updated: 2025/01/07 09:49:42 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	**allocate_map(t_map *map)
{
	int	i;
	int	**nmap;

	nmap = malloc(map->map_h * sizeof(int *));
	if (!nmap)
		return (NULL);
	i = 0;
	while (i < map->map_h)
	{
		nmap[i] = malloc(map->map_w * sizeof(int));
		if (!nmap[i])
		{
			while (i > 0)
				free(nmap[--i]);
			free(nmap);
			return (NULL);
		}
		i++;
	}
	return (nmap);
}

int	init_map(t_game *game)
{
	game->map.map_w = game->parsing.lenth_maps;
	game->map.map_h = game->parsing.height_maps;
	game->map.map = game->parsing.map;
	return (0);
}

int	init_image(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (printf("Error\nMLX failed\n"), -1);
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	if (!game->win)
		return (printf("Error\nWindow fail\n"), -1);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		return (printf("Error\nImage fail\n"), -1);
	game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, \
	&game->endian);
	if (!game->addr)
		return (printf("Error\nData_addr fail\n"), -1);
	return (0);
}

void	init_player(t_game *game)
{
	game->player.pos_x = game->parsing.pos_x;
	game->player.pos_y = game->parsing.pos_y;
	if (game->parsing.direction == 'N')
	{
		game->player.dir_x = -1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = 0.66;
	}
	if (game->parsing.direction == 'S')
	{
		game->player.dir_x = 1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = -0.66;
	}
	if (game->parsing.direction == 'E')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = 1.0;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0.0;
	}
	if (game->parsing.direction == 'W')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = -1.0;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0.0;
	}
}

int	init_game(t_game *game)
{
	if (init_map(game) == -1)
		return (-1);
	if (init_image(game) == -1)
		return (-1);
	init_player(game);
	init_textures(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (main_parser(argc, argv, &game) == ERROR) // mon parsing
	{
		ft_free_all(&game);
		return (1);	
	}
	if (init_game(&game) == -1)
		return (0);
	mlx_hook(game.win, KeyPress, KeyPressMask, &handle_keypress, &game);
	mlx_hook(game.win, 17, 0, &destroy, &game);
	mlx_mouse_move(game.mlx, game.win, WIDTH / 2, HEIGHT / 2); //bonus
	// mlx_mouse_hide(game.mlx, game.win); //bonus
	mlx_loop_hook(game.mlx, raycasting, &game);
	mlx_hook(game.win, KeyRelease, KeyReleaseMask, &handle_keyrelease, &game);
	mlx_loop(game.mlx);
	minimap(&game);
	mlx_destroy_display(game.mlx);
}