/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:41:00 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/15 16:38:05 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "MLX42/MLX42.h"
# include "libft.h"

/* Explicitly allowed functions for so_long, already included at the libraries
# include <stdbool.h> // Included in MLX42
# include <stddef.h>  // Already included in MLX42
# include <stdint.h>  // Already included in MLX42
# include <stdio.h>   // To use perror
# include <stdlib.h>  // To use memory allocation (malloc, free),exit and size_t
# include <string.h>  // To use strerror
# include <unistd.h>  // To use system calls like write, open, read, close.
 */

typedef struct s_entity
{
	int				x;
	int				y;
	mlx_image_t		*img;
}					t_entity;

typedef struct s_map
{
	char			**grid;
	int				width;
	int				height;
	int				tile_size;
	int				collect;
	bool			is_valid;
	t_entity		exit;
}					t_map;

typedef struct s_graph
{
	mlx_texture_t	*player_t;
	mlx_texture_t	*floor_t;
	mlx_texture_t	*wall_t;
	mlx_texture_t	*collect_t;
	mlx_texture_t	*exit_t;
	mlx_image_t		*player;
	mlx_image_t		*floor;
	mlx_image_t		*wall;
	mlx_image_t		*collect;
	mlx_image_t		*exit;
}					t_graph;

typedef struct s_game
{
	t_map			map;
	t_graph			graphs;
	t_entity		player;
	mlx_t			*mlx;
	int				moves;
	bool			is_running;
}					t_game;

# define TILE 36

void				ft_hook(t_game *game);
void				ft_error(const char *msg);
t_game				init_game(t_game *game, char *map_dir);
void				init_map(t_game *game, char *map_dir);
void				init_graph(t_game *game);
void				init_display(t_game *game);
bool				display(mlx_t *mlx, mlx_image_t *tile, int x, int y);

void				read_map(t_game *game, char *map_dir);
void				make_map_grid(t_game *game, char *map_dir);
void				print_map(char *map_dir);
void				print_map_grid(t_game *game);

#endif