/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsie <elsie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:35:10 by eleotard          #+#    #+#             */
/*   Updated: 2022/12/17 20:43:36 by elsie            ###   ########.fr       */
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

# define SIZEPIC		100
# define SENSITIVITY	0.4
# define SPEED			0.1
# define ERROR			(-1)
# define PI				3.1415926535

typedef struct s_line_params {
	int	dx; //distance
	int	dy;
	int sx; //sign
	int	sy;
} t_line_params;

typedef struct s_line_cd { //coordonnees
	float	x0;
	float	y0;
	float	x1;
	float	y1;
} t_line_cd;

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
	t_vec3	position;
	t_vec3	rotation;
	t_vec3	direction;
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
void	moveLeft(t_vars *vars);
void	moveRight(t_vars *vars);
void	moveForeward(t_vars *vars);
void	moveBackward(t_vars *vars);

void	watchLeft(t_vars *vars);
void	watchRight(t_vars *vars);

void	updateDirection(t_vars *vars);

/*MAP CHARACTERISTIC*/
int	ft_map_height(char **map);
int	ft_map_wide(char **map);

/*DRAW LINE*/
void	line(t_img *img, t_line_cd cd, int color);

/*MINIMAP IMAGE PAR IMAGE*/
void	set_minimap(t_vars *vars);
void	create_img(t_vars *vars, t_img *img, int x, int y);

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	pixelize_fill(t_img *img, int color);
void	pixelize_walls(t_vars *vars, t_img *img, int color);
void	pixelize_grid(t_vars *vars, t_img *img, int color);
void	pixelize_perso(t_vars *vars, t_img *img, int color);

void	re_display_minimap(t_vars *vars);

/*PERSO POSITION*/
void	init_perso_pos(t_vars *vars);
void	init_perso_rotation(t_vars *vars, char dir);
void	display_perso(t_vars *vars);



#endif