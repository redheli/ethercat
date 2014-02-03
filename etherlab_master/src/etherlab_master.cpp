#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

/****************************************************************************/

#include "ecrt.h"

/****************************************************************************/
#define AliasAndPositon  0, 0
#define VendorID_ProductCode  0x000000e4, 0x00001133
// EtherCAT
static ec_master_t *master = NULL;

static ec_domain_t *domain1 = NULL;

static ec_slave_config_t *sc_ana_in = NULL;

/****************************************************************************/

int main(int argc, char **argv)
{
    ec_slave_config_t *sc;
    struct sigaction sa;
    struct itimerval tv;

    master = ecrt_request_master(0);
    if (!master)
        return -1;

    domain1 = ecrt_master_create_domain(master);
    if (!domain1)
    {
        return -1;
    }

    if (!(sc_ana_in = ecrt_master_slave_config(master, AliasAndPositon, VendorID_ProductCode)))
    {
        fprintf(stderr, "Failed to get slave configuration.\n");
        return -1;
    }

}
