/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:07:05 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/26 19:08:25 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fireball_transform(t_mlx_data *mlx, t_fireball *fire,
	t_fireball_screen_params *params)
{
	params->rel_x = fire->x - mlx->pos_x;
	params->rel_y = fire->y - mlx->pos_y;
	params->inv_det = 1.0 / (mlx->plane_x
			* mlx->dir_y - mlx->dir_x * mlx->plane_y);
	params->transform_x = params->inv_det
		* (mlx->dir_y * params->rel_x - mlx->dir_x * params->rel_y);
	params->transform_y = params->inv_det
		* (-mlx->plane_y * params->rel_x + mlx->plane_x * params->rel_y);
}

int	compute_fireball_screen_params(t_mlx_data *mlx, t_fireball *fire,
									t_fireball_screen_params *params)
{
	fireball_transform(mlx, fire, params);
	if (params->transform_y <= 0)
		return (0);
	params->screen_x = (int)((W / 2)
			* (1 + params->transform_x / params->transform_y));
	params->sprite_height = abs((int)(H / params->transform_y));
	params->sprite_width = params->sprite_height;
	params->draw_start_x = params->screen_x - params->sprite_width / 2;
	params->draw_end_x = params->screen_x + params->sprite_width / 2;
	params->draw_start_y = (H / 2) - params->sprite_height / 2;
	params->draw_end_y = (H / 2) + params->sprite_height / 2;
	if (params->draw_start_x < 0)
		params->draw_start_x = 0;
	if (params->draw_end_x >= W)
		params->draw_end_x = W - 1;
	if (params->draw_start_y < 0)
		params->draw_start_y = 0;
	if (params->draw_end_y >= H)
		params->draw_end_y = H - 1;
	return (1);
}

void	init_fireballs(t_mlx_data *mlx)
{
	int	i;

	i = 0;
	while (i < MAX_FIREBALLS)
	{
		mlx->fireballs[i].active = 0;
		mlx->fireballs[i].frame = 0;
		mlx->fireballs[i].frame_count = 0;
		i++;
	}
}

void	load_fire_textures(t_mlx_data *mlx, t_data *data)
{
	int		i;
	char	*paths[FIREBALL_FRAMES];

	paths[0] = "textures/fire/fire0.xpm";
	paths[1] = "textures/fire/fire1.xpm";
	paths[2] = "textures/fire/fire2.xpm";
	paths[3] = "textures/fire/fire3.xpm";
	i = 0;
	while (i < FIREBALL_FRAMES)
	{
		mlx->fire_tex[i] = load_xpm(mlx->mlx, paths[i]);
		if (!mlx->fire_tex[i])
			error_exit("Fire texture loading failed", data);
		i++;
	}
}
