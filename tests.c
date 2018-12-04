
#include "lem_in.h"

t_tube	*t_init(t_room *path)
{
	t_tube	*tmp;

	tmp = (t_tube *)malloc(sizeof(t_tube));
	tmp->path = path;
	tmp->next = NULL;
	return (tmp);
}

t_room	*test_init(void)
{
	t_room	*new;

	new = add_room(NULL, "2", 0);
	new = add_room(new, "start", 1);
	new = add_room(new, "end", 2);
	new = add_room(new, "3", 0);

	add_connection(new, "start", "2");
	add_connection(new, "start", "end");
	add_connection(new, "start", "3");
	add_connection(new, "3", "2");
	add_connection(new, "2", "end");
	return (new);
}

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
