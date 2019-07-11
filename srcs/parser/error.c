#include "lemin.h"

uint8_t	is_major_error(uint32_t error)
{
	if ((unsigned char)(error >> 24))
		return (TRUE);
	else if (error & ANTS_ERR)
		return (TRUE);
	else if (error & ROOMS_ERR)
		return (TRUE);
	return (FALSE);
}

void	print_error(__attribute__((unused)) uint32_t error)
{
	ft_putendl_fd("ERROR", 2);
}
