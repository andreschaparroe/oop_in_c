#include <stdio.h>

#include "new.h"
#include "object.h"
#include "set.h"

static const size_t _Set = sizeof(struct Set);
static const size_t _Object = sizeof(struct Object);

const void * Set = &_Set;
const void * Object = &_Object;

int main(void)
{
    void * s = new(Set);
    void * a = add(s, new(Object));
    void * b = add(s, new(Object));
    void * c = new(Object);

    if(contains(s, a) && contains (s,b))
        puts("ok");
    if(differ(a, add(s,a)))
        puts("differ?");
    if(contains(s, drop(s,a)))
        puts("drop?");

    delete(drop(s,b));
    delete(drop(s,c));

    while(1);
    /* return 0;*/
}
