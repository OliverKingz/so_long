/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:41:00 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/25 17:30:01 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

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
	int				t_size;
	int				item;
	bool			is_valid;
}					t_map;

typedef struct s_graph
{
	mlx_texture_t	*player_t[3];
	mlx_texture_t	*item_t[2];
	mlx_texture_t	*floor_t;
	mlx_texture_t	*wall_t;
	mlx_texture_t	*exit_t;
	mlx_texture_t	*enemy_t;
	mlx_image_t		*player[3];
	mlx_image_t		*item[2];
	mlx_image_t		*floor;
	mlx_image_t		*wall;
	mlx_image_t		*exit;
	mlx_image_t		*enemy;
	mlx_image_t		*text;
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

t_game				init_game(t_game *game, char *map_dir);
void				init_texture(t_game *game);
void				init_images(t_game *game);
void				init_player(t_game *game);
void				init_mlx(t_game *game);

void				init_display(t_game *game);
void				display_player(t_game *game);
void				display_img(t_game *game, mlx_image_t *tile, int x, int y);
void				display_text(t_game *game);

void				ft_loop_hook(void *param);
void				ft_key_hook(mlx_key_data_t keydata, void *param);
void				ft_close_hook(void *param);

void				move(t_game *game, int dx, int dy);
bool				allow_to_move(t_game *game, int new_x, int new_y,
						char next_tile);

void				init_map(t_game *game, char *map_dir);
void				read_map(t_game *game, char *map_dir);
void				make_map_grid(t_game *game, char *map_dir);

void				check_map_file(t_game *game, char *map_dir);
void				check_map_elements(t_game *game);
void				check_elements(t_game *game, int exit_count,
						int player_count);
void				check_map_enclosed(t_game *game);
void				check_map_solvable(t_game *game, char *map_dir);

void				print_map(char *map_dir);
void				print_map_grid(t_game *game);
void				flood_fill(t_game *game, int x, int y);

void				ft_mlx_err(const char *msg, t_game *game);
void				free_map_grid(t_game *game);
void				free_images(t_game *game);
void				free_textures(t_game *game);
void				free_game(t_game *game);

#endif