/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 03:20:17 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/14 03:06:17 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <fdf.h>

int		draw_radius(int keycode, t_window *w)
{
	t_pixel	px;

	px.color.r = (char)keycode;
	px.color.g = (char)keycode * 2;
	px.color.b = (char)keycode * 3;
	print_memory(&px.color, sizeof(t_hexcolor));
	px.x = w->width / 2;
	px.y = w->height / 2;
	ft_putnbr(keycode);
	ft_putchar('\n');
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
		mlx_pixel_put(w->mlx, w->ptr, px.x, px.y, 750000);
	}
	return (0);
}

int		main(void)
{
	t_window	w;

	ft_bzero(&w, sizeof(t_window));
	w.width = 750;
	w.height = 750;
	ft_strcpy(w.name, "lolilol");
	w.mlx = mlx_init();
	w.ptr = mlx_new_window(w.mlx, w.width, w.height, w.name);
	mlx_key_hook(w.ptr, &draw_radius, &w);
	mlx_loop(w.mlx);
	return (0);
}
