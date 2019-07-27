/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_links.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 10:26:00 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/27 13:09:57 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_room	*get_room_adress(t_list *run, char *room_name)
{
	t_room	*cur_room;

	while (run != NULL)
	{
		cur_room = (t_room *)run->content;
		if (ft_strequ(room_name, cur_room->name) == TRUE)
			return (cur_room);
		run = run->next;
	}
	return (NULL);
}

static int8_t	room_linker(t_lemin *lemin, t_room *room1, t_room *room2)
{
	t_list	*node_room1;
	t_list	*node_room2;

	node_room1 = ft_lstnew_nomalloc(room1, sizeof(t_room *));
	node_room2 = ft_lstnew_nomalloc(room2, sizeof(t_room *));
	if (node_room1 == NULL || node_room2 == NULL)
	{
		free(node_room1);
		free(node_room2);
		lemin->error = MALLOC_ERR;
		return (FAILURE);
	}
	ft_lstadd(&room1->links, node_room2);
	ft_lstadd(&room2->links, node_room1);
	room1->nb_links++;
	room2->nb_links++;
	return (SUCCESS);
}

static int8_t	do_links(t_lemin *lemin, char *room_name1, char *room_name2)
{
	t_room	*room1;
	t_room	*room2;

	room1 = get_room_adress(lemin->main_list_room, room_name1);
	room2 = get_room_adress(lemin->main_list_room, room_name2);
	if (room1 == NULL || room2 == NULL)
	{
		lemin->error = LINKS_ERR | UNKNOW_ROOM;
		return (FAILURE);
	}
	return (room_linker(lemin, room1, room2));
}

int8_t			get_links(t_lemin *lemin, char *line)
{
	char	*room_name1;
	char	*room_name2;
	char	*hyphen;

	if (is_comment(line) & COMMENT)
		return (SUCCESS);
	if (line == NULL || *line == '\0'
			|| (hyphen = ft_strchr(line, '-')) == NULL)
	{
		lemin->error = LINKS_ERR | BAD_FORMAT;
		return (FAILURE);
	}
	room_name1 = ft_strcdup(line, '-');
	room_name2 = ft_strdup(hyphen + 1);
	if (room_name1 == NULL || room_name2 == NULL)
		lemin->error = MALLOC_ERR;
	else
		do_links(lemin, room_name1, room_name2);
	ft_strdel(&room_name1);
	ft_strdel(&room_name2);
	lemin->links_validation = TRUE;
	return (lemin->error ? FAILURE : SUCCESS);
}
