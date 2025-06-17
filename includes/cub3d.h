/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:03:57 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/17 19:25:13 by luinasci         ###   ########.fr       */
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

// CHECKERS
int		is_wall_or_space(char c);
int		is_walkable(char c);
int		is_enclosed(t_map *map, int y, int x);
int		is_player_char(char c);

// INITS
void	set_player_position(t_map *map, int x, int y);

// MAP VALIDATOR
void	validate_map(t_map *map);
void	check_and_set_player(t_map *map, int x, int y, int *found);
void	find_player_position(t_map *map);

// PARSERS - CONFIG
void	parse_rgb(char *line, t_rgb *color);
void	parse_config_line(char *line, t_config *config);

// PARSERS - MAP
int		is_map_line(char *line);
void	read_cub_lines(int fd, t_game *game, t_list **map_lines);
void	parse_cub_file(const char *filename, t_game *game);

// UTILS
int		ft_isspace(int c);
void	ft_free_split(char **split);
int		isempty(char *line);

#endif
