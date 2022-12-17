/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsie <elsie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 18:31:17 by eleotard          #+#    #+#             */
/*   Updated: 2022/12/17 21:33:19 by elsie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	moveForeward(t_vars *vars)
{
	//t_line_cd cd;
	printf("passe\n");
	//updateDirection(vars);
	vars->perso.position.x += vars->perso.direction.x;
	vars->perso.position.y -= vars->perso.direction.y;
	printf("perso x = %f\n", vars->perso.position.x);
	printf("perso y = %f\n", vars->perso.position.y);
	printf("dir x = %f\n", vars->perso.direction.x);
	printf("dir y = %f\n", vars->perso.direction.y);
	printf("\ndistance parcourue = %f\n", sqrt(pow(vars->perso.direction.x, 2) + pow(vars->perso.direction.y, 2)));
	// cd.x0 = roundf(vars->perso.position.x * SIZEPIC);
	// cd.y0 = roundf(vars->perso.position.y * SIZEPIC);
	// cd.x1 = cd.x0 + roundf(vars->perso.direction.x) * 10000;
	// cd.y1 = cd.y0 +  roundf(vars->perso.direction.y) * 10000;
	// line(&(vars->minimap.mini_img), cd, 0xFFFF00);

	//vars->perso.position.x -= 0.1;
	//vars->perso.position.z += 0.1;
	
	re_display_minimap(vars);
}

void	updateDirection(t_vars *vars)
{
	printf("ROT x = %f\n", vars->perso.rotation.y);
	printf("%f\n", (3*PI)/2);
	vars->perso.direction.y = sin(vars->perso.rotation.y) * SPEED; //-1
    vars->perso.direction.x = cos(vars->perso.rotation.y) * SPEED; //0
	
	printf("que avec les cos sin purs:\n\tcos: %f\n", cos(vars->perso.rotation.y));
	printf("\tsin: %f\n", sin(vars->perso.rotation.y));
	
	printf("dir x = %f\n", vars->perso.direction.x);
	printf("dir y = %f\n\n", vars->perso.direction.y);

}

void	moveBackward(t_vars *vars)
{
	//updateDirection(vars);
	vars->perso.position.x -= vars->perso.direction.x;
	vars->perso.position.y += vars->perso.direction.y;
	printf("perso x = %f\n", vars->perso.position.x);
	printf("perso y = %f\n", vars->perso.position.y);
	printf("dir x = %f\n", vars->perso.direction.x);
	printf("dir y = %f\n", vars->perso.direction.y);
	printf("\ndistance parcourue = %f\n", sqrt(pow(vars->perso.direction.x, 2) + pow(vars->perso.direction.y, 2)));
	re_display_minimap(vars);
}

void	moveLeft(t_vars *vars)
{
	vars->perso.position.x += vars->perso.direction.y;
	vars->perso.position.y += vars->perso.direction.x;
	re_display_minimap(vars);
	printf("\nLEFT\nperso x = %f\n", vars->perso.position.x);
	printf("perso y = %f\n", vars->perso.position.y);
	printf("dir x = %f\n", vars->perso.direction.x);
	printf("dir y = %f\n", vars->perso.direction.y);
	printf("\ndistance parcourue = %f\n", sqrt(pow(vars->perso.direction.x, 2) + pow(vars->perso.direction.y, 2)));
}

void	moveRight(t_vars *vars)
{
	vars->perso.position.x -= vars->perso.direction.y;
	vars->perso.position.y -= vars->perso.direction.x;
	re_display_minimap(vars);
	printf("\nRIGHT\nperso x = %f\n", vars->perso.position.x);
	printf("perso y = %f\n", vars->perso.position.y);
	printf("dir x = %f\n", vars->perso.direction.x);
	printf("dir y = %f\n", vars->perso.direction.y);
	printf("\ndistance parcourue = %f\n", sqrt(pow(vars->perso.direction.x, 2) + pow(vars->perso.direction.y, 2)));
}


void	watchLeft(t_vars *vars)
{
	//t_line_cd cd;

	vars->perso.rotation.y += SENSITIVITY;
	/*if (vars->perso.rotation.y -= SENSITIVITY > 0)
		vars->perso.rotation.y = 2 * PI;*/
	//if (vars->perso.rotation.y += SENSITIVITY > 2 * PI)
	//	vars->perso.rotation.y = 0;
	updateDirection(vars);
	// cd.x0 = vars->perso.position.x * SIZEPIC;
	// cd.y0 = vars->perso.position.y * SIZEPIC;
	// cd.x1 = cd.x0 + vars->perso.direction.x;
	// cd.y1 = cd.y0 +  vars->perso.direction.y;
	// line(&(vars->minimap.mini_img), cd, 0xFFFF00);
	// re_display_minimap(vars);
}
void	watchRight(t_vars *vars)
{
	vars->perso.rotation.y -= SENSITIVITY;
	//if (vars->perso.rotation.y += SENSITIVITY > 2 * PI)
	//	vars->perso.rotation.y = 0;
	updateDirection(vars);
}
