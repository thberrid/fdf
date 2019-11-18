/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_addrow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 07:42:57 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/18 07:12:29 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void				matrix_free(t_matrix *matrix)
{
	unsigned int	i;

	i = 0;
	while (i < matrix->row_len)
	{
		ft_memdel((void **)&matrix[i]);
		i += 1;
	}
	ft_memdel((void **)&matrix);
}

void				arr_free(void *arr, unsigned int step, unsigned int len)
{
	unsigned int	i;

	i = 0;
	while (i < len)
	{
		ft_memdel((void **)&arr[i]);
		i += step;
	}
	ft_memdel((void **)&arr);
}

static unsigned int	matrix_padding(t_matrix *matrix)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	padding;
	unsigned int	padding_biggest;

	i = 0;
	padding = 0;
	while (i < matrix->row_len)
	{
		j = 0;
		while (j < matrix->column_len)
		{
			padding = ft_intlen(matrix->value[i][j]);
			if (padding > padding_biggest)
				padding_biggest = padding;
			j += 1;
		}
		i += 1;
	}
	return (padding_biggest + 1);
}

void				matrix_print(t_matrix *matrix)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	intlen;

	i = 0;
	matrix->padding = matrix_padding(matrix);
	while (i < matrix->row_len)
	{
		j = 0;
		while (j < matrix->column_len)
		{
			ft_putnbr(matrix->value[i][j]);
			intlen = matrix->padding - ft_intlen(matrix->value[i][j]);
			while (intlen)
			{
				ft_putchar(' ');
				intlen -= 1;
			}
			j += 1;
		}
		ft_putchar('\n');
		i += 1;
	}
}

static int			matrix_extend(t_matrix *matrix)
{
	unsigned int	row_n;
	int				**new_value;

	new_value = (int **)ft_memalloc(sizeof(int *) * (matrix->row_len + 1));
	if (!new_value)
		return (0);
	row_n = 0;
	while (row_n < matrix->row_len)
	{
		new_value[row_n] = matrix->value[row_n];
		row_n += 1;
	}
	ft_memdel((void **)&matrix->value);
	matrix->row_len += 1;
	matrix->value = new_value;
	return (1);
}

int					matrix_addrow(t_matrix *matrix, char **raw)
{
	unsigned int	i;
	unsigned int	rawlen;
	int				*new_row;

	if (!matrix_extend(matrix))
		return (0);
	rawlen = raw_len(raw);
	if (!matrix->column_len)
		matrix->column_len = rawlen;
	if (!(new_row = (int *)ft_memalloc(matrix->column_len * sizeof(int))))
		return (0);
	i = 0;
	while (i < matrix->column_len && i < rawlen)
	{
		new_row[i] = ft_atoi(raw[i]);
		i += 1;
	}
	matrix->value[matrix->row_len - 1] = new_row;
	return (1);
}
