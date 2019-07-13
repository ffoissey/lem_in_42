
#include "lemin.h"

uint8_t		is_room_uniq(t_lemin *lemin, t_room *room, t_room *cur_room)
{
	if (cur_room == NULL || room == NULL)
		return (TRUE);
	if (ft_strequ(cur_room->name, room->name) == TRUE)
		lemin->error = ROOMS_ERR | SAME_NAME;
	else if (cur_room->coord.x == room->coord.x
			&& cur_room->coord.y == room->coord.y)
		lemin->error = ROOMS_ERR | SAME_COORD;
	else
		return (TRUE);
	return (FALSE);
}

int8_t		room_control(t_lemin *lemin, t_room *room)
{
	t_list		*run;

	run = lemin->main_list_room;
	while (run != NULL)
	{
		if (is_room_uniq(lemin, room, (t_room *)run->content) == FALSE)
			return (FAILURE);
		run = run->next;
	}
	return (SUCCESS);
}

int8_t		get_start_and_end(t_lemin *lemin, t_room *room, uint8_t cmd)
{
	if (cmd == START_CMD)
	{
		if (lemin->start_room != NULL)
		{
			lemin->error = ROOMS_ERR | START_ROOM;
			return (FAILURE);
		}
		lemin->start_room = room;
	}
	else if (cmd == END_CMD)
	{
		if (lemin->end_room != NULL)
		{
			lemin->error = ROOMS_ERR | END_ROOM;
			return (FAILURE);
		}
		lemin->end_room = room;
	}
	return (SUCCESS);
}

/////////// Hashmap maybe ? 

int8_t		create_room_node(t_lemin *lemin, t_room *room, uint8_t cmd)
{
	t_list	*new_node;

	if (cmd == END_CMD)
		ft_printf("END\n");
	if (cmd == START_CMD)
		ft_printf("START\n");
	if (room_control(lemin, room) == FAILURE)
		return (FAILURE);
	new_node = ft_lstnew(room, sizeof(t_room));
	if (new_node == NULL)
	{
		lemin->error = MALLOC_ERR;
		return (FAILURE);
	}
	ft_lstadd(&lemin->main_list_room, new_node);
	if (get_start_and_end(lemin, (t_room *)new_node->content, cmd) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
