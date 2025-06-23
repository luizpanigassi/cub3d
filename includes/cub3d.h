/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcologne <jcologne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:03:57 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/23 17:55:48 by jcologne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include "../mlx/mlx.h"
# include <math.h>

# define MAP_CHARS " 01NSEW"
# define PLAYER_CHARS "NSEW"
# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define MOVE_SPEED 0.1
# define ROTATION_SPEED 0.05
# define COLLISION_MARGIN 0.1
# define NUM_RAYS 1200

//WINDOW SIZE
# define W 1200
# define H 800
# define TILE_SIZE 40

typedef struct s_data
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	**map;
	char	player_direction;
	int		floor;
	int		ceiling;
	int		map_width;
	int		map_height;
	int		player_x;
	int		player_y;
}	t_data;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
	int	esc;
}	t_keys;

typedef struct mlx_data
{
	void	*mlx;
	void	*win;
	void	*img;
	int		bpp;
	int		line_size;
	int		endian;
	char	*img_addr;
	t_data	*data;
	t_keys	*keys;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_mlx_data;

typedef struct s_parse_ctx
{
	t_data	*data;
	t_list	**map_lines;
	int		*max_width;
}	t_parse_ctx;

typedef struct s_game
{
	t_data		*data;
	t_mlx_data	*mlx;
	t_keys		keys;
}	t_game;

// CONTROLLER
void	try_movement(t_mlx_data *mlx, double dx, double dy);
int		is_walkable(t_data *data, double x, double y);

// ERROR HANDLER
int		error_exit(char *msg, t_data *data);

// EVENTS
int		close_event(t_game *game);
void	events(t_game *game);

// FLOOD FILL
char	**dup_map(t_data *data);
void	flood_fill(t_data *data, char **map, int x, int y);

// MAIN

// MAP VALIDATOR

int		is_invalid_tile(t_data *data, int x, int y);
void	validate_map_char_at(t_data *data, int x, int y, int *player_count);
void	validate_map_chars(t_data *data);
void	validate_map_with_flood_fill(t_data *data);

// MOVEMENT
int		key_press(int keycode, t_game *game);
int		key_release(int keycode, t_game *game);
void	rotate_player(t_mlx_data *mlx);
void	update_player_position(t_game *game);
void	calculate_movement(t_mlx_data *mlx, double *move_x, double *move_y);

// CUB PARSER
void	parse_lines_loop(int fd, t_data *data,
			t_list **map_lines, int *max_width);
void	check_required_elements(t_data *data);
t_data	*parse_cub_file(char *filename);

// PARSER
int		parse_rgb_component(char *part, int *value);
int		parse_rgb(char **parts, int *rgb);
int		parse_color(char *line, t_data *data, char id);
int		parse_texture(char *line, t_data *data, const char *id);
int		parse_color_line(char *trimmed, t_data *data);

// MAP PROCESSING UTILS
void	copy_map_lines(t_data *data, t_list *map_lines, int max_width);
void	process_trimmed_line(char *trimmed, int *map_started, t_parse_ctx *ctx);
void	allocate_and_fill_map(t_data *data, t_list *map_lines, int max_width);
void	add_map_line(char *trimmed, t_list **map_lines, int *max_width);

// MAP UTILS
int		parse_texture_line(char *trimmed, t_data *data);
int		handle_non_map_line(char *trimmed,
			t_data *data, t_list **map_lines, int *max_width);
void	handle_map_line(char *trimmed, t_list **map_lines, int *max_width);

// UTILS
void	ft_free_array(char **array);
int		ft_isdigit_str(char *str);
void	free_data(t_data *data);
int		ft_strcmp(const char *s1, const char *s2);
char	*trim_and_free_line(char *line);
int		ft_isspace(int c);

//MLX_WINDOW
void	render_image(t_data *data);
void	redraw_minimap(t_data *data, t_mlx_data *mlx);

//INIT
void	init_window(t_mlx_data *mlx);
void	init_player(t_game *game);

#endif
