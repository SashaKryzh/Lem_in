/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 10:54:53 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/17 10:54:54 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		good(t_route *routes, t_route *current, int ant_start)
{
	int		sum;

	sum = 0;
	while (routes != current)
	{
		sum += current->len - routes->len;
		routes = routes->next;
	}
	if (ant_start > sum)
		return (1);
	return (0);
}

void	print(t_route *first_route, t_route *routes, t_room **rooms, int i)
{
	static int cnt;

	if (ROOM[i - 1]->role == start
		&& good(first_route, routes, rooms[g_src]->ant))
	{
		ROOM[i - 1]->ant -= 1;
		ROOM[i]->ant += 1;
		ROOM[i]->ant_index = ++cnt;
		ft_printf("L%d-%s ", ROOM[i]->ant_index, ROOM[i]->name);
	}
	else if (ROOM[i - 1]->role != start)
	{
		ROOM[i - 1]->ant -= 1;
		ROOM[i]->ant += 1;
		ROOM[i]->ant_index = ROOM[i - 1]->ant_index;
		ft_printf("L%d-%s ", ROOM[i]->ant_index, ROOM[i]->name);
	}
	if (ROOM[i]->role == dead)
	{
		ROOM[i]->ant = 0;
		g_cnt_dead += 1;
	}
}

int		move(t_room **rooms, t_route *first_route)
{
	t_route *routes;
	int		cnt;
	int		i;

	cnt = 0;
	rooms[g_src]->ant = g_ants;
	while (rooms[g_dst]->ant < g_ants - g_cnt_dead)
	{
		routes = first_route;
		while (routes)
		{
			i = routes->len;
			while (i > 0)
			{
				if (ROOM[i - 1]->ant)
					print(first_route, routes, rooms, i);
				i--;
			}
			routes = routes->next;
		}
		ft_printf("\n");
		cnt++;
	}
	return (cnt);
}

void	short_print(t_route *first_route, int i)
{
	static int cnt;

	if (first_route->route[i - 1]->role == start)
	{
		first_route->route[i - 1]->ant -= 1;
		first_route->route[i]->ant += 1;
		first_route->route[i]->ant_index = ++cnt;
		ft_printf("L%d-%s ", first_route->route[i]->ant_index,
			first_route->route[i]->name);
	}
	else if (first_route->route[i - 1]->role != start)
	{
		first_route->route[i - 1]->ant -= 1;
		first_route->route[i]->ant += 1;
		first_route->route[i]->ant_index = first_route->route[i - 1]->ant_index;
		ft_printf("L%d-%s ", first_route->route[i]->ant_index,
			first_route->route[i]->name);
	}
	if (first_route->route[i]->role == dead)
	{
		first_route->route[i]->ant = 0;
		g_cnt_dead += 1;
	}
}

int		short_move(t_room **rooms, t_route *first_route)
{
	int		cnt;
	int		i;

	cnt = 0;
	rooms[g_src]->ant = g_ants;
	while (rooms[g_dst]->ant < g_ants - g_cnt_dead)
	{
		i = first_route->len;
		while (i > 0)
		{
			if (first_route->route[i - 1]->ant)
				short_print(first_route, i);
			i--;
		}
		ft_printf("\n");
		cnt++;
	}
	return (cnt);
}
