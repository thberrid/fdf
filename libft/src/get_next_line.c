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

#include "libft.h"

# define BUFF_SIZEGNL 1

char		*ft_fill_line(char *s, char **line)
{
	char	*tmp;

	tmp = NULL;
	if ((tmp = ft_strchr(s, '\n')))
	{
		*tmp = 0;
		if (!(tmp = ft_strdup(tmp)))
			return (NULL);
		if (!(*line = ft_strdup(s)))
		{
			ft_strdel(&tmp);
			return (NULL);
		}
		ft_strdel(&s);
		s = tmp;
	}
	else
	{
		if (!(*line = ft_strdup(s)))
			return (NULL);
		ft_strclr(s);
	}
	return (s);
}

int			ft_returnfree(char *s, int ret)
{
	ft_strdel(&s);
	return (ret);
}

int			get_next_line(const int fd, char **line)
{
	static char	*s;
	char		buf[BUFF_SIZEGNL + 1];
	char		*tmp;
	int			ret;

	if (fd < 0 || line == NULL || read(fd, 0, 0) < 0)
		return (-1);
	if (s == NULL)
		if (!(s = ft_strnew(0)))
			return (-1);
	while ((ret = read(fd, buf, BUFF_SIZEGNL)))
	{
		buf[ret] = '\0';
		if (!(tmp = ft_strjoin(s, buf)))
			return (-1);
		ft_strdel(&s);
		s = tmp;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	if (ret <= 0 && !(*s))
		return (ft_returnfree(s, 0));
	if (!(s = ft_fill_line(s, line)))
		return (ft_returnfree(s, -1));
	return (1);
}