/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:14:48 by elpastor          #+#    #+#             */
/*   Updated: 2023/01/20 19:11:49 by elpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_file(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '.')
		i++;
	if (s[i] == '.' && !ft_strcmp(&s[i], ".cub"))
		return (1);
	return (0);
}

int	map_is_valid(char *s)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (s[i])
	{
		if (s[i] != '0' && s[i] != '1' && s[i] != 'N' && s[i] != 'S'
			&& s[i] != 'W' && s[i] != 'E' && s[i] != ' ' && s[i] != '\n')
			return (0);
		if (ret == 0 && (s[i] == 'N' || s[i] == 'S'
				|| s[i] == 'W' || s[i] == 'E'))
			ret = 1;
		else if (ret == 1 && (s[i] == 'N' || s[i] == 'S'
				|| s[i] == 'W' || s[i] == 'E'))
			return (0);
		i++;
	}
	if (ret == 0)
		return (0);
	return (1);
}

void	get_map_line(t_vars *vars, int j, char *to_free, char **map)
{
	int		i;
	int		map_l;
	char	**new_map;

	map_l = map_length(map);
	new_map = &vars->map[j];
	new_map[0] = (char *)malloc(sizeof(char) * (map_l + 1));
	if (!new_map[0])
		destroy_all_msg(vars, "Error\nMalloc failed\n", to_free, map);
	i = 0;
	while (map[j][i])
	{
		if (map[j][i] == ' ')
			new_map[0][i] = '1';
		else
			new_map[0][i] = map[j][i];
		i++;
	}
	while (i < map_l)
	{
		new_map[0][i] = '1';
		i++;
	}
	new_map[0][i] = 0;
}

int	splited_map_is_closed(char **map, int j)
{
	int	i;

	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == '0' || map[j][i] == 'N' || map[j][i] == 'S'
					|| map[j][i] == 'W' || map[j][i] == 'E')
			{
				if (j == 0 || i == 0)
					return (0);
				if ((int)ft_strlen(map[j - 1]) <= i || map[j - 1][i] == ' ')
					return (0);
				if ((int)ft_strlen(map[j + 1]) <= i || map[j + 1][i] == ' ')
					return (0);
				if (map[j][i - 1] == ' ' || !map[j][i + 1]
						|| map[j][i + 1] == ' ')
					return (0);
			}
			i++;
		}
		j++;
	}
	return (1);
}
