/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:07:38 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/05 19:42:13 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

	//mlx_get_screen_size(vars->mlx, &x, &y);

void	defineProjPlanDist(t_vars *vars)
{
	vars->projPlanDist = (vars->gameWinWide / 2) / tan(FOV_ANGLE / 2);
	printf(RED "distance plan de projection = %f\n" RESET, vars->projPlanDist);
}

//WallStripHeight = hauteur totale de la bande du mur en pixel
//hauteur du mur qui est aussi egale a TILE_SIZE

void	render(t_vars *vars)
{
	defineProjPlanDist(vars);
}