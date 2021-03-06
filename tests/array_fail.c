#include <stdio.h>
#include <stdlib.h>
#include "open_shmem.h"

// shmem_barrier removed
// catches unsynchrized access  to symmetric variables

int main(int argc, char *argv[])
{
    void *dest = shmem_malloc(10);
    void *source = malloc(10);
    int pe = 2;    

    shmem_put(&dest[3],&source[2],1,pe);	


    // void *alias = &dest[2];

    // notice the barrier has been removed from all_is_well.c
    // boom! access to unsynchronized dest
    shmem_get(&dest[3],&source[2],1,pe);
    
    free(dest);
    free(source);
    return 0;
}

// TODO: Check if Clang static analyzer have aliasing information
//TODO: Global and static


// If not available, assume everything is restricted (Don't think about aliasing now)