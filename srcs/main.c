/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 03:20:17 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/15 07:49:30 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int		draw_radius(int keycode, t_window *w)
{
	t_pixel		px;

	ft_putnbr(keycode);
	ft_putchar('\n');
	if (keycode > 75)
		return (0);
	px.color.r = (char)keycode;
	px.color.g = (char)keycode * 2;
	px.color.b = (char)keycode * 3;
	px.color.a = 0;
	print_memory(&px.color, sizeof(t_hexcolor));
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
		mlx_pixel_put(w->mlx, w->ptr, px.x, px.y, 99999999);
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
	t_window	w;
	t_matrix	matrix;

	if (ac == 2 && map_parse(&matrix, av[1]))
	{
		window_init(&w);
		w.mlx = mlx_init();
		w.ptr = mlx_new_window(w.mlx, w.width, w.height, w.name);
		mlx_key_hook(w.ptr, &draw_radius, &w);
		mlx_loop(w.mlx);
	}
	matrix_free(&matrix);
	return (0);
}
