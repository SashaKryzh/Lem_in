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

void	solution(t_room *room, t_room *src)
{
	room = NULL;
	src = NULL;
	ft_printf("tyt");
}

int		main(void)
{
	int		ants;
	t_room	*rooms;
	t_room	*src;

	ants = get_ants();
	rooms = get_rooms();

	print_rooms(rooms);
	ft_printf("!!!!!!!!!!!\n\n");

	src = find_room_role(rooms, 1);
	print_room_info(src);

	solution(rooms, src);
	return (0);
}