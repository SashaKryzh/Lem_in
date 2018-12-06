
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
	
	ft_printf("--- %s (used: %d) (index: %d)---\n", room->name, room->used, room->index);
	tmp = room->tubes;
	while (tmp)
	{
		ft_printf("path to: %s\n", tmp->path->name);
		tmp = tmp->next;
	}
	ft_printf("\n");
}

void	print_routs(t_room *rooms, t_path *routs, int src, int dst)
{
	int i = 0;

	while (routs)
	{
		print_path(rooms, routs->src, dst, routs->p);
		// ft_printf(" <- %s (%d)\n", find_room_index(rooms, src)->name, routs->len);
		ft_printf("\n");
		routs = routs->next;
		i++;
	}
	ft_printf("count: %d\n", i);
}
