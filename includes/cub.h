/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:35:10 by eleotard          #+#    #+#             */
/*   Updated: 2022/12/13 00:06:11 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "get_next_line.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>

# define SIZEPIC	60
# define ERROR		(-1)

typedef struct s_vars {
	void	*mlx;
	void	*win;
	char	**map;
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
void	ft_destroy_all(char **map, void *mlx, void *win);
void	ft_print_error_exit(char *error);


#endif