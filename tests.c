
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

	new = add_room(NULL, "2", none);
	new = add_room(new, "start", start);
	new = add_room(new, "end", end);
	return (new);
}

void	print_room_info(t_room room)
{
	ft_printf("name: %s, role: %d\n", room.name, room.role);
}
