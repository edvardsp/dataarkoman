/*
 * Tracker BASED PREFETCHING
 */

#include <map>

#include "interface.hh"

enum State
{
    INVALID, ALLOCATED, TRAINING, MONITOR
};

class Tracker
{
public:
    Tracker() : state(INVALID) {}
    ~Tracker() {}
    
private:
    State state;
    Addr entry;
};

std::map<Tracker, int> help;


void prefetch_init(void)
{
    /* Called before any calls to prefetch_access. */
    /* This is the place to initialize data structures. */

    DPRINTF(HWPrefetch, "Initialized sequential-on-access prefetcher\n");
}


void prefetch_access(AccessStat stat)
{
    if (stat.miss)
    {
    
    }
    else
    {
    
    }
}

void prefetch_complete(Addr addr) {
    /*
     * Called when a block requested by the prefetcher has been loaded.
     */
}
