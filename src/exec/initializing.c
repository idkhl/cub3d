/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:57:04 by sben-tay          #+#    #+#             */
/*   Updated: 2025/01/09 10:33:35 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_game(t_game *game)
{
	game->map.map_w = game->parsing.lenth_maps;
	game->map.map_h = game->parsing.height_maps;
	game->map.map = game->parsing.map;
	if (init_mlx(game) == ERROR)
		return (ERROR);
	if (init_player(game) == ERROR)
		return (ERROR);
	if (init_textures_wall(game) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
