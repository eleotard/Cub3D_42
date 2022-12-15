/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eleotard <eleotard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 17:19:58 by eleotard          #+#    #+#             */
/*   Updated: 2022/12/15 21:22:33 by eleotard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"
#include "../minilibx-linux/mlx.h"





int	ft_map_height(char **map)
{
	int	k;

	k = 0;
	while (map[k])
		k++;
	return (k);
}

int	ft_map_wide(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i][j])
		j++;
	return (j);
}

int	ft_check_cub(char *map_name)
{
	int		i;
	int		j;
	char	*extension;

	i = 0;
	j = 0;
	while (map_name[i])
		i++;
	if (i <= 4)
	{
		ft_putstr_fd("Error\nWrong map file format\n", 2);
		return (ERROR);
	}
	j = i - 4;
	extension = ft_substr(map_name, j, 4);
	if (ft_strcmp(extension, ".cub") != 0)
	{
		free(extension);
		ft_putstr_fd("Error\nWrong map file format\n", 2);
		return (ERROR);
	}
	free(extension);
	return (0);
}

// A CHANGER POUR PRENDRE QUE LA MAP ET PAS LES TRUCS D AVANT
	//il faudra isoler la map pour la mettre dans un tableau de tableau 
		//afin de pouvoir lui appliquer les ft si dessous
	//il faudra aussi faire deux autres tableaux de tableaux (ou liste chainee aussi)
		//un avec les paths des textures NSEW
		//un avec les couleurs du sol et du ciel
		//il faudra ajouter ces tab dans la structure vars a cote de char **map

char	*create_map_str(char *map_name)
{
	char	*map_str;
	char	*tmp;
	int		fd;

	map_str = malloc(sizeof(char) * 1);
	if (!map_str)
		return (NULL);
	map_str[0] = '\0';
	tmp = malloc(sizeof(char) * 1);
	if (!tmp)
		return (free(map_str), NULL);
	tmp[0] = '1';
	fd = open(map_name, O_RDONLY);
	while (ft_strcmp(tmp, map_str) != 0)
	{
		tmp = ft_free(tmp, NULL);
		tmp = ft_strdup(map_str);
		map_str = join(map_str, get_next_line(fd));
		if (!map_str)
			break ;
	}
	if (!map_str)
		return (free(tmp), NULL);
	free(tmp);
	close(fd);
	//en dessous : check si ya autre chose que 1 0 N S W E
	if (ft_parsing_check(map_str) == ERROR)
		return (NULL);
	return (map_str);
}

char	**create_map_tab(char *map_name)
{
	char	*map_str;
	char	**map;

	map_str = create_map_str(map_name);
	if (!map_str)
		return (NULL);
	map = ft_split(map_str, '\n');
	if (!map)
		return (free(map_str), NULL);
	free(map_str);
		
	//CHECK DU PARSING SUR LE TAB DE TAB
		//que la map soit pas trop petite
		//que c'est bien ferme
		//que yait pas deux personnages
	return (map);
}

void	ft_mlx_win_init(t_vars *vars)
{
	int		win_height;
	int		win_wide;

	vars->mlx = mlx_init();
	if (!vars->mlx)
	{
		ft_destroy_map(vars->map);
		ft_print_error_exit("Error\nMlx pointer == NULL");
	}
	//ft_img_init(vars);
	win_height = SIZEPIC * ft_map_height(vars->map);
	win_wide = SIZEPIC * ft_map_wide(vars->map);
	vars->minimap.win = mlx_new_window(vars->mlx, win_wide, win_height,
			"minimap");
	if (!vars->minimap.win)
		ft_destroy_all_message(vars->map, vars->mlx,
			"Error\nWin pointer == NULL\n");
	init_perso_pos(vars);
	printf("perso x = %f\n", vars->perso.position.x);
	//init_perso_pos_y(vars);
	printf("perso y = %f\n", vars->perso.position.y);
	set_minimap(vars);
}

//ORDRE: (NORMALEMENT)
	//checker le nb d'arguments
	//checker l'extension du fichier
	//creer le tableau de tableau du fichier
	//init la mlx et win
	//display la minimap avec la grille et des cases colorees pour les murs
	//grille: faire l'interieur d'une couleur et la bordure d'une autre


int	main(int argc, char **argv)
{
	t_vars	vars;
	vars = (t_vars){0}; //initialise la strcutures et celles a l'interieur
	if (argc != 2)
		return (-1);
	if (ft_check_cub(argv[1]) == ERROR)
		return (-2);
	vars.map = create_map_tab(argv[1]);
	if (!vars.map)
		return (-3);
	ft_mlx_win_init(&vars);
	mlx_hook(vars.minimap.win, KeyPress, KeyPressMask, ft_key_hook, &vars);
	mlx_hook(vars.minimap.win, ClientMessage, LeaveWindowMask, ft_mouse_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}


	/*t_vars	vars =
	{
		NULL, NULL, NULL, {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	}
	};*/