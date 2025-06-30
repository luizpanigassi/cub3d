/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:03:57 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/30 15:01:57 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// LIBS
# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include "../mlx/mlx.h"
# include <math.h>

// CHARS
# define MAP_CHARS " 01NSEWD"
# define PLAYER_CHARS "NSEW"

// KEYS
# define ESC_KEY 65307
# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define E_KEY 101
# define F_KEY 102
# define LEFT_KEY 65361
# define RIGHT_KEY 65363

// CONFIG
# define MOVE_SPEED 0.03
# define ROTATION_SPEED 0.03
# define COLLISION_MARGIN 0.1
# define NUM_RAYS 1200
# define MAX_DOORS 128

//WINDOW SIZE
# define W 1200
# define H 800
# define TILE_SIZE 40
# define MINIMAP_MAX_W 300
# define MINIMAP_MAX_H 300

//FIREBALLS
# define MAX_FIREBALLS 6
# define FIREBALL_FRAMES 4
# define FIREBALL_SPEED 0.2
# define FIREBALL_ANIM_SPEED 0.5

typedef struct s_fireball_screen_params {
	double	rel_x;
	double	rel_y;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		screen_x;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_x;
	int		draw_end_x;
	int		draw_start_y;
	int		draw_end_y;
}	t_fireball_screen_params;

typedef struct s_minimap_tile {
	int	x;
	int	y;
	int	tile_size;
}	t_minimap_tile;

typedef struct s_player_draw {
	int	center_x;
	int	center_y;
	int	half;
	int	y;
	int	x;
	int	px;
	int	py;
	int	offset;
}	t_player_draw;

typedef struct s_vision_line {
	int	line_length;
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
}	t_vision_line;

typedef struct s_fireball
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	int		active;
	int		distance;
	int		frame;
	int		frame_count;
}	t_fireball;

typedef struct s_line_state {
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
	int	x;
	int	y;
}	t_line_state;

typedef struct s_door {
	int	x;
	int	y;
	int	is_open;
}	t_door;

typedef struct s_line {
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
	int	color;
}	t_line;

typedef struct s_orientation {
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_orientation;

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
	t_door	doors[MAX_DOORS];
	int		door_count;
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

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		w;
	int		h;
}	t_img;

typedef struct mlx_data
{
	void		*mlx;
	void		*win;
	void		*img;
	int			bpp;
	int			line_size;
	int			endian;
	char		*img_addr;
	t_data		*data;
	t_keys		*keys;
	t_img		*textures[5];
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	t_fireball	fireballs[MAX_FIREBALLS];
	t_img		*fire_tex[FIREBALL_FRAMES];
}	t_mlx_data;

typedef struct s_parse_ctx
{
	t_data	*data;
	t_list	**map_lines;
	int		*max_width;
	int		*map_started;
}	t_parse_ctx;

typedef struct s_game
{
	t_data		*data;
	t_mlx_data	*mlx;
	t_keys		keys;
}	t_game;

typedef struct s_wall_draw_ctx {
	int		line_height;
	int		draw_end;
	int		draw_start;
	t_img	*tex;
	int		tex_x;
	int		tex_y;
	int		y;
	int		d;
	int		color;
}	t_wall_draw_ctx;

typedef struct s_ray_hit {
	double	dist;
	int		tex_id;
	double	wall_x;
	int		side;
	double	dir_x;
	double	dir_y;
}	t_ray_hit;

typedef struct s_dda_ctx {
	int		map_x;
	int		map_y;
	double	delta_x;
	double	delta_y;
	int		step_x;
	int		step_y;
	double	side_dist_x;
	double	side_dist_y;
	int		hit_wall;
	int		side;
	int		tex_id;
}	t_dda_ctx;

typedef struct s_square_draw_ctx {
	t_mlx_data	*mlx;
	int			x;
	int			y;
	int			tile_size;
	int			color;
}	t_square_draw_ctx;

// CONTROLLER
void		try_movement(t_mlx_data *mlx, double dx, double dy);
int			is_walkable(t_data *data, double x, double y);

// DOOR UTILS
t_door		*get_door(t_data *data, int x, int y);
int			is_door_open(t_data *data, int x, int y);
int			is_door_at(t_data *data, int x, int y);

// DOOR
void		toggle_door(t_game *game);
void		try_toggle_door(t_game *game);
void		register_doors(t_data *data);

// DRAW
void		draw_vision(t_mlx_data *mlx, int tile_size);
void		draw_square(t_square_draw_ctx *ctx);
void		draw_player(t_mlx_data *mlx, int tile_size);
void		draw_wall(t_mlx_data *mlx, int x, t_ray_hit hit);

// DRAWING UTILS
void		draw_pixel(t_mlx_data *mlx, int x, int y, int color);
void		draw_h_line(t_mlx_data *mlx, int y, int color);
void		draw_background(t_mlx_data *mlx, int sky, int ground);

// ERROR HANDLER
int			error_exit(char *msg, t_data *data);

// EVENTS
void		rotate_player_view(t_mlx_data *mlx, double angle);
int			close_event(t_game *game);
void		events(t_game *game);
int			mouse_move(int x, int y, t_game *game);

// FIRE UTILS
void		fireball_transform(t_mlx_data *mlx, t_fireball *fire,
				t_fireball_screen_params *params);
int			compute_fireball_screen_params(t_mlx_data *mlx, t_fireball *fire,
				t_fireball_screen_params *params);
void		init_fireballs(t_mlx_data *mlx);
void		load_fire_textures(t_mlx_data *mlx, t_data *data);

//FIRE
void		spawn_fireball(t_mlx_data *mlx);
void		update_fireballs(t_mlx_data *mlx);
void		draw_fireball_pixels(t_mlx_data *mlx,
				t_img *tex, t_fireball_screen_params *params);
void		draw_fireball(t_mlx_data *mlx, t_fireball *fire);
void		render_fireballs(t_mlx_data *mlx);

// FLOOD FILL
void		flood_fill(t_data *data, char **map, int x, int y);
char		**dup_map(t_data *data);

// INIT
void		init_window(t_mlx_data *mlx);
void		set_orientation(t_mlx_data *mlx, t_orientation o);
void		init_keys(t_keys *keys);
void		init_player(t_game *game);
void		init_textures(t_game *game);

// MAIN

// MAP VALIDATOR
int			is_invalid_tile(t_data *data, int x, int y);
void		validate_map_char_at(t_data *data, int x, int y, int *player_count);
void		validate_map_chars(t_data *data);
void		validate_map_with_flood_fill(t_data *data);

// MINIMAP
void		draw_line_on_minimap(t_mlx_data *mlx, t_line *line);
void		draw_minimap_tile(t_data *data, t_mlx_data *mlx,
				t_minimap_tile *tile_info);
int			get_minimap_tile_size(int map_width, int map_height);
void		minimap(t_data *data, t_mlx_data *mlx);
void		put_pixel_minimap(t_mlx_data *mlx, int x, int y, int color);

//MLX WINDOW
int			get_step_direction(int start, int end);
int			abs_int(int n);
void		update_line_state(t_line_state *s);
int			game_loop(t_game *game);
void		render_image(t_data *data);

// MOVEMENT
int			key_press(int keycode, t_game *game);
int			key_release(int keycode, t_game *game);
void		rotate_player(t_mlx_data *mlx);
void		calculate_movement(t_mlx_data *mlx, double *move_x, double *move_y);
void		update_player_position(t_game *game);

// PARSER CUB
void		handle_parse_error(char *line, char *trimmed,
				int line_num, t_parse_ctx *ctx);
int			handle_non_map_line_block(char *line, char *trimmed,
				int line_num, t_parse_ctx *ctx);
void		parse_lines_loop(int fd, t_data *data,
				t_list **map_lines, int *max_width);
void		check_required_elements(t_data *data);
t_data		*parse_cub_file(char *filename);

// PARSER UTILS
void		advance_line(char **line, int *line_num, int fd);
void		trim_newline_inplace(char *line);
int			process_non_map_line(char *line, int line_num, t_parse_ctx *ctx);
int			process_line(char **line, int *line_num, int fd, t_parse_ctx *ctx);
int			handle_map_line_block(char *line, t_list **map_lines,
				int *max_width, t_data *data);

// PARSER
int			parse_rgb_component(char *part, int *value);
int			parse_rgb(char **parts, int *rgb);
int			parse_color(char *line, t_data *data, char id);
int			parse_texture(char *line, t_data *data, const char *id);
int			parse_color_line(char *trimmed, t_data *data);

// RAY CASTING UTILS
int			get_tex_id(t_dda_ctx *ctx, double *dir);
void		set_hit_texture_and_wallx(t_game *game, t_ray_hit *hit,
				t_dda_ctx *ctx, double *dir);
t_ray_hit	ray_distance(t_game *game, int x);
int			apply_shade(int color, double distance);

// RAY CASTING
double		*ray_direction(t_game *game, int x);
void		perform_dda(t_game *game, t_dda_ctx *ctx);
void		init_dda_ctx(t_game *game, double *dir, t_dda_ctx *ctx);
void		draw_wall_column(t_mlx_data *mlx, int x,
				t_wall_draw_ctx *ctx, double dist);
void		render_view(t_game *game);

// TEXTURE LOADER
t_img		*load_xpm(void *mlx, char *path);

// MAP PROCESSING UTILS
void		copy_map_lines(t_data *data, t_list *map_lines, int max_width);
void		process_trimmed_line(char *trimmed, int *map_started,
				t_parse_ctx *ctx);
void		allocate_and_fill_map(t_data *data, t_list *map_lines,
				int max_width);
void		add_map_line(char *trimmed, t_list **map_lines, int *max_width);

// MAP UTILS
int			parse_texture_line(char *trimmed, t_data *data);
int			handle_non_map_line(char *trimmed,
				t_data *data, t_list **map_lines, int *max_width);
void		handle_map_line(char *trimmed, t_list **map_lines,
				int *max_width, t_data *data);

// UTILS
void		ft_free_array(char **array);
int			ft_isdigit_str(char *str);
void		free_data(t_data *data);
void		free_textures(t_mlx_data *mlx);
int			ft_strcmp(const char *s1, const char *s2);
char		*trim_and_free_line(char *line);
int			ft_isspace(int c);
void		report_texture_errors(t_game *game);
void		setup_orientation(t_mlx_data *mlx, char dir);

#endif
