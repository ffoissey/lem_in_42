#include "lemin.h"

int8_t        creat_ants_list(t_lemin *lemin)
{
    size_t  id;
    t_ant   ant;
    t_list  *new;

    id = 1;
    while (id <= lemin->total_ants)
    {
        ant.position = lemin->start_room;
        ant.id = id;
        new = ft_lstnew(&ant, sizeof(t_ant));
        if (new == NULL)
            return (FAILURE);
        ft_lstadd_back(&(lemin->ants), new);
        id++;
    }
    return (SUCCESS);
}

void        free_ant(void *content)
{
    free(content);
}
