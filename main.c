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

int	g_cnt_rooms;

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
	ft_printf("%s", find_room_index(rooms, v)->name);
}

void	print_moves(t_room **rooms, t_path *routs, int src)
{

}

int		main(void)
{
	t_room	*lst;
	t_room	**rooms;
	t_path	*routs;
	int		ants;
	int		src;
	int		dst;

	ants = get_ants();
	lst = get_rooms();
	rooms = lst_to_array(lst);
	g_cnt_rooms = count_rooms(*rooms);
	print_rooms(*rooms);
	
	src = find_room_role(*rooms, start)->index;
	dst = find_room_role(*rooms, end)->index;
	routs = find_routs(rooms, src, dst);
	print_routs(*rooms, routs, src, dst);

	print_moves(rooms, routs, src);
	return (0);
}
