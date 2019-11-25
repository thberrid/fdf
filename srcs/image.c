/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 01:52:05 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/25 05:49:17 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

float	get_range(t_matrix *plan, unsigned char dimension)
{
	float	min;
	float	max;

	min = matrix_get(plan, 0, dimension, &get_min);
	ft_putstr("min ");
	ft_putfloat(min, 5);
	ft_putchar('\n');
	max = matrix_get(plan, 0, dimension, &get_max);
	ft_putstr("max ");
	ft_putfloat(max, 5);
	ft_putchar('\n');
	return (max - min);
}

void	englarge_this(t_vertex *this_px, t_vertex *this_vertex, t_vertex *ratio)
{
	this_px->x = (int)(this_vertex->x * ratio->x);
	this_px->y = (int)(this_vertex->y * ratio->x);
	ft_putstr("ratio ");
	ft_putfloat(ratio->x, 5);
	ft_putchar('\n');
	ft_putstr("px x ");
	ft_putnbr(this_px->x);
	ft_putchar('\n');
	ft_putstr("px y ");
	ft_putnbr(this_px->y);
	ft_putchar('\n');
}

void	print_this(t_vertex *this, t_vertex *nullit)
{
	FT_UNUSED(nullit);

	ft_putstr("new hope ");
	ft_putnbr((unsigned int)this->x);
	ft_putchar('\n');
}

void	img_update(t_matrix *img, t_matrix *plan, t_window *w)
{
	t_vertex	range;
	t_vertex	enlargmnt;

	range.x = get_range(plan, X);
	range.y = get_range(plan, Y);
	
	ft_putstr("rx ");
	ft_putfloat(range.x, 5);
	ft_putchar('\n');
	ft_putstr("ry ");
	ft_putfloat(range.y, 5);
	ft_putchar('\n');
	
	enlargmnt.x = w->width / range.x;
	ft_putstr("img ");
	ft_putnbr(w->width);
	ft_putchar('\n');
	//matrix_cpy(img, plan, &enlargmnt, &englarge_this);
	unsigned int		y;
	unsigned int		x;
	t_pixel *px;
	t_vertex *this_vertex;

	y = 0;
	while (y < img->row_len)
	{
		x = 0;
		while (x < img->column_len)
		{
			px = &((t_pixel *)img->value[y])[x];
			this_vertex = &((t_vertex *)plan->value[y])[x];
			px->x = (unsigned int)(this_vertex->x  * 50);
			px->y = (unsigned int)(this_vertex->y * 50);
			x += 1;
		}
		y += 1;
	}
}
