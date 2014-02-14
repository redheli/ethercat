#include "etherlab.h"

fm_auto::DuetflEthercatController::DuetflEthercatController()
{

}
bool fm_auto::DuetflEthercatController::init()
{
    FREQUENCY = 300;

    ROS_INFO("Starting timer...\n");
    tv.it_interval.tv_sec = 0;
    tv.it_interval.tv_usec = 1000000 / FREQUENCY;
    tv.it_value.tv_sec = 0;
    tv.it_value.tv_usec = 1000;
    if (setitimer(ITIMER_REAL, &tv, NULL)) {
        fprintf(stderr, "Failed to start timer: %s\n", strerror(errno));
        return false;
    }
}

void fm_auto::DuetflEthercatController::run()
{
    while (1) {
        pause();

        ros::spinOnce();

        while (sig_alarms != user_alarms) {
            cyclic_task();
            user_alarms++;
        }
    }
}

void fm_auto::DuetflEthercatController::cyclic_task()
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


        // read process data SDO
       read_sdo();


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

fm_auto::HOMING_METHOD fm_auto::DuetflEthercatController::getMotorHomingMode(const ec_slave_config_t *slave_config)
{
    fm_auto::HOMING_METHOD m;

    return m;

}

fm_auto::OPERATIN_MODE fm_auto::DuetflEthercatController::getMotorOperatingMode(const ec_slave_config_t *slave_config)
{

}
