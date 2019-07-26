/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_list_tool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpillot <tpillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 10:25:33 by tpillot           #+#    #+#             */
/*   Updated: 2019/07/26 10:25:39 by tpillot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int8_t		create_ants_list(t_lemin *lemin)
{
	size_t	id;
	t_ant	ant;
	t_list	*new;

	id = 1;
	while (id <= lemin->total_ants)
	{
		ant.position = lemin->start_room;
		ant.id = id;
		new = ft_lstnew(&ant, sizeof(t_ant));
		if (new == NULL)
			return (FAILURE);
		ft_lstadd_back(&(lemin->ants), new);
		id++;
	}
	return (SUCCESS);
}

void		free_ant(void *content)
{
	free(content);
}
