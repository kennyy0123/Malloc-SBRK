#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


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
  return (n + (size -1)&~(size-1));
}

void zerofill(void *ptr, size_t len)
{
  char  *pointeur;
  pointeur = (char*)ptr;
  size_t i;
  for (i = 0 ; i <= len ; i++)
   {
    pointeur[i] = 0;
   }
}

void wordcpy(void *dst, void *src, size_t len)
{
  char *ptr, *dos;
  dos = dst;
  ptr = src;

  for (size_t i = 0 ; i <= len ; i++)
   {
    dos[i] = ptr[i]; 
   }
}

static
struct chunk* get_base(void) 
{
  static struct chunk *base = NULL;

  if (base == NULL) 
   {
    if ((base = sbrk(0)) != (void *)(-1)
          && sbrk(word_align(sizeof(struct chunk))) != (void *)-1)
     {
      base->next = NULL;
      base->prev = NULL;
      base->size = 0;
      base->free = 0;
      base->data = NULL;
     }
   }
  return base;
}

static
int extend_heap(struct chunk *last, size_t size)
{
  struct chunk *base = sbrk(0);
  if (sbrk(sizeof(struct chunk) + size) == (void*)-1)
   {
    return 0;
   }
  else
   {
    base-> size = size;
    base->next = NULL;

    if (last != NULL)
     {
      last->next = base;
     } 
    base->free = 0;
    return 1;
   }
}

static
struct chunk* find_chunk(size_t size)
{
  struct chunk *prev = NULL;
  struct chunk *premier = get_base();


  while(premier != NULL && (premier->size < size || premier->free == 0))
   {
    prev = premier;
    premier = premier->next;
   } 
  return prev;
}

static
struct chunk* get_chunk(void *p)
{

  if (p != NULL && word_align(sizeof (*p)) == sizeof(p) && p >= get_base() && 
        p <= sbrk(0))
   {
    struct chunk *base = p - sizeof(struct chunk);
    if (p == base->data)
     {
      return base;
     }
   }
  return NULL;
}


void *malloc(size_t size)
{
  struct chunk *last;
  size_t b = word_align(size);

  last = find_chunk(b);

  if (last == NULL)
   {
    if (!extend_heap(last,size))
     {
      return (NULL);
     }
    else
     {
      return (last->data);
     }
   }
  else
   {
    last->size = size;
    last->free = 0;
    return (last->data);
   }

}

void free ( void *ptr)
{

  struct chunk *test = get_chunk(ptr);
  if (test != NULL)
   {
    test->free = 1;
   }
}

void *calloc (size_t nmenb, size_t size)
{
  size_t *new;
  new = malloc (nmenb * size);
  zerofill(new,size);

  return new;

}
