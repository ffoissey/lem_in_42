#include "lemin.h"

int8_t		mark_way(t_list *lst, uint8_t mark)
{
	t_room *room;
	t_list	*head;

	head = lst;
	while (lst != NULL && lst->next != NULL)
	{
		room = (t_room *)lst->content;
		if (mark == UNMARK)
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

size_t		get_nb_max_ways(t_lemin *lemin)
{
	if (lemin->start_room->nb_links > lemin->end_room->nb_links)
		return (lemin->end_room->nb_links);
	return (lemin->start_room->nb_links);
}
