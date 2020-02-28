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
  const void * class; /**< must be first, class descriptor */
  char * text;        /**< String attributes */
};

/* String Class descriptor */
static const struct Class _String =
{
    sizeof(struct String),      /**< size of this type class*/
    String_ctor, String_dtor,
    String_clone, String_differ
};

const void * String = &_String;


/** String Constructor */
static void * String_ctor (void * _self, va_list * app)
{
    struct String * self = _self;
    const char * text = va_arg(*app, const char *);

    self->text = malloc(strlen(text) + 1);
    assert(self->text);
    strcpy(self->text, text);
    return self;

}
/** String destructor */
static void * String_dtor (void * _self)
{
    struct String * self = _self;

    free(self->text), self->text = 0;
    return self;
}

/** String clone function */
static void * String_clone ( const void * _self)
{
    const struct String * self = _self;
    return new(String, self->text);
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
