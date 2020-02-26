#ifndef NEW_H
#define NEW_H

/**
  * Accepts a descriptor like Set and possibly more arguments
  * for initialization and returns a pointer to a new data item
  * with a repesentation conforming to the descriptor
  */
void * new (const void * type, ...);

/**
  * Accepts a pointer originally produced by new() and recylces the associated resources
  */
void delete (void * item);

#endif /* NEW_H */