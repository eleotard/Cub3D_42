/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:35:10 by eleotard          #+#    #+#             */
/*   Updated: 2022/12/15 17:31:40 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "get_next_line.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>

# define SIZEPIC	100
# define ERROR		(-1)

typedef struct s_img {
	void	*ptr;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		px_length;
	int		px_height;
}	t_img;

typedef struct s_minimap {
	void		*win;
	t_img		ground;
	t_img		wall;
	t_img		p_point;
	t_img		mini_img;
}	t_minimap;

typedef struct s_vec3 {
	float x;
	float y;
	float z;
}	t_vec3;


typedef struct s_perso {
	t_vec3 position;
	t_vec3 rotation;
	t_vec3 direction;
}	t_perso;

typedef struct s_vars {
	void		*mlx;
	char		**map;
	t_minimap	minimap;
	t_perso		perso;
	//tab de tab des paths de textures NSEW
	//tab de tab des couleurs du sol et du ciel
	
}	t_vars;

int	ft_parsing_check(char *map_str);

/*UTILS*/
int		ft_strcmp(char *s1, char *s2);
char	*ft_strjoin_s(char *base, char *read);
char	*join(char *base, char *read);

/*HOOK*/
int		ft_mouse_hook(t_vars *vars);
int		ft_key_hook(int keycode, t_vars	*vars);
void	ft_close(t_vars *vars);

/*ERRORS DESTROY FREE*/
void	ft_destroy_all_message(char **map, void	*mlx, char *message);
void	ft_destroy_map(char **map);
void	ft_destroy_all(char **map, void *mlx, void *win, t_vars *vars);
void	ft_print_error_exit(char *error);

/*MOVES*/
void	ft_move_left(t_vars *vars);
void	ft_move_right(t_vars *vars);
void	ft_move_up(t_vars *vars);
void	ft_move_down(t_vars *vars);

/*MAP CHARACTERISTIC*/
int	ft_map_height(char **map);
int	ft_map_wide(char **map);

/*MINIMAP IMAGE PAR IMAGE*/
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	create_img(t_vars *vars, t_img *img, int x, int y);
void	pixelize_borders(t_img *img, int color);
void	pixelize_fill(t_img *img, int color);
void	pixelize_square(t_img *img, int x, int y, int color);
void	pixelize_minimap_base(t_vars *vars);

void line(t_img *img, int x0, int y0, int x1, int y1);
void	set_minimap(t_vars *vars);
void	set_good_minimap(t_vars *vars);

void	display_minimap_base(t_vars *vars);

/*PERSO POSITION*/
void	init_perso_pos_x(t_vars *vars);
void	init_perso_pos_y(t_vars *vars);
void	display_perso(t_vars *vars);
void	pixelize_perso(t_vars *vars, t_img *img, int color);



#endif