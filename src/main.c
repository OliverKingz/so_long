/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:37:28 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/15 16:38:16 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void ft_hook(t_game* game)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP)
		|| mlx_is_key_down(game->mlx, MLX_KEY_W))
		game->player.img->instances[0].y -= TILE;
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN)
		|| mlx_is_key_down(game->mlx, MLX_KEY_S))
		game->player.img->instances[0].y += TILE;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(game->mlx, MLX_KEY_A))
		game->player.img->instances[0].x -= TILE;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(game->mlx, MLX_KEY_D))
		game->player.img->instances[0].x += TILE;
}

void	ft_error(const char *msg)
{
	if (msg)
		perror(msg);
	if (mlx_errno != 0)
	{
		write(2, "MLX42 Error: ", 13);
		write(2, mlx_strerror(mlx_errno), ft_strlen(mlx_strerror(mlx_errno)));
		write(2, "\n", 1);
	}
	exit(EXIT_FAILURE);
}

// -----------------------------------------------------------------------------

int32_t	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		ft_error("Usage: ./so_long \"assets/maps/example.ber\"");
	game = init_game(&game, argv[1]);
	mlx_loop_hook(game.mlx, ft_hook, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
