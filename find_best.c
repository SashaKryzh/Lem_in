/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_best.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 18:55:55 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/10 18:55:55 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		is_rout_free(t_path *route)
{
	int i;

	i = 1;
	while (route->route[i + 1])
	{
		if (route->route[i]->used)
			return (0);
		i++;
	}
	return (1);
}

void	mark_best_rout(t_path *routes)
{
	while (routes)
	{
		routes->best_rout = 0;
		if (routes->selected)
			routes->best_rout = 1;
		routes->selected = 0;
		routes = routes->next;
	}
}

void	unselect_rout(t_path *routes)
{
	while (routes)
	{
		routes->selected = 0;
		routes = routes->next;
	}
}

int		cnt_moves(t_room **rooms, t_path *first_routes)
{
	t_path	*routes;
	int		moved;
	int		cnt;
	int		i;

	cnt = 0;
	rooms[g_src]->ant = g_ants;
	rooms[g_dst]->ant = 0;
	while (rooms[g_dst]->ant != g_ants)
	{
		moved = 0;
		routes = first_routes;
		while (routes)
		{
			if (routes->selected)
			{
				i = routes->len;
				while (i > 0)
				{
					if (routes->route[i - 1]->ant)
					{
						routes->route[i - 1]->ant -= 1;
						routes->route[i]->ant += 1;
						moved = 1;
					}
					i--;
				}
			}
			routes = routes->next;
		}
		cnt += moved;
	}
	return (cnt);
}

void	find_best(t_room **rooms, t_path *first_route)
{
	t_path	*routes;
	t_path	*tmp;
	int		best_moves;
	int		moves1;
	int		moves2;

	best_moves = INF;
	ft_printf("ants: %d\n", g_ants); //

	routes = first_route;
	while (routes)
	{
		routes->selected = 1;
		moves1 = cnt_moves(rooms, first_route);
		mark_rout2(routes);
		tmp = first_route;
		while (tmp && tmp->len <= g_ants)
		{
			if (is_rout_free(tmp))
			{
				tmp->selected = 1;
				moves2 = cnt_moves(rooms, first_route);
				mark_rout2(tmp);
				if (moves2 < moves1)
				{
					moves1 = moves2;
				} else {
					tmp->selected = 0;
					unmark_rout2(tmp);
				}
			}
			tmp = tmp->next;
		}
		if (moves1 < best_moves)
		{
			best_moves = moves1;
			mark_best_rout(first_route);
		}
		unselect_rout(first_route);
		unmark_rout(*rooms);
		routes = routes->next;
	}
	ft_printf("best: %d\n\n", best_moves); //
}
