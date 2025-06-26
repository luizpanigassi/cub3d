/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 19:05:41 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/26 19:06:18 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_door	*get_door(t_data *data, int x, int y)
{
	int	i;

	i = 0;
	while (i < data->door_count)
	{
		if (data->doors[i].x == x && data->doors[i].y == y)
			return (&data->doors[i]);
		i++;
	}
	return (NULL);
}

int	is_door_at(t_data *data, int x, int y)
{
	return (data->map[y][x] == 'D');
}

int	is_door_open(t_data *data, int x, int y)
{
	t_door	*door;

	door = get_door(data, x, y);
	return (door && door->is_open);
}
