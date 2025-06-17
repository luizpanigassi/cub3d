/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:31:07 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/17 18:37:56 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	build_map_from_list(t_list *lines, t_map *map)
{
	int		height;
	char	**grid;
	t_list	*node;
	int		i;

	i = 0;
	height = ft_lstsize(lines);
	grid = malloc(sizeof (char *) * (height + 1));
	node = lines;
	if (!grid)
	{
		perror("Error allocating memory for the grid");
		exit(1);
	}
	while (node)
	{
		grid[i++] = ft_strdup((char *)node->content);
		node = node->next;
	}
	grid[i] = NULL;
	map->grid = grid;
	map->height = height;
	map->width = ft_strlen(grid[0]);
	find_player_position(map);
}
