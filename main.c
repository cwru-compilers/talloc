#include "talloc.h"

int main(int argc, char** argv) {
    void * ptr1 = talloc(21);
    tfree(ptr1);
    void * ptr2 = talloc(7);
    void * ptr3 = talloc(7);
    void * ptr4 = talloc(7);
    tfree(ptr2);
    tfree(ptr3);
    tfree(ptr4);
    return 0;
}
