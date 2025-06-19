/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luinasci <luinasci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:44:28 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/19 19:11:26 by luinasci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	char	*ext;
	t_data	*data;

	if (argc != 2)
		error_exit("Usage: ./cub3D <map.cub>", NULL);

	// Validate file extension
	ext = ft_strrchr(argv[1], '.');
	if (!ext || ft_strcmp(ext, ".cub"))
		error_exit("Invalid file extension", NULL);

	// Parse and validate map file
	data = parse_cub_file(argv[1]);

	// Clean exit (error_exit handles memory cleanup)
	printf("Map parsed successfully!\n");
	free_data(data);
	return (0);
}
