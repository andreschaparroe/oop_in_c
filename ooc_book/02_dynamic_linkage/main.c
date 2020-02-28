#include <stdio.h>

#include "string.h"
#include "new.h"


int main(void)
{

    void * a = new(String, "a"), * aa = clone(a);
    void * b = new(String, "b");

    printf("sizeOf(a) == %u\n", sizeOf(a));

    if(differ(a, aa))
        puts("differ?");

    if(a == aa)
       puts("clone?");

    delete(a), delete(aa), delete(b);

    while(1);
    /* return 0;*/
}
