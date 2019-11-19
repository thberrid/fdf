/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 03:20:17 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/19 08:25:00 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int		draw_radius(int keycode, t_window *w)
{
	t_pixel		px;
	int			color;

	color = 0;
	color_add(&color, 255, RED);
	color_add(&color, 255, BLUE);
	color_remove(&color, 255, BLUE);
	
	ft_putstr("color ");
	ft_putnbr(color);
	ft_putchar('\n');
	print_memory(&color, sizeof(int));
	
	ft_putstr("keycode ");
	ft_putnbr(keycode);
	ft_putchar('\n');

	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(w->mlx, w->ptr);
		exit(0);
	}
	if (keycode > 75)
		return (0);
	px.x = w->width / 2;
	px.y = w->height / 2;
	mlx_clear_window(w->mlx, w->ptr);
	while (px.x != keycode * 100 && px.y != keycode * 50)
	{
		if (px.x != keycode * 100)
		{
			if (px.x < keycode * 100)
				px.x += 1;
			else
				px.x -= 1;
		}
		if (px.y != keycode * 50)
		{
			if (px.y < keycode * 50)
				px.y += 1;
			else
				px.y -= 1;
		}
		mlx_pixel_put(w->mlx, w->ptr, px.x, px.y, color);
	}
	return (0);
}

void	window_init(t_window *w)
{
	ft_bzero(w, sizeof(t_window));
	w->width = 750;
	w->height = 750;
	ft_strcpy(w->name, "lolilol");
}

int		main(int ac, char **av)
{
	t_window		w;
	t_matrix		vertices;
	t_matrix		plan;

	if (ac == 2 && map_parse(&vertices, av[1]))
	{
		if (!plan_init(&vertices, &plan))
			return (0);
		//projection_perspective(&vertices, &plan);
		window_init(&w);
		w.mlx = mlx_init();
		w.ptr = mlx_new_window(w.mlx, w.width, w.height, w.name);
		mlx_key_hook(w.ptr, &draw_radius, &w);
		mlx_loop(w.mlx);
	}
	matrix_free(&vertices);
	return (0);
}
