/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcologne <jcologne@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 08:10:39 by jcologne          #+#    #+#             */
/*   Updated: 2025/06/26 13:12:45 by jcologne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window(t_mlx_data *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, W, H, "Cub3d");
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx->img_addr = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->line_size, &mlx->endian);
}

static void	setup_orientation(t_mlx_data *mlx, char dir)
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

static void init_keys(t_keys *keys)
{
	keys->w = 0;
	keys->a = 0;
	keys->s = 0;
	keys->d = 0;
	keys->left = 0;
	keys->right = 0;
	keys->esc = 0;
}

void	init_player(t_game *game)
{
	init_keys(&game->keys);
	game->mlx->pos_x = game->data->player_x + 0.5;
	game->mlx->pos_y = game->data->player_y + 0.5;
	setup_orientation(game->mlx, game->data->player_direction);
}

void load_fire_textures(t_mlx_data *mlx, t_data *data)
{
    char *paths[FIREBALL_FRAMES] = {
        "textures/fire/fire0.xpm",
        "textures/fire/fire1.xpm",
        "textures/fire/fire2.xpm",
        "textures/fire/fire3.xpm"
    };
    int i = 0;

    printf("Loading fireball textures...\n");
    while (i < FIREBALL_FRAMES)
    {
        mlx->fire_tex[i] = load_xpm(mlx->mlx, paths[i]);
        if (!mlx->fire_tex[i])
        {
            printf("Error: Failed to load fire texture %d: %s\n", i, paths[i]);
            error_exit("Fire texture loading failed", data);
        }
        printf("Loaded fire texture %d: %dx%d\n", 
              i, mlx->fire_tex[i]->w, mlx->fire_tex[i]->h);
        i++;
    }
}

void init_fireballs(t_mlx_data *mlx)
{
    int i = 0;

    printf("Initializing fireballs...\n");
    while (i < MAX_FIREBALLS)
    {
        mlx->fireballs[i].active = 0;
        mlx->fireballs[i].frame = 0;
        mlx->fireballs[i].frame_count = 0;
        i++;
    }
}

void	init_textures(t_game *game)
{
	t_mlx_data	*mlx = game->mlx;

	mlx->textures[0] = load_xpm(mlx->mlx, game->data->north);
	mlx->textures[1] = load_xpm(mlx->mlx, game->data->south);
	mlx->textures[2] = load_xpm(mlx->mlx, game->data->east);
	mlx->textures[3] = load_xpm(mlx->mlx, game->data->west);
	mlx->textures[4] = load_xpm(mlx->mlx, "textures/door.xpm");
	load_fire_textures(mlx, game->data);
   init_fireballs(mlx);

	if (!mlx->textures[0] || !mlx->textures[1]
		|| !mlx->textures[2] || !mlx->textures[3] || !mlx->textures[4])
	{
		fprintf(stderr, "Error: Failed to load one or more textures:\n");
		if (!mlx->textures[0]) fprintf(stderr, "- North texture: %s\n", game->data->north);
		if (!mlx->textures[1]) fprintf(stderr, "- South texture: %s\n", game->data->south);
		if (!mlx->textures[2]) fprintf(stderr, "- East texture: %s\n", game->data->east);
		if (!mlx->textures[3]) fprintf(stderr, "- West texture: %s\n", game->data->west);
		if (!mlx->textures[4]) fprintf(stderr, "- Door texture: textures/door.xpm\n");
		error_exit("Texture loading failed!", game->data);
	}
}
