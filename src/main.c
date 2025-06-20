/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcologne <jcologne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:44:28 by luinasci          #+#    #+#             */
/*   Updated: 2025/06/20 20:04:08 by jcologne         ###   ########.fr       */
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
	render_image(data);
	free_data(data);
	return (0);
}
