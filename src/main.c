/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:37:28 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/15 19:50:00 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_hook(void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP)
		|| mlx_is_key_down(game->mlx, MLX_KEY_W))
		game->player.img->instances[0].y -= game->map.tile_size;
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN)
		|| mlx_is_key_down(game->mlx, MLX_KEY_S))
		game->player.img->instances[0].y += game->map.tile_size;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(game->mlx, MLX_KEY_A))
		game->player.img->instances[0].x -= game->map.tile_size;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT)
		|| mlx_is_key_down(game->mlx, MLX_KEY_D))
		game->player.img->instances[0].x += game->map.tile_size;
}

void	ft_mlx_err(const char *msg)
{
	//ft_putstr_fd("Error\n", 2);
	perror("Error");
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
	print_map(argv[1]);
	ft_putstr("\n\n");
	game = init_game(&game, argv[1]);
	print_map_grid(&game);
	ft_putstr("\n\n");
	mlx_loop_hook(game.mlx, ft_hook, &game);
	mlx_loop(game.mlx);
	free_game(&game);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
