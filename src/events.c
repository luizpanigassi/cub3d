/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 11:45:31 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/20 11:53:41 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_event(t_mlx_data *mlx)
{
	if (mlx->img)
		mlx_destroy_image(mlx->mlx, mlx->img);
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	free(mlx);
	exit(0);
	return (0);
}

void	events(t_mlx_data *mlx)
{
	mlx_hook(mlx->win, 2, 1L << 0, key_press, mlx); // Key down
	mlx_hook(mlx->win, 3, 1L << 1, key_release, mlx); // Key up
	mlx_hook(mlx->win, 17, 0, close_event, mlx); // Close
}
