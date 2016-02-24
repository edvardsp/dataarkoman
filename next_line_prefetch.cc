/*
 * NEXT-LINE PREFETCHING
 */

#include "interface.hh"

#define N_LINES  16


void prefetch_init(void)
{
    /* Called before any calls to prefetch_access. */
    /* This is the place to initialize data structures. */

    DPRINTF(HWPrefetch, "Initialized sequential-on-access prefetcher\n");
}


void prefetch_access(AccessStat stat)
{
    if (stat.miss) {
        Addr pf_addr = stat.mem_addr + BLOCK_SIZE;
        for (int i = 0; i < N_LINES; i++) {
	        if (!in_cache(pf_addr))
                issue_prefetch(pf_addr);
            pf_addr += BLOCK_SIZE;
        }
    }
}

void prefetch_complete(Addr addr) {
    /*
     * Called when a block requested by the prefetcher has been loaded.
     */
}
