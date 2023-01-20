/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elpastor <elpastor@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 17:46:00 by elpastor          #+#    #+#             */
/*   Updated: 2023/01/20 19:13:01 by elpastor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*file_to_str(char *fichier, t_vars *vars)
{
	int		fd;
	char	*ret;
	char	*str;

	str = NULL;
	fd = open(fichier, O_DIRECTORY);
	if (fd != -1)
		destroy_all_msg(vars, "Error\nFile '.cub' is a directory\n", NULL, NULL);
	fd = open(fichier, O_RDONLY);
	if (fd == -1)
		destroy_all_msg(vars, "Error\nFile '.cub' invalid\n", NULL, NULL);
	ret = get_next_line(fd);
	while (ret)
	{
		str = ft_strjoinspe(str, ret);
		free(ret);
		ret = get_next_line(fd);
	}
	close(fd);
	return (str);
}

int	get_color_and_texture(char *s, t_vars *vars)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == 'N' && s[i + 1] == 'O')
			i += get_texture(&s[i], vars, 0, s);
		else if (s[i] == 'S' && s[i + 1] == 'O')
			i += get_texture(&s[i], vars, 1, s);
		else if (s[i] == 'W' && s[i + 1] == 'E')
			i += get_texture(&s[i], vars, 2, s);
		else if (s[i] == 'E' && s[i + 1] == 'A')
			i += get_texture(&s[i], vars, 3, s);
		else if (s[i] == 'F' || s[i] == 'C')
			i += get_color(&s[i], vars, s);
		else if (s[i] != '\n' && is_in_map(&s[i]))
			break ;
		else if (s[i] != '\n')
			destroy_all_msg(vars, "Error\nInvalid char in '.cub'\n", s, NULL);
		else
			i++;
	}
	if (!s[i])
		return (0);
	return (i);
}

void	verify_colors_and_texture(t_vars *vars, char *to_free)
{
	int	i;

	i = 0;
	if (vars->floor == -1 || vars->ceiling == -1)
		destroy_all_msg(vars, "Error\nFile '.cub' invalid, color not defined\n",
			to_free, NULL);
	while (i < 4)
	{
		if (vars->textures[i].ptr == NULL)
			destroy_all_msg(vars,
				"Error\nFile '.cub' invalid, texture not defined\n",
				to_free, NULL);
		i++;
	}
}

void	get_map(char *s, t_vars *vars, char *to_free)
{
	int		i;
	char	**map;

	if (!map_is_valid(s))
		destroy_all_msg(vars, "Error\nFile '.cub' invalid map\n", to_free, NULL);
	map = ft_split(s, '\n');
	if (!splited_map_is_closed(map, 0))
		destroy_all_msg(vars, "Error\nMap not closed\n", to_free, map);
	vars->map = (char **)malloc(sizeof(char *) * (get_map_height(s) + 1));
	if (!vars->map)
		destroy_all_msg(vars, "Error\nMalloc failed\n", to_free, map);
	i = 0;
	while (map[i])
		i++;
	if (i != get_map_height(s))
	{
		free(vars->map);
		vars->map = NULL;
		destroy_all_msg(vars, "Error\nMap has empty line\n", to_free, map);
	}
	i = -1;
	while (map[++i])
		get_map_line(vars, i, to_free, map);
	vars->map[i] = 0;
	ft_destroy_map(map);
}

void	parsing(char *fichier, t_vars *vars)
{
	char	*str;
	int		i;

	vars->textures = (t_img *)malloc(sizeof(t_img) * 4);
	if (!vars->textures)
		destroy_all_msg(vars, "Error\nMalloc failed\n", NULL, NULL);
	vars->floor = -1;
	vars->ceiling = -1;
	i = 0;
	while (i < 4)
		vars->textures[i++].ptr = NULL;
	if (!check_file(fichier))
		destroy_all_msg(vars, "Error\nFile name invalid\n", NULL, NULL);
	str = file_to_str(fichier, vars);
	if (!str)
		destroy_all_msg(vars, "Error\nFile '.cub' empty\n", NULL, NULL);
	i = get_color_and_texture(str, vars);
	verify_colors_and_texture(vars, str);
	get_map(&str[i], vars, str);
	free(str);
}
