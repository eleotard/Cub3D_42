/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 18:31:17 by eleotard          #+#    #+#             */
/*   Updated: 2022/12/13 20:54:52 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

/*void	ft_move_left(t_vars *vars)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (vars->map[++i])
	{
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == 'P')
				break ;
			j++;
		}
		if (vars->map[i][j] == 'P')
			break ;
		j = 0;
	}
	if (vars->map[i][j - 1] != '1' && (j > 0))
		ft_swap_perso(vars, &vars->map[i][j],
			&vars->map[i][j - 1], count);
}

void	ft_move_right(t_vars *vars)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (vars->map[++i])
	{
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == 'P')
				break ;
			j++;
		}
		if (vars->map[i][j] == 'P')
			break ;
		j = 0;
	}
	if (vars->map[i][j + 1] != '1' && j < (ft_map_wide(vars->map) - 2))
		ft_swap_perso(vars, &vars->map[i][j],
			&vars->map[i][j + 1], count);
}

void	ft_move_up(t_vars *vars)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (vars->map[++i])
	{
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == 'P')
				break ;
			j++;
		}
		if (vars->map[i][j] == 'P')
			break ;
		j = 0;
	}
	if (vars->map[i - 1][j] != '1' && (i > 0))
		ft_swap_perso(vars, &vars->map[i][j],
			&vars->map[i - 1][j], count);
}

void	ft_move_down(t_vars *vars)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (vars->map[++i])
	{
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == 'P')
				break ;
			j++;
		}
		if (vars->map[i][j] == 'P')
			break ;
		j = 0;
	}
	if (vars->map[i + 1][j] != '1' && (i < (ft_map_height(vars->map) - 2)))
		ft_swap_perso(vars, &vars->map[i][j],
			&vars->map[i + 1][j], count);
}*/