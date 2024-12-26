/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prout.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:19:41 by idakhlao          #+#    #+#             */
/*   Updated: 2024/12/26 19:23:55 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	destroy(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	exit(EXIT_FAILURE);
}

int	handle_keypress(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
		destroy(game);
	handle_movement(game, keysym);
	return (0);
}

int	**allocate_map(t_map *map)
{
	int	i;
	int	**nmap;

	nmap = malloc(map->height * sizeof(int *));
	if (!nmap)
		return (NULL);
	i = 0;
	while (i < map->height)
	{
		nmap[i] = malloc(map->width * sizeof(int));
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

void	fill_map(t_map *map)
{
	int temp_map[24][24] = {
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	for (int y = 0; y < map->height; y++)
		for (int x = 0; x < map->width; x++)
			map->map[y][x] = temp_map[y][x];
}

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= game->map.screen_w || y < 0 || y >= game->map.screen_h)
	{
		fprintf(stderr, "Error\nPixel out of bounds: (%d, %d)\n", x, y);
		return ;
	}
	dst = game->addr + (y * game->size_line + x * (game->bpp / 8));
	*(unsigned int*)dst = color;
}

int	init_map(t_game *game)
{
	ft_memset(&game->map, 0, sizeof(t_map));
	game->map.width = 24;
	game->map.height = 24;
	game->map.texture_w = 64;
	game->map.texture_h = 64;
	game->map.screen_w = 640;
	game->map.screen_h = 480;
	game->map.map = allocate_map(&game->map);
	if (!game->map.map)
	{
		exit(EXIT_FAILURE);
		return (-1);
	}
	fill_map(&game->map);
	return (0);
}

int	init_image(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (printf("Error\nMLX failed\n"), -1);
	game->win = mlx_new_window(game->mlx, game->map.screen_w, game->map.screen_h, "cub3d");
	if (!game->win)
		return (printf("Error\nWindow fail\n"), -1);
	game->img = mlx_new_image(game->mlx, game->map.screen_w, game->map.screen_h);
	if (!game->img)
		return (printf("Error\nImage fail\n"), -1);
	game->addr = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	if (!game->addr)
		return (printf("Error\nData_addr fail\n"), -1);
	return (0);
}

void	init_player(t_game *game)
{
	game->player.pos_x = 22.0;
	game->player.pos_y = 12.0;
	game->player.dir_x = -1.0;
	game->player.dir_y = 0.0;
	game->player.plane_x = 0.0;
	game->player.plane_y = 0.66;
	game->player.time = 0;
}

int	init_game(t_game *game)
{
	if (init_map(game) == -1)
		return (-1);
	if (init_image(game) == -1)
	{
		destroy(game);
		return (-1);
	}
	init_player(game);
	return (0);
}

int	main(void)
{
	t_game	game;

	if (init_game(&game) == -1)
		return (0);
	// raycasting(&game);
	mlx_hook(game.win, KeyPress, KeyPressMask, &handle_keypress, &game);
	mlx_hook(game.win, 17, 0, &destroy, &game);
	mlx_loop_hook(game.mlx, raycasting, &game);
	mlx_loop(game.mlx);
	mlx_destroy_display(game.mlx);
}
