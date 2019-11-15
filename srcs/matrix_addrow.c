/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_addrow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 07:42:57 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/15 08:13:42 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	matrix_free(t_matrix *matrix)
{
	unsigned int	i;

	i = 0;
	while (i < matrix->row_len)
	{
		ft_memdel((void **)&matrix);
		i += 1;
	}
}

void	matrix_print(t_matrix *matrix)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < matrix->row_len)
	{
		j = 0;
		while (j < matrix->column_len)
		{
			ft_putnbr(matrix->value[i][j]);
			ft_putchar(' ');
			j += 1;
		}
		ft_putchar('\n');
		i += 1;
	}
}

int		matrix_extend(t_matrix *matrix)
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

int		matrix_addrow(t_matrix *matrix, char **raw)
{
	unsigned int	i;
	int				*new_row;

	if (!matrix_extend(matrix))
		return (0);
	if (!matrix->column_len)
		matrix->column_len = raw_len(raw);
	if (!(new_row = (int *)ft_memalloc(raw_len(raw) * sizeof(int))))
		return (0);
	matrix->value[matrix->row_len - 1] = new_row;
	i = 0;
	while (i < matrix->column_len)
	{
		matrix->value[matrix->row_len - 1][i] = ft_atoi(raw[i]);
		i += 1;
	}
	return (1);
}
