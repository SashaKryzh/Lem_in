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

// int		solution(t_room *room, t_room *src)
// {
// 	t_tube	*tubes;

// 	if (src->role == end)
// 		return (1);
// 	tubes = src->tubes;
// 	while (tubes)
// 	{

// 	}
// }

int		main(void)
{
	int		ants;
	t_room	*rooms;
	t_room	*src;

	ants = get_ants();
	rooms = get_rooms();

	print_rooms(rooms);
	//ft_printf("!!!!!!!!!!!\n\n");

	src = find_room_role(rooms, 1);
	//print_room_info(src);

	//solution(rooms, src);
	return (0);
}
