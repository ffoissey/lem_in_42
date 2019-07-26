/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_division.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpillot <tpillot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 10:25:55 by tpillot           #+#    #+#             */
/*   Updated: 2019/07/26 10:47:13 by ffoissey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static void		put_rest(t_list *ways_list, int rest)
{
	t_list	*first_way;
	t_way	*cur_way;

	first_way = ways_list;
	while (rest != 0)
	{
		if (ways_list != NULL)
		{
			cur_way = (t_way *)ways_list->content;
			cur_way->ants++;
			rest--;
			ways_list = ways_list->next;
			if (ways_list == NULL)
				ways_list = first_way;
		}
	}
}

void			ants_divison(t_lemin *lemin)
{
	t_list	*ways_list;
	t_way	*cur_way;
	int		total_ants;
	int		nb;

	ways_list = lemin->way_list;
	total_ants = lemin->total_ants;
	while (ways_list != NULL && lemin->total_ants != 0)
	{
		cur_way = (t_way *)ways_list->content;
		nb = (int)lemin->size - (int)cur_way->size;
		if (nb == 0)
			nb = 1;
		if (total_ants - nb < 0)
			nb = total_ants;
		cur_way->ants = (size_t)nb;
		total_ants -= (int)cur_way->ants;
		ways_list = ways_list->next;
	}
	if (total_ants != 0)
		put_rest(lemin->way_list, total_ants);
}
