#include "new.h"

/***************************************************
*                 object        class
*      _ _         _ _            _ _
*    p|_*_| ----> |_*_|--------> |_ _| size
*                 |_ _|          |_ _| ctor
*                 |   |          |_ _| dtor
*                                |_ _| clone
*                                |_ _| differ
*                             struct class
*
* The type descriptor class at the right is initialized
* at compile time. The object is created at run time and
* the dashed pointers are then inserted.
****************************************************/
void * new (const void * _class, ...)
{
    const struct Class * class  = _class;
    void *p = calloc(1, class->size);

    assert(p);
    /* p points to the beginning of the new memory area for the object */
    *(const struct Class **)p = class;

    if(class->ctor)
    {
        va_list ap;
        va_start(ap, _class);
        p = class->ctor(p, &ap);
        va_end(ap);
    }
    return p;
}

void * clone(const void * _class)
{
    const struct Class * const * class = _class;

    assert(_class && class && (*class)->clone);

   return (*class)->clone(_class);
}

void delete (void * self)
{
    const struct Class ** cp = self;

    if(self && *cp && (*cp)->dtor)
        self = (*cp)->dtor(self);

    free(self);
}

int differ (const void * self, const void * b)
{
    const struct Class * const * cp = self;

    assert(self && * cp && (*cp)->differ);

    return (*cp)->differ(self, b);
}

size_t sizeOf(const void * self)
{
    const struct Class * const * cp = self;

    assert(self && *cp);

    return (*cp)->size;
}
