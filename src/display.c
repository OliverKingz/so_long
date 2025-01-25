/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:28:43 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/25 17:27:45 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_display(t_game *game)
{
	int		j;
	int		i;
	char	tile;

	display_player(game);
	j = -1;
	while (++j < game->map.height)
	{
		i = -1;
		while (++i < game->map.width)
		{
			tile = game->map.grid[j][i];
			if (tile == '0' || tile == 'P' || tile == 'C')
				display_img(game, game->graphs.floor, i, j);
			if (tile == '1')
				display_img(game, game->graphs.wall, i, j);
			if (tile == 'E')
				display_img(game, game->graphs.exit, i, j);
			if (tile == 'C')
				display_img(game, game->graphs.item[1], i, j);
			if (tile == 'C')
				display_img(game, game->graphs.item[0], i, j);
		}
	}
}

void	display_player(t_game *game)
{
	mlx_image_to_window(game->mlx, game->graphs.player[0],
		game->map.t_size * game->player.x, game->map.t_size * game->player.y);
	mlx_image_to_window(game->mlx, game->graphs.player[1],
		game->map.t_size * game->player.x, game->map.t_size * game->player.y);
	mlx_image_to_window(game->mlx, game->graphs.player[2],
		game->map.t_size * game->player.x, game->map.t_size * game->player.y);
	game->graphs.player[0]->enabled = false;
	game->graphs.player[2]->enabled = false;
}

void	display_img(t_game *game, mlx_image_t *tile, int x, int y)
{
	int32_t	i_instance;

	i_instance = mlx_image_to_window(game->mlx, tile, game->map.t_size * x,
			game->map.t_size * y);
	if (i_instance < 0)
		(free_game(game), ft_mlx_err("Failed displaying image", game));
	mlx_set_instance_depth(game->graphs.player[0]->instances,
		tile->instances[i_instance].z + 3);
	mlx_set_instance_depth(game->graphs.player[1]->instances,
		tile->instances[i_instance].z + 2);
	mlx_set_instance_depth(game->graphs.player[2]->instances,
		tile->instances[i_instance].z + 3);
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
