/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:49:16 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/15 16:23:07 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_game	init_game(t_game *game, char *map_dir);
void	init_map(t_game *game, char *map_dir);
void	init_graph(t_game *game);
bool	display(mlx_t *mlx, mlx_image_t *tile, int x, int y);

t_game	init_game(t_game *game, char *map_dir)
{
	int	width;
	int	height;

	init_map(game, map_dir);
	if (!game->map.is_valid)
		ft_error("Failed parsing map");
	print_map_grid(game);
	ft_putstr("\n\n");
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	width = (game->map.width - 1) * TILE;
	height = game->map.height * TILE;
	game->mlx = mlx_init(width, height, "so_long", true);
	if (!game->mlx)
		ft_error("Failed init MLX42");
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
		ft_error("Failed loading texture");
	game->graphs.floor_t = mlx_load_png("./assets/sprites/OZ_Tile.png");
	if (!game->graphs.floor_t)
		ft_error("Failed loading texture");
	game->graphs.wall_t = mlx_load_png("./assets/sprites/OZ_Tree_Orange.png");
	if (!game->graphs.wall_t)
		ft_error("Failed loading texture");
	game->graphs.collect_t = mlx_load_png("./assets/sprites/OZ_Food.png");
	if (!game->graphs.collect_t)
		ft_error("Failed loading texture");
	game->graphs.exit_t = mlx_load_png("./assets/sprites/OZ_House.png");
	if (!game->graphs.exit_t)
		ft_error("Failed loading texture");
	game->graphs.player = mlx_texture_to_image(game->mlx,
			game->graphs.player_t);
	game->graphs.floor = mlx_texture_to_image(game->mlx, game->graphs.floor_t);
	game->graphs.wall = mlx_texture_to_image(game->mlx, game->graphs.wall_t);
	game->graphs.collect = mlx_texture_to_image(game->mlx,
			game->graphs.collect_t);
	game->graphs.exit = mlx_texture_to_image(game->mlx, game->graphs.exit_t);
}

void	init_display(t_game *game)
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
			if (xy == 'P' && display(game->mlx, game->graphs.player, i, j))
				game->player.x = i;
			if (xy == 'P')
				game->player.y = j;
			else if (xy == '0')
				display(game->mlx, game->graphs.floor, i, j);
			else if (xy == '1')
				display(game->mlx, game->graphs.wall, i, j);
			else if (xy == 'C')
				display(game->mlx, game->graphs.collect, i, j);
			else if (xy == 'E')
				display(game->mlx, game->graphs.exit, i, j);
		}
	}
}

bool	display(mlx_t *mlx, mlx_image_t *tile, int x, int y)
{
	int	window_image;

	window_image = mlx_image_to_window(mlx, tile, TILE * x, TILE * y);
	if (window_image < 0)
		return (ft_error("Failed displaying image"), false);
	return (true);
}
