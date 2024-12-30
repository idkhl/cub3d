/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:19:52 by idakhlao          #+#    #+#             */
/*   Updated: 2024/12/30 17:02:38 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../includes/mlx.h"
# include "../includes/mlx_int.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/time.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <X11/Xlib.h>
# include <math.h>

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	time;
	int		up;
	int		down;
	int		left;
	int		right;
	int		r_left;
	int		r_right;
}	t_player;

typedef struct s_map
{
	int		map_w;
	int		map_h;
	int		**map;
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	int		map_x;
	int		map_y;
	double	sidedist_x;
	double	sidedist_y;
	double	deltadist_x;
	double	deltadist_y;
	double	perpwalldist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}	t_map;

typedef struct s_texture
{
	int		texture_w;
	int		texture_h;
	void	*img_data;
	int		bpp;
	int		size_line;
	int		endian;
	char	*addr;
}	t_texture;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
	t_map		map;
	t_player	player;
	t_texture	textures[4];
}	t_game;

	/*	RAYCASTING	*/

int		raycasting(t_game *game);
void	put_pixel(t_game *game, int x, int y, int color);
void	handle_movement(t_game *game);

	/*	UTILS	*/

void	*ft_memset(void *s, int c, size_t n);

#endif