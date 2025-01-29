/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:12:04 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/29 16:17:55 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	mlx_delete_texture(game->graphs.play_t[0]);
	mlx_delete_texture(game->graphs.play_t[1]);
	mlx_delete_texture(game->graphs.play_t[2]);
	mlx_delete_texture(game->graphs.item_t[0]);
	mlx_delete_texture(game->graphs.item_t[1]);
	mlx_delete_texture(game->graphs.floor_t);
	mlx_delete_texture(game->graphs.wall_t);
	mlx_delete_texture(game->graphs.exit_t);
}

void	free_images(t_game *game)
{
	mlx_delete_image(game->mlx, game->graphs.play[0]);
	mlx_delete_image(game->mlx, game->graphs.play[1]);
	mlx_delete_image(game->mlx, game->graphs.play[2]);
	mlx_delete_image(game->mlx, game->graphs.item[0]);
	mlx_delete_image(game->mlx, game->graphs.item[1]);
	mlx_delete_image(game->mlx, game->graphs.floor);
	mlx_delete_image(game->mlx, game->graphs.wall);
	mlx_delete_image(game->mlx, game->graphs.exit);
	mlx_delete_image(game->mlx, game->graphs.text);
}

void	free_game(t_game *game)
{
	free_images(game);
	free_textures(game);
	free_map_grid(game);
}
