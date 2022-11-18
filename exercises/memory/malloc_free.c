/*
what does malloc do?

    malloc frees space in heap memory using the sbrk() sys call

    malloc(#number of bytes)
        return pointer to first byte of newly allocated space 
        return NULL if heap overflow (program break hits stack frame)

    extern char etext, edata, end;
    end global symbol - beginning of heap
    | - length of allocated space
    |
    |
    |
    |
    program break (sbrk(0)) or beginning of free memory block

what does free do?

    frees allocated memory and adds pointers for the previous and next freespace 

*/


#include <stdio.h>
#include <unistd.h>
#include <limits.h>

#ifndef BLOCK_SIZE
#define BLOCK_SIZE 1024
#endif

struct free_list
{
    char *first;
    int length;
    struct free_list *prev_node;
    struct free_list *next_node;
};

static struct free_list Free_List;




void *new_malloc(int bytes)
{
    void *res;
    struct free_list list = Free_List;

    /* loop through free list for perfect fit*/
    while (list.next_node!=NULL) {
        if (list.length==bytes) {
            res = list.first + 4;
            /* remove from free memory linked list*/
            /* prev = next, next = prev */
            if (list.prev_node!=NULL) {
                Free_List = *list.next_node;
            } else {
                struct free_list *tmp = list.prev_node;
                list.prev_node = list.next_node;
                list.next_node->prev_node = tmp;
            }
            return res;
        }
        list = *list.next_node;
    }
    /* loop through free list for best fit*/
    list = Free_List;
    while (list.next_node!=NULL) {
        if (list.length>bytes) {
            res = list.first + 4;

            /* if */

            /* remove from free memory linked list*/
            /* prev = next, next = prev */
            if (list.prev_node!=NULL) {
                Free_List = *list.next_node;
            } else {
                struct free_list *tmp = list.prev_node;
                list.prev_node = list.next_node;
                list.next_node->prev_node = tmp;
            }
            return res;
        }
        list = *list.next_node;
    }

    /* push program break */
    res = sbrk(bytes);
    if (res==-1) {
        return NULL;
    } else {
        return res;
    }
}


void new_free(char *pointer) {
    struct free_list new_block;
    new_block.first = pointer - 4;
    
    struct free_list list = Free_List;
    
}



int main(int argc, char *argv[]) 
{
    printf("allocated %d bytes starting at %p\n", 1024, new_malloc(1024));
}



