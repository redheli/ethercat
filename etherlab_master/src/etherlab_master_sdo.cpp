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

#define MODES_OF_OPERATION_DISPLAY 0x6061
#define MODES_OF_OPERATION 0x6060

// Application parameters
#define FREQUENCY 100
#define PRIORITY 1
// Optional features
#define CONFIGURE_PDOS  0
#define SDO_ACCESS      1
// Timer
static unsigned int sig_alarms = 0;
static unsigned int user_alarms = 0;

#if SDO_ACCESS
static ec_sdo_request_t *sdo_operation_mode_display;
static ec_sdo_request_t *sdo_operation_mode_write;
#endif

// PDO items
// process data
static uint8_t *domain1_pd = NULL;

// offsets for PDO entries
static unsigned int off_ana_in_status;
static unsigned int off_ana_in_value;

const static ec_pdo_entry_reg_t domain1_regs[] = {
    {AliasAndPositon,  VendorID_ProductCode, 0x6061, 0, &off_ana_in_status},
    {AliasAndPositon,  VendorID_ProductCode, 0x6098, 0, &off_ana_in_value},
    {}
};
ec_pdo_entry_info_t duetfl80_channel1[] = {
    {0x6061, 0,  8}, // modes_of_operation_display
    {0x6098, 0,  8}  // homing_method
};
static ec_pdo_info_t duetfl80_pdos[] = {
    {0x1A00, 2, duetfl80_channel1}    // pdo index input 0x1A00?
};
static ec_sync_info_t duetfl80_syncs[] = {
    {2, EC_DIR_OUTPUT},
    {3, EC_DIR_INPUT, 1, duetfl80_pdos},
    {0xff}
};

// EtherCAT
static ec_master_t *master = NULL;
static ec_master_state_t master_state = {};

static ec_domain_t *domain1 = NULL;
static ec_domain_state_t domain1_state = {};

static ec_slave_config_t *sc_ana_in = NULL;
static ec_slave_config_state_t sc_ana_in_state = {};

static unsigned int counter = 0;
static unsigned int blink = 0;
/*****************************************************************************/

#if SDO_ACCESS
void read_sdo(void)
{
    switch (ecrt_sdo_request_state(sdo_operation_mode_display)) {
        case EC_REQUEST_UNUSED: // request was not used yet
            ecrt_sdo_request_read(sdo_operation_mode_display); // trigger first read
//            ecrt_sdo_request_write(sdo);
            break;
        case EC_REQUEST_BUSY:
            fprintf(stderr, "Still busy...\n");
            break;
        case EC_REQUEST_SUCCESS:
            fprintf(stderr, "SDO value: 0x%04X\n",
                    EC_READ_U8(ecrt_sdo_request_data(sdo_operation_mode_display)));
            ecrt_sdo_request_read(sdo_operation_mode_display); // trigger next read
            break;
        case EC_REQUEST_ERROR:
            fprintf(stderr, "Failed to read SDO!\n");
            ecrt_sdo_request_read(sdo_operation_mode_display); // retry reading
            break;
    }
}
#endif

/*****************************************************************************/

void check_domain1_state(void)
{
    ec_domain_state_t ds;

    ecrt_domain_state(domain1, &ds);

    if (ds.working_counter != domain1_state.working_counter)
        printf("Domain1: WC %u.\n", ds.working_counter);
    if (ds.wc_state != domain1_state.wc_state)
        printf("Domain1: State %u.\n", ds.wc_state);

    domain1_state = ds;
}

/*****************************************************************************/

void check_master_state(void)
{
    ec_master_state_t ms;

    ecrt_master_state(master, &ms);

    if (ms.slaves_responding != master_state.slaves_responding)
        printf("%u slave(s).\n", ms.slaves_responding);
    if (ms.al_states != master_state.al_states)
        printf("AL states: 0x%02X.\n", ms.al_states);
    if (ms.link_up != master_state.link_up)
        printf("Link is %s.\n", ms.link_up ? "up" : "down");

    master_state = ms;
}
/*****************************************************************************/

void check_slave_config_states(void)
{
    ec_slave_config_state_t s;

    ecrt_slave_config_state(sc_ana_in, &s);

    if (s.al_state != sc_ana_in_state.al_state)
        printf("AnaIn: State 0x%02X.\n", s.al_state);
    if (s.online != sc_ana_in_state.online)
        printf("AnaIn: %s.\n", s.online ? "online" : "offline");
    if (s.operational != sc_ana_in_state.operational)
        printf("AnaIn: %soperational.\n",
                s.operational ? "" : "Not ");

    sc_ana_in_state = s;
}

/****************************************************************************/

void cyclic_task()
{
    // receive process data
    ecrt_master_receive(master);
    ecrt_domain_process(domain1);

    // check process data state (optional)
    check_domain1_state();

    if (counter) {
        counter--;
    } else { // do this at 1 Hz
        counter = FREQUENCY;

        // calculate new process data
        blink = !blink;

        // check for master state (optional)
        check_master_state();

        // check for islave configuration state(s) (optional)
        check_slave_config_states();

#if SDO_ACCESS
        // read process data SDO
        read_sdo();
#endif

    }

#if CONFIGURE_PDOS
    // read process data
    printf("AnaIn: state %u value %u\n",
            EC_READ_U8(domain1_pd + off_ana_in_status),
            EC_READ_U8(domain1_pd + off_ana_in_value));
#endif

#if 0
    // write process data
//    EC_WRITE_U8(domain1_pd + off_dig_out, blink ? 0x06 : 0x09);
#endif

    // send process data
    ecrt_domain_queue(domain1);
    ecrt_master_send(master);
}

/****************************************************************************/

void signal_handler(int signum) {
    switch (signum) {
        case SIGALRM:
            sig_alarms++;
            break;
    case SIGINT:
        printf("use ctrl+x ,need do something");
        // disable the operation
        // send 0x0007 to controlword
        break;
    }
}
/*****************************************************************************/
int main(int argc, char **argv)
{
//    ec_slave_config_t *sc;
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

#if SDO_ACCESS
    fprintf(stderr, "Creating operation mode read SDO requests...\n");
    if (!(sdo_operation_mode_display = ecrt_slave_config_create_sdo_request(sc_ana_in, MODES_OF_OPERATION_DISPLAY, 0, 1))) // data size 1 ?
    {
        fprintf(stderr, "Failed to create SDO modes_of_operation_display 0x6061 request.\n");
        return -1;
    }

    fprintf(stderr, "Creating operation mode write SDO requests...\n");
    if (!(sdo_operation_mode_write = ecrt_slave_config_create_sdo_request(sc_ana_in, MODES_OF_OPERATION, 0, 1))) // data size 1 ?
    {
        fprintf(stderr, "Failed to create SDO modes_of_operation_display MODES_OF_OPERATION request.\n");
        return -1;
    }

    //EC_WRITE_U16(ecrt_sdo_request_data(sdo), 0xFFFF);

    ecrt_sdo_request_timeout(sdo_operation_mode_display, 500); // ms
    ecrt_sdo_request_timeout(sdo_operation_mode_write, 500); // ms
#endif

#if CONFIGURE_PDOS
    printf("Configuring PDOs...\n");
    if (ecrt_slave_config_pdos(sc_ana_in, EC_END, duetfl80_syncs)) {
        fprintf(stderr, "Failed to configure PDOs.\n");
        return -1;
    }

//    if (!(sc = ecrt_master_slave_config(
//                    master, AnaOutSlavePos, Beckhoff_EL4102))) {
//        fprintf(stderr, "Failed to get slave configuration.\n");
//        return -1;
//    }

//    if (ecrt_slave_config_pdos(sc, EC_END, el4102_syncs)) {
//        fprintf(stderr, "Failed to configure PDOs.\n");
//        return -1;
//    }

//    if (!(sc = ecrt_master_slave_config(
//                    master, DigOutSlavePos, Beckhoff_EL2032))) {
//        fprintf(stderr, "Failed to get slave configuration.\n");
//        return -1;
//    }

//    if (ecrt_slave_config_pdos(sc, EC_END, el2004_syncs)) {
//        fprintf(stderr, "Failed to configure PDOs.\n");
//        return -1;
//    }


//    // Create configuration for bus coupler
//    sc = ecrt_master_slave_config(master, BusCouplerPos, Beckhoff_EK1100);
//    if (!sc)
//        return -1;

    if (ecrt_domain_reg_pdo_entry_list(domain1, domain1_regs)) {
            fprintf(stderr, "PDO entry registration failed!\n");
            return -1;
        }
#endif

    printf("Activating master...\n");
    if (ecrt_master_activate(master))
        return -1;

#if CONFIGURE_PDOS
    if (!(domain1_pd = ecrt_domain_data(domain1))) {
        return -1;
    }
#endif

#if PRIORITY
    pid_t pid = getpid();
    if (setpriority(PRIO_PROCESS, pid, -19))
        fprintf(stderr, "Warning: Failed to set priority: %s\n",
                strerror(errno));
#endif

    // 1. check operation mode
    bool getModeOk=false;
    for(int i=0;i<10;++i)
    {
        ecrt_sdo_request_read(sdo_operation_mode_display); // trigger read
        switch (ecrt_sdo_request_state(sdo_operation_mode_display)) {
            case EC_REQUEST_UNUSED: // request was not used yet
                ecrt_sdo_request_read(sdo_operation_mode_display); // trigger first read
    //            ecrt_sdo_request_write(sdo);
                break;
            case EC_REQUEST_BUSY:
                fprintf(stderr, "Still busy...\n");
                break;
            case EC_REQUEST_SUCCESS:
                fprintf(stderr, "sdo_operation_mode_display value: 0x%04X\n",
                        EC_READ_U8(ecrt_sdo_request_data(sdo_operation_mode_display)));
                getModeOk = true;
                break;
            case EC_REQUEST_ERROR:
                fprintf(stderr, "Failed to read SDO!\n");
                break;
        }
        if(getModeOk)
        {
            break;
        }
        sleep(1);
    }
    // 2. set operation mode to velocity mode
    EC_WRITE_U8(ecrt_sdo_request_data(sdo_operation_mode_write), 0x03);
    switch (ecrt_sdo_request_state(sdo_operation_mode_write)) {
        case EC_REQUEST_UNUSED: // request was not used yet
//            ecrt_sdo_request_read(sdo_operation_mode_display); // trigger first read
//            ecrt_sdo_request_write(sdo);
            break;
        case EC_REQUEST_BUSY:
            fprintf(stderr, "Request to Write,But Still busy...\n");
            break;
        case EC_REQUEST_SUCCESS:
            fprintf(stderr, "sdo_operation_mode_write write value 0x03");
            ecrt_sdo_request_write(sdo_operation_mode_write);
            break;
        case EC_REQUEST_ERROR:
            fprintf(stderr, "Failed to read SDO state!\n");
            break;
    }
    // 1. check operation mode
    getModeOk=false;
    for(int i=0;i<10;++i)
    {
        ecrt_sdo_request_read(sdo_operation_mode_display); // trigger read
        switch (ecrt_sdo_request_state(sdo_operation_mode_display)) {
            case EC_REQUEST_UNUSED: // request was not used yet
                ecrt_sdo_request_read(sdo_operation_mode_display); // trigger first read
    //            ecrt_sdo_request_write(sdo);
                break;
            case EC_REQUEST_BUSY:
                fprintf(stderr, "Still busy...\n");
                break;
            case EC_REQUEST_SUCCESS:
                fprintf(stderr, "sdo_operation_mode_display value: 0x%04X\n",
                        EC_READ_U8(ecrt_sdo_request_data(sdo_operation_mode_display)));
                getModeOk = true;
                break;
            case EC_REQUEST_ERROR:
                fprintf(stderr, "Failed to read SDO!\n");
                break;
        }
        if(getModeOk)
        {
            break;
        }
        sleep(1);
    }





    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGALRM, &sa, 0)) {
        fprintf(stderr, "Failed to install signal handler!\n");
        return -1;
    }

    printf("Starting timer...\n");
    tv.it_interval.tv_sec = 0;
    tv.it_interval.tv_usec = 1000000 / FREQUENCY;
    tv.it_value.tv_sec = 0;
    tv.it_value.tv_usec = 1000;
    if (setitimer(ITIMER_REAL, &tv, NULL)) {
        fprintf(stderr, "Failed to start timer: %s\n", strerror(errno));
        return 1;
    }

    printf("Started.\n");
    while (1) {
        pause();

#if 0
        struct timeval t;
        gettimeofday(&t, NULL);
        printf("%u.%06u\n", t.tv_sec, t.tv_usec);
#endif

        while (sig_alarms != user_alarms) {
            cyclic_task();
            user_alarms++;
        }
    }

    return 0;
}
