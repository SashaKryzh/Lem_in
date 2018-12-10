
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
	
	ft_printf("--- %s (used: %d) (index: %d) (ants: %d)---\n", room->name, room->used, room->index, room->ant);
	tmp = room->tubes;
	while (tmp)
	{
		ft_printf("path to: %s\n", tmp->path->name);
		tmp = tmp->next;
	}
	ft_printf("\n");
}

void	print_path(t_path *routs)
{
	int i;

	i = 0;
	while (routs->route[i + 1])
	{
		ft_printf("%s -> ", routs->route[i]->name);
		i++;
	}
	ft_printf("%s (%d) (sel: %d)", routs->route[i]->name, routs->len, routs->selected);
}

void	print_routs(t_path *routs)
{
	int i = 0;

	while (routs)
	{
		print_path(routs);
		ft_printf("\n");
		routs = routs->next;
		i++;
	}
	ft_printf("count: %d\n", i);
}
