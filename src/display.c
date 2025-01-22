/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozamora- <ozamora-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:28:43 by ozamora-          #+#    #+#             */
/*   Updated: 2025/01/22 20:38:05 by ozamora-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_display(t_game *game)
{
	int		j;
	int		i;
	char	tile;

	j = -1;
	while (++j < game->map.height)
	{
		i = -1;
		while (++i < game->map.width)
		{
			tile = game->map.grid[j][i];
			if (tile == '0' || tile == 'P' || tile == 'C')
				display_img(game, game->graphs.floor, i, j);
			if (tile == '1')
				display_img(game, game->graphs.wall, i, j);
			if (tile == 'E')
				display_img(game, game->graphs.exit, i, j);
			if (tile == 'C')
				display_img(game, game->graphs.item[1], i, j);
			if (tile == 'C')
				display_img(game, game->graphs.item[0], i, j);
		}
	}
}

void	display_img(t_game *game, mlx_image_t *tile, int x, int y)
{
	int32_t	i_instance;

	i_instance = mlx_image_to_window(game->mlx, tile, game->map.t_size * x,
			game->map.t_size * y);
	if (i_instance < 0)
		(free_game(game), ft_mlx_err("Failed displaying image"));
	mlx_set_instance_depth(game->graphs.player[0]->instances,
		tile->instances[i_instance].z + 3);
	mlx_set_instance_depth(game->graphs.player[1]->instances,
		tile->instances[i_instance].z + 2);
	mlx_set_instance_depth(game->graphs.player[2]->instances,
		tile->instances[i_instance].z + 3);
}

void	display_text(t_game *game)
{
	char	*moves;

	moves = ft_itoa(game->moves);
	ft_printf("Moves made: %d\n", game->moves);
	mlx_delete_image(game->mlx, game->graphs.text);
	game->graphs.text = mlx_put_string(game->mlx, moves, 6, 4);
	free(moves);
}

void	print_map(char *map_dir)
{
	int		fd;
	char	*line;

	fd = open(map_dir, O_RDONLY);
	if (fd == -1)
		ft_mlx_err("Invalid map: unable to open or doesn't exists");
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		else
			ft_printf("%s", line);
		free(line);
	}
	free(line);
	close(fd);
}

void	print_map_grid(t_game *game)
{
	int	i;
	int	j;

	j = 0;
	while (j < game->map.height)
	{
		i = 0;
		while (i < game->map.width)
		{
			ft_putchar(game->map.grid[j][i]);
			i++;
		}
		ft_putchar('\n');
		j++;
	}
}
