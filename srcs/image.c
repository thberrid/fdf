/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 01:52:05 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/30 07:45:35 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

float	get_range(t_matrix *plan, unsigned char dimension)
{
	float	min;
	float	max;

	min = matrix_get(plan, FT_INTMAX, dimension, &get_min);
//	ft_putstr("min ");
//	ft_putfloat(min, 5);
//	ft_putchar('\n');
	max = matrix_get(plan, FT_INTMIN, dimension, &get_max);
//	ft_putstr("max ");
//	ft_putfloat(max, 5);
//	ft_putchar('\n');
	return (max - min);
}

void	print_this(t_vertex *this, t_vertex *nullit)
{
	FT_UNUSED(nullit);

	ft_putstr("new hope ");
	ft_putnbr((unsigned int)this->x);
	ft_putchar('\n');
}

int		get_dimension(int dimension, t_pixel *px)
{
	if (dimension == X)
		return (px->x);
	return (px->y);
}

int		is_inf(int a, t_pixel *px, int dimension)
{
	int	b;

	b = get_dimension(dimension, px);
	if (a < b)
		return (a);
	return (b);
}

int		is_sup(int a, t_pixel *px, int dimension)
{
	int	b;

	b = get_dimension(dimension, px);
	if (a > b)
		return (a);
	return (b);
}

int		int_minmax(t_matrix *matrix, int def_val, int dimension, int (*f)(int, t_pixel *, int))
{
	unsigned int		i;
	unsigned int		j;
	int		extrem;

	i = 0;
	extrem = def_val;
	while (i < matrix->row_len)
	{
		j = 0;
		while (j < matrix->column_len)
		{
			extrem = f(extrem, &((t_pixel *)matrix->value[i])[j], dimension);
			j += 1;
		}
		i += 1;
	}
	return (extrem);
}

int		int_range(t_matrix *matrix, int dimension)
{
	int min;
	int max;

	min = int_minmax(matrix, FT_INTMAX, dimension, &is_inf);
	max = int_minmax(matrix, FT_INTMIN, dimension, &is_sup);
	return (max - min);
}

unsigned char get_alt_color(float y, float max)
{
	unsigned char color;

	color = (unsigned char)((y * 255) / max);
	return (color);
}

void	img_build(t_matrix *img, t_matrix *plan, t_window *w)
{
	float		ratio_img;
	float		ratio_w;
	float		scaler;
	float		y_min;
	float		y_max;
	float		y_median;

	y_min = matrix_get(&w->vertices, FT_INTMAX, Y, &get_min);
	y_max = matrix_get(&w->vertices, FT_INTMIN, Y, &get_max);
	y_median = y_min + ((y_max - y_min) / 2);

/*	
	ft_putfloat(y_min, 5);
	ft_putchar('\n');
	ft_putfloat(y_max, 5);
	ft_putchar('\n');
*/
	/* protect against 0 division :> */
	ratio_img = get_range(plan, X) / get_range(plan, Y);
	ratio_w = (w->width - 100) / (w->height - 100);
	
	/* scale */

	if (ratio_img > ratio_w)
		scaler = (w->width - 100) / get_range(plan, X);
	else
		scaler = (w->height - 100) / get_range(plan, Y);

	unsigned int		y;
	unsigned int		x;
	t_pixel *px;
	t_vertex *this_vertex;
	t_vertex *this_y;

	y = 0;
	while (y < img->row_len)
	{
		x = 0;
		while (x < img->column_len)
		{
			px = &((t_pixel *)img->value[y])[x];
			this_vertex = &((t_vertex *)plan->value[y])[x];
			this_y = &((t_vertex *)w->vertices.value[y])[x];
			px->x = (unsigned int)(this_vertex->x * scaler);
			px->y = w->height - ((unsigned int)(this_vertex->y * scaler));
			
			px->color = 0;
			color_add(&px->color, 255, GREEN);
			color_add(&px->color, 255, BLUE);
			color_add(&px->color, 255, RED);
			if (this_y->y > y_median)
			{
				color_remove(&px->color, get_alt_color(this_y->y - y_median, y_max - y_min), RED);
//				ft_putendl("ici");
			}
			if (this_y->y < y_median)
			{
				color_remove(&px->color, get_alt_color(y_median + this_y->y, y_max - y_min), GREEN);
//				ft_putendl("la");
			}
//	ft_putstr("> ");
//	ft_putfloat(this_vertex->y, 5);
//	ft_putchar('\n');
//	ft_putnbr(get_alt_color(this_y->y, -1 * y_min));
//		ft_putendl("");
//			ft_putnbr(px->color);
//			ft_putchar('\n');
	//		px->y = (unsigned int)(this_vertex->y * 50);
			x += 1;
		}
		y += 1;
	}


	/* centering img */

	int		shift_x;
	int		shift_y;

	shift_x = int_minmax(img, FT_INTMIN, X, &is_sup) - ((w->width) / 2) - (int_range(img, X) / 2);
	shift_y = int_minmax(img, FT_INTMIN, Y, &is_sup) - ((w->height) / 2) - (int_range(img, Y) / 2); 
		y = 0;
	while (y < img->row_len)
	{
		x = 0;
		while (x < img->column_len)
		{
			px = &((t_pixel *)img->value[y])[x];
			px->x -= shift_x;
			px->y -= shift_y;
			x += 1;
		}
		y += 1;
	}

}
