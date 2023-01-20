/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:35:10 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/20 19:11:03 by elpastor         ###   ########.fr       */
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

# define MSF			0.2
# define ROTATION_SPEED	0.03490658503888889 //2 * (3.1415926535 / 180)
# define MOVE_SPEED		10
# define ERROR			(-1)
# define PI				3.1415926535
# define FOV_ANGLE		1.0471975511666667 //60 * (3.1415926535 / 180)

typedef enum s_type
{
	north,
	south,
	west,
	east,
}	t_type;

typedef struct s_line_params {
	int	dx;
	int	dy;
	int	sx;
	int	sy;
}	t_line_params;

typedef struct s_line_cd {
	float	x0;
	float	y0;
	float	x1;
	float	y1;
}	t_line_cd;

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
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_player {
	t_vec3	pos;
	t_vec3	rotation;
	t_vec3	direction;
	int		walk_direction;
	int		turn_direction;
}	t_player;

typedef struct s_ray {
	float	ray_angle;
	float	dist_coll_horiz;
	float	dist_coll_vert;
	float	collpthoriz_x;
	float	collpthoriz_y;
	float	collptvert_x;
	float	collptvert_y;
	float	good_dist;
	float	goodcoll_x;
	float	goodcoll_y;
	int		was_hit_vertical;
	int		was_hit_horizontal;
	float	no_fisheye_dist;
	int		is_ray_facing_right;
	int		is_ray_facing_left;
	int		is_ray_facing_up;
	int		is_ray_facing_down;
	float	wall_strip_height;
	int		texture;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
	int		textureoffset_x;
	int		textureoffset_y;
}	t_ray;

typedef struct s_rc {
	float	xstep;
	float	ystep;
	float	xintercept;
	float	yintercept;
}	t_rc;

typedef struct s_vars {
	void		*mlx;
	char		**map;
	t_minimap	minimap;
	t_player	player;
	t_ray		*rays;
	t_img		game_img;
	void		*game_win;
	int			game_win_wide;
	int			game_win_height;
	int			ray_nb;
	float		angle_step;
	float		projplan_dist;
	float		wsf;
	int			tile_sz;
	t_img		*textures;
	int			**north;
	int			**south;
	int			**west;
	int			**east;
	int			floor;
	int			ceiling;
}	t_vars;

/*PARSE*/
char	*file_to_str(char *fichier, t_vars *vars);
int		get_color_and_texture(char *s, t_vars *vars);
void	verify_colors_and_texture(t_vars *vars, char *to_free);
void	get_map(char *s, t_vars *vars, char *to_free);
void	parsing(char *fichier, t_vars *vars);

/*PARSE COLOR TEXTURES*/
int		check_color(char *s);
int		get_color(char *s, t_vars *vars, char *to_free);
void	path2img(char *path, t_img *texture, t_vars *vars, char *to_free);
char	*get_path_texture(char *s, int *count, t_vars *vars, char *to_free);
int		get_texture(char *s, t_vars *vars, int texture_type, char *to_free);

/*PARSE MAP*/
int		check_file(char *s);
int		map_is_valid(char *s);
void	get_map_line(t_vars *vars, int j, char *to_free, char **map);
int		splited_map_is_closed(char **map, int j);

/*PARSE MAP UTILS*/
int		is_in_map(char *s);
int		is_in_map_wbn(char *s);
int		get_map_height(char *s);
int		map_height(char **map);
int		map_length(char **map);

/*UTILS*/
int		ft_strcmp(char *s1, char *s2);
char	*ft_strjoin_s(char *base, char *read);
char	*join(char *base, char *read);
int		find_char(char *s, char c);
char	*ft_strjoinspe(char *s1, char *s2);

/*HOOK*/
int		ft_mouse_hook(t_vars *vars);
int		ft_key_hook(int keycode, t_vars	*vars);
int		ft_key_release(int keycode, t_vars	*vars);
void	ft_close(t_vars *vars);

/*ERRORS DESTROY FREE*/
void	ft_print_error_exit(char *error);
void	destroy_all_imgs(t_vars *vars);
void	ft_destroy_all(char **map, void *mlx, void *win, t_vars *vars);
void	ft_destroy_all_message(char **map, void	*mlx, char *message);
void	destroy_all_msg(t_vars *vars, char *message, char *to_free,
			char **map_to_free);

/*DESTROY TABS*/
void	destroy_inttab(t_vars *vars, int **pix_tab);
void	destroy_all_inttabs(t_vars *vars);
void	ft_destroy_map(char **map);

/*MOVES*/
void	move_left(t_vars *vars);
void	move_right(t_vars *vars);
void	move_foreward(t_vars *vars);
void	move_backward(t_vars *vars);

void	watch_left(t_vars *vars);
void	watch_right(t_vars *vars);

void	update_direction(t_vars *vars);

/*MAP CHARACTERISTIC*/
int		ft_map_height(char **map);
int		ft_map_wide(char **map);

/*DRAW LINE*/
void	line(t_img *img, t_line_cd cd, int color);

/*MINIMAP IMAGE PAR IMAGE*/
void	set_minimap(t_vars *vars);
void	create_img(t_vars *vars, t_img *img, int x, int y);

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	pixelize_fill(t_vars *vars, t_img *img, int color);
void	pixelize_walls(t_vars *vars, t_img *img, int color);
void	pixelize_grid(t_vars *vars, t_img *img, int color);
void	pixelize_player(t_vars *vars, t_img *img, int color);
void	pixelize_ground(t_vars *vars, t_img *img, int color);
void	pixelize_dir_vector(t_vars *vars, t_img *img, int color);

void	display_minimap_img(t_vars *vars);
void	render(t_vars *vars);

/*RAYCASTING*/
void	draw_rays(t_vars *vars, t_img *img, int color);
void	cast_all_rays(t_vars *vars);
void	cast_horiz_ray(t_vars *vars, t_ray *ray);
void	update_rays_orientation(t_vars *vars);
void	update_rays_angles(t_vars *vars);
void	set_good_distance(t_vars *vars, t_ray *ray);
void	find_ray_texture(t_vars *vars, t_ray *ray);
int		precheck_coll_vert(t_vars *vars, t_ray *ray, t_rc *rc, int *found);
void	find_coll_vert(t_vars *vars, t_ray *ray, t_rc *rc);
void	cast_vert_ray(t_vars *vars, t_ray *ray);

/*RENDERING*/
void	render(t_vars *vars);
int		**create_pixel_tab(t_vars *vars, t_img *texture);
void	init_pixel_tabs(t_vars *vars);
void	init_wall_top_bottom_pixels(t_vars *vars, t_ray *ray);
int		**create_pixel_tab(t_vars *vars, t_img *texture);
void	find_wall_strip_heights(t_vars *vars);
void	define_projplan_dist(t_vars *vars);
void	set_img(t_vars *vars);

/*player POSITION*/
void	init_player_pos(t_vars *vars);
void	init_player_rotation(t_vars *vars, char dir);
void	display_player(t_vars *vars);

/*3D*/
void	create_game_window(t_vars *vars);

# define RESET   "\033[0m"
# define BLACK   "\033[30m"      /* Black */
# define RED     "\033[31m"      /* Red */
# define GREEN   "\033[32m"      /* Green */
# define YELLOW  "\033[33m"      /* Yellow */
# define BLUE    "\033[34m"      /* Blue */
# define MAGENTA "\033[35m"      /* Magenta */
# define CYAN    "\033[36m"      /* Cyan */
# define WHITE   "\033[37m"      /* White */

#endif