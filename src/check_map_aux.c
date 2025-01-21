/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:56:55 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/21 12:06:30 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_map_elements_aux(t_game *game, int exit_count, int player_count)
{
	if (game->map.collect == 0)
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

void	flood_fill(t_game *game, int x, int y)
{
	if (x < 0 || x >= game->map.width
		|| y < 0 || y >= game->map.height)
		return ;
	if (game->map.grid[y][x] == '1' || game->map.grid[y][x] == 'X'
		|| game->map.grid[y][x] == 'E')
	{
		if (game->map.grid[y][x] == 'E')
			game->map.is_valid = true;
		return ;
	}
	if (game->map.grid[y][x] == 'C')
		game->map.collect--;
	game->map.grid[y][x] = 'X';
	flood_fill(game, x + 1, y);
	flood_fill(game, x - 1, y);
	flood_fill(game, x, y + 1);
	flood_fill(game, x, y - 1);
}
