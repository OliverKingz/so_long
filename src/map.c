/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliverkingz <oliverkingz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:49:16 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/17 00:39:23 by oliverkingz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_map(t_game *game, char *map_dir)
{
	game->map.width = 0;
	game->map.height = 0;
	game->map.t_size = game->graphs.floor_t->width;
	game->map.collect = 0;
	game->map.is_valid = true;
	check_map_file(map_dir);
	read_map(game, map_dir);
	make_map_grid(game, map_dir);
	check_map_enclosed(game);
	check_map_elements(game);
	if (!game->map.is_valid)
		(free_map_grid(game), ft_mlx_err("Error parsing map"));
}

void	read_map(t_game *game, char *map_dir)
{
	int		fd;
	char	*line;
	size_t	line_len;

	fd = open(map_dir, O_RDONLY);
	if (fd == -1)
		ft_mlx_err("Error opening map file");
	line = get_next_line(fd);
	while (line != NULL)
	{
		line_len = ft_strlen(line);
		if (line[line_len - 1] == '\n')
			line_len--;
		if (game->map.height == 0)
			game->map.width = line_len;
		else if (line_len != game->map.width)
			game->map.is_valid = false;
		game->map.height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	if (game->map.is_valid == false)
		ft_mlx_err("Invalid map: not rectangular or inconsistent dimensions");
}

void	make_map_grid(t_game *game, char *map_dir)
{
	int		fd;
	char	**grid;
	int		i;

	grid = malloc(game->map.height * sizeof(char *));
	if (!grid)
		ft_mlx_err("Failed malloc");
	fd = open(map_dir, O_RDONLY);
	if (fd == -1)
		(free(grid), ft_mlx_err("Error opening map file"));
	i = -1;
	while (++i < game->map.height)
	{
		grid[i] = get_next_line(fd);
		if (grid[i] == NULL)
		{
			while (i-- > 0)
				free(grid[j]);
			(free(grid), close(fd), ft_mlx_err("Error to get next line"));
		}
	}
	close(fd);
	game->map.grid = grid;
}

void	print_map(char *map_dir)
{
	int		fd;
	char	*line;

	fd = open(map_dir, O_RDONLY);
	if (fd == -1)
		ft_mlx_err("Error opening map file");
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

void	print_map_grid(t_game *game)
{
	int	i;
	int	j;

	j = 0;
	while (j < game->map.height)
	{
		i = 0;
		while (i < game->map.width)
		{
			ft_putchar(game->map.grid[j][i]);
			i++;
		}
		ft_putchar('\n');
		j++;
	}
}
