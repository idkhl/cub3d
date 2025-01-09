/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 13:32:22 by idakhlao          #+#    #+#             */
/*   Updated: 2025/01/09 10:57:24 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	destroy_images_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img_data)
			mlx_destroy_image(game->mlx, game->textures[i].img_data);
		i++;
	}
}

int	handle_keypress(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
		ft_free_all(game);
	if (keysym == XK_w)
		game->player.up = 1;
	if (keysym == XK_s)
		game->player.down = 1;
	if (keysym == XK_a)
		game->player.left = 1;
	if (keysym == XK_d)
		game->player.right = 1;
	if (keysym == XK_Left)
		game->player.r_left = 1;
	if (keysym == XK_Right)
		game->player.r_right = 1;
	return (0);
}

int	handle_keyrelease(int keysym, t_game *game)
{
	if (keysym == XK_w)
		game->player.up = 0;
	if (keysym == XK_s)
		game->player.down = 0;
	if (keysym == XK_a)
		game->player.left = 0;
	if (keysym == XK_d)
		game->player.right = 0;
	if (keysym == XK_Left)
		game->player.r_left = 0;
	if (keysym == XK_Right)
		game->player.r_right = 0;
	return (0);
}
