/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 07:56:05 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/19 07:56:11 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void				matrix_free(t_matrix *matrix)
{
	unsigned int	i;

	i = 0;
	while (i < matrix->row_len)
	{
		ft_memdel((void **)&matrix->value[i]);
		i += 1;
	}
	ft_memdel((void **)matrix);
}
