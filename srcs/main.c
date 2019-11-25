/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 03:20:17 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/25 06:28:51 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	matrix_printinfos(t_matrix *matrix)
{
	ft_putstr("mi n_lines ");
	ft_putnbr(matrix->row_len);
	ft_putstr("\nmi n_colums ");
	ft_putnbr(matrix->column_len);
	ft_putendl("");
}

int		draw_px(unsigned int keycode, t_window *w)
{
	int		color;
	unsigned int		x;
	unsigned int		y;

	ft_putstr("keycode ");
	ft_putnbr(keycode);
	ft_putchar('\n');
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(w->mlx, w->ptr);
		exit(0);
	}		
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

	t_pixel *this;
	color = 0;
	color_add(&color, 255, BLUE);
	color_add(&color, 255, GREEN);
	
	matrix_printinfos(&w->px_coord);

	unsigned int maxdot =  (w->width * w->img.bits_px / 8) + (w->height * w->img.size_line);

	y = 0;
	while (y < w->px_coord.row_len)
	{
		x = 0;
		while (x < w->px_coord.column_len)
		{
			this = &((t_pixel *)w->px_coord.value[y])[x];
			ft_putstr("str ");
			ft_putnbr((unsigned int)this->x);
			ft_putchar(' ');
			ft_putnbr((unsigned int)this->y);
			ft_putchar('\n');
			unsigned int dot = ((unsigned int)this->x * w->img.bits_px / 8) + ((unsigned int)this->y * w->img.size_line);
			if (dot < maxdot)
				ft_memcpy(&(w->img.data[((unsigned int)this->x * w->img.bits_px / 8) + ((unsigned int)this->y * w->img.size_line)]), &color, w->img.bits_px / 8);
			x += 1;
		}
		y += 1;
	}
	mlx_put_image_to_window(w->mlx, w->ptr, w->img.id, 0, 0);
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
		ft_putstr("w ");
		ft_putnbr(w.width);
		ft_putchar('\n');
		if (!matrix_init(&plan, &vertices, VERTEX))
			return (0);
		window_init(&w);
		matrix_apply(&plan, &vertices, &perspective);
		matrix_init(&w.px_coord, &plan, PIXEL);
		img_update(&w.px_coord, &plan, &w);
		matrix_set(&w.px_coord, NULL, &print_this);
		w.mlx = mlx_init();
		w.ptr = mlx_new_window(w.mlx, w.width, w.height, w.name);	
		mlx_key_hook(w.ptr, &draw_px, &w);
	//	vertices_update > translation, rotation, zoom
	//	perspective() / ortho()
	//	img_update(&frame, &plan);
		mlx_loop(w.mlx);
		matrix_free(&vertices);
	}
	return (0);
}
