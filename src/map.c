/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:49:16 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/18 17:50:19 by ozamora-         ###   ########.fr       */
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
	check_map_file(game, map_dir);
	read_map(game, map_dir);
	make_map_grid(game, map_dir);
	init_player(game);
	check_map_enclosed(game);
	check_map_elements(game);
	check_map_solvable(game, map_dir);
	if (!game->map.is_valid)
		(free_game(game), ft_mlx_err("Error parsing map"));
}

void	read_map(t_game *game, char *map_dir)
{
	int		fd;
	char	*line;
	int		line_len;

	fd = open(map_dir, O_RDONLY);
	if (fd == -1)
		(free_graphs(game), ft_mlx_err("Invalid map: unable to open"));
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
		(free_graphs(game), ft_mlx_err("Invalid map: not rectangular"));
}

void	make_map_grid(t_game *game, char *map_dir)
{
	int		fd;
	char	**grid;
	int		j;

	grid = malloc(game->map.height * sizeof(char *));
	if (!grid)
		(free_graphs(game), ft_mlx_err("Failed malloc"));
	fd = open(map_dir, O_RDONLY);
	if (fd == -1)
		(free_graphs(game), free(grid), ft_mlx_err("Invalid map: unable open"));
	j = -1;
	while (++j < game->map.height)
	{
		grid[j] = get_next_line(fd);
		if (grid[j] == NULL)
		{
			while (j-- > 0)
				free(grid[j]);
			free_graphs(game);
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
		ft_mlx_err("Invalid map: unable to open or doesn't exists");
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
