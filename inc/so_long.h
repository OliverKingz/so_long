/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:41:00 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/10 19:59:07 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include <stdbool.h>

/* Explicitly allowed functions for so_long, already included at the libraries
# include <unistd.h> // To use system calls like write, open, read, close.
# include <stdlib.h> // To use memory allocation (malloc, free), exit and size_t
# include <stdio.h>  // To use perror
# include <string.h> // To use strerror
 */

typedef struct s_entity
{
	int			x;
	int			y;
	mlx_image_t	*img;
}	t_entity;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		tile_size;
	int		collect;
	bool	is_valid;
	t_entity	exit;
}	t_map;

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
}	t_graph;

typedef struct s_game
{
	mlx_t		*mlx;
	t_entity	player;
	t_map		map;
	t_graph		graphs;
	int			moves;
	bool		is_running;
}	t_game;

#endif