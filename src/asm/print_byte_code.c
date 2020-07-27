#include "corewar.h"

int print_byte_code(char *file_name, t_bot *bot)
{
  int   fd;
  int   i;
  char  *name;

  i = ft_strlen(file_name);
  i--;
  if (file_name[i] == 's')
    i--;
  else
    return (KO);
  if (file_name[i] == '.')
    i--;
  else
    return (KO);
  name = (char*)malloc(sizeof(char) * (i + 5));
  name[i + 5] = '\0';
  name[i + 1] = '.';
  name[i + 2] = 'c';
  name[i + 3] = 'o';
  name[i + 4] = 'r';
  while (i >= 0){
    name[i] = file_name[i];
    i--;
  }
  fd = open(name, O_CREAT, S_IRUSR | S_IWUSR);
  return (OK);
}
