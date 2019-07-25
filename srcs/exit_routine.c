#include "lemin.h"

void	free_links_list(t_list *lst)
{
	if (lst == NULL)
		return ;
	free_links_list(lst->next);
	free(lst);
}

void	free_room(t_room *room)
{
	ft_strdel(&room->name);
	free_links_list(room->links);
	free(room);
}

void	free_main_list_room(t_list *lst)
{
	if (lst == NULL)
		return ;
	free_main_list_room(lst->next);
	free_room((t_room *)lst->content);
	free(lst);
}


void	free_way_list(t_list *lst)
{
	if (lst != NULL)
	{
		free_way_list(lst->next);
		free_links_list(((t_way *)(lst->content))->list);
		free_links_list(((t_way *)(lst->content))->link);
		((t_way *)(lst->content))->list = NULL;
		((t_way *)(lst->content))->link = NULL;
		free(lst->content);
		lst->content = NULL;
		free(lst);
		lst = NULL;
	}
}

void	exit_routine(t_lemin *lemin)
{
	free_way_list(lemin->possible_way_list);
	free_main_list_room(lemin->main_list_room);
}
