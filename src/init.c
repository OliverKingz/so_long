/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:49:16 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/18 16:16:05 by ozamora-         ###   ########.fr       */
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
	mlx_set_icon(game->mlx, game->graphs.player_t);
	init_images(game);
	init_display(game);
	game->graphs.text = mlx_put_string(game->mlx, "0", 6, 4);
	game->moves = 0;
	game->is_running = true;
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
	game->player.img = mlx_texture_to_image(game->mlx, game->graphs.player_t);
	game->graphs.player = game->player.img;
	game->graphs.floor = mlx_texture_to_image(game->mlx, game->graphs.floor_t);
	game->graphs.wall = mlx_texture_to_image(game->mlx, game->graphs.wall_t);
	game->graphs.collect = mlx_texture_to_image(game->mlx,
			game->graphs.collect_t);
	game->graphs.exit = mlx_texture_to_image(game->mlx, game->graphs.exit_t);
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
				game->player.img = game->graphs.player;
			}
			j++;
		}
		i++;
	}
}

void	init_display(t_game *game)
{
	int		j;
	int		i;
	char	tile;

	display_img(game, game->player.img, game->player.x, game->player.y);
	j = -1;
	while (++j < game->map.height)
	{
		i = -1;
		while (++i < game->map.width)
		{
			tile = game->map.grid[j][i];
			if (tile == '0' || tile == 'P')
				display_img(game, game->graphs.floor, i, j);
			else if (tile == '1')
				display_img(game, game->graphs.wall, i, j);
			else if (tile == 'C')
				display_img(game, game->graphs.collect, i, j);
			else if (tile == 'E')
				display_img(game, game->graphs.exit, i, j);
		}
	}
	game->graphs.text = mlx_put_string(game->mlx, "0", 6, 4);
}
