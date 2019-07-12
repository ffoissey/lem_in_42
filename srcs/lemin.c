/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffoissey <ffoisssey@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 17:50:47 by ffoissey          #+#    #+#             */
/*   Updated: 2019/07/12 11:58:53 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static uint8_t		is_completed(t_lemin *lemin)
{
	t_room *end_room;

	if (lemin->end_room == NULL)
		return (TRUE);
	end_room = (t_room *)lemin->end_room->content;
	if (end_room == NULL)
		return (TRUE);
	else if (end_room->ants == lemin->total_ants)
		return (TRUE);
	return (FALSE);
}

int					main(void)
{
	t_lemin lemin;
	char	*result;

	ft_bzero(&lemin, sizeof(lemin));
	if (parser(&lemin) == FAILURE)
		return (EXIT_FAILURE);
	//else if (pre_process(&lemin) == FAILURE)
	//	return (EXIT_FAILURE);
	result = NULL;
	while (is_completed(&lemin) == FALSE)
	{
	//	result = process(lemin->start_room, lemin->turn);
		ft_putendl(result);
		ft_strdel(&result);
		lemin.turn++;
	}
	return (EXIT_SUCCESS);
}
