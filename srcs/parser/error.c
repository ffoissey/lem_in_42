#include "lemin.h"
#include <errno.h>
#include <stdio.h>

uint8_t			is_major_error(uint32_t error)
{
	if ((unsigned char)(error >> 24))
		return (TRUE);
	else if (error & ANTS_ERR)
		return (TRUE);
	else if (error & ROOMS_ERR)
		return (TRUE);
	return (FALSE);
}

static void		ants_error(uint32_t error)
{
	ft_putstr_fd("ants: ", 2);
	if (error & NO_ANT)
		ft_putendl_fd("There can not be 0 ant", 2);
	else if (error & TOO_MANY_ANTS)
		ft_putendl_fd("Too many ants", 2);
	else if (error & BAD_FORMAT)
		ft_putendl_fd("Bad format", 2);
	else
		ft_putendl_fd("Undefined error", 2);

}

void			print_error(uint32_t error)
{
	ft_putstr_fd("Error: ", 2);
	if (error & READ_ERR)
		perror("read");
	else if (error & MALLOC_ERR)
		perror("malloc");
	else if (error & WRITE_ERR)
		perror("write");
	else if (error & ANTS_ERR)
		ants_error(error);
}
