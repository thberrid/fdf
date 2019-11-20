/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 05:33:53 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/20 07:50:26 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

/*
**	BROWSE A MATRIX
**	AND SET ITS VALUES FROM A SINGLE VECTOR
*/

void	matrix_set(t_matrix *vertices, t_vertex *vector,
				void (*f)(t_vertex *, t_vertex *))
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < vertices->row_len)
	{
		j = 0;
		while (j < vertices->column_len)
		{
			f(&((t_vertex *)vertices->value[i])[j], vector);
			j += 1;
		}
		i += 1;
	}
}

/*
**	BROWSE A MATRIX
**	AND APPLY TRANFORMATIONS FROM ANOTHER SAME SIZED MATRIX
*/

void	matrix_apply(t_matrix *vertices, t_matrix *vectors,
				void (*f)(t_vertex *, t_vertex *))
{
	unsigned int	i;
	unsigned int	j;
	t_vertex		*vector;

	i = 0;
	while (i < vertices->row_len)
	{
		j = 0;
		while (j < vertices->column_len)
		{
			vector = &((t_vertex *)vectors->value[i])[j];
			f(&((t_vertex *)vertices->value[i])[j], vector);
			j += 1;
		}
		i += 1;
	}
}

/*
** BROWSE A MATRIX
** AND RETURN VALUE DEPENDING A *FUNCTION
*/

float	matrix_get(t_matrix *vertices, float value, float (*f)(float, float))
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < vertices->row_len)
	{
		j = 0;
		while (j < vertices->column_len)
		{
			value = f(value, (float)((t_vertex *)vertices->value[i])[j].y);
			j += 1;
		}
		i += 1;
	}
	return (value);
}
