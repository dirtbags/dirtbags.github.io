#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
    setenv("CGIT_CONFIG", "/srv/www/dirtbags.net/cgitrc", 1);
    execl("/usr/local/bin/cgit", "cgit", NULL);

    return 0;
}
