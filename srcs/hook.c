/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:28:10 by eleotard          #+#    #+#             */
/*   Updated: 2022/12/12 23:50:25 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_mouse_hook(t_vars *vars)
{
	ft_close(vars);
	return (0);
}

int	ft_key_hook(int keycode, t_vars	*vars)
{
	// static int	count_moves;

	if (keycode == XK_Escape)
		ft_close(vars);
	// if (keycode == XK_a || keycode == XK_Left)
	// 	ft_move_left(vars, &count_moves);
	// if (keycode == XK_d || keycode == XK_Right)
	// 	ft_move_right(vars, &count_moves);
	// if (keycode == XK_w || keycode == XK_Up)
	// 	ft_move_up(vars, &count_moves);
	// if (keycode == XK_s || keycode == XK_Down)
	// 	ft_move_down(vars, &count_moves);
	return (0);
}

void	ft_close(t_vars *vars)
{
	ft_destroy_all(vars->map, vars->mlx, vars->win);
	exit (0);
}
