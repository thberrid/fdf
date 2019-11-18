/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 03:48:01 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/18 05:57:36 by thberrid         ###   ########.fr       */
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

int					map_parse(t_matrix *matrix, char *path)
{
	int		fd;
	int		retrn;
	char	*line;
	char	**raw;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (0);
	line = NULL;
	ft_bzero(matrix, sizeof(t_matrix));
	while ((retrn = get_next_line(fd, &line)))
	{
		if (retrn < 0 || !(raw = ft_strsplitspaces(line)))
			return (0);
		if (raw_len(raw))
			if (!matrix_addrow(matrix, raw))
				return (0);
		ft_strdel(&line);
		raw_free(raw);
	}
	matrix_print(matrix);
	return (1);
}
