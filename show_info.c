/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 11:34:08 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/13 11:34:09 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	show_rooms(t_room **rooms)
{
	t_tube	*tmp;
	int		cnt;
	int		i;

	ft_printf("\033[0;32m------ ROOMS: %d ------\033[0m\n\n", g_cnt_rooms);
	i = -1;
	while (rooms[++i])
	{
		if (rooms[i]->role == start || rooms[i]->role == end)
			ft_printf("\x1b[33m===== %s =====\033[0m\n", rooms[i]->name);
		else if (rooms[i]->role == dead)
			ft_printf("\x1b[31m===== %s =====\033[0m\n", rooms[i]->name);
		else
			ft_printf("\x1b[32m===== %s =====\033[0m\n", rooms[i]->name);
		tmp = rooms[i]->tubes;
		cnt = 0;
		while (tmp)
		{
			ft_printf("\x1b[35m %s -> %s\033[0m\n",
				rooms[i]->name, tmp->path->name);
			tmp = tmp->next;
			cnt += 1;
		}
		ft_printf("\x1b[34m count: %d\033[0m\n\n", cnt);
	}
}

void	show_routes(t_route *routes)
{
	int cnt;
	int i;

	ft_printf("\033[0;32m------ ROUTES ------\033[0m\n\n");
	cnt = 0;
	while (routes)
	{
		i = 0;
		while (routes->route[i + 1])
		{
			ft_printf("\x1b[35m%s -> ", routes->route[i]->name);
			i++;
		}
		ft_printf("%s\033[0m \x1b[34m(len: %d)\033[0m\n",
			routes->route[i]->name, routes->len);
		routes = routes->next;
		cnt += 1;
	}
	ft_printf("\x1b[34mcount: %d\033[0m\n\n", cnt);
}

void	show_info(t_room **rooms, t_route *routes)
{
	if (g_flag != 1)
		return ;
	ft_printf("\033[0;32m=======================  INFO");
	ft_printf("  =============================\033[0m\n\n");
	show_rooms(rooms);
	show_routes(routes);
	ft_printf("\033[0;32m==============================");
	ft_printf("===============================\033[0m\n\n");
}
