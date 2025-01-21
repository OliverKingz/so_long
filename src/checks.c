/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:57:02 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/21 14:46:42 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
				game->map.item++;
			else if (game->map.grid[j][i] == 'E')
				exit_counter++;
			else if (game->map.grid[j][i] == 'P')
				player_counter++;
		}
	}
	check_elements(game, exit_counter, player_counter);
}

void	check_elements(t_game *game, int exit_count, int player_count)
{
	if (game->map.item == 0)
	{
		game->map.is_valid = false;
		(free_textures(game), free_map_grid(game));
		ft_mlx_err("Invalid map: needs 1+ Collectibles");
	}
	if (exit_count != 1)
	{
		game->map.is_valid = false;
		(free_textures(game), free_map_grid(game));
		ft_mlx_err("Invalid map: needs 1x Exit only");
	}
	if (player_count != 1)
	{
		game->map.is_valid = false;
		(free_textures(game), free_map_grid(game));
		ft_mlx_err("Invalid map: needs 1x Player only");
	}
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
			(free_textures(game), free_map_grid(game));
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
			(free_textures(game), free_map_grid(game));
			ft_mlx_err("Invalid map: needs enclosed in Walls (column check)");
		}
		j++;
	}
}

void	check_map_solvable(t_game *game, char *map_dir)
{
	int	item_count;

	item_count = game->map.item;
	game->map.is_valid = false;
	flood_fill(game, game->player.x, game->player.y);
	print_map_grid(game);
	ft_putchar('\n');
	if (game->map.item > 0)
	{
		(free_textures(game), free_map_grid(game));
		ft_mlx_err("Invalid map: Collectibles aren't reachable");
	}
	if (game->map.is_valid == false)
	{
		(free_textures(game), free_map_grid(game));
		ft_mlx_err("Invalid map: Exit is not reachable");
	}
	game->map.item = item_count;
	free_map_grid(game);
	make_map_grid(game, map_dir);
}

void	flood_fill(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map.width
		|| y < 0 || y >= game->map.height)
		return ;
	if (game->map.grid[y][x] == '1' || game->map.grid[y][x] == 'W'
		|| game->map.grid[y][x] == 'E')
	{
		if (game->map.grid[y][x] == 'E')
			game->map.is_valid = true;
		return ;
	}
	if (game->map.grid[y][x] == 'C')
		game->map.item--;
	game->map.grid[y][x] = 'W';
	flood_fill(game, x + 1, y);
	flood_fill(game, x - 1, y);
	flood_fill(game, x, y + 1);
	flood_fill(game, x, y - 1);
}
