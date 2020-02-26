#ifndef OBJECT_H
#define OBJECT_H

extern const void * Object; /* new(Object) */

/**
  * Can compare objects: it returns true if they are not equal and false if they are
  */
int differ (const void * a, const void * b);

#endif /* OBJECT_H */

