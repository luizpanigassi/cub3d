/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:16:23 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/30 14:44:52 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

void	report_texture_errors(t_game *game)
{
	fprintf(stderr, "Error: Failed to load one or more textures:\n");
	if (!game->mlx->textures[0])
		fprintf(stderr, "- North texture: %s\n", game->data->north);
	if (!game->mlx->textures[1])
		fprintf(stderr, "- South texture: %s\n", game->data->south);
	if (!game->mlx->textures[2])
		fprintf(stderr, "- East texture: %s\n", game->data->east);
	if (!game->mlx->textures[3])
		fprintf(stderr, "- West texture: %s\n", game->data->west);
	if (!game->mlx->textures[4])
		fprintf(stderr, "- Door texture: textures/door.xpm\n");
	error_exit("Texture loading failed!", game->data);
}

void	setup_orientation(t_mlx_data *mlx, char dir)
{
	if (dir == 'N')
		set_orientation(mlx, (t_orientation){0, -1, 0.66, 0});
	else if (dir == 'S')
		set_orientation(mlx, (t_orientation){0, 1, -0.66, 0});
	else if (dir == 'E')
		set_orientation(mlx, (t_orientation){1, 0, 0, 0.66});
	else if (dir == 'W')
		set_orientation(mlx, (t_orientation){-1, 0, 0, -0.66});
}

void	free_textures(t_mlx_data *mlx)
{
	int	i;

	if (!mlx || !mlx->mlx)
		return ;
	i = 0;
	while (i < 5)
	{
		if (mlx->textures[i] && mlx->textures[i]->img)
		{
			mlx_destroy_image(mlx->mlx, mlx->textures[i]->img);
			free(mlx->textures[i]);
			mlx->textures[i] = NULL;
		}
		i++;
	}
	i = 0;
	while (i < FIREBALL_FRAMES && mlx->fire_tex[i] && mlx->fire_tex[i]->img)
	{
		mlx_destroy_image(mlx->mlx, mlx->fire_tex[i]->img);
		free(mlx->fire_tex[i]);
		mlx->fire_tex[i] = NULL;
		i++;
	}
}
