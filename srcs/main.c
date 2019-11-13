/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thberrid <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 03:20:17 by thberrid          #+#    #+#             */
/*   Updated: 2019/11/13 08:46:24 by thberrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <fdf.h>

int 	go(t_engine *engine)
{
	mlx_pixel_put(engine->mlx, engine->window, engine->dot.x, engine->dot.x, 42949672);
	return (0);
}

int		k(int keycode, t_engine *engine)
{
	while (engine->dot.color != keycode * 10050 && engine->dot.x != keycode * 100 && engine->dot.y != keycode * 50)
	{
		if (engine->dot.color != keycode * 10050)
		{
			if (engine->dot.color < keycode * 10050)
				engine->dot.color += 100;
			else
				engine->dot.color -= 100;

		}
		if (engine->dot.x != keycode * 100)
		{
			if (engine->dot.x < keycode * 100)
				engine->dot.x += 1;
			else
				engine->dot.x -= 1;
		}
		if (engine->dot.y != keycode * 50)
		{
			if (engine->dot.y < keycode * 50)
				engine->dot.y += 1;
			else
				engine->dot.y -= 1;
		}
		mlx_pixel_put(engine->mlx, engine->window, engine->dot.x, engine->dot.y, engine->dot.color);
	}
	return (0);
}

int		main(void)
{
	t_engine	engine;

	ft_bzero(&engine, sizeof(t_engine));
	engine.dot.x = 100;
	engine.dot.y = 500;
	engine.mlx = mlx_init();
	engine.window = mlx_new_window(engine.mlx, 750, 750, "LOOL");
	mlx_pixel_put(engine.mlx, engine.window, engine.dot.x, engine.dot.y, 42949672);

	mlx_key_hook(engine.window, &k, &engine);

	mlx_loop(engine.mlx);
	return (0);
}
