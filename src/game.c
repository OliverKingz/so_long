/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:55:35 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/29 17:16:19 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move(t_game *game, int dx, int dy)
{
	int		new_x;
	int		new_y;
	char	next_tile;

	new_x = game->play.x + dx;
	new_y = game->play.y + dy;
	next_tile = game->map.grid[new_y][new_x];
	if (new_x < 0 || new_x >= game->map.width
		|| new_y < 0 || new_y >= game->map.height)
		return ;
	if (!allow_to_move(game, new_x, new_y, next_tile))
		return ;
	if (game->is_running == true)
	{
		game->play.x = new_x;
		game->play.y = new_y;
		game->graphs.play->instances[0].x += (dx * game->map.t_size);
		game->graphs.play->instances[0].y += (dy * game->map.t_size);
		game->moves++;
		display_text(game);
	}
}

bool	allow_to_move(t_game *game, int new_x, int new_y, char next_tile)
{
	if (next_tile == '1')
		return (false);
	else if (next_tile == 'C')
	{
		game->map.item--;
		ft_printf("Items left: 0%d\n", game->map.item);
		game->map.grid[new_y][new_x] = '0';
		display_img(game, game->graphs.floor, new_x, new_y);
		return (true);
	}
	else if (next_tile == 'E')
	{
		if (game->map.item == 0)
		{
			mlx_close_window(game->mlx);
			ft_printf("You win!\n");
			game->is_running = false;
			free_game(game);
			return (false);
		}
		ft_printf("Items left: 0%d\n", game->map.item);
		return (false);
	}
	return (true);
}
