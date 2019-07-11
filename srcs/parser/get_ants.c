#include "lemin.h"

int8_t			get_ants(t_lemin *lemin, char *line)
{
	if (is_comment(lemin, line) & COMMENT)
		return (SUCCESS);
	if (is_correct_numeric_format(line) == FALSE)
	{
		lemin->error = ANTS_ERR | BAD_FORMAT;
		return (FAILURE);
	}
	lemin->total_ants = ft_atol(line);
	if (lemin->total_ants <= 0) 
		lemin->error = ANTS_ERR | NO_ANT;
	else if (lemin->total_ants > INT_MAX || ft_strlen(line) > 10) 
		lemin->error = ANTS_ERR | TOO_MANY_ANTS;
	else
	{
		lemin->state = GET_ROOMS;
		return (SUCCESS);
	}
	return (FAILURE);
}
