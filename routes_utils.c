/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routs_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 09:19:03 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/11 09:19:03 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	mark_rout(t_room **rooms, int *p, int src, int dst)
{
	int v;

	v = p[dst];
	while (v != src)
	{
		rooms[v]->used = 1;
		v = p[v];
	}
}

void	mark_rout2(t_route *routes)
{
	int i;

	i = 1;
	while (routes->route[i + 1])
	{
		routes->route[i]->used = 1;
		i++;
	}
}

void	unmark_routs(t_room *rooms)
{
	while (rooms)
	{
		rooms->used = 0;
		rooms = rooms->next;
	}
}

void	unmark_rout(t_route	*route)
{
	int i;

	i = 0;
	while (route->route[i])
	{
		route->route[i]->used = 0;
		i++;
	}
}
