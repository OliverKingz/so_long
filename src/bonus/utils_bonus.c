/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 13:00:36 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/25 16:12:49 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	print_map(char *map_dir)
{
	int		fd;
	char	*line;

	fd = open(map_dir, O_RDONLY);
	if (fd == -1)
		ft_mlx_err("Invalid map: unable to open or doesn't exists", NULL);
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

void	flood_fill(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map.width
		|| y < 0 || y >= game->map.height)
		return ;
	if (game->map.grid[y][x] == '1' || game->map.grid[y][x] == '*'
		|| game->map.grid[y][x] == 'E' || game->map.grid[y][x] == 'X')
	{
		if (game->map.grid[y][x] == 'E')
			game->map.is_valid = true;
		return ;
	}
	if (game->map.grid[y][x] == 'C')
		game->map.item--;
	game->map.grid[y][x] = '*';
	flood_fill(game, x + 1, y);
	flood_fill(game, x - 1, y);
	flood_fill(game, x, y + 1);
	flood_fill(game, x, y - 1);
}
