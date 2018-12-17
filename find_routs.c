/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_routs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 08:49:49 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/07 08:49:49 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_route		*create_route(int *p, int len, int src)
{
	t_route	*new;
	int		i;

	new = (t_route *)malloc(sizeof(t_route));
	ft_bzero(new, sizeof(t_route));
	new->p = (int *)malloc(sizeof(int) * (g_cnt_rooms));
	i = -1;
	while (++i < g_cnt_rooms)
		new->p[i] = p[i];
	new->src = src;
	new->len = len;
	return (new);
}

t_route		*add_rout(t_route *routs, int *p, int len, int src)
{
	t_route	*tmp;
	t_route	*new;

	new = create_route(p, len, src);
	if (!routs)
		routs = new;
	else
	{
		tmp = routs;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (routs);
}

t_route		*find_routs(t_room **rooms)
{
	t_route	*routs;
	int		p[g_cnt_rooms];
	int		dist;

	routs = NULL;
	while (1)
	{
		dist = bfs(rooms, p, g_src, NULL);
		if (p[g_dst] == -1)
			break ;
		mark_route_p(rooms, p, g_src, g_dst);
		routs = add_rout(routs, p, dist, g_src);
		if (p[g_dst] == g_src)
			break ;
	}
	lst_sort(routs);
	return (convert_routs(rooms, routs));
}
