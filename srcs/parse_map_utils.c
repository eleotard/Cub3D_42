/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 19:15:22 by elpastor          #+#    #+#             */
/*   Updated: 2023/01/19 19:56:50 by elpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	is_in_map(char *s)
{
	int	i;
	int	in_map;

	i = 0;
	in_map = 0;
	if (!s)
		return (0);
	if (s[i] && s[i] == '\n' && (s[i + 1] == '0' || s[i + 1] == '1'
			|| s[i + 1] == 'N' || s[i + 1] == 'S' || s[i + 1] == 'W'
			|| s[i + 1] == 'E' || s[i + 1] == ' '))
		return (1);
	while (s[i] && s[i] != '\n')
	{
		if (s[i] != '0' && s[i] != '1' && s[i] != 'N' && s[i] != 'S'
			&& s[i] != 'W' && s[i] != 'E' && s[i] != ' ')
			return (0);
		else
			in_map = 1;
		i++;
	}
	return (in_map);
}

int	is_in_map_wbn(char *s)
{
	int	i;
	int	in_map;

	i = 0;
	in_map = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] != '0' && s[i] != '1' && s[i] != 'N' && s[i] != 'S'
			&& s[i] != 'W' && s[i] != 'E' && s[i] != ' ' && s[i] != '\n')
			return (0);
		else
			in_map = 1;
		i++;
	}
	return (in_map);
}

int	get_map_height(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (s[i] && is_in_map(&s[i]))
	{
		if (s[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

int	map_height(char **map)
{
	int	i;

	i = 0;
	while (map[i] && is_in_map_wbn(map[i]))
		i++;
	return (i);
}

int	map_length(char **map)
{
	int	i;
	int	max;

	i = 0;
	max = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
		i++;
	}
	return (max);
}
