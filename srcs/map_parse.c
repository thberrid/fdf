/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 03:48:01 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/20 07:56:32 by thberrid         ###   ########.fr       */
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

static float		get_min(float value, float new_value)
{
	if (new_value < value)
		return (new_value);
	return (value);
}

static void			map_center(t_matrix *vertices)
{
	t_vertex	vector;

	vector.x = vertices->column_len / 2;
	vector.y = matrix_get(vertices, 0, &get_min);
	vector.z = vertices->row_len + 1;
	matrix_set(vertices, &vector, &vertex_decrement);
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
			if (!matrix_addrow(vertices, raw, (float)line_n))
				return (0);
		ft_strdel(&line);
		raw_free(raw);
		line_n += 1;
	}
	map_center(vertices);
	return (1);
}
