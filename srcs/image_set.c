/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 08:29:34 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/08 22:31:47 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	color_set(t_vertex *min, t_vertex *max, t_pixel *px, t_vertex *this_y)
{
//	if (min->z < 0)
//		min->z *= -1;
//	color_add(&px->color,
//		get_alt_alpha(this_y->z + min->z, max->z + min->z), ALPHA);
	if (this_y->y > 0)
		color_remove(&px->color, get_alt_color(this_y->y + 1, max->y + 1), RED);
	if (this_y->y < 0)
		color_remove(&px->color,
			get_alt_color(this_y->y + 1, min->y + 1), GREEN);
}

void	set_minmax(t_vertex *min, t_vertex *max, t_matrix *matrix)
{
	min->y = matrix_get(matrix, FT_INTMAX, Y, &get_min);
	max->y = matrix_get(matrix, FT_INTMIN, Y, &get_max);
	min->z = matrix_get(matrix, FT_INTMAX, Z, &get_min);
	max->z = matrix_get(matrix, FT_INTMIN, Z, &get_max);
}

void	img_centering(t_matrix *img, t_window *w)
{
	unsigned int	y;
	unsigned int	x;
	int				shift_x;
	int				shift_y;
	t_pixel			*px;

	shift_x = int_minmax(img,
		FT_INTMIN, X, &is_sup) - ((w->width) / 2) - (int_range(img, X) / 2);
	shift_y = int_minmax(img,
		FT_INTMIN, Y, &is_sup) - ((w->height) / 2) - (int_range(img, Y) / 2);
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

void	apply_scale(t_matrix *img, t_matrix *plan, t_window *w, float scaler)
{
	unsigned int	y;
	unsigned int	x;
	t_pixel			*px;
	t_vertex		*this_vertex;
	t_vertex		*this_y;

	y = 0;
	while (y < img->row_len)
	{
		x = 0;
		while (x < img->column_len)
		{
			px = &((t_pixel *)img->value[y])[x];
			this_vertex = &((t_vertex *)plan->value[y])[x];
			this_y = &((t_vertex *)w->obj_vertices.value[y])[x];
			px->x = (unsigned int)(this_vertex->x * scaler);
			px->y = w->height - ((unsigned int)(this_vertex->y * scaler));
			x += 1;
		}
		y += 1;
	}
}

void	img_setcolors(t_matrix *img, t_matrix *obj)
{
	t_vertex		min;
	t_vertex		max;
	t_pixel			index;
	t_pixel			*px;
	t_vertex		*this_vertex;

	set_minmax(&min, &max, obj);
	index.y = 0;
	while ((unsigned int)index.y < img->row_len)
	{
		index.x = 0;
		while ((unsigned int)index.x < img->column_len)
		{
			px = &((t_pixel *)img->value[index.y])[index.x];
	//		px->color = 0;
			this_vertex = &((t_vertex *)obj->value[index.y])[index.x];
			color_setwhite(&px->color);
			color_set(&min, &max, px, this_vertex);
			index.x += 1;
		}
		index.y += 1;
	}
}

void	img_setalpha(t_matrix *img, t_matrix *obj)
{
	float			min;
	float			max;
	t_pixel			index;
	t_pixel			*px;
	t_vertex		*this_vertex;

	min = matrix_get(obj, FT_INTMAX, Z, &get_min);
	max = matrix_get(obj, FT_INTMIN, Z, &get_max);
	if (min < 0)
		min *= -1;
	if (max < 0)
		max *= -1;
	index.y = 0;
	while ((unsigned int)index.y < img->row_len)
	{
		index.x = 0;
		while ((unsigned int)index.x < img->column_len)
		{
			px = &((t_pixel *)img->value[index.y])[index.x];
			this_vertex = &((t_vertex *)obj->value[index.y])[index.x];
			color_add(&px->color,
			get_alt_alpha(this_vertex->z + min, max + min), ALPHA);
			index.x += 1;
		}
		index.y += 1;
	}
}

void	img_setpositions(t_matrix *img, t_matrix *plan, t_window *w)
{
	t_pixel			index;
	t_pixel			*px;
	t_vertex		*this_vertex;

	index.y = 0;
	while ((unsigned int)index.y < img->row_len)
	{
		index.x = 0;
		while ((unsigned int)index.x < img->column_len)
		{
			px = &((t_pixel *)img->value[index.y])[index.x];
			this_vertex = &((t_vertex *)plan->value[index.y])[index.x];
			px->x = (unsigned int)(this_vertex->x);
			px->y = w->height - ((unsigned int)(this_vertex->y));
			index.x += 1;
		}
		index.y += 1;
	}
}
