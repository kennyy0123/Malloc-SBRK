#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void *malloc (size_t size);
void free (void *ptr);


int main ()
{

char *test = NULL;
test = malloc(sizeof(char) * 4 );
if (test == NULL)
 {
 printf("Ca marche pas \n");
 }
else 
 {
 printf("Ca marche ");
 }

}
