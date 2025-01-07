/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 09:57:04 by sben-tay          #+#    #+#             */
/*   Updated: 2025/01/07 17:22:38 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_game(t_game *game)
{
	game->map.map_w = game->parsing.lenth_maps;
	game->map.map_h = game->parsing.height_maps;
	game->map.map = game->parsing.map;
	if (init_mlx(game) == ERROR) // [OK][NORME OK !]
		return (ERROR);
	if (init_player(game) == ERROR) // [OK][NORME OK !]
		return (ERROR);
	if (init_textures_wall(game) == ERROR) // [OK][NORME OK !]
		return (ERROR);
	return (SUCCESS);
}
