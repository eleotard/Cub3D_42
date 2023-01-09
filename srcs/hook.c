/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:28:10 by eleotard          #+#    #+#             */
/*   Updated: 2022/12/19 19:02:11 by eleotard         ###   ########.fr       */
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
	{
		printf("perso x = %f\n", vars->perso.pos.x);
		printf("perso y = %f\n", vars->perso.pos.y);
		ft_close(vars);
	}
	if (keycode == XK_d)
		moveRight(vars);
	if (keycode == XK_a)
		moveLeft(vars);
	if (keycode == XK_w)
		moveForeward(vars);
	if (keycode == XK_s)
		moveBackward(vars);
	if (keycode == XK_Right)
		watchRight(vars);
	if (keycode == XK_Left)
		watchLeft(vars);
	return (0);
}

void	ft_close(t_vars *vars)
{
	ft_destroy_all(vars->map, vars->mlx, vars->minimap.win, vars);
	exit (0);
}
