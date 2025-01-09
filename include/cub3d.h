/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sben-tay <sben-tay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 17:19:52 by idakhlao          #+#    #+#             */
/*   Updated: 2025/01/09 10:57:56 by sben-tay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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
# include <X11/Xutil.h>
# include <limits.h>
# include <stdbool.h>
# include <mlx.h>
# include <errno.h>

# include "get_next_line.h"
# include "ft_printf.h"
# include "libft.h"


# define WIDTH 1920
# define HEIGHT 1080
# define ERROR 1
# define SUCCESS 0


typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	int		up;
	int		down;
	int		left;
	int		right;
	int		r_left;
	int		r_right;
	int		mr_right; //bonus
	int		mr_left; //bonus
}	t_player;

typedef struct s_map
{
	int		map_w;
	int		map_h;
	char	**map;
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
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	double	wall_x;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
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

typedef struct s_minimap //bonus
{
	// int		minimap_w;
	// int		minimap_h;
	void	*minimap;
	int		bpp;
	int		size_line;
	int		endian;
	char	*addr;
	int		scale;
}	t_minimap;

typedef struct s_parsing
{
	char		*no; // texture nord
	char		*so; // texture sud
	char		*we; // texture ouest
	char		*ea; // texture est
	int			r_c; // couleur RGB type C
	int			g_c; // G
	int			b_c; // B
	int			r_f; // couleur RGB type F
	int			g_f; // G
	int			b_f; // B
	char		**map; // map
	int			nb_pos; // calcul pas cette variable.
	int			height_maps; // hauteur de la mini_map 
	int			lenth_maps; // largeur de la mini_map
	double		pos_x; // position x du joueur
	double		pos_y; // position y du joueur
	char		direction; // direction du joueur
}				t_parsing;

typedef struct s_game
{
	char		**file;
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			size_line;
	int			endian;
	int			mouse_x;
	int			mouse_y;
	t_map		map;
	t_player	player;
	t_texture	textures[4];
	t_minimap	minimap; //bonus
	t_parsing	parsing; // tu trouveras ton bonheur dedans
}	t_game;

//////////////////////////////////////////////////////////////////
//                       INITIALIZING						   //
////////////////////////////////////////////////////////////////

int				init_game(t_game *game);
int				init_player(t_game *game);
int				init_mlx(t_game *game);
int				init_textures_wall(t_game *game);


//////////////////////////////////////////////////////////////////
//                        RAYCASTING						   //
////////////////////////////////////////////////////////////////

int				raycasting(t_game *game);
void			handle_movement(t_game *game);
void			dist_height(t_game *game);
void			dda_loop(t_game *game);
void			ray_calc(t_game *game);
void			ray_calc2(t_game *game);
void			get_textures(t_game *game, int x);
int				init_textures_wall(t_game *game);
int				handle_keyrelease(int keysym, t_game *game);
int				handle_keypress(int keysym, t_game *game);
void			destroy_images_textures(t_game *game);

//////////////////////////////////////////////////////////////////
//                          UTILS							   //
////////////////////////////////////////////////////////////////

void			floor_ceiling(t_game *game);
int				rgb(int r, int g, int b);
void			put_pixel(t_game *game, int x, int y, int color);
bool			is_pos_player(char c);
void			minimap(t_game *game);

//////////////////////////////////////////////////////////////////
//                          PARSING							   //
////////////////////////////////////////////////////////////////

int				main_parser(int argc, char **argv, t_game *data);

int				handle_parsing(int	argc, char **argv, t_game *data);
int				get_fd_in_tab(char *file, t_game *data);
int				get_map_in_tab(t_game *data);
int				get_value_fd(t_game *data);
int				check_valid_fd(t_game *data);
int				check_c(t_game *data);
int				check_f(t_game *data);
int				check_ea(t_game *data);
int				check_we(t_game *data);
int				check_so(t_game *data);
int				check_no(t_game *data);
int				check_map_is_last_param(t_game *data);
int				check_format_rgb(char *str);
int				check_double_param(t_game *data);
bool			valid_char(char c);
bool			valid_char_map(char *str);
int				check_valid_map(t_game *data);
int				replace_space_by_set(char **str, const char set);
int				check_valid_map_char(t_game *data);
char			**map_duplicate(char **map);
int				flood_fill_map_and_island(t_game *data);
bool			is_pos_char(char c);
void			init_pos_s_n(t_game *data, char **map, int x, int y);
void			init_pos_e_w(t_game *data, char **map, int x, int y);
int				check_space_in_map(t_game *data);
int				check_first_last_line(t_game *data);
int				check_valid_xpm(t_game *data);

int				ft_free_all(t_game *data);
void			print_tab(char **str);

#endif