/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 17:50:47 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/10 19:01:09 by ffoissey         ###   ########.fr       */
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
	/////////////PARSING
	if (parser(&lemin) == FAILURE)
	{
		print_error(lemin.error);
		exit_routine(&lemin);
		return (EXIT_FAILURE);
	}
	print_graph(&lemin); /// DEBUG
	//return (EXIT_SUCCESS);
	ft_printf("starting graph_course...\n");
	graph_course(lemin.end_room, &lemin);
	ft_printf("count: %zu\n", lemin.nb_ways);
	return (EXIT_SUCCESS);
	ways_selection(&lemin); // WAYS SELECTION
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
