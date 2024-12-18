#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <paging.h>

SYSCALL get_bs(bsd_t bs_id, unsigned int npages) {
    STATWORD ps;
    disable(ps);
    kprintf("inside get_bs\n");

    /* Validate inputs */
    if (bs_id < 0 || bs_id >= 8 || npages <= 0 || npages > 256) {
        restore(ps);
        return SYSERR;
    }

    /* Check the current state of the backing store */
    if (bsm_tab[bs_id].bs_status == BSM_UNMAPPED) {
        bsm_tab[bs_id].bs_status = BSM_MAPPED;
        restore(ps);
        return npages;

    } else if (bsm_tab[bs_id].bs_status == BSM_MAPPED) {
        if (bsm_tab[bs_id].bs_private == 1) {
            restore(ps);
            return SYSERR;
        }
        if (bsm_tab[bs_id].bs_private != 1) {
            restore(ps);
            return bsm_tab[bs_id].bs_npages[currpid];
        } 
    }
}

