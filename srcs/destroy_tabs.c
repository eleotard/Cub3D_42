/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_tabs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:33:46 by eleotard          #+#    #+#             */
/*   Updated: 2023/01/16 20:25:55 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	destroy_inttab(t_vars *vars, int **pix_tab)
{
	int	k;

	k = vars->tile_sz - 1;
	while (k >= 0)
	{
		free(pix_tab[k]);
		k--;
	}
	free(pix_tab);
}

void	destroy_all_inttabs(t_vars *vars)
{
	if (vars->north)
		destroy_inttab(vars, vars->north);
	if (vars->south)
		destroy_inttab(vars, vars->south);
	if (vars->east)
		destroy_inttab(vars, vars->east);
	if (vars->west)
		destroy_inttab(vars, vars->west);
}

void	ft_destroy_map(char **map)
{
	int	k;

	k = 0;
	while (map[k])
		k++;
	while (k >= 0)
	{
		free(map[k]);
		k--;
	}
	free(map);
}
