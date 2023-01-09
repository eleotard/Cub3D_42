/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_perso.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:10:16 by eleotard          #+#    #+#             */
/*   Updated: 2022/12/19 19:03:43 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_perso_pos(t_vars *vars)
{
	int	i;
	int	j;

	i = -1;
	while (vars->map[++i])
	{
		j = -1;
		while (vars->map[i][++j])
		{
			if (vars->map[i][j] == 'N' || vars->map[i][j] == 'S'
				|| vars->map[i][j] == 'E' || vars->map[i][j] == 'W')
			{
				vars->perso.pos.x = j + 0.5;
				vars->perso.pos.y = i + 0.5;
				init_perso_rotation(vars, vars->map[i][j]);
				updateDirection(vars);
			}
		}
	}
}


void	init_perso_rotation(t_vars *vars, char dir)
{
	if (dir == 'N')
		vars->perso.rot.y = PI/2;
	else if (dir == 'S')
		vars->perso.rot.y = (3 * PI) / 2;
	else if (dir == 'E')
		vars->perso.rot.y = 0;
	else if (dir == 'W')
		vars->perso.rot.y = PI;
}