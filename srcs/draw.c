/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 06:31:16 by thberrid          #+#    #+#             */
/*   Updated: 2019/12/07 06:51:54 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int		draw_obj(t_window *w)
{
	t_img				next_img;

	ft_bzero(&next_img, sizeof(next_img));
	next_img.id = mlx_new_image(w->mlx, w->width, w->height);
	next_img.data = mlx_get_data_addr(next_img.id, &next_img.bits_px,\
		&next_img.size_line, &next_img.endian);
	next_img.height = w->height;
	next_img.width = w->width;
	foreach_edges_draw(&next_img, w);
	if (w->img.id)
		mlx_destroy_image(w->mlx, w->img.id);
	w->img = next_img;
	mlx_clear_window(w->mlx, w->ptr);
	mlx_put_image_to_window(w->mlx, w->ptr, w->img.id, 0, 0);
	return (0);
}

void	draw_line(t_pixel *start, t_pixel *end, t_img *img)
{
	unsigned int	delta_fast;
	float			error;
	unsigned int	i;
	t_pixel			pen;

	if (!end)
		return ;
	ft_bzero(&pen, sizeof(t_pixel));
	delta_fast = bresen_set_deltafast(start, end);
	pen.x = start->x;
	pen.y = start->y;
	pen.color = start->color;
	bresen_init_stepcolor(delta_fast, &pen, start, end);
	error = delta_fast / 2;
	i = 0;
	while (i < delta_fast)
	{
		if (pen.x >= 0 && pen.y >= 0 && pen.x < img->width
			&& pen.y < img->height)
			ft_memcpy(&(img->data[(pen.x * img->bits_px / 8)\
				+ (pen.y * img->size_line)]), &pen.color, img->bits_px / 8);
		error = bresen_update_error(error, start, end, &pen);
		bresen_update_color(&pen, start, end, delta_fast);
		i += 1;
	}
}

void	draw_edges(t_img *img, t_matrix *pixels, unsigned int x, unsigned int y)
{
	t_pixel		*start;
	t_pixel		*end;

	start = &((t_pixel *)pixels->value[y])[x];
	end = NULL;
	if (x + 1 != pixels->column_len)
		end = &((t_pixel *)pixels->value[y])[x + 1];
	draw_line(start, end, img);
	end = NULL;
	if (y + 1 != pixels->row_len)
		end = &((t_pixel *)pixels->value[y + 1])[x];
	draw_line(start, end, img);
}

void	foreach_edges_draw(t_img *img, t_window *w)
{
	unsigned int		x;
	unsigned int		y;

	y = 0;
	while (y < w->px_coord.row_len)
	{
		x = 0;
		while (x < w->px_coord.column_len)
		{
			draw_edges(img, &w->px_coord, x, y);
			x += 1;
		}
		y += 1;
	}
}
