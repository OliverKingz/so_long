/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:12:04 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/25 17:32:00 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	ft_mlx_err(const char *msg, t_game *game)
{
	ft_putstr_fd("Error\n", 2);
	if (msg)
		ft_putstr_fd((char *)msg, 2);
	if (mlx_errno != 0)
	{
		ft_putstr_fd("MLX42 Error: ", 2);
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), 2);
	}
	if (game)
		free_game(game);
	exit(EXIT_FAILURE);
}

void	free_map_grid(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->map.height)
	{
		free(game->map.grid[i]);
		i++;
	}
	free(game->map.grid);
}

void	free_textures(t_game *game)
{
	if (game->graphs.player_t[0])
		mlx_delete_texture(game->graphs.player_t[0]);
	if (game->graphs.player_t[1])
		mlx_delete_texture(game->graphs.player_t[1]);
	if (game->graphs.player_t[2])
		mlx_delete_texture(game->graphs.player_t[2]);
	if (game->graphs.item_t[0])
		mlx_delete_texture(game->graphs.item_t[0]);
	if (game->graphs.item_t[1])
		mlx_delete_texture(game->graphs.item_t[1]);
	if (game->graphs.floor_t)
		mlx_delete_texture(game->graphs.floor_t);
	if (game->graphs.wall_t)
		mlx_delete_texture(game->graphs.wall_t);
	if (game->graphs.exit_t)
		mlx_delete_texture(game->graphs.exit_t);
	if (game->graphs.enemy_t)
		mlx_delete_texture(game->graphs.enemy_t);
}

void	free_images(t_game *game)
{
	if (game->graphs.player[0])
		mlx_delete_image(game->mlx, game->graphs.player[0]);
	if (game->graphs.player[1])
		mlx_delete_image(game->mlx, game->graphs.player[1]);
	if (game->graphs.player[2])
		mlx_delete_image(game->mlx, game->graphs.player[2]);
	if (game->graphs.item[0])
		mlx_delete_image(game->mlx, game->graphs.item[0]);
	if (game->graphs.item[1])
		mlx_delete_image(game->mlx, game->graphs.item[1]);
	if (game->graphs.floor)
		mlx_delete_image(game->mlx, game->graphs.floor);
	if (game->graphs.wall)
		mlx_delete_image(game->mlx, game->graphs.wall);
	if (game->graphs.exit)
		mlx_delete_image(game->mlx, game->graphs.exit);
	if (game->graphs.text)
		mlx_delete_image(game->mlx, game->graphs.text);
	if (game->graphs.enemy)
		mlx_delete_image(game->mlx, game->graphs.enemy);
}

void	free_game(t_game *game)
{
	if (game->graphs.player[0] || game->graphs.player[1]
		|| game->graphs.player[2] || game->graphs.item[0]
		|| game->graphs.item[1] || game->graphs.floor || game->graphs.wall
		|| game->graphs.exit || game->graphs.enemy)
		free_images(game);
	if (game->graphs.player_t[0] || game->graphs.player_t[1]
		|| game->graphs.player_t[2] || game->graphs.item_t[0]
		|| game->graphs.item_t[1] || game->graphs.floor_t || game->graphs.wall_t
		|| game->graphs.exit_t || game->graphs.enemy_t)
		free_textures(game);
	if (game->map.grid)
		free_map_grid(game);
	if (game->mlx)
	{
		mlx_close_window(game->mlx);
	}
}
