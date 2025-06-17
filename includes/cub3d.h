/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:03:57 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/17 18:49:09 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include <stdio.h>
# include <fcntl.h>

// Struct for RGB color representation
typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}	t_rgb;

// Struct for texture settings
typedef struct s_config
{
	char	*texture_north;
	char	*texture_south;
	char	*texture_east;
	char	*texture_west;
	t_rgb	color_floor;
	t_rgb	color_ceiling;
}	t_config;

// Struct for map representation
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_direction;
}	t_map;

// Struct for the game state, combining configuration and map
typedef struct s_game
{
	t_config	config;
	t_map		map;
}	t_game;

// BUILD MAP
void	build_map_from_list(t_list *lines, t_map *map);

// PARSERS - MAP
void	parse_cub_file(const char *filename, t_game *game);
void	read_cub_lines(int fd, t_game *game, t_list **map_lines);
int		is_map_line(char *line);

// PARSERS - CONFIG
void	parse_config_line(char *line, t_config *config);
void	parse_rgb(char *line, t_rgb *color);

// UTILS
int		ft_isspace(int c);
void	ft_free_split(char **split);
int		isempty(char *line);

#endif
