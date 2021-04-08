#include "types.h"
#include "user.h"
#include "pstat.h"

int main(int argc, char *argv[])
{
    struct pstat ps;
    int returnval = getpinfo(&ps);
    if (returnval != -1)
    {
        for (int i = 0; i < 10; i++)
        {
            printf(1, "#%d: ", i);
            printf(1, "Inuse-%d ", ps.inuse[i]);
            printf(1, "Tickets-%d ", ps.tickets[i]);
            printf(1, "PID-%d ", ps.pid[i]);
            printf(1, "Ticks-%d", ps.ticks[i]);
            printf(1, "\n");
        }
    }

    settickets(50);
    printf(1, "\n");

    int returnval1 = getpinfo(&ps);
    if (returnval1 != -1)
    {
        for (int i = 0; i < 10; i++)
        {
            printf(1, "#%d: ", i);
            printf(1, "Inuse-%d ", ps.inuse[i]);
            printf(1, "Tickets-%d ", ps.tickets[i]);
            printf(1, "PID-%d ", ps.pid[i]);
            printf(1, "Ticks-%d", ps.ticks[i]);
            printf(1, "\n");
        }
    }

    int returnval2 = fork();
    if (returnval2 != 0)
    {
        printf(1, "We ran the parent\n");
        settickets(25);
        int returnval1_temp = getpinfo(&ps);
        if (returnval1_temp != -1)
        {
            for (int i = 0; i < 10; i++)
            {
                printf(1, "#%d: ", i);
                printf(1, "Inuse-%d ", ps.inuse[i]);
                printf(1, "Tickets-%d ", ps.tickets[i]);
                printf(1, "PID-%d ", ps.pid[i]);
                printf(1, "Ticks-%d", ps.ticks[i]);
                printf(1, "\n");
            }
        }

    }
    else
    {
        printf(1, "We ran the child\n");
        // Give more tickets to child
        settickets(50);
        int returnval1_temp = getpinfo(&ps);
        if (returnval1_temp != -1)
        {
            for (int i = 0; i < 10; i++)
            {
                printf(1, "#%d: ", i);
                printf(1, "Inuse-%d ", ps.inuse[i]);
                printf(1, "Tickets-%d ", ps.tickets[i]);
                printf(1, "PID-%d ", ps.pid[i]);
                printf(1, "Ticks-%d", ps.ticks[i]);
                printf(1, "\n");
            }
        }

    }

    exit();
    

}