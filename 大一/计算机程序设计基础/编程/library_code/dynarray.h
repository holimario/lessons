#ifndef __DYNARRAY__
#define __DYNARRAY__

typedef struct __DYNAMIC_INTEGERS * DYNAMIC_INTEGERS;

DYNAMIC_INTEGERS DiCreate( unsigned int capacity );
void DiDestroy( DYNAMIC_INTEGERS a );
void DiResize( DYNAMIC_INTEGERS a, unsigned int capacity );
void DiAddElement( DYNAMIC_INTEGERS a, int element );
void DiInsertElement( DYNAMIC_INTEGERS a, unsigned int pos, int element );
void DiRemoveElement( DYNAMIC_INTEGERS a, unsigned int pos );
int DiGetElement( DYNAMIC_INTEGERS a, unsigned int pos );
void DiSetElement( DYNAMIC_INTEGERS a, unsigned int pos, int element );
unsigned int DiGetCapacity( DYNAMIC_INTEGERS a );
unsigned int DiGetCount( DYNAMIC_INTEGERS a );
unsigned int DiFindElementFirst( DYNAMIC_INTEGERS a, int element );
unsigned int DiFindElementNext( DYNAMIC_INTEGERS a, unsigned int pos, int element );

#endif