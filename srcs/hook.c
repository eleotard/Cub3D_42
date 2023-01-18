/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:28:10 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/18 18:51:36 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

int	ft_mouse_hook(t_vars *vars)
{
	ft_close(vars);
	return (0);
}

int	key_hook_2(int keycode, t_vars	*vars)
{
	if (keycode == XK_Right)
	{
		vars->player.turn_direction = +1;
		watch_right(vars);
	}
	if (keycode == XK_Left)
	{
		vars->player.turn_direction = -1;
		watch_left(vars);
	}
	return (0);
}

int	ft_key_hook(int keycode, t_vars	*vars)
{
	if (keycode == XK_Escape)
		ft_close(vars);
	if (keycode == XK_w)
	{
		vars->player.walk_direction = +1;
		move_foreward(vars);
	}
	if (keycode == XK_s)
	{
		vars->player.walk_direction = -1;
		move_backward(vars);
	}
	if (keycode == XK_d)
		move_right(vars);
	if (keycode == XK_a)
		move_left(vars);
	key_hook_2(keycode, vars);
	return (0);
}

int	ft_key_release(int keycode, t_vars	*vars)
{
	if (keycode == XK_w)
		vars->player.walk_direction = 0;
	if (keycode == XK_s)
		vars->player.walk_direction = 0;
	if (keycode == XK_Right)
		vars->player.turn_direction = 0;
	if (keycode == XK_Left)
		vars->player.turn_direction = 0;
	return (0);
}

void	ft_close(t_vars *vars)
{
	free(vars->rays);
	ft_destroy_all(vars->map, vars->mlx, vars->game_win, vars);
	exit (0);
}
