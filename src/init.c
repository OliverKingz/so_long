/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 19:49:16 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/15 19:43:40 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

t_game				init_game(t_game *game, char *map_dir);
void				init_map(t_game *game, char *map_dir);
void				init_texture(t_game *game);
void				init_images(t_game *game);
void				init_display(t_game *game);
void				init_game_data(t_game *game);
bool				display(t_game *game, mlx_image_t *tile, int x, int y);

t_game	init_game(t_game *game, char *map_dir)
{
	init_texture(game);
	init_map(game, map_dir);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	game->mlx = mlx_init((game->map.width - 1) * game->map.tile_size,
			game->map.height * game->map.tile_size, "so_long", true);
	if (!game->mlx)
		ft_mlx_err("Failed init MLX42");
	init_images(game);
	init_display(game);
	game->player.img = game->graphs.player;
	game->moves = 0;
	return (*game);
}

void	init_map(t_game *game, char *map_dir)
{
	game->map.width = 0;
	game->map.height = 0;
	game->map.tile_size = game->graphs.floor_t->width;
	game->map.collect = 0;
	game->map.is_valid = true;
	read_map(game, map_dir);
	make_map_grid(game, map_dir);
	if (!game->map.is_valid)
		(free_game(game), ft_mlx_err("Failed parsing map"));
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
		while (++i < game->map.width - 1)
		{
			p = game->map.grid[j][i];
			if (p == 'P' && display(game, game->graphs.player, i, j))
				game->player.x = i;
			if (p == 'P')
				game->player.y = j;
			else if (p == '0')
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

bool	display(t_game *game, mlx_image_t *tile, int x, int y)
{
	int	window_image;

	window_image = mlx_image_to_window(game->mlx, tile, game->map.tile_size * x,
			game->map.tile_size * y);
	if (window_image < 0)
		return (ft_mlx_err("Failed displaying image"), false);
	return (true);
}
