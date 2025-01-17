/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:56:55 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/17 15:13:53 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_map_elements_aux(t_game *game, int exit_count, int player_count)
{
	if (game->map.collect == 0)
	{
		game->map.is_valid = false;
		free_map_grid(game);
		ft_mlx_err("Invalid map: needs 1+ Collectibles");
	}
	if (exit_count != 1)
	{
		game->map.is_valid = false;
		free_map_grid(game);
		ft_mlx_err("Invalid map: needs 1x Exit only");
	}
	if (player_count != 1)
	{
		game->map.is_valid = false;
		free_map_grid(game);
		ft_mlx_err("Invalid map: needs 1x Player only");
	}
}
