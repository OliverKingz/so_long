/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:49:16 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/25 16:10:45 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

t_game	init_game(t_game *game, char *map_dir)
{
	init_texture(game);
	init_map(game, map_dir);
	init_mlx(game);
	init_images(game);
	display_player(game);
	init_display(game);
	game->graphs.text = mlx_put_string(game->mlx, "0", 6, 4);
	game->moves = 0;
	game->is_running = true;
	return (*game);
}

void	init_texture(t_game *game)
{
	game->graphs.player_t[0] = mlx_load_png("./assets/textures/Player_TL.png");
	game->graphs.player_t[1] = mlx_load_png("./assets/textures/Player_TF.png");
	game->graphs.player_t[2] = mlx_load_png("./assets/textures/Player_TR.png");
	game->graphs.item_t[0] = mlx_load_png("./assets/textures/Food.png");
	game->graphs.item_t[1] = mlx_load_png("./assets/textures/Food_B.png");
	game->graphs.floor_t = mlx_load_png("./assets/textures/Tile.png");
	game->graphs.wall_t = mlx_load_png("./assets/textures/Tree.png");
	game->graphs.exit_t = mlx_load_png("./assets/textures/House.png");
	game->graphs.enemy_t = mlx_load_png("./assets/textures/Enemy.png");
	if (!game->graphs.player_t[0] || !game->graphs.player_t[1]
		|| !game->graphs.player_t[2] || !game->graphs.item_t[0]
		|| !game->graphs.item_t[1] || !game->graphs.floor_t
		|| !game->graphs.wall_t || !game->graphs.exit_t
		|| !game->graphs.enemy_t)
		ft_mlx_err("Failed loading textures\n", game);
}

void	init_images(t_game *game)
{
	game->graphs.player[0] = mlx_texture_to_image(game->mlx,
			game->graphs.player_t[0]);
	game->graphs.player[1] = mlx_texture_to_image(game->mlx,
			game->graphs.player_t[1]);
	game->graphs.player[2] = mlx_texture_to_image(game->mlx,
			game->graphs.player_t[2]);
	game->graphs.item[0] = mlx_texture_to_image(game->mlx,
			game->graphs.item_t[0]);
	game->graphs.item[1] = mlx_texture_to_image(game->mlx,
			game->graphs.item_t[1]);
	game->player.img = game->graphs.player[1];
	game->graphs.floor = mlx_texture_to_image(game->mlx, game->graphs.floor_t);
	game->graphs.wall = mlx_texture_to_image(game->mlx, game->graphs.wall_t);
	game->graphs.exit = mlx_texture_to_image(game->mlx, game->graphs.exit_t);
	game->graphs.enemy = mlx_texture_to_image(game->mlx, game->graphs.enemy_t);
	if (!game->graphs.player[0] || !game->graphs.player[1]
		|| !game->graphs.player[2] || !game->graphs.item[0]
		|| !game->graphs.item[1] || !game->graphs.floor || !game->graphs.wall
		|| !game->graphs.exit || !game->graphs.enemy)
		ft_mlx_err("Failed loading images\n", game);
}

void	init_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.grid[i][j] == 'P')
			{
				game->player.x = j;
				game->player.y = i;
				game->player.img = game->graphs.player[1];
			}
			j++;
		}
		i++;
	}
}

void	init_mlx(t_game *game)
{
	int	height;
	int	width;

	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	height = game->map.height * game->map.t_size;
	width = game->map.width * game->map.t_size;
	game->mlx = mlx_init(width, height, "so_long", true);
	if (!game->mlx)
		ft_mlx_err("Failed init MLX42", game);
	mlx_set_window_size(game->mlx, width * 2, height * 2);
	mlx_set_icon(game->mlx, game->graphs.player_t[1]);
	mlx_set_window_limit(game->mlx, width, height, width * 3, height * 3);
}
