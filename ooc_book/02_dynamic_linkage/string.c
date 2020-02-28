#include "new.h"
#include "string.h"

/* Prototypes */
static void * String_ctor (void * _self, va_list * app);
static void * String_dtor (void * _self);
static void * String_clone ( const void * _self);
static int String_differ (const void * _self, const void * _b);

/* String struct */
struct String
{
  const void * class;   /**< must be first, class descriptor */
  char * text;          /**< String attributes */
  struct String * next; /**< circular list maintainer */
  unsigned count;       /**< count the number of times an atom is cloned*/
};

/* String Class descriptor */
static const struct Class _String =
{
    sizeof(struct String),      /**< size of this type class*/
    String_ctor, String_dtor,
    String_clone, String_differ
};

const void * String = &_String;

static struct String * ring; /* of all strings */

/** String Constructor */
static void * String_ctor (void * _self, va_list * app)
{
    struct String * self = _self;
    const char * text = va_arg(*app, const char *);

    if(ring)
    {
        struct String * p = ring;
        do
        {
            /* if a suitable atom is found */
            if(strcmp(p->text, text) == 0 )
            {
                ++p->count; /* increment its reference count*/
                free(self); /* free the new string object self */
                return p; /* return the atom p instead */
            }
        }
        while((p = p->next) != ring);
    }
    else
    {
        ring = self; /* if ring empty, insert first object*/
    }
    /* otherwise we insert the new string object into the circular list */

    self->next = ring->next, ring->next = self;
    self->count = 1;

    self->text = malloc(strlen(text) + 1);
    assert(self->text);
    strcpy(self->text, text);
    return self;

}
/** String destructor */
static void * String_dtor (void * _self)
{
    struct String * self = _self;

    if(--self->count > 0)
    {
        return 0;
    }

    assert(ring);

    if(ring == self)
        ring = self->next;
    if(ring == self)
        ring = 0;
    else
    {
        struct String * p = ring;
        while(p->next != self)
        {
            p = p->next;
            assert( p != ring );
        }

        p->next = self->next;
    }

    free(self->text), self->text = 0;
    return self;
}

/** String clone function */
static void * String_clone ( const void * _self)
{
    struct String * const self = (void *)_self;
    ++ self->count;
    return self;
}

/** String comparator */
static int String_differ (const void * _self, const void * _b)
{
    const struct String * self = _self;
    const struct String * b = _b;

    if (self == b)
        return 0;
    if (! b || b->class != String)
        return 1;

    return strcmp(self->text, b->text);

}
