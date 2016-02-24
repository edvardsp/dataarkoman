/*
 * INSTRUCTION PC BASED STRIDE PREFETCHING
 */

#include <map>

#include "interface.hh"

#define N_STRIDE 16

std::map<Addr, Addr> stride_table;

void prefetch_init(void)
{
    /* Called before any calls to prefetch_access. */
    /* This is the place to initialize data structures. */

    DPRINTF(HWPrefetch, "Initialized sequential-on-access prefetcher\n");
}

void stride_forward(AccessStat stat)
{
    Addr stride = stat.mem_addr - stride_table[stat.pc];
    if (stride == 0)
        return;
        
    Addr pf_addr = stat.mem_addr;
    for (int i = 0; i < N_STRIDE; i++)
    {
        if (pf_addr > MAX_PHYS_MEM_ADDR - stride)
            break;
        pf_addr += stride;
        
        if (!in_cache(pf_addr))
            issue_prefetch(pf_addr);
    }
}

void stride_backward(AccessStat stat)
{
    Addr stride = stride_table[stat.pc] - stat.mem_addr;
    if (stride == 0)
        return;
        
    Addr pf_addr = stat.mem_addr;
    for (int i = 0; i < N_STRIDE; i++)
    {
        if (pf_addr < stride)
            break;
        pf_addr -= stride;
        
        if (!in_cache(pf_addr))
            issue_prefetch(pf_addr);
    }
}

void prefetch_access(AccessStat stat)
{
    if (stride_table.find(stat.pc) != stride_table.end())
    {
        if (stat.mem_addr > stride_table[stat.pc])
            stride_forward(stat);
        else
            stride_backward(stat);
    }
    
    stride_table[stat.pc] = stat.mem_addr;
}

void prefetch_complete(Addr addr) {
    /*
     * Called when a block requested by the prefetcher has been loaded.
     */
}
