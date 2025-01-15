/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:49:16 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/15 19:35:21 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	read_map(t_game *game, char *map_dir)
{
	int		fd;
	char	*line;

	fd = open(map_dir, O_RDONLY);
	if (fd == -1)
		ft_mlx_err("Invalid map direction");
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (game->map.height == 0)
			game->map.width = ft_strlen(line);
		game->map.height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

// void	read_map(t_game *game, char *map_dir)
// {
// 	int		fd;
// 	char	*line;
// 	int		row;

// 	game->map.is_valid = true;
// 	fd = open(map_dir, O_RDONLY);
// 	if (fd == -1)
// 		ft_mlx_err("Invalid map direction");
// 	row = 0;
// 	line = get_next_line(fd);
// 	if (line != NULL)
// 	{
// 		game->map.width = ft_strlen(line);
// 		row++;
// 		free(line);
// 	}
// 	while (1)
// 	{
// 		line = get_next_line(fd);
// 		if (line == NULL)
// 			break ;
// 		else
// 			row++;
// 		if (game->map.width != (int)ft_strlen(line))
// 			game->map.is_valid = false;
// 		free(line);
// 	}
// 	(free(line), close(fd));
// 	game->map.height = row;
// }

void	make_map_grid(t_game *game, char *map_dir)
{
	int		fd;
	char	**grid;
	int		i;
	int		j;

	grid = malloc(game->map.height * sizeof(char *));
	if (!grid)
		ft_mlx_err("Failed malloc");
	fd = open(map_dir, O_RDONLY);
	if (fd == -1)
		(free(grid), ft_mlx_err("Invalid map dir"));
	i = -1;
	while (++i < game->map.height)
	{
		grid[i] = get_next_line(fd);
		if (grid[i] == NULL)
		{
			j = -1;
			while (++j < i)
				free(grid[j]);
			(free(grid), close(fd), ft_mlx_err("Failed to get next line"));
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
		ft_mlx_err("Invalid map dir");
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
		// putchar('\n');
		j++;
	}
}
