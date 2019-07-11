#include "lemin.h"

static uint8_t	is_correct_ants_format(char *line)
{
	if (line == NULL || *line == '\0')
		return (FALSE);
	else if (ft_str_is_numeric(line) == FALSE)
		return (FALSE);
	return (TRUE);
}

int8_t			get_ants(t_lemin *lemin, char *line)
{
	if (is_comment(line) & COMMENT)
		return (SUCCESS);
	if (is_correct_ants_format(line) == FALSE)
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
