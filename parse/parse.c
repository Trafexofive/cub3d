
#include "parse.h"

char **parse_init(t_args args);
bool valid_args(t_args args);
bool valid_map(char **map);

int main(int ac, char *av[]) {
  char **map;
  t_args args;
  args.ac = ac;
  args.av = av;

  valid_args(args);
  map = parse_init(args);
  valid_map(map);

  return EXIT_SUCCESS;
}
