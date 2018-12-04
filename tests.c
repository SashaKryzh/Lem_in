
#include "lem_in.h"

void	print_rooms(t_room *room)
{
	while (room)
	{
		print_room_info(room);
		room = room->next;
	}
}

void	print_room_info(t_room *room)
{
	t_tube	*tmp;
	
	ft_printf("--- %s (%d) ---\n", room->name, room->role);
	tmp = room->tubes;
	while (tmp)
	{
		ft_printf("path to: %s\n", tmp->path->name);
		tmp = tmp->next;
	}
	ft_printf("\n");
}
