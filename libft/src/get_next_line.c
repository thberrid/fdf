/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:42:02 by thberrid          #+#    #+#             */
/*   Updated: 2019/05/31 23:16:30 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <get_next_line.h>

static int	push_line(char **line, int *line_len, t_buf *buffer)
{
	char	*endl_pos;
	int		rest_len;

	rest_len = buffer->len;
	endl_pos = ft_memchr(buffer->arr, '\n', rest_len);
	if (endl_pos)
		rest_len = endl_pos - buffer->arr;
	*line = ft_memrealloc(*line, *line_len, *line_len + rest_len + 1);
	if (!*line)
		return (FT_ERROR);
	ft_memmove(*line + *line_len, buffer->arr, rest_len);
	*line_len += rest_len;
	return (1);
}

static int	pop_buffer(t_buf *buffer)
{
	char	*endl_pos;
	size_t	blank_len;

	endl_pos = ft_memchr(buffer->arr, '\n', buffer->len);
	if (!endl_pos)
	{
		ft_bzero(buffer->arr, BUFF_SIZE);
		buffer->len = 0;
		return (0);
	}
	blank_len = endl_pos - buffer->arr + 1;
	buffer->len = BUFF_SIZE - blank_len;
	ft_memmove(buffer->arr, endl_pos + 1, buffer->len);
	ft_bzero(buffer->arr + buffer->len, blank_len);
	return (1);
}

static int	transfer_toline(char **line, int *line_len, t_buf *buffer)
{
	if (!buffer->len)
		return (0);
	if (push_line(line, line_len, buffer) < 0)
		return (FT_ERROR);
	if (pop_buffer(buffer))
		return (1);
	return (0);
}

static int	read_fd(const int fd, char **line, int line_len)
{
	static t_buf	buffer = { .len = 0 };
	int				new_line;
	int				read_bytes;

	new_line = transfer_toline(line, &line_len, &buffer);
	if (new_line == FT_ERROR)
		return (FT_ERROR);
	if (new_line)
		return (1);
	read_bytes = read(fd, buffer.arr, BUFF_SIZE);
	if (read_bytes == FT_ERROR)
		return (FT_ERROR);
	if (read_bytes < BUFF_SIZE)
		return ((read_bytes > 0));
	return (read_fd(fd, line, line_len));
}

int			get_next_line(const int fd, char **line)
{
	if (fd < 1 || !line)
		return (FT_ERROR);	
	ft_strdel(line);
	return (read_fd(fd, line, 0));
}
