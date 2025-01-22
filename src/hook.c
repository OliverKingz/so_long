/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oliverkingz <oliverkingz@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:40:28 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/21 22:58:58 by oliverkingz      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_loop_hook(void *param)
{
	static int 	counter = 0;
	t_game 		*game;
	int 		i;
	bool		state;

	game = (t_game *)param;
	counter++;
	if (counter % 20 == 0)
	{
		i = game->graphs.item->count;
		while (i-- > 0)
		{
			state = (counter % 40 != 0);
			game->graphs.item->enabled = state;
			game->graphs.b_item->enabled = !state;
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
