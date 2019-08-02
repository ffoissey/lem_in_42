/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_routine.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 10:11:40 by ffoissey          #+#    #+#             */
/*   Updated: 2019/08/02 12:15:24 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		free_links_list(t_list *lst)
{
	if (lst == NULL)
		return ;
	free_links_list(lst->next);
	free(lst);
}

void	free_room(void *content)
{
	t_room *room;
	
	room = (t_room *)content;
	ft_strdel(&room->name);
	free_links_list(room->links);
}

static void	free_list(t_list *lst, void (*f)(void *))
{
	if (lst == NULL)
		return ;
	free_list(lst->next, f);
	if (f != NULL)
		f(lst->content);
	free(lst->content);
	free(lst);
}

static void	free_way_list(t_list *lst)
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

void		exit_routine(t_lemin *lemin)
{
	free_list(lemin->map, NULL);
	free_way_list(lemin->possible_way_list);
	free_list(lemin->main_list_room, free_room);
}
