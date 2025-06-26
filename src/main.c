/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:44:28 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/26 16:28:11 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	char	*ext;
	t_data	*data;

	if (argc != 2)
		error_exit("Usage: ./cub3D <map.cub>", NULL);
	ext = ft_strrchr(argv[1], '.');
	if (!ext || ft_strcmp(ext, ".cub"))
		error_exit("Invalid file extension", NULL);
	data = parse_cub_file(argv[1]);
	printf("Map parsed successfully!\n");
	render_image(data);
	free_data(data);
	return (0);
}
