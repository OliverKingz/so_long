/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:55:35 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/21 13:22:06 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	display_img(t_game *game, mlx_image_t *tile, int x, int y)
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
	ft_printf("Moves made: %d\n", game->moves);
	mlx_delete_image(game->mlx, game->graphs.text);
	game->graphs.text = mlx_put_string(game->mlx, moves, 6, 4);
	free(moves);
}

void	ft_key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
		{
			free_game(game);
			mlx_close_window(game->mlx);
		}
		if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_W)
			move(game, 0, -1);
		if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_S)
			move(game, 0, 1);
		if (keydata.key == MLX_KEY_LEFT || keydata.key == MLX_KEY_A)
			move(game, -1, 0);
		if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_D)
			move(game, 1, 0);
	}
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
			ft_printf("You win!\n");
			game->is_running = false;
			free_game(game);
			mlx_close_window(game->mlx);
			return (true);
		}
		ft_printf("Items left: 0%d\n", game->map.item);
		return (false);
	}
	return (true);
}
