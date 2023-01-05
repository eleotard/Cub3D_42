/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:28:10 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/05 19:47:28 by eleotard         ###   ########.fr       */
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
	if (keycode == XK_Escape)
		ft_close(vars);
	if (keycode == XK_w)
	{
		vars->player.walkDirection = +1;
		moveForeward(vars);
	}
	if (keycode == XK_s)
	{
		vars->player.walkDirection = -1;
		moveBackward(vars);
	}
	if (keycode == XK_d)
	{
		moveRight(vars);
	}
	if (keycode == XK_a)
	{
		moveLeft(vars);
	}
	if (keycode == XK_Right)
	{
		vars->player.turnDirection = +1;
		watchRight(vars);
	}
	if (keycode == XK_Left)
	{
		vars->player.turnDirection = -1;
		watchLeft(vars);
	}
	// printf("turn = %d\n", vars->player.turnDirection);
	// printf("walk = %d\n", vars->player.walkDirection);
	return (0);
}

int	ft_key_release(int keycode, t_vars	*vars)
{
	if (keycode == XK_w)
		vars->player.walkDirection = 0;
	if (keycode == XK_s)
		vars->player.walkDirection = 0;
	if (keycode == XK_Right)
		vars->player.turnDirection = 0;
	if (keycode == XK_Left)
		vars->player.turnDirection = 0;
	//if (keycode == XK_d)
	//	vars->player.turnDirection = 0;
	//if (keycode == XK_a)
	//	vars->player.turnDirection = 0;
	// printf("turn = %d\n", vars->player.turnDirection);
	// printf("walk = %d\n", vars->player.walkDirection);
	return (0);
}

void	ft_close(t_vars *vars)
{
	// if (vars->game_win)
	// 	mlx_destroy_window(vars->mlx, vars->game_win);
	free(vars->rays);
	ft_destroy_all(vars->map, vars->mlx, vars->game_win, vars);
	exit (0);
}
