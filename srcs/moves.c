/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 18:31:17 by eleotard          #+#    #+#             */
/*   Updated: 2022/12/19 19:46:09 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	moveForeward(t_vars *vars)
{
	//t_line_cd cd;
	printf("passe\n");
	//updateDirection(vars);
	vars->perso.pos.x += vars->perso.dir.x;
	vars->perso.pos.y -= vars->perso.dir.y;
	printf("perso x = %f\n", vars->perso.pos.x);
	printf("perso y = %f\n", vars->perso.pos.y);
	printf("dir x = %f\n", vars->perso.dir.x);
	printf("dir y = %f\n", vars->perso.dir.y);
	printf("\ndistance parcourue = %f\n", sqrt(pow(vars->perso.dir.x, 2) + pow(vars->perso.dir.y, 2)));
	
	re_display_minimap(vars);
}

void	updateDirection(t_vars *vars)
{
	printf("ROT x = %f\n", vars->perso.rot.y);

	
	vars->perso.dir.y = sin(vars->perso.rot.y) * SPEED; //-1
    vars->perso.dir.x = cos(vars->perso.rot.y) * SPEED; //0
	


	
	printf("que avec les cos sin purs:\n\tcos: %f\n", cos(vars->perso.rot.y));
	printf("\tsin: %f\n", sin(vars->perso.rot.y));
	
	printf("dir x = %f\n", vars->perso.dir.x);
	printf("dir y = %f\n\n", vars->perso.dir.y);

}

void	moveBackward(t_vars *vars)
{
	//updateDirection(vars);
	vars->perso.pos.x -= vars->perso.dir.x;
	vars->perso.pos.y += vars->perso.dir.y;
	printf("perso x = %f\n", vars->perso.pos.x);
	printf("perso y = %f\n", vars->perso.pos.y);
	printf("dir x = %f\n", vars->perso.dir.x);
	printf("dir y = %f\n", vars->perso.dir.y);
	printf("\ndistance parcourue = %f\n", sqrt(pow(vars->perso.dir.x, 2) + pow(vars->perso.dir.y, 2)));
	re_display_minimap(vars);
}

void	moveLeft(t_vars *vars)
{
	vars->perso.pos.x -= vars->perso.dir.y;
	vars->perso.pos.y -= vars->perso.dir.x;
	re_display_minimap(vars);
	printf("\nLEFT\nperso x = %f\n", vars->perso.pos.x);
	printf("perso y = %f\n", vars->perso.pos.y);
	printf("dir x = %f\n", vars->perso.dir.x);
	printf("dir y = %f\n", vars->perso.dir.y);
	printf("\ndistance parcourue = %f\n", sqrt(pow(vars->perso.dir.x, 2) + pow(vars->perso.dir.y, 2)));
}

void	moveRight(t_vars *vars)
{
	vars->perso.pos.x += vars->perso.dir.y;
	vars->perso.pos.y += vars->perso.dir.x;
	re_display_minimap(vars);
	printf("\nRIGHT\nperso x = %f\n", vars->perso.pos.x);
	printf("perso y = %f\n", vars->perso.pos.y);
	printf("dir x = %f\n", vars->perso.dir.x);
	printf("dir y = %f\n", vars->perso.dir.y);
	printf("\ndistance parcourue = %f\n", sqrt(pow(vars->perso.dir.x, 2) + pow(vars->perso.dir.y, 2)));
}


void	watchLeft(t_vars *vars)
{
	vars->perso.rot.y += SENSITIVITY;
	updateDirection(vars);
}
void	watchRight(t_vars *vars)
{
	vars->perso.rot.y -= SENSITIVITY;
	updateDirection(vars);
}
