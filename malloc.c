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

void wordcpy(void *dst, void *src, size_t len)
{
  char *ptr , *dos;
  dos = dst;
  ptr = src;

  for (size_t i = 0 ; i < len ; i++)
   {
    dst[i] = src[i]  
   }
}

static
struct chunk* get_base(void) 
{
  static struct chunk *base = NULL;
  if (base == NULL) 
   {
    /* FIX ME */
   }
}
}
