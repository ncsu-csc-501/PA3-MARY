/* frame.c - manage physical frames */
#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <paging.h>

/*-------------------------------------------------------------------------
 * init_frm - initialize frm_tab
 *-------------------------------------------------------------------------
 */
fr_map_t frm_tab[NFRAMES];
SYSCALL init_frm()
{
  //kprintf("To be implemented!\n");
  // STATWORD ps;
  // disable(ps);
  // int i, j;
  // for (i = 0; i < NFRAMES; i++) {
  //       frm_tab[i].fr_status = FRM_UNMAPPED;  /* Frame is initially unmapped */
  //       frm_tab[i].fr_refcnt = 0;             /* Reference count is 0 */
  //       frm_tab[i].fr_type = 0;               /* No specific type */
  //       frm_tab[i].fr_dirty = 0;              /* Not dirty initially */
  //       for(j = 0; j < NPROC; j++) {
  //         frm_tab[i].fr_pid[j] = -1;               /* No process associated (use -1 as default) */
  //         frm_tab[i].fr_vpno[j] = -1;              /* No virtual page number */
  //       }
  //   }
  // restore(ps);
  return OK;

}

/*-------------------------------------------------------------------------
 * get_frm - get a free frame according page replacement policy
 *-------------------------------------------------------------------------
 */
SYSCALL get_frm(int* avail)
{
  kprintf("To be implemented!\n");
  return OK;
}

/*-------------------------------------------------------------------------
 * free_frm - free a frame 
 *-------------------------------------------------------------------------
 */
SYSCALL free_frm(int i)
{

  kprintf("To be implemented!\n");
  return OK;
}