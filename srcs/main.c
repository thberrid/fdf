/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 03:20:17 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/27 07:17:23 by thberrid         ###   ########.fr       */
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

void	draw_line(t_pixel *start, t_pixel *end, t_img *img)
{
	unsigned int delta_fast;
	unsigned int delta_slow;
	int delta_x;
	int delta_y;
	int step_x;
	int step_y;
	unsigned int x;
	unsigned int y;
	int			color;
	float		error;
	unsigned int	i;

	i = 0;

	if (!end)
		return ;
	
	color = 0;
	color_add(&color, 255, RED);

//	delta_x = ABS((end->x - start->x));	
//	delta_y = ABS(end->y - start->y));
	delta_x = end->x - start->x;
	delta_y = end->y - start->y;
	if (delta_x < 0)
		delta_x *= -1;
	if (delta_y < 0)
		delta_y *= -1;
	delta_fast = delta_x > delta_y ? delta_x : delta_y;
	delta_slow = delta_x < delta_y ? delta_x : delta_y;
	
	step_x = end->x > start->x ? 1 : -1;
	step_y = end->y > start->y ? 1 : -1;
/*	
	ft_putstr("whaaaaaat ");
	ft_putnbr(start->y);
	ft_putchar(' ');
	ft_putnbr(end->y);
	ft_putchar('\n');
	ft_putstr("step ");
	ft_putnbr(step_y);
	ft_putchar('\n');
*/
	x = start->x;
	y = start->y;
	error = delta_fast / 2;
	/*
	if (delta_x < delta_y)
	{
		ft_putstr("ob ");
		ft_putnbr(delta_y);
		ft_putchar('\n');
	}
	*/
	/*
ft_putendl("-----------------");
		ft_putstr("delta x ");
		ft_putnbr(delta_x);
		ft_putchar('\n');
		ft_putstr("delta y ");
		ft_putnbr(delta_y);
		ft_putchar('\n');
		ft_putstr("delta fast ");
		ft_putnbr(delta_fast);
		ft_putchar('\n');
		ft_putstr("x start ");
		ft_putnbr(x);
		ft_putchar('\n');
		ft_putstr("y start ");
		ft_putnbr(y);
		ft_putchar('\n');
ft_putendl("");
		ft_putstr("x end ");
		ft_putnbr(end->x);
		ft_putchar('\n');
		ft_putstr("y end ");
		ft_putnbr(end->y);
		ft_putchar('\n');
ft_putendl("");
*/
//	unsigned int maxdot =  (750 * img->bits_px / 8) + (750 * img->size_line);
	while (i < delta_fast)
	{
	
	/*	
		ft_putstr("x ");
		ft_putnbr(x);
		ft_putchar(' ');
		ft_putstr("y ");
		ft_putnbr(y);
		ft_putchar('\n');
	*/
//		unsigned int dot = (x * img->bits_px / 8) + (y * img->size_line);
		if (x > 0 && y > 0 && x < 750 && y < 750)
			ft_memcpy(&(img->data[(x * img->bits_px / 8) + (y * img->size_line)]), &color, img->bits_px / 8);
		error -= delta_slow;
		if (error <= 0)
		{
			if (delta_x > delta_y)
				y += step_y;
			else
				x += step_x;
			error += (delta_x > delta_y ? delta_x : delta_y);
		}
		if (delta_x <= delta_y)
			y += step_y;
		else
			x += step_x;
		i += 1;
	}
}

void	draw_edges(t_img *img, t_matrix *pixels, unsigned int x, unsigned int y)
{
	t_pixel		*start;
	t_pixel		*end;

	start = &((t_pixel *)pixels->value[y])[x];
	end = NULL;
	if (x + 1 != pixels->column_len)
		end = &((t_pixel *)pixels->value[y])[x + 1];
	draw_line(start, end, img);
	end = NULL;
	if (y + 1 != pixels->row_len)
		end = &((t_pixel *)pixels->value[y + 1])[x];
	draw_line(start, end, img);
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

	/* print px */
	
	y = 0;
	while (y < w->px_coord.row_len)
	{
		x = 0;
		while (x < w->px_coord.column_len)
		{
			this = &((t_pixel *)w->px_coord.value[y])[x];
			ft_putstr("px ");
			ft_putnbr(x + (w->px_coord.column_len * y));
			ft_putstr("\nx ");
			ft_putnbr(this->x);
			ft_putstr("\ny ");
			ft_putnbr(this->y);
			ft_putendl("\n-----------\n");
			x += 1;
		}
		y += 1;
	}
	

	/* line */

	ft_putendl("ok boomer");
	y = 0;

	while (y < w->px_coord.row_len)
	{
		x = 0;
		while (x < w->px_coord.column_len)
		{
			draw_edges(&w->img, &w->px_coord, x, y);
			x += 1;
		}
		y += 1;
	}

	//ft_putendl("ok kevin");
	//matrix_printinfos(&w->px_coord);

//	unsigned int maxdot =  (w->width * w->img.bits_px / 8) + (w->height * w->img.size_line);

	y = 0;
	while (y < w->px_coord.row_len)
	{
		x = 0;
		while (x < w->px_coord.column_len)
		{
			this = &((t_pixel *)w->px_coord.value[y])[x];
		/*	ft_putstr("str ");
			ft_putnbr((unsigned int)this->x);
			ft_putchar(' ');
			ft_putnbr((unsigned int)this->y);
			ft_putchar('\n');
		*/
//			unsigned int dot = ((unsigned int)this->x * w->img.bits_px / 8) + ((unsigned int)this->y * w->img.size_line);
			if (this->x > 0 && this->y > 0 && this->y < 750 && this->x < 750)
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
	ft_strcpy(w->name, "ok boomer");
}

int		main(int ac, char **av)
{
	t_window		w;
	t_matrix		vertices;
	t_matrix		plan;

	if (ac == 2 && map_parse(&vertices, av[1]))
	{
		if (!matrix_init(&plan, &vertices, VERTEX))
			return (0);
		window_init(&w);
//		matrix_apply(&plan, &vertices, &perspective);
		matrix_apply(&plan, &vertices, &ortho);
		matrix_init(&w.px_coord, &plan, PIXEL);
		img_build(&w.px_coord, &plan, &w);
//		matrix_set(&w.px_coord, NULL, &print_this);
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
