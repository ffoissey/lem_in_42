/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 17:50:47 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/16 20:17:03 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static uint8_t		is_completed(t_lemin *lemin)
{
	if (lemin->end_room == NULL)
		return (FALSE);
	if (lemin->end_room->ants == lemin->total_ants)
		return (TRUE);
	return (FALSE);
}

int					main(void)
{
	t_lemin lemin;
	char	*result;

	ft_bzero(&lemin, sizeof(lemin));
	if (parser(&lemin) == FAILURE)
	{
		print_error(lemin.error);
		exit_routine(&lemin);
		return (EXIT_FAILURE);
	}
	lemin.nb_max_ways = get_nb_max_ways(&lemin);
	set_distance_from_start(lemin.start_room, &lemin, 0);
	set_distance_from_end(lemin.end_room, &lemin, 0);
//	print_graph(&lemin);	/// GRAPH DEBUG
	graph_course(&lemin);
	ways_selection(&lemin); // WAYS SELECTION
	print_list_ways(&lemin); /// POSSIBLE WAY LIST DEBUG
	return (EXIT_SUCCESS);
	result = NULL;
	while (is_completed(&lemin) == FALSE)
	{
		//result = process(lemin->start_room, lemin->turn);
		ft_putendl(result);
		ft_strdel(&result);
	}
	exit_routine(&lemin);
	return (EXIT_SUCCESS);
}
