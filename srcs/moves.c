/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsie <elsie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 18:31:17 by eleotard          #+#    #+#             */
/*   Updated: 2022/12/30 00:43:47 by elsie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	moveForeward(t_vars *vars)
{
	float	moveStep;
	float	nextX;
	float	nextY;
	
	moveStep = vars->player.walkDirection * MOVE_SPEED;
	nextX = vars->player.position.x + vars->player.direction.x * moveStep;
	nextY = vars->player.position.y + vars->player.direction.y * moveStep;
	printf("testing map[%d][%d]\n", (int)(nextY), (int)(nextX));
	if (vars->map[(int)(nextY / TILE_SIZE)][(int)(nextX / TILE_SIZE)] != '1')
	{
		vars->player.position.x = nextX;
		vars->player.position.y = nextY;
	}
	else
		printf("\nCOLLISION\n");
	printf("player x = %f\n", vars->player.position.x);
	printf("player y = %f\n", vars->player.position.y);
	printf("dir x = %f\n", vars->player.direction.x);
	printf("dir y = %f\n", vars->player.direction.y);
	printf("NEXTx = %f\n", nextX);
	printf("NEXTy = %f\n", nextY);
	re_display_minimap(vars);
}

void	updateDirection(t_vars *vars)
{
	vars->player.rotation.y += vars->player.turnDirection * ROTATION_SPEED;
    vars->player.direction.x = cos(vars->player.rotation.y); //0
	vars->player.direction.y = sin(vars->player.rotation.y); //-1
	
	printf("rot y = %f\n", vars->player.rotation.y);
	printf("dir x = %f\n", vars->player.direction.x);
	printf("dir y = %f\n\n", vars->player.direction.y);
}

void	moveBackward(t_vars *vars)
{
	float	moveStep;
	float	nextX;
	float	nextY;
	
	moveStep = vars->player.walkDirection * MOVE_SPEED;
	nextX = vars->player.position.x + vars->player.direction.x * moveStep;
	nextY = vars->player.position.y + vars->player.direction.y * moveStep;
	printf("testing map[%d][%d]\n", (int)(nextY), (int)(nextX));
	if (vars->map[(int)(nextY / TILE_SIZE)][(int)(nextX / TILE_SIZE)] != '1')
	{
		vars->player.position.x = nextX;
		vars->player.position.y = nextY;
	}
	else
		printf("\nCOLLISION\n");
	
	printf("player x = %f\n", vars->player.position.x);
	printf("player y = %f\n", vars->player.position.y);
	printf("dir x = %f\n", vars->player.direction.x);
	printf("dir y = %f\n", vars->player.direction.y);
	printf("NEXTx = %f\n", nextX);
	printf("NEXTy = %f\n", nextY);
	re_display_minimap(vars);
}

void	moveLeft(t_vars *vars)
{
	float	nextX;
	float	nextY;
	
	nextX = vars->player.position.x + vars->player.direction.y * MOVE_SPEED;
	nextY = vars->player.position.y - vars->player.direction.x * MOVE_SPEED;
	printf("testing map[%d][%d]\n", (int)(nextY), (int)(nextX));
	if (vars->map[(int)(nextY / TILE_SIZE)][(int)(nextX / TILE_SIZE)] != '1')
	{
		vars->player.position.x = nextX;
		vars->player.position.y = nextY;
	}
	else
		printf("\nCOLLISION\n");
	
	
	re_display_minimap(vars);
	printf("\nLEFT\nplayer x = %f\n", vars->player.position.x);
	printf("player y = %f\n", vars->player.position.y);
	printf("dir x = %f\n", vars->player.direction.x);
	printf("dir y = %f\n", vars->player.direction.y);
	printf("NEXTx = %f\n", nextX);
	printf("NEXTy = %f\n", nextY);
}

void	moveRight(t_vars *vars)
{
	
	float	nextX;
	float	nextY;
	
	nextX = vars->player.position.x - vars->player.direction.y * MOVE_SPEED;
	nextY = vars->player.position.y + vars->player.direction.x * MOVE_SPEED;
	printf("testing map[%d][%d]\n", (int)(nextY), (int)(nextX));
	if (vars->map[(int)(nextY / TILE_SIZE)][(int)(nextX / TILE_SIZE)] != '1')
	{
		vars->player.position.x = nextX;
		vars->player.position.y = nextY;
	}
	else
		printf("\nCOLLISION\n");
	re_display_minimap(vars);
	printf("\nRIGHT\nplayer x = %f\n", vars->player.position.x);
	printf("player y = %f\n", vars->player.position.y);
	printf("dir x = %f\n", vars->player.direction.x);
	printf("dir y = %f\n", vars->player.direction.y);
	printf("NEXTx = %f\n", nextX);
	printf("NEXTy = %f\n", nextY);
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
