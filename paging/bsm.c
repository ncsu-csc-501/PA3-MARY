/* bsm.c - manage the backing store mapping*/

#include <conf.h>
#include <kernel.h>
#include <paging.h>
#include <proc.h>

/*-------------------------------------------------------------------------
 * init_bsm- initialize bsm_tab
 *-------------------------------------------------------------------------
 */

bs_map_t bsm_tab[7];
SYSCALL init_bsm()
{
    STATWORD ps;
    disable(ps);
    int i;
    for (i = 0; i <=7; i++) {
        free_bsm(i);
    }
    restore(ps);
    return OK;
}

/*-------------------------------------------------------------------------
 * get_bsm - get a free entry from bsm_tab 
 *-------------------------------------------------------------------------
 */
SYSCALL get_bsm(int* avail)
{
	STATWORD ps;
	disable(ps);
	*avail = 0;
	int i=0;
	while(i<8)
	{
		kprintf("current bs is %d, status = %d\n",i, bsm_tab[i].bs_status);
		if(bsm_tab[i].bs_status == BSM_UNMAPPED)
		{
			*avail = i;
			restore(ps);
			return OK;
		}
		i++;
	}
	restore(ps);
	return SYSERR;
}


/*-------------------------------------------------------------------------
 * free_bsm - free an entry from bsm_tab 
 *-------------------------------------------------------------------------
 */
SYSCALL free_bsm(int i)
{
    STATWORD ps;
	disable(ps);
    int j;
	if(i<0 || i>=8)
	{
		restore(ps);
		return SYSERR;
	}

	bsm_tab[i].bs_status = BSM_UNMAPPED;
	bsm_tab[i].bs_sem = 0;
	bsm_tab[i].bs_private = 0;
    bsm_tab[i].bs_refcnt = 0;

	for(j = 0; j < NPROC; j++)
	{
		bsm_tab[i].bs_pid[j] = -1;
        bsm_tab[i].bs_vpno[j] = -1;
		bsm_tab[i].bs_npages[j] = 0;
	}

	restore(ps);
	return OK;
}

/*-------------------------------------------------------------------------
 * bsm_lookup - lookup bsm_tab and find the corresponding entry
 *-------------------------------------------------------------------------
 */
SYSCALL bsm_lookup(int pid, long vaddr, int* store, int* pageth)
{
}


/*-------------------------------------------------------------------------
 * bsm_map - add an mapping into bsm_tab 
 *-------------------------------------------------------------------------
 */
SYSCALL bsm_map(int pid, int vpno, int source, int npages)
{
	STATWORD ps;
	disable(ps);
	int i;

    /* Validate parameters */
    if (pid < 0 || pid >= NPROC || source < 0 || source >= 8 || npages <= 0 || npages > 256) {
		restore(ps);
        return SYSERR;
    }

    /* If store is unmapped, we should have called get_bs before,
       but let's just check and allow mapping only if get_bs was done */
    if (bsm_tab[source].bs_status == BSM_UNMAPPED) {
        return SYSERR;
    }

    /* If the backing store is private, it can only be mapped by one process. */
    if (bsm_tab[source].bs_private == 1) {
        return SYSERR;
    } 
	
	if (bsm_tab[source].bs_private != 1) {
		proctab[pid].store = source;
		bsm_tab[source].bs_pid[currpid] = pid;
		bsm_tab[source].bs_vpno[currpid] = vpno;
		bsm_tab[source].bs_npages[currpid] = npages;
		/* If the store was previously unmapped (unlikely if we are calling after get_bs), set it mapped */
		bsm_tab[source].bs_status = BSM_MAPPED;
		/* Increase the reference count since we are adding a new mapping */
		bsm_tab[source].bs_refcnt++;
	}
	 kprintf("inside bsm_map\n");
    return OK;
}



/*-------------------------------------------------------------------------
 * bsm_unmap - delete an mapping from bsm_tab
 *-------------------------------------------------------------------------
 */
SYSCALL bsm_unmap(int pid, int vpno, int flag)
{
}