#ifndef SET_H
#define SET_H

struct Set { unsigned count; };

/**
  * takes an element, adds it to a set, and returns whatever was added or already present in the set
  */
void * add (void * set, const void * element);

/**
  * Looks for an element in a set and return whatever is present in the set
  */
void * find (const void * set, const void * element);

/**
  * Locates an element, removes it from a set, and returns whatever was removed
  */
void * drop ( void * set, const void * element);

/**
  * converts the result of find() into a truth value
  */
int contains ( const void * set, const void * element);


#endif
