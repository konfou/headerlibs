#include <stdio.h>
#include "chkpath.h"


int main(void)
{
    if (iscmdavail("/bin/bash")) {
        printf((which("/bin/bash")));
        printf(" is available\n");
    }

    if (iscmdavail("which")) {
        printf((which("which")));
        printf("\n");
    }

    if (!iscmdavail("this_cmd_doesnt_exist"))
        printf("this cmd doesnt exist\n");

    return 0;
}
