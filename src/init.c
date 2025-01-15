/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:49:16 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/15 23:26:01 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_game	init_game(t_game *game, char *map_dir)
{
	int	height;
	int	width;

	init_texture(game);
	init_map(game, map_dir);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	height = game->map.height * game->map.t_size;
	width = game->map.width * game->map.t_size;
	game->mlx = mlx_init(width, height, "so_long", true);
	if (!game->mlx)
		ft_mlx_err("Failed init MLX42");
	mlx_set_window_size(game->mlx, width * 2, height * 2);
	init_images(game);
	init_display(game);
	init_display_player(game);
	game->moves = 0;
	game->is_running = true;
	// mlx_set_instance_depth(game->player.img->instances,
	// 	game->player.img->instances->z + (game->map.height * game->map.width));
	mlx_set_window_limit(game->mlx, width, height, width * 4, height * 4);
	return (*game);
}

void	init_texture(t_game *game)
{
	game->graphs.player_t = mlx_load_png("./assets/sprites/OZ_Player.png");
	if (!game->graphs.player_t)
		ft_mlx_err("Failed loading texture");
	game->graphs.floor_t = mlx_load_png("./assets/sprites/OZ_Tile.png");
	if (!game->graphs.floor_t)
		ft_mlx_err("Failed loading texture");
	game->graphs.wall_t = mlx_load_png("./assets/sprites/OZ_Tree_Orange.png");
	if (!game->graphs.wall_t)
		ft_mlx_err("Failed loading texture");
	game->graphs.collect_t = mlx_load_png("./assets/sprites/OZ_Food.png");
	if (!game->graphs.collect_t)
		ft_mlx_err("Failed loading texture");
	game->graphs.exit_t = mlx_load_png("./assets/sprites/OZ_House.png");
	if (!game->graphs.exit_t)
		ft_mlx_err("Failed loading texture");
}

void	init_images(t_game *game)
{
	game->graphs.player = mlx_texture_to_image(game->mlx,
			game->graphs.player_t);
	game->graphs.floor = mlx_texture_to_image(game->mlx, game->graphs.floor_t);
	game->graphs.wall = mlx_texture_to_image(game->mlx, game->graphs.wall_t);
	game->graphs.collect = mlx_texture_to_image(game->mlx,
			game->graphs.collect_t);
	game->graphs.exit = mlx_texture_to_image(game->mlx, game->graphs.exit_t);
	game->graphs.text = mlx_put_string(game->mlx, "0", 6, 4);
}

void	init_display(t_game *game)
{
	int		j;
	int		i;
	char	p;

	j = -1;
	while (++j < game->map.height)
	{
		i = -1;
		while (++i < game->map.width)
		{
			p = game->map.grid[j][i];
			if (p == '0' || p == 'P')
				display(game, game->graphs.floor, i, j);
			else if (p == '1')
				display(game, game->graphs.wall, i, j);
			else if (p == 'C' && display(game, game->graphs.collect, i, j))
				game->map.collect++;
			else if (p == 'E')
				display(game, game->graphs.exit, i, j);
		}
	}
}

void	init_display_player(t_game *game)
{
	int		j;
	int		i;
	char	p;

	game->player.img = game->graphs.player;
	j = -1;
	while (++j < game->map.height)
	{
		i = -1;
		while (++i < game->map.width)
		{
			p = game->map.grid[j][i];
			if (p == 'P' && display(game, game->player.img, i, j))
				game->player.x = i;
			if (p == 'P')
				game->player.y = j;
		}
	}
	mlx_set_instance_depth(game->player.img->instances,
		game->player.img->instances->z++);
}

