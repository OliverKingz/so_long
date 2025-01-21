/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 16:12:04 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/21 14:06:41 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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
	mlx_delete_texture(game->graphs.player_t);
	mlx_delete_texture(game->graphs.floor_t);
	mlx_delete_texture(game->graphs.wall_t);
	mlx_delete_texture(game->graphs.exit_t);
	mlx_delete_texture(game->graphs.item_t[0]);
	mlx_delete_texture(game->graphs.item_t[1]);
}

void	free_images(t_game *game)
{
	mlx_delete_image(game->mlx, game->graphs.player);
	mlx_delete_image(game->mlx, game->graphs.floor);
	mlx_delete_image(game->mlx, game->graphs.wall);
	mlx_delete_image(game->mlx, game->graphs.exit);
	mlx_delete_image(game->mlx, game->graphs.text);
	mlx_delete_image(game->mlx, game->graphs.item);
	mlx_delete_image(game->mlx, game->graphs.b_item);
}

void	free_game(t_game *game)
{
	free_images(game);
	free_textures(game);
	free_map_grid(game);
}

