/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliverkingz <oliverkingz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:49:16 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/12 17:41:02 by oliverkingz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_game	init_game(t_game *game, char *map_dir);
void	init_map(t_game *game, char *map_dir);
//void	init_graph();

t_game	init_game(t_game *game, char *map_dir)
{
	init_map(game, map_dir);
	return *game;
}

void	init_map(t_game *game, char *map_dir)
{
	int		fd;
	char	*line;

	read_map(game, map_dir);
	if (game->map.is_valid)
		make_map_grid(game, map_dir);
}

void	read_map(t_game *game, char *map_dir)
{
	int		fd;
	char	*line;
	int 	row;

	game->map.is_valid = true;
	fd = open(map_dir, O_RDONLY);
	if (fd == -1)
		ft_error();
	row = 0;
	line = get_next_line(fd);
	if (line != NULL)
		(game->map.width = ft_strlen(line), row++, free(line));
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		else
			row++;
			if (game->map.width != ft_strlen(line))
				game->map.is_valid = false;
		free(line);
	}
	(free(line), close(fd));
	game->map.height = row;
}

void	make_map_grid(t_game *game, char *map_dir)
{
	int		fd;
	char	*line;
	char	**grid;
	int		i;

	grid = malloc(game->map.height * sizeof(char *));
	fd = open(map_dir, O_RDONLY);
	if (fd == -1)
		ft_error();
	i = 0;
	while (i < game->map.height)
	{
		grid[i] = get_next_line(fd);
		i++;
	}
}

void	print_map_grid(t_game *game, char *map_dir)
{
	int		fd;
	char	*line;

	(void)game;
	fd = open(map_dir, O_RDONLY);
	if (fd == -1)
		ft_error();
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		else
			ft_printf("%s", line);
		free(line);
	}
	free(line);
	close(fd);
}
