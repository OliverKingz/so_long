/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:37:28 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/21 14:25:16 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_loop_hook(void *param)
{
	t_game* 		game = (t_game*)param;
	static int		counter = 0;
	int				i;
	
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

int32_t	main(int argc, char **argv)
{
	t_game	game;

	if (argc == 2)
	{
		if (ft_strlen(argv[1]) == 0)
			ft_mlx_err("Invalid map: path is empty");
		game = init_game(&game, argv[1]);
		print_map_grid(&game);
		if (game.is_running == true)
		{
			mlx_key_hook(game.mlx, &ft_key_hook, &game);
			mlx_loop_hook(game.mlx, ft_loop_hook, &game);
			//mlx_close_hook(game.mlx, );
			mlx_loop(game.mlx);
		}
		mlx_terminate(game.mlx);
	}
	else
		ft_mlx_err("Usage: ./so_long \"assets/maps/example.ber\"");
	return (EXIT_SUCCESS);
}
