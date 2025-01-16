#include "so_long.h"

/**
 * Checklist:
 * - Does the map file exist ? Looking fd result when opened, reason in perror
 * - Is the map rectangular ? All the lines should be the same length.
 * - Is there something in the map file ?
 * - Is the map enclosed in walls ? Check the first and last lines and columns, they should all be 1. 
 * - Is there only one exit ? Simply count how many E you find on the map.
 * - Is there only one start position ? Simply count how many P you find on the map.
 * - Is there at least one collectibles ? Simply count how many C you find on the map.
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
	if (game->map.collect == 0)
		(free_map_grid(game), ft_mlx_err("Invalid map: needs 1+ Collectibles"));
	if (exit_counter != 1)
		(free_map_grid(game), ft_mlx_err("Invalid map: needs 1x Exit only"));
	if (player_counter != 1)
		(free_map_grid(game), ft_mlx_err("Invalid map: needs 1x Player only"));
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
