/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:35:19 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/25 18:22:29 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void parse_lines_loop(int fd, t_data *data,
					  t_list **map_lines, int *max_width)
{
	char *line;
	int map_started;
	//t_parse_ctx ctx;
	int line_num = 1;

	map_started = 0;
	//ctx.data = data;
	//ctx.map_lines = map_lines;
	//ctx.max_width = max_width;
	line = get_next_line(fd);
	while (line)
	{
		char *nl = strchr(line, '\n');
		if (nl)
			*nl = '\0';

		if (map_started)
		{
			// Ignore trailing blank lines after the map
			char *trimmed = trim_and_free_line(ft_strdup(line));
			if (!trimmed || trimmed[0] == '\0')
			{
				free(trimmed);
				free(line);
				line = get_next_line(fd);
				line_num++;
				continue;
			}
			handle_map_line(line, map_lines, max_width, data);
			free(trimmed);
		}
		else
		{
			char *trimmed = trim_and_free_line(ft_strdup(line));
			if (!trimmed)
			{
				free(line);
				line = get_next_line(fd);
				line_num++;
				continue;
			}
			if (trimmed[0] == '\0')
			{
				free(trimmed);
				free(line);
				line = get_next_line(fd);
				line_num++;
				continue;
			}
			int res = handle_non_map_line(trimmed, data, map_lines, max_width);
			if (res == 1)
			{
				free(line);
			}
			else if (res == 2)
			{
				map_started = 1;
				handle_map_line(line, map_lines, max_width, data);
			}
			else
			{
				fprintf(stderr, "Error\nUnrecognized line at %d: \"%s\"\n", line_num, line);
				free(trimmed);
				free(line);
				error_exit("Parsing failed due to unrecognized line.", data);
			}
		}
		line = get_next_line(fd);
		line_num++;
	}
}

void check_required_elements(t_data *data)
{
	if (!data->north || !data->south || !data->east || !data->west || data->floor == -1 || data->ceiling == -1)
	{
		fprintf(stderr, "Error\nMissing required map elements:\n");
		if (!data->north)
			fprintf(stderr, "- North texture (NO)\n");
		if (!data->south)
			fprintf(stderr, "- South texture (SO)\n");
		if (!data->east)
			fprintf(stderr, "- East texture (EA)\n");
		if (!data->west)
			fprintf(stderr, "- West texture (WE)\n");
		if (data->floor == -1)
			fprintf(stderr, "- Floor color (F)\n");
		if (data->ceiling == -1)
			fprintf(stderr, "- Ceiling color (C)\n");
		error_exit("There's something missing in your map!", data);
	}
}

t_data *parse_cub_file(char *filename)
{
	int fd;
	t_data *data;
	t_list *map_lines;
	int max_width;

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
	check_required_elements(data);
	allocate_and_fill_map(data, map_lines, max_width);
	register_doors(data);
	ft_lstclear(&map_lines, free);
	validate_map_chars(data);
	validate_map_with_flood_fill(data);
	return (data);
}
