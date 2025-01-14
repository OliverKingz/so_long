/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:49:16 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/14 16:38:49 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_game	init_game(t_game *game, char *map_dir);
void	init_map(t_game *game, char *map_dir);
void	init_graph(t_game *game);
void	init_display(t_game *game);

t_game	init_game(t_game *game, char *map_dir)
{
	init_map(game, map_dir);
	if (!game->map.is_valid)
		ft_error();
	game->mlx = mlx_init(game->map.width * TILE_SIZE, game->map.height * TILE_SIZE, "so_long", true);
	if (!game->mlx)
		ft_error();
	init_graph(game);
	init_display(game);
	return (*game);
}

void	init_map(t_game *game, char *map_dir)
{
	int		fd;
	char	*line;

	(void)fd;
	(void)line;
	read_map(game, map_dir);
	make_map_grid(game, map_dir);
	game->map.is_valid = true;
}

void	init_graph(t_game *game)
{
	game->graphs.player_t = mlx_load_png("./assets/sprites/OZ_Player.png");
	if (!game->graphs.player_t)
		ft_error();
	game->graphs.floor_t = mlx_load_png("./assets/sprites/OZ_Tile.png");
	if (!game->graphs.floor_t)
		ft_error();
	game->graphs.wall_t = mlx_load_png("./assets/sprites/OZ_Tree_Orange.png");
	if (!game->graphs.wall_t)
		ft_error();
	game->graphs.collect_t = mlx_load_png("./assets/sprites/OZ_Food.png");
	if (!game->graphs.collect_t)
		ft_error();
	game->graphs.exit_t = mlx_load_png("./assets/sprites/OZ_House.png");
	if (!game->graphs.exit_t)
		ft_error();
	game->graphs.player = mlx_texture_to_image(game->mlx, game->graphs.player_t);
	game->graphs.floor = mlx_texture_to_image(game->mlx, game->graphs.floor_t);
	game->graphs.wall = mlx_texture_to_image(game->mlx, game->graphs.wall_t);
	game->graphs.collect = mlx_texture_to_image(game->mlx, game->graphs.collect_t);
	game->graphs.exit = mlx_texture_to_image(game->mlx, game->graphs.exit_t);
}

void	init_display(t_game *game)
{
	if (mlx_image_to_window(game->mlx, game->graphs.player, TILE_SIZE * 0, 0) < 0)
		ft_error();
	if (mlx_image_to_window(game->mlx, game->graphs.floor, TILE_SIZE * 1, 0) < 0)
		ft_error();
	if (mlx_image_to_window(game->mlx, game->graphs.wall, TILE_SIZE * 2, 0) < 0)
		ft_error();
	if (mlx_image_to_window(game->mlx, game->graphs.collect, TILE_SIZE * 3, 0) < 0)
		ft_error();
	if (mlx_image_to_window(game->mlx, game->graphs.exit, TILE_SIZE * 4, 0) < 0)
		ft_error();
}

