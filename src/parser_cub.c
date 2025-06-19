/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:35:19 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/19 19:53:11 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	parse_lines_loop(int fd, t_data *data,
	t_list **map_lines, int *max_width)
{
	char		*line;
	char		*trimmed;
	int			map_started;
	t_parse_ctx	ctx;

	map_started = 0;
	ctx.data = data;
	ctx.map_lines = map_lines;
	ctx.max_width = max_width;
	line = get_next_line(fd);
	while (line)
	{
		trimmed = trim_and_free_line(line);
		if (!trimmed)
		{
			line = get_next_line(fd);
			continue ;
		}
		process_trimmed_line(trimmed, &map_started, &ctx);
	line = get_next_line(fd);
	}
}

void	check_required_elements(t_data *data)
{
	if (!data->north || !data->south || !data->east
		||!data->west || data->floor == -1 || data->ceiling == -1)
		error_exit("There's something missing in your map!", data);
}

t_data	*parse_cub_file(char *filename)
{
	int		fd;
	t_data	*data;
	t_list	*map_lines;
	int		max_width;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Something is wrong with the file!", NULL);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		error_exit("Memory allocation failed!", NULL);
	data->floor = -1;
	data->ceiling = -1;
	map_lines = NULL;
	max_width = 0;
	parse_lines_loop(fd, data, &map_lines, &max_width);
	close(fd);
	printf("N: %s\nS: %s\nE: %s\nW: %s\nF: %d\nC: %d\n",
	data->north, data->south, data->east, data->west,
	data->floor, data->ceiling); //debug
	check_required_elements(data);
	allocate_and_fill_map(data, map_lines, max_width);
	ft_lstclear(&map_lines, free);
	validate_map_chars(data);
	validate_map_with_flood_fill(data);
	return (data);
}
