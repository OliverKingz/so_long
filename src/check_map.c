/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:57:02 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/17 19:52:27 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * Checklist:
 * - Does the map file exist ? Looking fd result when opened, reason in perror
 * - Is the map rectangular ? All the lines should be the same length.
 * - Is there something in the map file ?
 * - Is the map enclosed in walls ? Check the first and last lines and columns 
 * - Is there only one exit ? Simply count how many E you find on the map.
 * - Is there only one start position ? Simply count how many P on the map.
 * - Is there at least one collectibles ? Simply count how many C on the map.
 * - Is the map solvable? Is there a way valid way?
 */

void	check_map_file(char *map_dir)
{
	int		fd;
	char	buffer[1];
	ssize_t	bytes_read;

	fd = open(map_dir, O_RDONLY);
	if (fd == -1)
		ft_mlx_err("Error opening map file");
	bytes_read = read(fd, buffer, 1);
	if (bytes_read == 0)
		(close(fd), ft_mlx_err("Invalid map: file is empty"));
	else if (bytes_read == -1)
		(close(fd), ft_mlx_err("Invalid map: error reading"));
	close(fd);
}

void	check_map_elements(t_game *game)
{
	int	j;
	int	i;
	int	exit_counter;
	int	player_counter;

	exit_counter = 0;
	player_counter = 0;
	j = -1;
	while (++j < game->map.height)
	{
		i = -1;
		while (++i < game->map.width)
		{
			if (game->map.grid[j][i] == 'C')
				game->map.collect++;
			else if (game->map.grid[j][i] == 'E')
				exit_counter++;
			else if (game->map.grid[j][i] == 'P')
				player_counter++;
		}
	}
	check_map_elements_aux(game, exit_counter, player_counter);
}

void	check_map_enclosed(t_game *game)
{
	int	j;
	int	i;

	i = 0;
	while (i < game->map.width)
	{
		if ((game->map.grid[0][i] != '1')
			|| (game->map.grid[game->map.height - 1][i] != '1'))
		{
			free_map_grid(game);
			ft_mlx_err("Invalid map: needs enclosed in Walls (row check)");
		}
		i++;
	}
	j = 0;
	while (j < game->map.height)
	{
		if ((game->map.grid[j][0] != '1')
			|| (game->map.grid[j][game->map.width - 1] != '1'))
		{
			free_map_grid(game);
			ft_mlx_err("Invalid map: needs enclosed in Walls (column check)");
		}
		j++;
	}
}

void	flood_fill(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map.width
		|| y < 0 || y >= game->map.height)
		return ;
	if (game->map.grid[y][x] == '1' || game->map.grid[y][x] == 'X') // Already visited or wall
		return;
	if (game->map.grid[y][x] != '0' && game->map.grid[y][x] != 'C' && game->map.grid[y][x] != 'E')
		return;
	game->map.grid[y][x] = 'X';
	flood_fill(game, x + 1, y);
	flood_fill(game, x - 1, y);
	flood_fill(game, x, y + 1);
	flood_fill(game, x, y - 1);
}

void	check_map_solvable(t_game *game, char *map_dir)
{
	flood_fill(game, game->player.x, game->player.y);

	print_map_grid(game);
	ft_putchar('\n');

	int y, x;
	for (y = 0; y < game->map.height; y++)
	{
		for (x = 0; x < game->map.width; x++)
		{
			if (game->map.grid[y][x] == 'C' || game->map.grid[y][x] == 'E')
			{
				free_map_grid(game);
				ft_mlx_err("Invalid map: not all collectibles or exit are reachable");
			}
		}
	}
	free_map_grid(game);
	make_map_grid(game, map_dir);
}

// void	fill(char **tab, t_point size, t_point begin, char to_fill)
// {
// 	if(begin.x < 0 || begin.x >= size.x
// 		|| begin.y < 0 || begin.y >= size.y
// 		|| tab[begin.y][begin.x] != to_fill)
// 		return ;

// 	tab[begin.y][begin.x] = 'F';
// 	fill(tab, size, (t_point){begin.x + 1, begin.y}, to_fill);
// 	fill(tab, size, (t_point){begin.x - 1, begin.y}, to_fill);
// 	fill(tab, size, (t_point){begin.x, begin.y + 1}, to_fill);
// 	fill(tab, size, (t_point){begin.x, begin.y - 1}, to_fill);
// }

// void  flood_fill(char **tab, t_point size, t_point begin)
// {
// 	fill(tab, size, begin, tab[begin.y][begin.x]);
// }
