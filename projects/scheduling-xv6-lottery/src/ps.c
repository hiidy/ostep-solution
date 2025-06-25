#include "types.h"
#include "stat.h"
#include "user.h"
#include "pstat.h"

int
main(void)
{
    struct pstat ps;

    printf(1, "PID\tTickets\tTicks\n");
    for (int i = 0; i < NPROC; i++) {
        if (getpinfo(&ps) < 0) {
            printf(2, "Error getting process info\n");
            return 1;
        }
        if (ps.inuse[i]) {
            printf(1, "%d\t%d\t%d\n", ps.pid[i], ps.tickets[i], ps.ticks[i]);
        }
    }

    exit();
}