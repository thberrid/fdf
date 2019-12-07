/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertices_transform.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 06:27:27 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/07 12:29:43 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <math.h>

int		set_rotation_angle(t_matrix *matrix, double theta)
{
	t_vertex			*this;

	if (!malloc_matrix(matrix))
		return (0);
	this = &((t_vertex *)matrix->value[0])[0];
	this->x = (float)cos(theta);
	this->y = 0;
	this->z = (float)(-1 * sin(theta));
	this = &((t_vertex *)matrix->value[0])[1];
	this->x = 0;
	this->y = 1;
	this->z = 0;
	this = &((t_vertex *)matrix->value[0])[2];
	this->x = (float)sin(theta);
	this->y = 0;
	this->z = (float)cos(theta);
	return (1);
}

int		set_scale(t_matrix *matrix, float coef)
{
	t_vertex		*this;

	if (!malloc_matrix(matrix))
		return (0);
	this = &((t_vertex *)matrix->value[0])[0];
	this->x = coef;
	this->y = 0;
	this->z = 0;
	this = &((t_vertex *)matrix->value[0])[1];
	this->x = 0;
	this->y = coef;
	this->z = 0;
	this = &((t_vertex *)matrix->value[0])[2];
	this->x = 0;
	this->y = 0;
	this->z = coef;
	return (1);
}

void	matrix_transform(t_matrix *rot, t_vertex *vertices)
{
	t_vertex tmp;
	t_vertex *one;
	t_vertex *two;
	t_vertex *three;

	one = &((t_vertex *)rot->value[0])[0];
	two = &((t_vertex *)rot->value[0])[1];
	three = &((t_vertex *)rot->value[0])[2];
	tmp.x = (one->x * vertices->x) + (two->x * vertices->y)
		+ (three->x * vertices->z);
	tmp.y = (one->y * vertices->x) + (two->y * vertices->y)
		+ (three->y * vertices->z);
	tmp.z = (one->z * vertices->x) + (two->z * vertices->y)
		+ (three->z * vertices->z);
	vertices->x = tmp.x;
	vertices->y = tmp.y;
	vertices->z = tmp.z;
}

int		vertices_scale(t_matrix *vertices, float coef)
{
	unsigned int		i;
	unsigned int		j;
	t_matrix			scale;

	ft_bzero(&scale, sizeof(t_matrix));
	scale.row_len = 1;
	scale.column_len = 3;
	if (!set_scale(&scale, coef))
		return (0);
	i = 0;
	while (i < vertices->row_len)
	{
		j = 0;
		while (j < vertices->column_len)
		{
			matrix_transform(&scale, &((t_vertex *)vertices->value[i])[j]);
			j += 1;
		}
		i += 1;
	}
	matrix_free(&scale);
	return (1);
}

int		vertices_rotate(t_window *w, unsigned int keycode)
{
	unsigned int	i;
	unsigned int	j;
	t_matrix		rot;

	ft_bzero(&rot, sizeof(t_matrix));
	rot.row_len = 1;
	rot.column_len = 3;
	if (!set_rotation_angle(&rot, keycode == KEY_LEFT ? -25 : 25))
		return (0);
	i = 0;
	while (i < w->vertices.row_len)
	{
		j = 0;
		while (j < w->vertices.column_len)
		{
			matrix_transform(&rot, &((t_vertex *)w->vertices.value[i])[j]);
			j += 1;
		}
		i += 1;
	}
	matrix_free(&rot);
	return (1);
}
