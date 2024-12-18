/* xm.c = xmmap xmunmap */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <paging.h>


/*-------------------------------------------------------------------------
 * xmmap - xmmap
 *-------------------------------------------------------------------------
 */
SYSCALL xmmap(int virtpage, bsd_t source, int npages)
{
  /* Validate parameters */
    if (virtpage < 4096 || virtpage >= 1048575 ) {
        /* virtpage is out of valid virtual address space for this process */
        return SYSERR;
    }

    if (source < 0 || source >= 8 || npages <= 0 || npages > 256) {
        return SYSERR;
    }

    /* Check if the backing store can provide npages pages */
    // int bs_npages = get_bs(source, npages);
    // if (bs_npages == SYSERR || bs_npages < npages) {
    //     /* get_bs either failed or returned fewer pages than requested */
    //     return SYSERR;
    // }

    /* Attempt to map the given virtual page to the backing store */
    if (bsm_map(currpid, virtpage, source, npages) == SYSERR) {
        /* Failed to record the mapping in the global table */
        return SYSERR;
    }
    
    return OK;
}



/*-------------------------------------------------------------------------
 * xmunmap - xmunmap
 *-------------------------------------------------------------------------
 */
SYSCALL xmunmap(int virtpage)
{
  kprintf("To be implemented!");
  return SYSERR;
}
