/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliverkingz <oliverkingz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:37:28 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/16 22:33:17 by oliverkingz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	ft_mlx_err(const char *msg)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
		ft_putstr_fd((char *)msg, 2);
	if (mlx_errno != 0)
	{
		ft_putstr_fd("MLX42 Error: ", 2);
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	}
	exit(EXIT_FAILURE);
}

void	free_game(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.height)
	{
		free(game->map.grid[i]);
		i++;
	}
	free(game->map.grid);
	mlx_delete_image(game->mlx, game->graphs.player);
	mlx_delete_image(game->mlx, game->graphs.floor);
	mlx_delete_image(game->mlx, game->graphs.wall);
	mlx_delete_image(game->mlx, game->graphs.collect);
	mlx_delete_image(game->mlx, game->graphs.exit);
	mlx_delete_image(game->mlx, game->graphs.text);
	mlx_delete_texture(game->graphs.player_t);
	mlx_delete_texture(game->graphs.floor_t);
	mlx_delete_texture(game->graphs.wall_t);
	mlx_delete_texture(game->graphs.collect_t);
	mlx_delete_texture(game->graphs.exit_t);
}

int32_t	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		ft_mlx_err("Usage: ./so_long \"assets/maps/example.ber\"");
	game = init_game(&game, argv[1]);
	print_map_grid(&game);
	if (game.is_running == true)
	{
		mlx_key_hook(game.mlx, &ft_key_hook, &game);
		mlx_loop(game.mlx);
	}
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
