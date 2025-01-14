/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:49:16 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/14 21:54:39 by ozamora-         ###   ########.fr       */
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
	print_map(game, map_dir);
	ft_putchar('\n');
	print_map_grid(game);
	ft_putchar('\n');
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->mlx = mlx_init((game->map.width - 1) * TILE, game->map.height * TILE, "so_long", true);
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

// void init_display(t_game *game)
// {
// 	int		j;
// 	int		i;
// 	char	xy;

// 	j = -1;
// 	while (++j < game->map.height)
// 	{
// 		i = -1;
// 		while (++i < game->map.width - 1)
// 		{
// 			xy = game->map.grid[j][i];
// 			if (xy == 'P' && mlx_image_to_window(game->mlx, game->graphs.player, TILE * i, TILE * j) < 0)
// 				ft_error();
// 			else if (xy == '0' && mlx_image_to_window(game->mlx, game->graphs.floor, TILE * i, TILE * j) < 0)
// 				ft_error();
// 			else if (xy == '1' && mlx_image_to_window(game->mlx, game->graphs.wall, TILE * i, TILE * j) < 0)
// 				ft_error();
// 			else if (xy == 'C' && mlx_image_to_window(game->mlx, game->graphs.collect, TILE * i, TILE * j) < 0)
// 				ft_error();
// 			else if (xy == 'E' && mlx_image_to_window(game->mlx, game->graphs.exit, TILE * i, TILE * j) < 0)
// 				ft_error();
// 		}
// 	}
// }

void init_display(t_game *game)
{
	int		j;
	int		i;
	char	xy;

	j = -1;
	while (++j < game->map.height)
	{
		i = -1;
		while (++i < game->map.width - 1)
		{
			xy = game->map.grid[j][i];
			if (xy == 'P' && display(game, i, j))
				ft_error();
			else if (xy == '0' && display(game, i, j))
				ft_error();
			else if (xy == '1' && display(game, i, j))
				ft_error();
			else if (xy == 'C' && display(game, i, j))
				ft_error();
			else if (xy == 'E' && display(game, i, j))
				ft_error();
		}
	}
}

bool display(t_game *game, int i, int j)
{
	int t;

	t = mlx_image_to_window(game->mlx, game->graphs.player, TILE * i, TILE * j);
	if (t < 0)
		return (false);
	return (true);
}
