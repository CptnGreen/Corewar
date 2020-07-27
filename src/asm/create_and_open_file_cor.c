#include "corewar.h"

int   create_and_open_file_cor(int i, char *name, char *file_name)
{
    int   fd;

    name = (char *)ft_memalloc(i + 5);
    name[i + 5] = '\0';
    if (name == NULL)
        return (-1);
    ft_strcpy(name + i + 1, ".cor");
    while (i >= 0)
    {
        name[i] = file_name[i];
        i--;
    }
    fd = open(name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    return (fd);
}
