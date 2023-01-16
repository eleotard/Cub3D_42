/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 21:10:16 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/16 20:25:55 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	init_player_pos(t_vars *vars)
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
				vars->player.pos.x = (j + 0.5) * vars->tile_sz;
				vars->player.pos.y = (i + 0.5) * vars->tile_sz;
				init_player_rotation(vars, vars->map[i][j]);
				update_direction(vars);
			}
		}
	}
}

void	init_player_rotation(t_vars *vars, char dir)
{
	if (dir == 'N')
		vars->player.rotation.y = -(PI / 2);
	else if (dir == 'S')
		vars->player.rotation.y = PI / 2;
	else if (dir == 'E')
		vars->player.rotation.y = 0;
	else if (dir == 'W')
		vars->player.rotation.y = PI;
}
