/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 03:48:01 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/19 10:02:19 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#include <fcntl.h>

static void			raw_free(char **raw)
{
	int		i;

	i = 0;
	while (raw[i])
	{
		ft_memdel((void **)&raw[i]);
		i += 1;
	}
	ft_memdel((void **)&raw);
}

unsigned int		raw_len(char **raw)
{
	unsigned int	i;

	i = 0;
	while (raw[i])
		i += 1;
	return (i);
}

static unsigned int	get_padding(t_matrix *matrix)
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
			padding = ft_intlen((int)(((t_vertex *)matrix->value[i])[j].z));
			if (padding > padding_biggest)
				padding_biggest = padding;
			j += 1;
		}
		i += 1;
	}
	return (padding_biggest + 1);
}

void				map_print(t_matrix *matrix)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	intlen;

	i = 0;
	matrix->padding = get_padding(matrix);
	while (i < matrix->row_len)
	{
		j = 0;
		while (j < matrix->column_len)
		{
			ft_putnbr((int)(((t_vertex *)matrix->value[i])[j]).z);
			intlen = matrix->padding;
			intlen -= ft_intlen((int)(((t_vertex *)matrix->value[i])[j].z));
			while (intlen < 5 && intlen)
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

/*
**	CONVERT FILE INTO MATRIX OF VERTICES
*/

int					map_parse(t_matrix *vertices, char *path)
{
	int				fd;
	int				retrn;
	char			*line;
	char			**raw;
	unsigned int	line_n;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (0);
	line = NULL;
	line_n = 0;
	ft_bzero(vertices, sizeof(t_matrix));
	vertices->type = VERTEX;
	while ((retrn = get_next_line(fd, &line)))
	{
		if (retrn < 0 || !(raw = ft_strsplitspaces(line)))
			return (0);
		if (raw_len(raw))
			if (!matrix_addrow(vertices, raw, (float)line_n, &row_setvertex))
				return (0);
		ft_strdel(&line);
		raw_free(raw);
		line_n += 1;
	}
	map_print(vertices);
	return (1);
}
