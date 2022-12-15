/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:28:10 by eleotard          #+#    #+#             */
/*   Updated: 2022/12/14 17:01:28 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_mouse_hook(t_vars *vars)
{
	ft_close(vars);
	return (0);
}

//XK_Left
//XK_Right
//XK_Up
//XK_Down

int	ft_key_hook(int keycode, t_vars	*vars)
{
	// static int	count_moves;

	if (keycode == XK_Escape)
		ft_close(vars);
	/*if (keycode == XK_a)
		ft_move_left(vars);
	if (keycode == XK_d)
		ft_move_right(vars);
	if (keycode == XK_w)
		ft_move_up(vars);
	if (keycode == XK_s)
		ft_move_down(vars);*/
	return (0);
}

void	ft_close(t_vars *vars)
{
	ft_destroy_all(vars->map, vars->mlx, vars->minimap.win, vars);
	exit (0);
}
