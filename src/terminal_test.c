#include "cub3d.h"

// Terminal input buffer size
#define INPUT_BUFFER 16

void	print_controls(void)
{
	printf("\nControls:\n");
	printf("  w       - Move forward\n");
	printf("  s       - Move backward\n");
	printf("  a       - Strafe left\n");
	printf("  d       - Strafe right\n");
	printf("  left    - Rotate left\n");
	printf("  right   - Rotate right\n");
	printf("  exit    - Exit test\n\n");
}

void	clear_keys(t_keys *keys)
{
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	keys->left = 0;
	keys->right = 0;
	keys->esc = 0;
}

void	simulate_keypress(t_keys *keys, char *input)
{
	clear_keys(keys);
	if (ft_strcmp(input, "w") == 0)
		keys->w = 1;
	else if (ft_strcmp(input, "s") == 0)
		keys->s = 1;
	else if (ft_strcmp(input, "a") == 0)
		keys->a = 1;
	else if (ft_strcmp(input, "d") == 0)
		keys->d = 1;
	else if (ft_strcmp(input, "left") == 0)
		keys->left = 1;
	else if (ft_strcmp(input, "right") == 0)
		keys->right = 1;
}

void	setup_orientation(t_mlx_data *mlx, char dir)
{
	if (dir == 'N')
	{
		mlx->dir_x = 0;
		mlx->dir_y = -1;
		mlx->plane_x = 0.66;
		mlx->plane_y = 0;
	}
	else if (dir == 'S')
	{
		mlx->dir_x = 0;
		mlx->dir_y = 1;
		mlx->plane_x = -0.66;
		mlx->plane_y = 0;
	}
	else if (dir == 'E')
	{
		mlx->dir_x = 1;
		mlx->dir_y = 0;
		mlx->plane_x = 0;
		mlx->plane_y = 0.66;
	}
	else if (dir == 'W')
	{
		mlx->dir_x = -1;
		mlx->dir_y = 0;
		mlx->plane_x = 0;
		mlx->plane_y = -0.66;
	}
}

int	main(int argc, char **argv)
{
	t_data		*data;
	t_mlx_data	mlx;
	char		input[INPUT_BUFFER];

	if (argc != 2)
		error_exit("Usage: ./terminal_test <map.cub>", NULL);
	data = parse_cub_file(argv[1]);

	// Init dummy mlx
	ft_memset(&mlx, 0, sizeof(t_mlx_data));
	mlx.data = data;
	mlx.pos_x = data->player_x + 0.5;
	mlx.pos_y = data->player_y + 0.5;
	setup_orientation(&mlx, data->player_direction);

	printf("Terminal Test Started!\nPlayer starts at (%.2f, %.2f)\n",
		mlx.pos_x, mlx.pos_y);
	print_controls();

	while (1)
	{
		printf("> ");
		if (!fgets(input, INPUT_BUFFER, stdin))
			break;
		input[ft_strlen(input) - 1] = '\0'; // remove newline

		if (ft_strcmp(input, "exit") == 0)
			break;

		simulate_keypress(&mlx.keys, input);
		calculate_movement(&mlx, &((double){0}), &((double){0}));
		update_player_position((t_game *)&mlx);

		printf("Current Position: (%.2f, %.2f)\n", mlx.pos_x, mlx.pos_y);
	}

	free_data(data);
	printf("Exiting terminal test.\n");
	return (0);
}
