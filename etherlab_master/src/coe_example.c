/*****************************************************************************
 * Mini example of PDO mapping with drive AKD Kollmorgen
 * The program maps some PDOs to monitor actual values of the drive
 *
 * Date: 2012-04-12 , Author: Sebastien BLANCHET
 *
 * Based on a previous example from IgH EtherCAT Master
 ****************************************************************************/

#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include "ecrt.h"

/****************************************************************************/

// Application parameters
#define FREQUENCY 100

/* EtherCAT */
static ec_master_t *master = NULL;
static ec_domain_t *domain1 = NULL;
static uint8_t *domain1_pd = NULL; /* process data */

static ec_slave_config_t *sc_akd = NULL;


#define AkdSlavePos    11,0
#define Kollmorgen_AKD  0x0000006a, 0x00414b44

/* Offsets for PDO entries */
static unsigned int off_akd_ctrlword;

static unsigned int off_akd_status;
static unsigned int off_akd_analog_in;
static unsigned int off_akd_digital_in;
static unsigned int off_akd_act_velocity;
static unsigned int off_akd_act_pos;

const static ec_pdo_entry_reg_t domain1_regs[] = {
    {AkdSlavePos, Kollmorgen_AKD, 0x6040, 0, &off_akd_ctrlword},

    {AkdSlavePos, Kollmorgen_AKD, 0x6041, 0, &off_akd_status},
    {AkdSlavePos, Kollmorgen_AKD, 0x3470, 4, &off_akd_analog_in},
    {AkdSlavePos, Kollmorgen_AKD, 0x60FD, 0, &off_akd_digital_in},
    {AkdSlavePos, Kollmorgen_AKD, 0x606C, 0, &off_akd_act_velocity},
    {AkdSlavePos, Kollmorgen_AKD, 0x6063, 0, &off_akd_act_pos},
    {}
};

/* AKD */
ec_pdo_entry_info_t akd_pdo_entries[] = {
    /* RxPdo 0x1600 */
    {0x6040, 0x00, 16}, /* ctrl word */
    {0x60c1, 0x01, 32}, /* interpolation data record */

    /* TxPDO 0x1a00 */
    {0x6041, 0x00, 16}, /* status word */
    {0x3470, 0x04, 16}, /* analog input */
    {0x60fd, 0x00, 32}, /* digital input */

    /* TxPDO 0x1a01 */
    {0x606C, 0x00, 32}, /* actual velocity, in rpm */
    {0x6063, 0x00, 32}, /* actual position */
};

ec_pdo_info_t akd_pdos[] = {
    {0x1600, 2, akd_pdo_entries + 0}, 
    {0x1a00, 3, akd_pdo_entries + 2}, 
    {0x1a01, 2, akd_pdo_entries + 5},
};

ec_sync_info_t akd_syncs[] = {
    {0, EC_DIR_OUTPUT, 0, NULL, EC_WD_DISABLE},
    {1, EC_DIR_INPUT, 0, NULL, EC_WD_DISABLE},
    {2, EC_DIR_OUTPUT, 1, akd_pdos + 0, EC_WD_DISABLE},
    {3, EC_DIR_INPUT, 2, akd_pdos + 1, EC_WD_DISABLE},
    {0xff}
};


/****************************************************************************/

void cyclic_task()
{
    static unsigned int counter = 0;

    /* receive process data */
    ecrt_master_receive(master);
    ecrt_domain_process(domain1);

    if (counter) {
        counter--;
    } else { /* do this at 1 Hz */
        counter = FREQUENCY;
       /* read process data */

       printf("AKD act_velocity = %8.3f rpm, act_pos = %d , %10.3f\n",
	   EC_READ_S32(domain1_pd + off_akd_act_velocity)/1000.0,
	   EC_READ_S32(domain1_pd + off_akd_act_pos),
	   EC_READ_S32(domain1_pd + off_akd_act_pos)/16.0
       );

       printf( "AKD analog in = %x %3.3f V, DigitalIn = %x\n",
	   EC_READ_S16(domain1_pd + off_akd_analog_in),
	   EC_READ_S16(domain1_pd + off_akd_analog_in)*5.0/0x3300,
	   EC_READ_U32(domain1_pd + off_akd_digital_in)
       );
    }
    /* send process data */
    ecrt_domain_queue(domain1);
    ecrt_master_send(master);
}

/****************************************************************************/

int main(int argc, char **argv)
{   
    master = ecrt_request_master(0);
    if (!master)
        return -1;

    domain1 = ecrt_master_create_domain(master);
    if (!domain1)
        return -1;

    if (!(sc_akd = ecrt_master_slave_config(
                    master, AkdSlavePos, Kollmorgen_AKD))) {
        fprintf(stderr, "Failed to get slave configuration for AKD.\n");
        return -1;
    }

    /* Configure AKD free PDO */
    printf("Configuring AKD with free PDO...\n");
    /* Clear RxPdo */
    ecrt_slave_config_sdo8( sc_akd, 0x1C12, 0, 0 ); /* clear sm pdo 0x1c12 */
    ecrt_slave_config_sdo8( sc_akd, 0x1600, 0, 0 ); /* clear RxPdo 0x1600 */
    ecrt_slave_config_sdo8( sc_akd, 0x1601, 0, 0 ); /* clear RxPdo 0x1601 */
    ecrt_slave_config_sdo8( sc_akd, 0x1602, 0, 0 ); /* clear RxPdo 0x1602 */
    ecrt_slave_config_sdo8( sc_akd, 0x1603, 0, 0 ); /* clear RxPdo 0x1603 */

    /* Define RxPdo */
    ecrt_slave_config_sdo32( sc_akd, 0x1600, 1, 0x60400010 ); /* 0x6040:0/16bits, control word */ 
    ecrt_slave_config_sdo32( sc_akd, 0x1600, 2, 0x60C10120 ); /* 0x60C1:1/32bits */ 
    ecrt_slave_config_sdo8( sc_akd, 0x1600, 0, 2 ); /* set number of PDO entries for 0x1600 */

    ecrt_slave_config_sdo16( sc_akd, 0x1C12, 1, 0x1600 ); /* list all RxPdo in 0x1C12:1-4 */
    ecrt_slave_config_sdo8( sc_akd, 0x1C12, 0, 1 ); /* set number of RxPDO */

    /* Clear TxPdo */
    ecrt_slave_config_sdo8( sc_akd, 0x1C13, 0, 0 ); /* clear sm pdo 0x1c13 */
    ecrt_slave_config_sdo8( sc_akd, 0x1A00, 0, 0 ); /* clear TxPdo 0x1A00 */
    ecrt_slave_config_sdo8( sc_akd, 0x1A01, 0, 0 ); /* clear TxPdo 0x1A01 */
    ecrt_slave_config_sdo8( sc_akd, 0x1A02, 0, 0 ); /* clear TxPdo 0x1A02 */
    ecrt_slave_config_sdo8( sc_akd, 0x1A03, 0, 0 ); /* clear TxPdo 0x1A03 */

    /* Define TxPdo */
    ecrt_slave_config_sdo32( sc_akd, 0x1A00, 1, 0x60410010 ); /* 0x6041:0/16bits, status word */ 
    ecrt_slave_config_sdo32( sc_akd, 0x1A00, 2, 0x34700410 ); /* 0x3470:4/16bits, analog input */ 
    ecrt_slave_config_sdo32( sc_akd, 0x1A00, 3, 0x60FD0020 ); /* 0x60FD:0/32bits, digital inputs */ 
    ecrt_slave_config_sdo8( sc_akd, 0x1A00, 0, 3 ); /* set number of PDO entries for 0x1A00 */

    ecrt_slave_config_sdo32( sc_akd, 0x1A01, 1, 0x606C0020 ); /* 0x606c:0/32bits, act velocity */ 
    ecrt_slave_config_sdo32( sc_akd, 0x1A01, 2, 0x60630020 ); /* 0x6063:0/32bits, act position */ 
    ecrt_slave_config_sdo8( sc_akd, 0x1A01, 0, 2 ); /* set number of PDO entries for 0x1A01 */

    ecrt_slave_config_sdo16( sc_akd, 0x1C13, 1, 0x1A00 ); /* list all TxPdo in 0x1C13:1-4 */
    ecrt_slave_config_sdo16( sc_akd, 0x1C13, 2, 0x1A01 ); /* list all TxPdo in 0x1C13:1-4 */
    ecrt_slave_config_sdo8( sc_akd, 0x1C13, 0, 2 ); /* set number of TxPDO */


	
    printf("Configuring PDOs...\n");
    if (ecrt_slave_config_pdos(sc_akd, EC_END, akd_syncs)) {
        fprintf(stderr, "Failed to configure AKD PDOs.\n");
        return -1;
    }
	
    if (ecrt_domain_reg_pdo_entry_list(domain1, domain1_regs)) {
        fprintf(stderr, "PDO entry registration failed!\n" );
        return -1;
    }
	
    printf("Activating master...\n");
    if (ecrt_master_activate(master))
        return -1;

    if (!(domain1_pd = ecrt_domain_data(domain1))) {
        return -1;
    }

    printf("Started.\n");
    while (1) {
	usleep( 1000000 / FREQUENCY );
	cyclic_task();
    }

    return 0;
}

/****************************************************************************/
