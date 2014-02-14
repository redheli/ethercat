#include "etherlab.h"

void signal_handler(int signum) {
//    fprintf(stderr,"signal_handler \n");
    switch (signum) {
        case SIGALRM:
            sig_alarms++;
            break;
    case SIGINT:
        fprintf(stderr,"use ctrl+c ,need do something \n");
        // disable the operation
        // send 0x0007 to controlword
        break;
    }
}
void my_sig_handler(int signum) {
    ROS_INFO("my_sig_handler <%d>\n",signum);
    switch (signum) {
        case SIGINT:
            fprintf(stderr,"use ctrl+c ,need do something before exit\n");
            // disable the operation
            // send 0x0002 to controlword
            disable_operation();
            exit(-1);
            break;
    }
}

fm_auto::DuetflEthercatController::DuetflEthercatController()
    : domain_input(NULL),domain_output(NULL),master(NULL)
{

}
bool fm_auto::DuetflEthercatController::init()
{
    FREQUENCY = 300; //hz

    ROS_INFO("Starting timer...\n");
    tv.it_interval.tv_sec = 0;
    tv.it_interval.tv_usec = 1000000 / FREQUENCY;
    tv.it_value.tv_sec = 0;
    tv.it_value.tv_usec = 1000;
    if (setitimer(ITIMER_REAL, &tv, NULL)) {
        ROS_ERROR("Failed to start timer: %s\n", strerror(errno));
        return false;
    }

    // init ethercat
    if(!initEthercat())
    {
        return false;
    }

    return true;
}
bool fm_auto::DuetflEthercatController::initEthercat()
{
    // we only have one master,who is g...
    master = ecrt_request_master(0);
    if (!master)
    {
        return -1;
    }

    if(!initSDOs())
    {
        ROS_ERROR("init sdos failed!\n");
        return false;
    }

    // two domains
    domain_input = ecrt_master_create_domain(master);
    domain_output = ecrt_master_create_domain(master);

    if (!domain_input || !domain_output)
    {
        ROS_ERROR("init domain failed!\n");
        return false;
    }

    ROS_INFO("Activating master...\n");
    if (ecrt_master_activate(master))
    {
        ROS_ERROR("active master failed!\n");
        return false;
    }

    // set pid priority
    pid_t pid = getpid();
    if (setpriority(PRIO_PROCESS, pid, -19))
    {
        ROS_ERROR("Warning: Failed to set priority: %s\n",
                strerror(errno));
    }

    // domain entry list
    if (ecrt_domain_reg_pdo_entry_list(domain_output, fm_auto::domain_output_regs)) {
        ROS_ERROR("Output PDO entry registration failed!\n");
        return false;
    }
    if (ecrt_domain_reg_pdo_entry_list(domain_input, fm_auto::domain_input_regs)) {
        ROS_ERROR("Input PDO entry registration failed!\n");
        return false;
    }

    // signal handler
    // handle ctrl+c important
    if (signal(SIGINT, my_sig_handler) == SIG_ERR)
    {
            ROS_ERROR("\ncan't catch SIGUSR1\n");
            return false;
    }

    // get alarm to control frequcy
    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGALRM, &sa, 0)) {
        fprintf(stderr, "Failed to install signal handler!\n");
        return -1;
    }
}

void fm_auto::DuetflEthercatController::run()
{
    while (1) {
        pause();

        ros::spinOnce();

//        while (sig_alarms != user_alarms) {
            cyclic_task();
//            user_alarms++;
//        }
    }
}
bool fm_auto::DuetflEthercatController::sendOneSDO()
{
    ecrt_master_receive(master);

    ecrt_master_send(master);
}

void fm_auto::DuetflEthercatController::cyclic_task()
{
    // receive process data
    ecrt_master_receive(master);
    ecrt_domain_process(domain_output);
    ecrt_domain_process(domain_input);


    // check process data state (optional)
    check_domain1_state();

        // check for master state (optional)
        check_master_state();

        // check for islave configuration state(s) (optional)
        check_slave_config_states();

        // check has sdos to send?
        // check sdos states

        // check has pdos to send
        // check pdos states


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


    // send process data
    ecrt_domain_queue(domain_output);
    ecrt_domain_queue(domain_input);
    ecrt_master_send(master);

    // write process data
//    EC_WRITE_U8(domain1_pd + off_dig_out, blink ? 0x06 : 0x09);


}

fm_auto::HOMING_METHOD fm_auto::DuetflEthercatController::getMotorHomingMode(const ec_slave_config_t *slave_config)
{
    fm_auto::HOMING_METHOD m;

    return m;

}

fm_auto::OPERATIN_MODE fm_auto::DuetflEthercatController::getMotorOperatingMode(const ec_slave_config_t *slave_config)
{

}
