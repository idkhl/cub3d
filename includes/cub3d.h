/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:19:52 by idakhlao          #+#    #+#             */
/*   Updated: 2024/12/26 19:03:11 by idakhlao         ###   ########.fr       */
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

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	time;
}	t_player;

typedef struct s_map
{
	int	width;
	int	height;
	int	screen_w;
	int	screen_h;
	int	texture_w;
	int	texture_h;
	int	**map;
}	t_map;

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
}	t_game;

typedef struct s_colorRGB
{
	int	red;
	int	green;
	int	blue;
}	ColorRGB;

#define RGB_Red    (ColorRGB){255, 0, 0}
#define RGB_Green  (ColorRGB){0, 255, 0}
#define RGB_Blue   (ColorRGB){0, 0, 255}
#define RGB_White  (ColorRGB){255, 255, 255}
#define RGB_Yellow (ColorRGB){255, 255, 0}

	/*	RAYCASTING	*/

void	raycasting(t_game *game);
void	put_pixel(t_game *game, int x, int y, int color);
void	handle_movement(t_game *game, int keysym);

	/*	UTILS	*/

void	*ft_memset(void *s, int c, size_t n);

#endif