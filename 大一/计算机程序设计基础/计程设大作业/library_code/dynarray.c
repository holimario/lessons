#ifndef __ZYLIB__
#include "zylib.h"
#endif

#ifndef __DYNARRAY__
#include "dynarray.h"
#endif

//#define CACHE_LINE_LENGTH 16
#define CACHE_LINE_LENGTH 256
static const unsigned int __capacity_factor = CACHE_LINE_LENGTH / sizeof(int);

struct __DYNAMIC_INTEGERS
{
  unsigned int capacity;
  unsigned int count;
  int * elements;
};

static void __DoDiResize( DYNAMIC_INTEGERS a, unsigned int capacity );

DYNAMIC_INTEGERS DiCreate( unsigned int capacity )
{
  DYNAMIC_INTEGERS t = NewObject( struct __DYNAMIC_INTEGERS );
  unsigned int mc = (capacity + __capacity_factor - 1) / __capacity_factor * __capacity_factor;
  if( !t )  PrintErrorMessage( FALSE, "DiCreate: Failed in allocating memory." );
  t->capacity = mc == 0 ? __capacity_factor : mc;
  t->count = 0;
  t->elements = CreateObjects( int, t->capacity );
  if(!t->elements)  PrintErrorMessage( FALSE, "DiCreate: Failed in allocating memory." );
  return t;
}

void DiDestroy( DYNAMIC_INTEGERS a )
{
  if( !a )  PrintErrorMessage( FALSE, "DiDestroy: Parameter illegal." );
  DestroyObjects( a->elements );
  DestroyObject( a );
}

void DiResize( DYNAMIC_INTEGERS a, unsigned int capacity )
{
  unsigned int mc, ac;
  if( !a )  PrintErrorMessage( FALSE, "DiResize: Parameter illegal." );
  if( capacity == a->capacity )  return;
  mc = capacity > a->count ? capacity : a->count;
  ac = (mc + __capacity_factor - 1) / __capacity_factor * __capacity_factor;
  __DoDiResize( a, ac );
}

void DiAddElement( DYNAMIC_INTEGERS a, int element )
{
  if( !a )  PrintErrorMessage( FALSE, "DiAddElement: Parameter illegal." );
  if(a->capacity <= a->count)  __DoDiResize( a, a->capacity + __capacity_factor );
  a->elements[a->count] = element;
  a->count++;
}

void DiInsertElement( DYNAMIC_INTEGERS a, unsigned int pos, int element )
{
  unsigned int i;
  if( !a )  PrintErrorMessage( FALSE, "DiInsertElement: Parameter illegal." );
  if( pos >= a->count ){  DiAddElement( a, element );  return;  }
  if(a->capacity <= a->count)  __DoDiResize( a, a->capacity + __capacity_factor );
  for( i = a->count; i > pos; i-- )  a->elements[i] = a->elements[i-1]; 
  a->elements[pos] = element;
  a->count++;
}

void DiRemoveElement( DYNAMIC_INTEGERS a, unsigned int pos )
{
  if( !a )  PrintErrorMessage( FALSE, "DiRemoveElement: Parameter illegal." );
  if( pos >= a->count )  PrintErrorMessage( FALSE, "DiRemoveElement: No such element." );
  if( pos < a->count - 1 ){
    unsigned int i;
    for( i = pos; i < a->count-1; i++ )  a->elements[i] = a->elements[i+1];
  }
  a->count--;
  if( a->capacity - a->count >= __capacity_factor )  __DoDiResize( a, a->capacity - __capacity_factor );
}

int DiGetElement( DYNAMIC_INTEGERS a, unsigned int pos )
{
  if( !a )  PrintErrorMessage( FALSE, "DiGetElement: Parameter illegal." );
  if( pos >= a->count )  PrintErrorMessage( FALSE, "DiGetElement: No such element." );
  return a->elements[pos];
}

void DiSetElement( DYNAMIC_INTEGERS a, unsigned int pos, int element )
{
  if( !a )  PrintErrorMessage( FALSE, "DiSetElement: Parameter illegal." );
  if( pos >= a->count )  PrintErrorMessage( FALSE, "DiSetElement: No such element." );
  a->elements[pos] = element;
}

unsigned int DiGetCapacity( DYNAMIC_INTEGERS a )
{
  if( !a )  PrintErrorMessage( FALSE, "DiGetCapacity: Parameter illegal." );
  return a->capacity;
}

unsigned int DiGetCount( DYNAMIC_INTEGERS a )
{
  if( !a )  PrintErrorMessage( FALSE, "DiGetCount: Parameter illegal." );
  return a->count;
}

unsigned int DiFindElementFirst( DYNAMIC_INTEGERS a, int element )
{
  unsigned int i;
  if( !a || !a->elements )  PrintErrorMessage( FALSE, "DiFindElementFirst: Parameter illegal." );
  for( i = 0; i < a->count; i++ ){  if( a->elements[i] == element )  return i;  }
  return inexistent_index;
}

unsigned int DiFindElementNext( DYNAMIC_INTEGERS a, unsigned int pos, int element )
{
  unsigned int i;
  for( i = pos; i < a->count; i++ ){  if( a->elements[i] == element )  return i;  }
  return inexistent_index;
}

static void __DoDiResize( DYNAMIC_INTEGERS a, unsigned int capacity )
{
  unsigned int i;
  unsigned int ac = a->count == 0 ? __capacity_factor : capacity;
  int * t = CreateObjects( int, ac );
  if( !t )  PrintErrorMessage( FALSE, "__DoDiResize: Failed in allocating memory." );
  for( i =0; i < a->count; i++ )  t[i] = a->elements[i];
  DestroyObjects( a->elements );
  a->elements = t;
  a->capacity = ac;
}
