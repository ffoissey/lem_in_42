#include "lemin.h"

int8_t		get_rooms(t_lemin *lemin, char *line)
{
	(void)lemin;
	if (is_comment(line) & COMMENT)
		return (SUCCESS);
	return (FAILURE);
}
