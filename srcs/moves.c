/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsie <elsie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 18:31:17 by eleotard          #+#    #+#             */
/*   Updated: 2022/12/20 23:13:05 by elsie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	moveForeward(t_vars *vars)
{
	float	moveStep;
	
	moveStep = vars->player.walkDirection * MOVE_SPEED; 
	vars->player.position.x += cos(vars->player.rotation.y) * moveStep;
	vars->player.position.y += sin(vars->player.rotation.y) * moveStep;
	
	printf("player x = %f\n", vars->player.position.x);
	printf("player y = %f\n", vars->player.position.y);
	printf("dir x = %f\n", vars->player.direction.x);
	printf("dir y = %f\n", vars->player.direction.y);
	printf("\ndistance parcourue = %f\n", sqrt(pow(vars->player.direction.x, 2) + pow(vars->player.direction.y, 2)));
	re_display_minimap(vars);
}

void	updateDirection(t_vars *vars)
{
	printf("ROT x = %f\n", vars->player.rotation.y);

	vars->player.rotation.y += vars->player.turnDirection * ROTATION_SPEED;
    vars->player.direction.x = cos(vars->player.rotation.y);//0
	vars->player.direction.y = sin(vars->player.rotation.y); //-1
	
	printf("rot y = %f\n", vars->player.rotation.y);
	printf("dir x = %f\n", vars->player.direction.x);
	printf("dir y = %f\n\n", vars->player.direction.y);
}

void	moveBackward(t_vars *vars)
{
	float	moveStep;
	
	moveStep = vars->player.walkDirection * MOVE_SPEED;//-1
	vars->player.position.x += cos(vars->player.rotation.y) * moveStep;
	vars->player.position.y += sin(vars->player.rotation.y) * moveStep;
	
	printf("player x = %f\n", vars->player.position.x);
	printf("player y = %f\n", vars->player.position.y);
	printf("dir x = %f\n", vars->player.direction.x);
	printf("dir y = %f\n", vars->player.direction.y);
	printf("\ndistance parcourue = %f\n", sqrt(pow(vars->player.direction.x, 2) + pow(vars->player.direction.y, 2)));
	re_display_minimap(vars);
}

void	moveLeft(t_vars *vars)
{
	vars->player.position.x -= vars->player.direction.y * MOVE_SPEED;
	vars->player.position.y -= vars->player.direction.x * MOVE_SPEED;
	re_display_minimap(vars);
	printf("\nLEFT\nplayer x = %f\n", vars->player.position.x);
	printf("player y = %f\n", vars->player.position.y);
	printf("dir x = %f\n", vars->player.direction.x);
	printf("dir y = %f\n", vars->player.direction.y);
	printf("\ndistance parcourue = %f\n", sqrt(pow(vars->player.direction.x, 2) + pow(vars->player.direction.y, 2)));
}

void	moveRight(t_vars *vars)
{
	vars->player.position.x += vars->player.direction.y * MOVE_SPEED;
	vars->player.position.y += vars->player.direction.x * MOVE_SPEED;
	re_display_minimap(vars);
	printf("\nRIGHT\nplayer x = %f\n", vars->player.position.x);
	printf("player y = %f\n", vars->player.position.y);
	printf("dir x = %f\n", vars->player.direction.x);
	printf("dir y = %f\n", vars->player.direction.y);
	printf("\ndistance parcourue = %f\n", sqrt(pow(vars->player.direction.x, 2) + pow(vars->player.direction.y, 2)));
}


void	watchLeft(t_vars *vars)
{
	vars->player.rotation.y += vars->player.turnDirection * ROTATION_SPEED;
	updateDirection(vars);
	re_display_minimap(vars);
}
void	watchRight(t_vars *vars)
{;
	vars->player.rotation.y += vars->player.turnDirection * ROTATION_SPEED;
	updateDirection(vars);
	re_display_minimap(vars);
}
