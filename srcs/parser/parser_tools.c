#include "lemin.h"

uint8_t			is_comment(t_lemin *lemin, char *line)
{
	if (line != NULL && *line != '#') 
		return (NO_COMMENT);
	else if (ft_strnequ(line, "##", 2) == FALSE)
	{
		if (ft_putendl(line + 1) == FAILURE)
			lemin->error = WRITE_ERR;
		return (COMMENT);
	}
	else if (ft_strequ(line, "##start") == TRUE)
		return (START_CMD);
	else if (ft_strequ(line, "##end") == TRUE)
		return (END_CMD);
	return (UNKNOW_CMD | COMMENT);
}
