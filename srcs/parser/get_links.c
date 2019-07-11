#include "lemin.h"

int8_t		get_links(t_lemin *lemin, char *line)
{
	if (is_comment(lemin, line) & COMMENT)
		return (SUCCESS);
	return (FAILURE);
}
