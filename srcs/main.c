/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:19:58 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/20 18:02:04 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"
#include "../minilibx-linux/mlx.h"

int	ft_map_height(char **map)
{
	int	k;

	k = 0;
	while (map[k])
		k++;
	return (k);
}

int	ft_map_wide(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i][j])
		j++;
	return (j);
}

void	check_window_size(t_vars *vars)
{
	int	x;
	int	y;

	vars->tile_sz = 60;
	mlx_get_screen_size(vars->mlx, &x, &y);
	vars->game_win_height = y ;
	vars->game_win_wide = x;
}

void	ft_mlx_win_init(t_vars *vars)
{
	check_window_size(vars);
	vars->game_win = mlx_new_window(vars->mlx, vars->game_win_wide,
			vars->game_win_height, "cub3D");
	if (!vars->game_win)
		ft_destroy_all_message(vars->map, vars->mlx,
			"Error\nWin pointer == NULL\n");
	init_pixel_tabs(vars);
	init_player_pos(vars);
	set_img(vars);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	vars = (t_vars){0};
	if (argc != 2)
		return (-1);
	vars.mlx = mlx_init();
	if (!vars.mlx)
		ft_print_error_exit("Error\nMlx pointer == NULL");
	parsing(argv[1], &vars);
	ft_mlx_win_init(&vars);
	mlx_hook(vars.game_win, KeyPress, KeyPressMask, ft_key_hook, &vars);
	mlx_hook(vars.game_win, KeyRelease, KeyReleaseMask, ft_key_release, &vars);
	mlx_hook(vars.game_win, ClientMessage, LeaveWindowMask,
		ft_mouse_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
