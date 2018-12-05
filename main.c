/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okryzhan <okryzhan@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 12:12:22 by okryzhan          #+#    #+#             */
/*   Updated: 2018/12/03 12:12:22 by okryzhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	exit_func(int type, char *msg)
{
	ft_printf("%s\n", msg);
	exit(type);
}

void	print_path(t_room *rooms, int src, int dst, int *p)
{
	int v;

	v = dst;
	if (p[v] == -1)
	{
		ft_printf("No path :(\n");
		return ;
	}
	while (v != src)
	{
		ft_printf("%s <- ", find_room_index(rooms, v)->name);
		v = p[v];
	}
	ft_printf("%s\n", find_room_index(rooms, v)->name);
}

int		main(void)
{
	t_room	*rooms;
	int		ants;
	int		*p;
	int		src;

	ants = get_ants();
	rooms = get_rooms();

	//print_rooms(lst);
	//ft_printf("!!!!!!!!!!!\n\n");

	src = find_room_role(rooms, 1)->index;
	print_rooms(rooms);
	dijkstra(rooms, count_rooms(rooms), src, &p);
	print_path(rooms, src, find_room_role(rooms, 2)->index, p);
	return (0);
}
