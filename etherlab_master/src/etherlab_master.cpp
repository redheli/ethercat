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
//#include "/home/redheli/Downloads/ethercat-1.5.2/master/slave_config.h"

/****************************************************************************/
#define AliasAndPositon  0, 0
#define VendorID_ProductCode  0x000000e4, 0x00001133

// Application parameters
#define FREQUENCY 300
#define PRIORITY 1
// Optional features
#define CONFIGURE_PDOS  1
#define SDO_ACCESS      0
// Timer
static unsigned int sig_alarms = 0;
static unsigned int user_alarms = 0;

static ec_sdo_request_t *sdo;

// PDO items
// process data
static uint8_t *domain_output_pd = NULL;
static uint8_t *domain_output_target_velocity_pd = NULL;
static uint8_t *domain_input_pd = NULL;
// offsets for PDO entries
//static unsigned int off_ana_in_status;
static unsigned int off_0x6040;
static unsigned int off_0x6060;
static unsigned int off_0x6098;
static unsigned int off_0x607a;
static unsigned int off_0x60ff;
static unsigned int off_0x6071;
static unsigned int off_0x6041;
static unsigned int off_0x6064;
static unsigned int off_0x6061;
static unsigned int off_0x1001;
static unsigned int off_0x606c;
static unsigned int off_0x6077;

static unsigned int off_ana_in_value;

////const static ec_pdo_entry_reg_t domain1_regs[] = {
////    {AliasAndPositon,  VendorID_ProductCode, 0x6061, 0, &off_ana_in_status},
////    {AliasAndPositon,  VendorID_ProductCode, 0x6098, 0, &off_ana_in_value},
////    {}
////};
const static ec_pdo_entry_reg_t domain_output_regs[] = {
    {AliasAndPositon,  VendorID_ProductCode, 0x6040, 0, &off_0x6040},
//    {AliasAndPositon,  VendorID_ProductCode, 0x6060, 0, &off_0x6060},
//    {AliasAndPositon,  VendorID_ProductCode, 0x6098, 0, &off_0x6098},
    {AliasAndPositon,  VendorID_ProductCode, 0x607a, 0, &off_0x607a},
//    {AliasAndPositon,  VendorID_ProductCode, 0x60ff, 0, &off_0x60ff},
//    {AliasAndPositon,  VendorID_ProductCode, 0x6071, 0, &off_0x6071},
//    {AliasAndPositon,  VendorID_ProductCode, 0x6041, 0, &off_0x6041},
//    {AliasAndPositon,  VendorID_ProductCode, 0x6064, 0, &off_0x6064},
//    {AliasAndPositon,  VendorID_ProductCode, 0x6061, 0, &off_0x6061},
//    {AliasAndPositon,  VendorID_ProductCode, 0x1001, 0, &off_0x1001},
//    {AliasAndPositon,  VendorID_ProductCode, 0x606c, 0, &off_0x606c},
//    {AliasAndPositon,  VendorID_ProductCode, 0x6077, 0, &off_0x6077},
    {}
};
const static ec_pdo_entry_reg_t domain_input_regs[] = {
//    {AliasAndPositon,  VendorID_ProductCode, 0x6040, 0, &off_0x6040},
//    {AliasAndPositon,  VendorID_ProductCode, 0x6060, 0, &off_0x6060},
//    {AliasAndPositon,  VendorID_ProductCode, 0x6098, 0, &off_0x6098},
//    {AliasAndPositon,  VendorID_ProductCode, 0x607a, 0, &off_0x607a},
//    {AliasAndPositon,  VendorID_ProductCode, 0x60ff, 0, &off_0x60ff},
//    {AliasAndPositon,  VendorID_ProductCode, 0x6071, 0, &off_0x6071},
        {AliasAndPositon,  VendorID_ProductCode, 0x6061, 0, &off_0x6061},
    {AliasAndPositon,  VendorID_ProductCode, 0x6041, 0, &off_0x6041},
//    {AliasAndPositon,  VendorID_ProductCode, 0x6064, 0, &off_0x6064},
{AliasAndPositon,  VendorID_ProductCode, 0x606c, 0, &off_0x606c},
    {AliasAndPositon,  VendorID_ProductCode, 0x1001, 0, &off_0x1001},
//
//    {AliasAndPositon,  VendorID_ProductCode, 0x6077, 0, &off_0x6077},
    {}
};
////ec_pdo_entry_info_t duetfl80_channel1[] = {
////    {0x6061, 0,  8}, // modes_of_operation_display
////    {0x6098, 0,  8}  // homing_method
////};
//ec_pdo_entry_info_t duetfl80_channel1[] = {
//    {0x6041, 0,  16} // modes_of_operation_display
//};
//static ec_pdo_info_t duetfl80_pdos[] = {
//    {0x1A00,1 , duetfl80_channel1}    // pdo index input 0x1A00?
//};
//static ec_sync_info_t duetfl80_syncs[] = {
//    {3, EC_DIR_INPUT, 1, duetfl80_pdos, EC_WD_DISABLE},
//    {0xff}
//};
/* Master 0, Slave 0, "Metronix DIS-2 ECAT"
 * Vendor ID:       0x000000e4
 * Product code:    0x00001133
 * Revision number: 0x00020000
 */

ec_pdo_entry_info_t slave_0_pdo_entries[] = {
    {0x6040, 0x00, 16}, /* Controlword */
//    {0x6060, 0x00, 8}, /* Mode_of_Operation */
//    {0x6098, 0x00, 8}, /* Homing_Method */
    {0x607a, 0x00, 32}, /* Target_Position */
//    {0x60ff, 0x00, 32}, /* Target_Velocity */
//    {0x6071, 0x00, 16}, /* Target_Torque */
    {0x6061, 0x00, 8}, /* Modes_Of_Operation_Display */
    {0x6041, 0x00, 16}, /* Statusword */
    {0x606c, 0x00, 32}, /* Velocity_Actual_Value */
//    {0x6064, 0x00, 32}, /* Position_Actual_Value */
    {0x1001, 0x00, 8}, /* Error_Register */
//    {0x606c, 0x00, 32}, /* Velocity_Actual_Value */
//    {0x6077, 0x00, 16}, /* Torque_Actual_Value */
};

ec_pdo_info_t slave_0_pdos[] = {
    {0x1600, 2, slave_0_pdo_entries + 0}, /* Outputs */
    {0x1A00, 4, slave_0_pdo_entries + 2}, /* Inputs */
};

ec_sync_info_t slave_0_syncs[] = {
    {0, EC_DIR_OUTPUT, 0, NULL, EC_WD_DISABLE},
    {1, EC_DIR_INPUT, 0, NULL, EC_WD_DISABLE},
    {2, EC_DIR_OUTPUT, 1, slave_0_pdos + 0, EC_WD_DISABLE},
    {3, EC_DIR_INPUT, 1, slave_0_pdos + 1, EC_WD_DISABLE},
    {0xff}
};

// EtherCAT
static ec_master_t *master = NULL;
static ec_master_state_t master_state = {};

static ec_domain_t *domain_output = NULL;
static ec_domain_t *domain_output_target_velocity = NULL;
static ec_domain_t *domain_input = NULL;
static ec_domain_state_t domain_input_state = {};

static ec_slave_config_t *sc_ana_in = NULL;
static ec_slave_config_state_t sc_ana_in_state = {};

static unsigned int counter = 0;
/*****************************************************************************/


void read_sdo(void)
{
    switch (ecrt_sdo_request_state(sdo)) {
        case EC_REQUEST_UNUSED: // request was not used yet
        printf("request was not used yet\n");
            ecrt_sdo_request_read(sdo); // trigger first read
//            ecrt_sdo_request_write(sdo);
            break;
        case EC_REQUEST_BUSY:
            fprintf(stderr, "Still busy...\n");
            break;
        case EC_REQUEST_SUCCESS:
            fprintf(stderr, "SDO value: 0x%04X\n",
                    EC_READ_U8(ecrt_sdo_request_data(sdo)));
            ecrt_sdo_request_read(sdo); // trigger next read
            break;
        case EC_REQUEST_ERROR:
            fprintf(stderr, "Failed to read SDO!\n");
            ecrt_sdo_request_read(sdo); // retry reading
            break;
    }
}


/*****************************************************************************/

void check_domain1_state(void)
{
    ec_domain_state_t ds;

    ecrt_domain_state(domain_input, &ds);

    if (ds.working_counter != domain_input_state.working_counter)
        printf("Domain1: WC %u.\n", ds.working_counter);
    if (ds.wc_state != domain_input_state.wc_state)
        printf("Domain_input: State %u.\n", ds.wc_state);

    domain_input_state = ds;
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
    ecrt_domain_process(domain_output);
    ecrt_domain_process(domain_input);


    // check process data state (optional)
    check_domain1_state();

    if (counter) {
        counter--;
    } else { // do this at 1 Hz

        counter = FREQUENCY;

        // check for master state (optional)
        check_master_state();

        // check for islave configuration state(s) (optional)
        check_slave_config_states();


    // read process data
//        {0x6040, 0x00, 16}, /* Controlword */
//        {0x6060, 0x00, 8}, /* Mode_of_Operation */
//        {0x6098, 0x00, 8}, /* Homing_Method */
//        {0x607a, 0x00, 32}, /* Target_Position */
//        {0x60ff, 0x00, 32}, /* Target_Velocity */
//        {0x6071, 0x00, 16}, /* Target_Torque */
//        {0x6041, 0x00, 16}, /* Statusword */
//        {0x6064, 0x00, 32}, /* Position_Actual_Value */
//        {0x6061, 0x00, 8}, /* Modes_Of_Operation_Display */
//        {0x1001, 0x00, 8}, /* Error_Register */
//        {0x606c, 0x00, 32}, /* Velocity_Actual_Value */
//        {0x6077, 0x00, 16}, /* Torque_Actual_Value */
//        printf("pdo value: %02x offset %u\n",
//                EC_READ_U16(domain1_pd + off_0x6040),off_0x6040);
//        printf("pdo value: %02x offset %u\n",
//                EC_READ_U16(domain1_pd + off_0x1001),off_0x1001);
    printf("pdo value: %04x offset %u\n",
            EC_READ_U16(domain_input_pd + off_0x6041),off_0x6041);
    printf("pdo value 6061asfsadf: %04x offset %u\n",
            EC_READ_U8(domain_input_pd + off_0x6061),off_0x6061);
    printf("pd: %u \n",*domain_input_pd);
//            EC_READ_U8(domain1_pd + off_ana_in_value));

#if SDO_ACCESS
        // read process data SDO
        read_sdo();
#endif


    }


    // send process data
    ecrt_domain_queue(domain_output);
    ecrt_domain_queue(domain_input);
    ecrt_master_send(master);
#if 0
    // write process data
//    EC_WRITE_U8(domain1_pd + off_dig_out, blink ? 0x06 : 0x09);
#endif


}

/****************************************************************************/

void signal_handler(int signum) {
    switch (signum) {
        case SIGALRM:
            sig_alarms++;
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

    domain_input = ecrt_master_create_domain(master);
    domain_output = ecrt_master_create_domain(master);
    if (!domain_input || !domain_output)
    {
        return -1;
    }

    if (!(sc_ana_in = ecrt_master_slave_config(master, AliasAndPositon, VendorID_ProductCode)))
    {
        fprintf(stderr, "Failed to get slave configuration.\n");
        return -1;
    }

#if SDO_ACCESS
    fprintf(stderr, "Creating SDO requests...\n");
    if (!(sdo = ecrt_slave_config_create_sdo_request(sc_ana_in, 0x6061, 0, 1))) // data size 1 ?
    {
        fprintf(stderr, "Failed to create SDO modes_of_operation_display 0x6061 request.\n");
        return -1;
    }
    //EC_WRITE_U16(ecrt_sdo_request_data(sdo), 0xFFFF);

    ecrt_sdo_request_timeout(sdo, 500); // ms
#endif

#if 1
    printf("Configuring PDOs...\n");
    if (ecrt_slave_config_pdos(sc_ana_in, EC_END, slave_0_syncs)) {
        fprintf(stderr, "Failed to configure PDOs.\n");
        return -1;
    }
#endif

    if (ecrt_domain_reg_pdo_entry_list(domain_output, domain_output_regs)) {
            fprintf(stderr, "Output PDO entry registration failed!\n");
            return -1;
        }
    if (ecrt_domain_reg_pdo_entry_list(domain_input, domain_input_regs)) {
            fprintf(stderr, "Input PDO entry registration failed!\n");
            return -1;
        }

    printf("Activating master...\n");
    if (ecrt_master_activate(master))
        return -1;

//    if (!(domain_output_pd = ecrt_domain_data(domain_output))) {
//        return -1;
//    }
    if (!(domain_output_target_velocity_pd = ecrt_domain_data(domain_output_target_velocity))) {
        return -1;
    }
    if (!(domain_input_pd = ecrt_domain_data(domain_input))) {
        return -1;
    }

#if PRIORITY
    pid_t pid = getpid();
    if (setpriority(PRIO_PROCESS, pid, -19))
        fprintf(stderr, "Warning: Failed to set priority: %s\n",
                strerror(errno));
#endif

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
