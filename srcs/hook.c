/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 23:28:10 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/01 18:29:13 by eleotard         ###   ########.fr       */
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
	printf("turn = %d\n", vars->player.turnDirection);
	printf("walk = %d\n", vars->player.walkDirection);
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
	printf("turn = %d\n", vars->player.turnDirection);
	printf("walk = %d\n", vars->player.walkDirection);
	return (0);
}

void	ft_close(t_vars *vars)
{
	free(vars->rays);
	ft_destroy_all(vars->map, vars->mlx, vars->minimap.win, vars);
	exit (0);
}
