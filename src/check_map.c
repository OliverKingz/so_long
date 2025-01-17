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

void	check_map_solvable(t_game *game);

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

void	fill(t_game *game, int begin_x, int begin_y, char to_fill)
{
	if (begin_x < 0 || begin_x >= game->map.width
		|| begin_y < 0 || begin_y >= game->map.height
		|| game->map.grid[begin_y][begin_x] != to_fill)
		return ;

	game->map.grid[begin_y][begin_x] = 'P';
	fill(game, begin_x + 1, begin_y, to_fill);
	fill(game, begin_x - 1, begin_y, to_fill);
	fill(game, begin_x, begin_y + 1, to_fill);
	fill(game, begin_x, begin_y - 1, to_fill);
}

void  flood_fill(t_game *game, char *map_dir)
{
	fill(game, game->player.x, game->player.y, 'P');
	print_map_grid(game);
	free_map_grid(game);
	make_map_grid(game, map_dir);
}
