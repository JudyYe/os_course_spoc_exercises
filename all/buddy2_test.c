#include "buddy2.h"
#include <stdio.h>
#include <unistd.h>


/*
 struct buddy2;
 struct buddy2* buddy2_new( int size );
 void buddy2_destroy( struct buddy2* self );
 
 int buddy2_alloc(struct buddy2* self, int size);
 void buddy2_free(struct buddy2* self, int offset);
 
 int buddy2_size(struct buddy2* self, int offset);
 void buddy2_dump(struct buddy2* self);
*/
int main() {
    printf("test start\n");
    struct buddy2* header = buddy2_new(512);
    buddy2_print(header);
    int mem1 = buddy2_alloc(header, 15);
    printf("\nmem1: %d / %d\n", mem1, header->size);
    buddy2_print(header);
    
    int mem2 = buddy2_alloc(header, 35);
    printf("mem2: %d / %d\n", mem2, header->size);
    
    buddy2_print(header);
    buddy2_free(header, mem1);
    buddy2_print(header);
}
