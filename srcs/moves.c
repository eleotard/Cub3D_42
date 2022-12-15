/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 18:31:17 by eleotard          #+#    #+#             */
/*   Updated: 2022/12/15 21:53:44 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	moveForeward(t_vars *vars)
{
	vars->perso.position.x -= vars->perso.direction.x;
	vars->perso.position.z += vars->perso.direction.y;
	//vars->perso.position.x -= vars->perso.direction.x;
	re_display_minimap(vars);
}

void	moveBackward(t_vars *vars)
{
	vars->perso.position.x += vars->perso.direction.x;
	vars->perso.position.z -= vars->perso.direction.y;
	re_display_minimap(vars);
}

void	moveLeft(t_vars *vars)
{
	vars->perso.position.x += vars->perso.direction.y;
	vars->perso.position.z -= vars->perso.direction.x;
	re_display_minimap(vars);
}

void	moveRight(t_vars *vars)
{
	vars->perso.position.x -= vars->perso.direction.y;
	vars->perso.position.z -= vars->perso.direction.x;
	re_display_minimap(vars);
}

void	watchLeft(t_vars *vars)
{
	vars->perso.rotation.y -= SENSITIVITY;
	updateDirection(vars);
}
void	watchRight(t_vars *vars)
{
	vars->perso.rotation.y += SENSITIVITY;
	updateDirection(vars);
}

void	updateDirection(t_vars *vars)
{
	vars->perso.direction.x = sin(vars->perso.rotation.y) * SPEED;
    vars->perso.direction.y = cos(vars->perso.rotation.y) * SPEED;
}