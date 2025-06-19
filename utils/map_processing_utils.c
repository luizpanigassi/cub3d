/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_processing_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:47:09 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/19 19:09:15 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	copy_map_lines(t_data *data, t_list *map_lines, int max_width)
{
	t_list	*tmp;
	int		i;

	tmp = map_lines;
	i = 0;
	while (tmp)
	{
		data->map[i] = ft_calloc(max_width + 1, sizeof(char));
		if (!data->map[i])
			error_exit("Memory allocation failed for map line!", data);
		ft_memset(data->map[i], ' ', max_width);
		ft_memcpy(data->map[i], tmp->content, ft_strlen(tmp->content));
		tmp = tmp->next;
		i++;
	}
}

void	process_trimmed_line(char *trimmed, int *map_started, t_parse_ctx *ctx)
{
	int	res;

	if (!*map_started)
	{
		res = handle_non_map_line(trimmed, ctx->data,
				ctx->map_lines, ctx->max_width);
		if (res == 2)
			*map_started = 1;
	}
	else
	{
		handle_map_line(trimmed, ctx->map_lines, ctx->max_width);
	}
}

void	allocate_and_fill_map(t_data *data, t_list *map_lines, int max_width)
{
	data->map_height = ft_lstsize(map_lines);
	data->map_width = max_width;
	data->map = ft_calloc(data->map_height + 1, sizeof(char *));
	if (!data->map)
		error_exit("Memory allocation failed for map!", data);
	copy_map_lines(data, map_lines, max_width);
}

void	add_map_line(char *trimmed, t_list **map_lines, int *max_width)
{
	int	len;

	len = ft_strlen(trimmed);
	if (len > *max_width)
		*max_width = len;
	ft_lstadd_back(map_lines, ft_lstnew(ft_strdup(trimmed)));
	free(trimmed);
}
