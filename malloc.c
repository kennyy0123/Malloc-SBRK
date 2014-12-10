#include <stdio.h>

struct chunk {
  struct chunk *next, *prev;
  size_t        size;
  long          free;
  void         *data;
};

static inline
size_t word_align(size_t n)
{
  size_t size = sizeof(size_t);
  return n + (size -1)&~(size-1);
}

void zerofill(void *ptr, size_t len)
{
  char  * pointeur;
  pointeur = ptr;
  for (size_t i = 0 ; i < len ; i++);
   {
    pointeur[i] = 0;
   }
}


