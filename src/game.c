/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:55:35 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/17 11:28:22 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	display(t_game *game, mlx_image_t *tile, int x, int y)
{
	int32_t	i_instance;

	i_instance = mlx_image_to_window(game->mlx, tile, game->map.t_size * x,
			game->map.t_size * y);
	if (i_instance < 0)
		(free_game(game), ft_mlx_err("Failed displaying image"));
	mlx_set_instance_depth(game->player.img->instances,
		tile->instances[i_instance].z + 2);
}

void	display_text(t_game *game)
{
	char	*moves;

	moves = ft_itoa(game->moves);
	ft_printf("Moves: %d\n", game->moves);
	mlx_delete_image(game->mlx, game->graphs.text);
	game->graphs.text = mlx_put_string(game->mlx, moves, 6, 4);
	free(moves);
}

void	move(t_game *game, int dx, int dy)
{
	int		new_x;
	int		new_y;
	char	next_tile;

	new_x = game->player.x + dx;
	new_y = game->player.y + dy;
	next_tile = game->map.grid[new_y][new_x];
	if (new_x < 1 || new_x >= game->map.width - 1
		|| new_y < 1 || new_y >= game->map.height - 1)
		return ;
	if (!allow_to_move(game, new_x, new_y, next_tile))
		return ;
	if (game->is_running == true)
	{
		game->player.x = new_x;
		game->player.y = new_y;
		game->player.img->instances[0].x += (dx * game->map.t_size);
		game->player.img->instances[0].y += (dy * game->map.t_size);
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
		game->map.collect--;
		game->map.grid[new_y][new_x] = '0';
		display(game, game->graphs.floor, new_x, new_y);
		return (true);
	}
	else if (next_tile == 'E')
	{
		if (game->map.collect == 0)
		{
			ft_printf("You win!\n");
			game->is_running = false;
			free_game(game);
			mlx_close_window(game->mlx);
			return (true);
		}
		return (false);
	}
	return (true);
}
