#include "lemin.h"

int8_t		mark_way(t_list *lst, uint8_t mark)
{
	t_room *room;

	while (lst != NULL)
	{
		room = (t_room *)lst->content;
		if (room == NULL)
			continue ;
		else if (mark == UNMARK)
				room->mark = UNMARK;
		else if (mark == MARK)
		{
			if (room->mark == MARK)
				return (FAILURE);
			room->mark = MARK;
		}
		lst = lst->next;
	}
	return (SUCCESS);
}
