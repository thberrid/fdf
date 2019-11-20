/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 03:20:17 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/20 10:07:14 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int		draw_radius(unsigned int keycode, t_window *w)
{
	t_pixel		px;
	int			color;
	int			blue;

	color = 0;
	blue = 0;
	color_add(&blue, 255, GREEN);
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
	
//	mlx_clear_window(w->mlx, w->ptr);
	if (w->img.id)
		mlx_destroy_image(w->mlx, w->img.id);
	w->img.id = mlx_new_image(w->mlx, w->width, w->height);
	w->img.data = mlx_get_data_addr(w->img.id, &w->img.bits_px, &w->img.size_line, &w->img.endian); 
	ft_putstr("sl ");
	ft_putnbr(w->img.size_line);
	ft_putchar('\n');
	ft_putstr("bpp ");
	ft_putnbr(w->img.bits_px);
	ft_putchar('\n');
	px.x = w->width / 2;
	px.y = w->height / 2;
	while (px.x != keycode * 100 && px.y != keycode * 50)
	{
	ft_putstr("X ");
	ft_putnbr(px.x * w->img.bits_px / 8);
	ft_putchar('\n');
	ft_putstr("Y ");
	ft_putnbr(px.y * w->img.size_line);
	ft_putchar('\n');
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
		ft_memcpy(&(w->img.data[(px.x * w->img.bits_px / 8) + (px.y * w->img.size_line)]), &color, w->img.bits_px / 8);
		mlx_pixel_put(w->mlx, w->ptr, px.x + 5, px.y + 5, blue);
	}
	mlx_put_image_to_window(w->mlx, w->ptr, w->img.id, 0, 0);
	return (0);
}
/*
static void		matrix_output(t_vertex *vertex, t_vertex *useless)
{
	FT_UNUSED(useless);
	ft_putfloat(vertex->x, 3);
	ft_putchar(' ');
	ft_putfloat(vertex->y, 3);
	ft_putchar(' ');
	ft_putfloat(vertex->z, 3);
	ft_putchar('\n');
}
*/
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
		matrix_apply(&plan, &vertices, &perspective);
	//	matrix_set(&plan, &((t_vertex *)vertices.value[0])[0], matrix_output);
	//	img_init(&image);
	//	img_update(&image, &plan);
	//	frame_put(&image, &w / mlx)
		window_init(&w);
		w.mlx = mlx_init();
		w.ptr = mlx_new_window(w.mlx, w.width, w.height, w.name);
		mlx_key_hook(w.ptr, &draw_radius, &w);
	//	vertices_update > translation, rotation, zoom
	//	perspective() / ortho()
	//	img_update(&frame, &plan);
		mlx_loop(w.mlx);
	}
	matrix_free(&vertices);
	return (0);
}
