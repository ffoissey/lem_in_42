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
	t_room *room;

	romm = (t_room *)lemin->end_room->data;
	if (room != NULL && room->ants == lemin->total_ants)
		return (TRUE);
	return (FALSE);
}

int					main(void)
{
	t_lemin lemin;
	char	*result;

	ft_bzero(&lemin, sizeof(lemin));
	/////////////PARSING
	result = NULL;
	while (is_completed(lemin) == FALSE)
	{
		result = process(lemin->start_room, lemin->turn);
		ft_putendl(result);
		ft_strdel(&result);
	}
	return (EXIT_SUCCESS);
}
