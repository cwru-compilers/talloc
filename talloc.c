#include <unistd.h>
#include <stdio.h>

struct free {
    int size;
    struct free* next;
};

struct free* head = NULL;

void* set_size(void* chunk, int size) {
    int * cs_ptr = (int*)chunk;
    (*cs_ptr) = size;
    chunk += sizeof(size);
    return chunk;
}

void* talloc(int size) {

    struct free ** prev = &head;
    struct free * cur = head;

    int asize = size;
    size += sizeof(size);

    printf("call to talloc %d\n", size);

    while (cur != NULL) {
        printf("  cur->size %d\n", cur->size);
        if (cur->size == size) {
            printf("  exact fit %d\n", size);
            (*prev) = cur->next;
            return set_size(cur, asize);
        } else if (cur->size > size) {
            printf("  chunked fit %d\n", size);
            struct free* next = cur->next;
            int chunk_size = cur->size;
            void* chunk = cur;
            cur += size;
            cur->size = chunk_size - size;
            cur->next= next;
            (*prev) = cur;
            return set_size(chunk, asize);
        }
        cur = cur->next;
    }

    printf("  call to sbrk %d\n", size);
    struct free* chunk = sbrk(size);
    if ((int)chunk != -1) {
        return set_size(chunk, asize);
    }
    return (void*)-1;
}

int tfree(void* ptr) {
    int size;
    struct free * chunk;

    ptr = ptr - sizeof(size);
    size = *((int*)ptr);


    chunk = (struct free *)ptr;
    chunk->size = size + sizeof(size);
    chunk->next = head;
    head = chunk;

    printf("call to tfree %d\n", chunk->size);

    return 0;
}

