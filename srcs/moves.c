/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elsie <elsie@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 18:31:17 by eleotard          #+#    #+#             */
/*   Updated: 2022/12/17 20:47:49 by elsie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	moveForeward(t_vars *vars)
{
	printf("passe\n");
	//updateDirection(vars);
	vars->perso.position.x += vars->perso.direction.x;
	vars->perso.position.y -= vars->perso.direction.y;
	printf("perso x = %f\n", vars->perso.position.x);
	printf("perso y = %f\n", vars->perso.position.y);
	printf("dir x = %f\n", vars->perso.direction.x);
	printf("dir y = %f\n", vars->perso.direction.y);

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

	printf("%f\n", cos((3*PI)/2));
	printf("%f\n", sin((3*PI)/2));
	
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
}


void	watchLeft(t_vars *vars)
{
	//t_line_cd cd;

	//cd.x0 = vars->perso.position.x;
	//cd.y0 = vars->perso.position.z;
	vars->perso.rotation.y += SENSITIVITY;
	/*if (vars->perso.rotation.y -= SENSITIVITY > 0)
		vars->perso.rotation.y = 2 * PI;*/
	//if (vars->perso.rotation.y += SENSITIVITY > 2 * PI)
	//	vars->perso.rotation.y = 0;
	updateDirection(vars);
	//cd.x1 = cd.x0 * SIZEPIC + cos(vars->perso.rotation.y);
	//cd.y1 = cd.y0 * SIZEPIC + sin(vars->perso.rotation.y);
	re_display_minimap(vars);
	//line(&(vars->minimap.mini_img), cd, 0xFFFF00);
}
void	watchRight(t_vars *vars)
{
	vars->perso.rotation.y -= SENSITIVITY;
	//if (vars->perso.rotation.y += SENSITIVITY > 2 * PI)
	//	vars->perso.rotation.y = 0;
	updateDirection(vars);
}
