/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:40:28 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/21 14:51:20 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_loop_hook(void *param)
{
	t_game* 	game = (t_game*)param;
	static int	counter = 0;
	int			i;

	counter++;
	if (counter % 20 == 0 && counter % 40 != 0)
	{
		i = game->graphs.item->count;
		while (i-- > 0)
		{
			game->graphs.item->enabled = false;
			game->graphs.b_item->enabled = true;
		}
	}
	if (counter % 40 == 0)
	{
		i = game->graphs.item->count;
		while (i-- > 0)
		{
			game->graphs.item->enabled = true;
			game->graphs.b_item->enabled = false;
		}
	}
	if (counter >= 1000000)
		counter = 0;
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

void	ft_close_hook(void *param)
{
	t_game	*game;

	game = param;
	free_game(game);
	mlx_close_window(game->mlx);
}
