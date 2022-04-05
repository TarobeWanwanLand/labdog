#include <labdog/foo.hpp>
#include <stdio.h>

void foo_print_version(void)
{
  #if (LABDOG_DEBUG)
    const char *m = "Debug";
  #else
    const char *m = "Not debug";
  #endif

  printf("This is foo version %s (%s)\n", LABDOG_VERSION, m);
}
