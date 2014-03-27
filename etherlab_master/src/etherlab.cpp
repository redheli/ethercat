#include "etherlab.h"

void fm_auto::DuetflEthercatController::signal_handler(int signum) {
//    fprintf(stderr,"signal_handler \n");
    switch (signum) {
        case SIGALRM:
//            sig_alarms++;
            break;
    case SIGINT:
        ROS_INFO_ONCE("user ctrl+c ,need do something \n");
        // disable the operation
        // send 0x0002 to controlword
//        uint16_t value = 0x0002;
//        writeSdoControlword(value);
        disableControlSDO(slave0_statusword_fmsdo,slave0_controlword_fmsdo);
        break;
    }
}
//void fm_auto::DuetflEthercatController::writeSdoControlword(uint16_t &value)
//{
//    static ec_sdo_request_t *slave0_sdo_controlword_write;
//}

void fm_auto::DuetflEthercatController::my_sig_handler(int signum) {
    ROS_INFO("my_sig_handler <%d>\n",signum);
    switch (signum) {
        case SIGINT:
            fprintf(stderr,"use ctrl+c ,need do something before exit\n");
            // disable the operation
            // send 0x0002 to controlword
//            disable_operation();
            disableControlSDO(fm_auto::slave0_statusword_fmsdo,fm_auto::slave0_controlword_fmsdo);
            exit(-1);
            break;
    }
}
bool fm_auto::DuetflEthercatController::goToPositionNewSetPoint_SDO_SlaveZero()
{
    //make sure controller enabled, bit 4 of controlword is not set
    // write 0x1f to controlword
    uint16_t value = 0x1f;
    if(!setControlwordSDO(fm_auto::slave0_controlword_fmsdo,value))
    {
        ROS_ERROR("goToPositionNewSetPoint_SlaveZero: set controlword 0x1f failed");
        return false;
    }
    return true;
}
bool fm_auto::DuetflEthercatController::clearNewSetPoint_ChangeSetPoint_SDO_SlaveZero()
{
    // write 0 to bit 4 of controlword,assume controller enabled
    uint16_t value = 0x0f;
    if(setControlwordSDO(fm_auto::slave0_controlword_fmsdo,value))
    {
        ROS_ERROR("clearNewSetPoint_SlaveZero: set controlword 0x0f failed");
        return false;
    }
    return true;
}

bool fm_auto::DuetflEthercatController::goToPositionChangeSetImt_SDO_SlaveZero()
{
    //make sure controller enabled, bit 4 and bit 5 of controlword are not set
    // write 0x003f to controlword
    uint16_t value = 0x3f;
    if(setControlwordSDO(fm_auto::slave0_controlword_fmsdo,value))
    {
        ROS_ERROR("goToPositionChangeSetImt_SlaveZero: set controlword 0x3f failed");
        return false;
    }
    // write 0x000f to controlword
    value = 0x000f;
    if(setControlwordSDO(fm_auto::slave0_controlword_fmsdo,value))
    {
        ROS_ERROR("goToPositionChangeSetImt_SlaveZero: set controlword 0xf failed");
        return false;
    }
    return true;
}

bool fm_auto::DuetflEthercatController::setSlaveZeroTargetPosition(int32_t &value)
{
//    int8_t v=(int8_t)value;
    EC_WRITE_S32(ecrt_sdo_request_data(fm_auto::slave0_target_position_fmsdo->sdo), value);
//    ecrt_master_send(master);
    sendOneWriteSDO(fm_auto::slave0_target_position_fmsdo);
    if(!waitSDORequestSuccess(fm_auto::slave0_target_position_fmsdo,WRITE))
    {
        ROS_ERROR("setMotorHomingModeSDO: set homing method %d failed",value);
    }
    return true;
}
bool fm_auto::DuetflEthercatController::getSlaveZeroTargetPositionSetting(int32_t &target_position)
{

}

bool fm_auto::DuetflEthercatController::getPositionActualValue(fm_sdo* position_actual_value_fmSdo,
                                                               int32_t &value)
{
    //1. send read sdo request
    sendOneReadSDO(position_actual_value_fmSdo);
    if(waitSDORequestSuccess(position_actual_value_fmSdo,READ))
    {
        value = EC_READ_S32(ecrt_sdo_request_data(position_actual_value_fmSdo->sdo));
        ROS_INFO("get statusword: 0x%08x %d",value,value);
        return true;
    }
    else
    {
        ROS_ERROR("getPositionActualValue failed");
    }
    return false;
}

//void fm_auto::DuetflEthercatController::disable_operation()
//{
//    //TODO
//}
fm_auto::DuetflEthercatController::DuetflEthercatController()
    : domain_input(NULL),domain_output(NULL),domain_output_target_velocity(NULL),steering_cmd_current(0),steering_cmd_new(0),braking_cmd_new(0),needWrite_0xf_2controlword(false),
      positionControlState(6),hasNewSteeringData(false),PDO_OK(true),restTick(1),controlword_PDO(0xf),velocity_actual_value(0)
{
    dt=0.0;
    hasSlaveOne = false;

    needDoHoming_SlaveZero = false;
    needDoHoming_SlaveOne = false;

    steering_slave_number = 1;
    braking_slave_number = 0;
}
fm_auto::DuetflEthercatController::~DuetflEthercatController()
{
    ROS_INFO_ONCE("DuetflEthercatController exit... \n");
    // disable the operation
    // send 0x0002 to controlword
    disableControlSDO(slave0_statusword_fmsdo,slave0_controlword_fmsdo);
}

bool fm_auto::DuetflEthercatController::init()
{
    FREQUENCY = 300; //hz

    initROS();

    // init ethercat master and slave zero and slave one
    if(!initEthercat())
    {
        ROS_ERROR("Failed to init ethercat slave zero: %s\n", strerror(errno));
        return false;
    }

//    // slave zero(steering motor) position zero
//    // 1. set operating mode to homing
//    if(!setSlaveZeroMotorOperatingMode2Homing())
//    {
//        ROS_ERROR("init: setSlaveZeroMotorOperatingMode2Homing failed");
//        return false;
//    }
//    // 2. enable controller
//    if(!enableControlSDO(slave0_statusword_fmsdo,slave0_controlword_fmsdo))
//    {
//        ROS_ERROR("init: enableControlSDO failed");
//        return false;
//    }
//    // 3. trigger homing operation
//    if(!operateSteeringMotorHomingMethod())
//    {
//        ROS_ERROR("init: operateSteeringMotorHomingMethod failed");
//        return false;
//    }

    return true;
}
bool fm_auto::DuetflEthercatController::setHomingMethod2CurrentPosition(fm_sdo *homing_method_fmSdo)
{
    fm_auto::HOMING_METHOD hm;
    if(!getMotorHomingMethodSDO(homing_method_fmSdo,hm))
    {
        ROS_ERROR("operateHomingMethod: get homing method failed");
    }
    if(hm != fm_auto::HM_current_position)
    {
//        ros::Time time_begin = ros::Time::now();
//        while(hm != HM_current_position)
//        {
            ROS_INFO("homing method not current position: %d",hm);
            fm_auto::HOMING_METHOD hm35 = fm_auto::HM_current_position;
            if(setMotorHomingModeSDO(homing_method_fmSdo,hm35))
            {
                ROS_ERROR("operateHomingMethod: set homing method failed");
                return false;
            }
    }
    // recheck
    fm_auto::HOMING_METHOD hm2 = fm_auto::HM_fail;
    if(!getMotorHomingMethodSDO(homing_method_fmSdo,hm2))
    {
        ROS_ERROR("operateHomingMethod: get homing method failed");
        return false;
    }
    if(hm2 != fm_auto::HM_current_position)
    {
        ROS_ERROR("operateHomingMethod: homing method not 35,after set, is %d",hm2);
        return false;
    }
    return true;
}

bool fm_auto::DuetflEthercatController::operateSteeringMotorHomingMethod_SlaveZero()
{
    // TODO: check operating mode , is homging
    //
    // set homing_method to current position
    if(!setHomingMethod2CurrentPosition(slave0_homing_method_fmSdo))
    {
        ROS_ERROR("operateHomingMethod: set homing method failed");
        return false;
    }
    // check controller enabled
//    if(!enableControlSDO(slave0_statusword_fmsdo,slave0_controlword_fmsdo))
//    {
//        ROS_ERROR("operateSteeringMotorHomingMethod: enable controller failed");
//    }

    // trigger home position
//     //1.0 set controlword bit 4: 0
//    uint16_t c = 0x00;
//    setControlwordSDO(slave0_controlword_fmsdo,c);
//    // 1.1 check statusword bit 13 has homing_error
//    uint16_t statusword_value;
//    if(!getStatuswordSDO(slave0_statusword_fmsdo,statusword_value))
//    {
//        ROS_ERROR("operateHomingMethod: get statusword failed");
//        return false;
//    }
//    if(Int16Bits(statusword_value).test(13))
//    {
//        //has error
//        //TODO handle error
//        ROS_ERROR("set controlword 0x00 has error");
//    }
    // 2.0 set controlword bit 4: 1, start homing operation
    uint16_t c = 0x1f;
    if(!setControlwordSDO(slave0_controlword_fmsdo,c))
    {
        ROS_ERROR("operateSteeringMotorHomingMethod: set controlword failed 0x04x",c);
        return false;
    }
    uint16_t statusword_value;
    if(!getStatuswordSDO(slave0_statusword_fmsdo,statusword_value))
    {
        ROS_ERROR("operateSteeringMotorHomingMethod: get statusword failed ");
        return false;
    }
    // 2.1 check statusword bit 13 has homing_error
    if(Int16Bits(statusword_value).test(13))
    {
        //has error
        //TODO handle error
        ROS_ERROR("set controlword 0x10 has error");
        return false;
    }
    // 2.2 check statusword bit 12 =1 , executed successfully
    ros::Time time_begin = ros::Time::now();
    bool is_success=false;
    while(!is_success)
    {
        ROS_INFO("check homing operation successful");
        uint16_t statusword_value = 0x0000;
        if(!getStatuswordSDO(slave0_statusword_fmsdo,statusword_value))
        {
            ROS_ERROR("get statusword failed");
            return false;
        }
        if(Int16Bits(statusword_value).test(12) && !Int16Bits(statusword_value).test(13)) //p106
        {
            is_success = true;
            ROS_INFO("homing operation success!");
            break;
        }
        ros::Time time_now = ros::Time::now();
        if( (time_now.toSec() - time_begin.toSec()) > 10 ) // 10 sec
        {
            ROS_ERROR("homing operation timeout");
            break;
        }
    }
    if(is_success)
    {
        //check actual position value 0x6064 ,shall be zero
        int32_t positionValue=0xff;
        if(getPositionActualValue(slave0_position_actual_value_fmsdo,positionValue))
        {
            ROS_INFO("operateSteeringMotorHomingMethod: position actual value 0x%08x %d",positionValue,positionValue);
        }
        else
        {
            ROS_ERROR("operateSteeringMotorHomingMethod: get position_actual_value failed");
            return false;
        }
    }
    //
    return is_success;
}
bool fm_auto::DuetflEthercatController::operateSteeringMotorHomingMethod_SlaveOne()
{
    // TODO: check operating mode , is homging
    //
    // set homing_method to current position
    if(!setHomingMethod2CurrentPosition(slave1_homing_method_fmSdo))
    {
        ROS_ERROR("operateSteeringMotorHomingMethod_SlaveOne: set homing method failed");
        return false;
    }

    // 2.0 set controlword bit 4: 1, start homing operation
    uint16_t c = 0x1f;
    if(!setControlwordSDO(slave1_controlword_fmsdo,c))
    {
        ROS_ERROR("operateSteeringMotorHomingMethod_SlaveOne: set controlword failed 0x04x",c);
        return false;
    }
    uint16_t statusword_value;
    if(!getStatuswordSDO(slave1_statusword_fmsdo,statusword_value))
    {
        ROS_ERROR("operateSteeringMotorHomingMethod_SlaveOne: get statusword failed ");
        return false;
    }
    // 2.1 check statusword bit 13 has homing_error
    if(Int16Bits(statusword_value).test(13))
    {
        //has error
        //TODO handle error
        ROS_ERROR("operateSteeringMotorHomingMethod_SlaveOne: set controlword 0x10 has error");
        return false;
    }
    // 2.2 check statusword bit 12 =1 , executed successfully
    ros::Time time_begin = ros::Time::now();
    bool is_success=false;
    while(!is_success)
    {
        ROS_INFO("operateSteeringMotorHomingMethod_SlaveOne: check homing operation successful");
        uint16_t statusword_value = 0x0000;
        if(!getStatuswordSDO(slave1_statusword_fmsdo,statusword_value))
        {
            ROS_ERROR("get statusword failed");
            return false;
        }
        if(Int16Bits(statusword_value).test(12) && !Int16Bits(statusword_value).test(13)) //p106
        {
            is_success = true;
            ROS_INFO("homing operation success!");
            break;
        }
        ros::Time time_now = ros::Time::now();
        if( (time_now.toSec() - time_begin.toSec()) > 10 ) // 10 sec
        {
            ROS_ERROR("homing operation timeout");
            break;
        }
    }
    if(is_success)
    {
        //check actual position value 0x6064 ,shall be zero
        int32_t positionValue=0xff;
        if(getPositionActualValue(slave1_position_actual_value_fmsdo,positionValue))
        {
            ROS_INFO("operateSteeringMotorHomingMethod_SlaveOne: position actual value 0x%08x %d",positionValue,positionValue);
        }
        else
        {
            ROS_ERROR("operateSteeringMotorHomingMethod_SlaveOne: get position_actual_value failed");
            return false;
        }
    }
    //
    return is_success;
}
bool fm_auto::DuetflEthercatController::getStatuswordSDO(fm_auto::fm_sdo *statusword_fmsdo,uint16_t &value)
{
//    uint16_t method_value=0x0000;
    //1. send read sdo request
    sendOneReadSDO(statusword_fmsdo);
    if(waitSDORequestSuccess(statusword_fmsdo,READ))
    {
        value = EC_READ_U16(ecrt_sdo_request_data(statusword_fmsdo->sdo));
//        ROS_INFO("get statusword: 0x%04x %d",value,value);
        return true;
    }
    else
    {
        ROS_ERROR("getStatuswordSDO failed");
    }
    return false;
}
bool fm_auto::DuetflEthercatController::setControlwordSDO(fm_auto::fm_sdo *controlword_fmsdo, uint16_t &value)
{
    EC_WRITE_U16(ecrt_sdo_request_data(controlword_fmsdo->sdo), value);
    sendOneWriteSDO(controlword_fmsdo);
    if(waitSDORequestSuccess(controlword_fmsdo,false))
    {
        ROS_INFO("setControlword 0x%04x ok",value);
        return true;
    }
    ROS_ERROR("setControlword 0x%04x failed",value);
    return false;
}
bool fm_auto::DuetflEthercatController::getControllerStateByStatusword(uint16_t &value, fm_auto::CONTROLLER_STATE &state)
{
    uint16_t withMask004F = value & 0x004F;
//    ROS_INFO("with mask 004F: value 0x%04x masked 0x%04x ",value,withMask004F);
    if(withMask004F == fm_auto::CS_FAULT)
    {
        ROS_INFO_ONCE("CS_FAULT");
        state = fm_auto::CS_FAULT;
        return true;
    }
    if( withMask004F == fm_auto::CS_NOT_READY_TO_SWITCH_ON)
    {
        ROS_INFO("getControllerStateByStatusword: CS_NOT_READY_TO_SWITCH_ON");
        state = fm_auto::CS_NOT_READY_TO_SWITCH_ON;
        return true;
    }
    if(withMask004F == fm_auto::CS_SWITCH_ON_DISABLED)
    {
        ROS_INFO("CS_SWITCH_ON_DISABLED");
        state = fm_auto::CS_SWITCH_ON_DISABLED;
        return true;
    }
    //
    uint16_t withMask006F = value & 0x006F;
//    ROS_INFO("with mask 006F: 0x%04x ",withMask006F);
    if(withMask006F == fm_auto::CS_READY_TO_SWITCH_ON)
    {
        ROS_INFO("CS_READY_TO_SWITCH_ON");
        state = fm_auto::CS_READY_TO_SWITCH_ON;
        return true;
    }
    if(withMask006F == fm_auto::CS_SWITCH_ON)
    {
        ROS_INFO("CS_SWITCH_ON");
        state = fm_auto::CS_SWITCH_ON;
        return true;
    }
    if(withMask006F == fm_auto::CS_OPERATION_ENABLE)
    {
//        ROS_INFO("CS_OPERATION_ENABLE");
        state = fm_auto::CS_OPERATION_ENABLE;
        return true;
    }
    ROS_ERROR("unknow controller state 0x%04x",value);
    return false;

}
bool fm_auto::DuetflEthercatController::getMotorOperatingModeSDO(fm_sdo *operation_mode_display_fmsdo,
                                                                 fm_auto::OPERATION_MODE &mode)
{
    int8_t mode_value=0x00;
    //1. send read sdo request
    if(!sendOneReadSDO(operation_mode_display_fmsdo))
    {
        ROS_ERROR("sendOneReadSDO failed");
        return false;
    }
//    bool isGetValue=false;
//    ros::Time time_begin = ros::Time::now();
//    ROS_INFO("getMotorHomingModeSDO %f",time_begin.toSec());
//    ros::Rate loop_rate(100);
//    ROS_INFO("getMotorHomingModeSDO spinOnce");
    if(waitSDORequestSuccess(operation_mode_display_fmsdo,READ))
    {
        mode_value = EC_READ_S8(ecrt_sdo_request_data(operation_mode_display_fmsdo->sdo));
        ROS_INFO("get operation mode: 0x%02x %d",mode_value,mode_value);
        mode = (fm_auto::OPERATION_MODE)mode_value;
        return true;
    }
    else
    {
        ROS_ERROR("getMotorOperatingModeSDO failed");
        return false;
    }
}
bool fm_auto::DuetflEthercatController::setMotorOperatingModeSDO(fm_sdo *sdo_operation_mode_write,
                                                                 fm_auto::OPERATION_MODE &value)
{
    int8_t v=(int8_t)value;
    EC_WRITE_S8(ecrt_sdo_request_data(sdo_operation_mode_write->sdo), v);
//    ecrt_master_send(master);
    sendOneWriteSDO(sdo_operation_mode_write);
    if(!waitSDORequestSuccess(sdo_operation_mode_write,false))
    {
        ROS_ERROR("setMotorHomingModeSDO: set homing method %d failed",value);
    }
    return true;
}
bool fm_auto::DuetflEthercatController::setSlaveZeroMotorOperatingMode2ProfileVelocity()
{
    //1. check current operation mode
    fm_auto::OPERATION_MODE operation_mode = fm_auto::OM_UNKNOW_MODE;
    if(!getMotorOperatingModeSDO(fm_auto::slave0_operation_mode_display_fmsdo,operation_mode))
    {
        ROS_ERROR("setSlaveZeroMotorOperatingMode2ProfileVelocity: get mode failed");
        return false;
    }
//ROS_INFO("dddd1.1   %d",operation_mode);
    if(operation_mode != fm_auto::OM_PROFILE_VELOCITY_MODE)
    {
        //2. set mode to profile velocity
        fm_auto::OPERATION_MODE value = fm_auto::OM_PROFILE_VELOCITY_MODE;
        if(!setMotorOperatingModeSDO(slave0_operation_mode_write_fmsdo,value))
        {
            ROS_ERROR("setSlaveZeroMotorOperatingMode2ProfileVelocity: set mode failed");
            return false;
        }
    }
//ROS_INFO("dddd1.2");
    //3. verify
    operation_mode = fm_auto::OM_UNKNOW_MODE;
    if(!getMotorOperatingModeSDO(slave0_operation_mode_display_fmsdo,operation_mode))
    {
        ROS_ERROR("setSlaveZeroMotorOperatingMode2ProfileVelocity: get mode failed 2");
        return false;
    }
    if(operation_mode != fm_auto::OMD_PROFILE_VELOCITY_MODE)
    {
        ROS_ERROR("setSlaveZeroMotorOperatingMode2ProfileVelocity: mode is not profile velocity after set %d\n",operation_mode);
        return false;
    }
    ROS_INFO("set profile velocity mode ok");
    return true;
}
bool fm_auto::DuetflEthercatController::setSlaveOneMotorOperatingMode2ProfileVelocity()
{
    //1. check current operation mode
    fm_auto::OPERATION_MODE operation_mode = fm_auto::OM_UNKNOW_MODE;
    if(!getMotorOperatingModeSDO(fm_auto::slave1_operation_mode_display_fmsdo,operation_mode))
    {
        ROS_ERROR("setSlaveOneMotorOperatingMode2ProfileVelocity: get mode failed");
        return false;
    }
//ROS_INFO("dddd1.1   %d",operation_mode);
    if(operation_mode != fm_auto::OM_PROFILE_VELOCITY_MODE)
    {
        //2. set mode to profile velocity
        fm_auto::OPERATION_MODE value = fm_auto::OM_PROFILE_VELOCITY_MODE;
        if(!setMotorOperatingModeSDO(slave1_operation_mode_write_fmsdo,value))
        {
            ROS_ERROR("setSlaveOneMotorOperatingMode2ProfileVelocity: set mode failed");
            return false;
        }
    }
//ROS_INFO("dddd1.2");
    //3. verify
    operation_mode = fm_auto::OM_UNKNOW_MODE;
    if(!getMotorOperatingModeSDO(slave1_operation_mode_display_fmsdo,operation_mode))
    {
        ROS_ERROR("setSlaveOneMotorOperatingMode2ProfileVelocity: get mode failed 2");
        return false;
    }
    if(operation_mode != fm_auto::OMD_PROFILE_VELOCITY_MODE)
    {
        ROS_ERROR("setSlaveOneMotorOperatingMode2ProfileVelocity: mode is not profile velocity after set %d\n",operation_mode);
        return false;
    }
    ROS_INFO("set profile velocity mode ok");
    return true;
}
bool fm_auto::DuetflEthercatController::setSlaveZeroMotorOperatingMode2ProfilePosition()
{
    //1. check current operation mode
    fm_auto::OPERATION_MODE operation_mode = fm_auto::OM_UNKNOW_MODE;
    if(!getMotorOperatingModeSDO(fm_auto::slave0_operation_mode_display_fmsdo,operation_mode))
    {
        ROS_ERROR("setSlaveZeroMotorOperatingMode2ProfilePosition: get mode failed");
        return false;
    }
//ROS_INFO("dddd1.1   %d",operation_mode);
    if(operation_mode != fm_auto::OM_PROFILE_POSITION_MODE)
    {
        //2. set mode to profile position
        fm_auto::OPERATION_MODE value = fm_auto::OM_PROFILE_POSITION_MODE;
        if(!setMotorOperatingModeSDO(slave0_operation_mode_write_fmsdo,value))
        {
            ROS_ERROR("setSlaveZeroMotorOperatingMode2ProfilePosition: set mode failed");
            return false;
        }
    }
//ROS_INFO("dddd1.2");
    //3. verify
    operation_mode = fm_auto::OM_UNKNOW_MODE;
    if(!getMotorOperatingModeSDO(slave0_operation_mode_display_fmsdo,operation_mode))
    {
        ROS_ERROR("setSlaveZeroMotorOperatingMode2ProfilePosition: get mode failed 2");
        return false;
    }
    if(operation_mode != fm_auto::OM_PROFILE_POSITION_MODE)
    {
        ROS_ERROR("setSlaveZeroMotorOperatingMode2ProfilePosition: mode is not profile position after set %d\n",operation_mode);
        return false;
    }
    ROS_INFO("set profile position mode ok");
    return true;
}
bool fm_auto::DuetflEthercatController::doHoming_SlaveZero()
{
    if(!setSlaveZeroMotorOperatingMode2Homing())
    {
        ROS_ERROR("setSlaveZeroMotorOperatingMode2Homing failed");
        return false;
    }
    else
    {
        ROS_INFO_ONCE("setSlaveZeroMotorOperatingMode2Homing ok\n");
    }
//    duetController.testEnableControllerSDO();
    if(!enableControlSDO_SlaveZero())
    {
        ROS_ERROR("enableControlSDO_SlaveZero failed");
        return false;
    }
    else
    {
        ROS_INFO_ONCE("enableControlSDO_SlaveZero ok\n");
    }
    if(!operateSteeringMotorHomingMethod_SlaveZero())
    {
        ROS_ERROR("operateSteeringMotorHomingMethod failed");
        return false;
    }
    else
    {
        ROS_INFO_ONCE("operateSteeringMotorHomingMethod ok\n");
    }
    if(!disableControlSDO_SlaveZero())
    {
        ROS_ERROR("disableControlSDO_SlaveZero failed");
        return false;
    }
    else
    {
        ROS_INFO_ONCE("disableControlSDO_SlaveZero ok\n");
    }

    return true;
}
bool fm_auto::DuetflEthercatController::doHoming_SlaveOne()
{
    if(!setSlaveOneMotorOperatingMode2Homing())
    {
        ROS_ERROR("setSlaveOneMotorOperatingMode2Homing failed");
        return false;
    }
    else
    {
        ROS_INFO_ONCE("setSlaveOneMotorOperatingMode2Homing ok\n");
    }
//    duetController.testEnableControllerSDO();
    if(!enableControlSDO_SlaveOne())
    {
        ROS_ERROR("enableControlSDO_SlaveOne failed");
        return false;
    }
    else
    {
        ROS_INFO_ONCE("enableControlSDO_SlaveOne ok\n");
    }
    if(!operateSteeringMotorHomingMethod_SlaveOne())
    {
        ROS_ERROR("operateSteeringMotorHomingMethod_SlaveOne failed");
        return false;
    }
    else
    {
        ROS_INFO_ONCE("operateSteeringMotorHomingMethod_SlaveOne ok\n");
    }
    if(!disableControlSDO_SlaveOne())
    {
        ROS_ERROR("disableControlSDO_SlaveOne failed");
        return false;
    }
    else
    {
        ROS_INFO_ONCE("disableControlSDO_SlaveOne ok\n");
    }

    return true;
}
bool fm_auto::DuetflEthercatController::setSlaveZeroMotorOperatingMode2Homing()
{
    //1. check current operation mode
    fm_auto::OPERATION_MODE operation_mode = fm_auto::OM_UNKNOW_MODE;
    if(!getMotorOperatingModeSDO(fm_auto::slave0_operation_mode_display_fmsdo,operation_mode))
    {
        ROS_ERROR("setSlaveZeroMotorOperatingMode2Homing: get mode failed");
        return false;
    }
ROS_INFO("dddd1.1   %d",operation_mode);
    if(operation_mode != fm_auto::OM_HOMING_MODE)
    {
        //2. set mode to homing
        fm_auto::OPERATION_MODE value = fm_auto::OM_HOMING_MODE;
        if(!setMotorOperatingModeSDO(slave0_operation_mode_write_fmsdo,value))
        {
            ROS_ERROR("setSlaveZeroMotorOperatingMode2Homing: set mode failed");
            return false;
        }
    }
ROS_INFO("dddd1.2");
    //3. verify
    operation_mode = fm_auto::OM_UNKNOW_MODE;
    if(!getMotorOperatingModeSDO(slave0_operation_mode_display_fmsdo,operation_mode))
    {
        ROS_ERROR("setSlaveZeroMotorOperatingMode2Homing: get mode failed 2");
        return false;
    }
    if(operation_mode != fm_auto::OM_HOMING_MODE)
    {
        ROS_ERROR("setSlaveZeroMotorOperatingMode2Homing: mode not homing after set %d\n",operation_mode);
        return false;
    }
    ROS_INFO("set homing mode ok");
    return true;
}
bool fm_auto::DuetflEthercatController::setSlaveOneMotorOperatingMode2Homing()
{
    //1. check current operation mode
    fm_auto::OPERATION_MODE operation_mode = fm_auto::OM_UNKNOW_MODE;
    if(!getMotorOperatingModeSDO(fm_auto::slave1_operation_mode_display_fmsdo,operation_mode))
    {
        ROS_ERROR("setSlaveOneMotorOperatingMode2Homing: get mode failed");
        return false;
    }
ROS_INFO("dddd1.1   %d",operation_mode);
    if(operation_mode != fm_auto::OM_HOMING_MODE)
    {
        //2. set mode to homing
        fm_auto::OPERATION_MODE value = fm_auto::OM_HOMING_MODE;
        if(!setMotorOperatingModeSDO(slave1_operation_mode_write_fmsdo,value))
        {
            ROS_ERROR("setSlaveOneMotorOperatingMode2Homing: set mode failed");
            return false;
        }
    }
ROS_INFO("dddd1.2");
    //3. verify
    operation_mode = fm_auto::OM_UNKNOW_MODE;
    if(!getMotorOperatingModeSDO(slave1_operation_mode_display_fmsdo,operation_mode))
    {
        ROS_ERROR("setSlaveOneMotorOperatingMode2Homing: get mode failed 2");
        return false;
    }
    if(operation_mode != fm_auto::OM_HOMING_MODE)
    {
        ROS_ERROR("setSlaveOneMotorOperatingMode2Homing: mode not homing after set %d\n",operation_mode);
        return false;
    }
    ROS_INFO("set slave one homing mode ok");
    return true;
}
bool fm_auto::DuetflEthercatController::initSDOs_SlaveZero()
{
    // slave0 sdo
    ROS_INFO("Creating operation mode read SDO requests...\n");
    if (!(fm_auto::slave0_sdo_operation_mode_display = ecrt_slave_config_create_sdo_request(fm_auto::slave_zero,
                                                                                            ADDRESS_MODES_OF_OPERATION_DISPLAY,
                                                                                            0, 1))) // uint8 data size 1
    {
        ROS_ERROR("Failed to create SDO modes_of_operation_display 0x6061 request.\n");
        return false;
    }
    fm_auto::slave0_operation_mode_display_fmsdo = new fm_sdo();
    fm_auto::slave0_operation_mode_display_fmsdo->sdo = fm_auto::slave0_sdo_operation_mode_display;
    fm_auto::slave0_operation_mode_display_fmsdo->descrption = "operation_mode_display 0x6061";
    fm_auto::slave0_operation_mode_display_fmsdo->controller = this;

    ROS_INFO("Creating Homing Method read SDO requests...\n");
    if (!(fm_auto::slave0_sdo_homing_method = ecrt_slave_config_create_sdo_request(fm_auto::slave_zero,
                                                                                            ADDRESS_HOMING_METHOD,
                                                                                            0, 1))) // uint8 data size 1
    {
        ROS_ERROR("Failed to create SDO slave0_sdo_homing_methiod 0x6098 request.\n");
        return false;
    }
    fm_auto::slave0_homing_method_fmSdo = new fm_sdo();
    fm_auto::slave0_homing_method_fmSdo->sdo = fm_auto::slave0_sdo_homing_method;
    fm_auto::slave0_homing_method_fmSdo->descrption = "homing_method 0x6098";
    fm_auto::slave0_homing_method_fmSdo->controller = this;

    ROS_INFO( "Creating operation mode write SDO requests...\n");
    if (!(fm_auto::slave0_sdo_operation_mode_write = ecrt_slave_config_create_sdo_request(fm_auto::slave_zero,
                                                                                          ADDRESS_MODES_OF_OPERATION,
                                                                                          0, 1))) // uint8 data size 1
    {
        ROS_ERROR("Failed to create SDO MODES_OF_OPERATION request.\n");
        return -1;
    }
    fm_auto::slave0_operation_mode_write_fmsdo = new fm_sdo();
    fm_auto::slave0_operation_mode_write_fmsdo->sdo = fm_auto::slave0_sdo_operation_mode_write;
    fm_auto::slave0_operation_mode_write_fmsdo->descrption = "operation_mode_ 0x6060";
    fm_auto::slave0_operation_mode_write_fmsdo->controller = this;

    ROS_INFO("Creating controlword write SDO requests...\n");
    if (!(fm_auto::slave0_sdo_controlword_write = ecrt_slave_config_create_sdo_request(fm_auto::slave_zero,
                                                                                       ADDRESS_CONTROLWORD,
                                                                                       0, 2))) // uint16 data size 2
    {
        ROS_ERROR("Failed to create SDO CONTROLWORD request.\n");
        return -1;
    }
    fm_auto::slave0_controlword_fmsdo = new fm_sdo();
    fm_auto::slave0_controlword_fmsdo->sdo = fm_auto::slave0_sdo_controlword_write;
    fm_auto::slave0_controlword_fmsdo->descrption = "statusword 0x6040";
    fm_auto::slave0_controlword_fmsdo->controller = this;

    ROS_INFO("Creating statusword read SDO requests...\n");
    if (!(fm_auto::slave0_sdo_statusword_read = ecrt_slave_config_create_sdo_request(slave_zero, ADDRESS_STATUSWORD,
                                                                                     0, 2))) // uint16 data size 2
    {
        ROS_ERROR("Failed to create SDO STATUSWORD request.\n");
        return -1;
    }
    fm_auto::slave0_statusword_fmsdo = new fm_sdo();
    fm_auto::slave0_statusword_fmsdo->sdo = fm_auto::slave0_sdo_statusword_read;
    fm_auto::slave0_statusword_fmsdo->descrption = "statusword 0x6041";
    fm_auto::slave0_statusword_fmsdo->controller = this;

    ROS_INFO("Creating position_actual_value read SDO requests...\n");
    if (!(fm_auto::slave0_sdo_position_actual_value_read = ecrt_slave_config_create_sdo_request(slave_zero, ADDRESS_POSITION_ACTUAL_VALUE,
                                                                                     0, 4))) // int16 data size 2
    {
        ROS_ERROR("Failed to create SDO position_actual_value request.\n");
        return -1;
    }
    fm_auto::slave0_position_actual_value_fmsdo = new fm_sdo();
    fm_auto::slave0_position_actual_value_fmsdo->sdo = fm_auto::slave0_sdo_position_actual_value_read;
    fm_auto::slave0_position_actual_value_fmsdo->descrption = "position_actual_value 0x6064";
    fm_auto::slave0_position_actual_value_fmsdo->controller = this;

    ROS_INFO("Creating position_actual_value read SDO requests...\n");
    if (!(fm_auto::slave0_sdo_target_position_read_write = ecrt_slave_config_create_sdo_request(slave_zero,
                                                                                                ADDRESS_TARGET_POSITION,
                                                                                                0, 4))) // int16 data size 2
    {
        ROS_ERROR("Failed to create SDO position_actual_value request.\n");
        return -1;
    }
    fm_auto::slave0_target_position_fmsdo = new fm_sdo();
    fm_auto::slave0_target_position_fmsdo->sdo = fm_auto::slave0_sdo_target_position_read_write;
    fm_auto::slave0_target_position_fmsdo->descrption = "target position";
    fm_auto::slave0_target_position_fmsdo->controller = this;

    ecrt_sdo_request_timeout(fm_auto::slave0_sdo_operation_mode_display, 500); // ms
    ecrt_sdo_request_timeout(fm_auto::slave0_sdo_operation_mode_write, 500); // ms
    ecrt_sdo_request_timeout(fm_auto::slave0_sdo_controlword_write, 500); // ms
    ecrt_sdo_request_timeout(fm_auto::slave0_sdo_statusword_read, 500); // ms
    ecrt_sdo_request_timeout(fm_auto::slave0_sdo_position_actual_value_read, 500); // ms
    ecrt_sdo_request_timeout(fm_auto::slave0_sdo_target_position_read_write, 500); // ms

    //TODO: slave1 sdo

    return true;
}
bool fm_auto::DuetflEthercatController::initSDOs_SlaveOne()
{
    // slave1 sdo
    ROS_INFO("Creating slave1 operation mode read SDO requests...\n");
    if (!(fm_auto::slave1_sdo_operation_mode_display = ecrt_slave_config_create_sdo_request(fm_auto::slave_one,
                                                                                            ADDRESS_MODES_OF_OPERATION_DISPLAY,
                                                                                            0, 1))) // uint8 data size 1
    {
        ROS_ERROR("Failed to create slave1 SDO modes_of_operation_display 0x6061 request.\n");
        return false;
    }
    fm_auto::slave1_operation_mode_display_fmsdo = new fm_sdo();
    fm_auto::slave1_operation_mode_display_fmsdo->sdo = fm_auto::slave1_sdo_operation_mode_display;
    fm_auto::slave1_operation_mode_display_fmsdo->descrption = "slave1 operation_mode_display 0x6061";
    fm_auto::slave1_operation_mode_display_fmsdo->controller = this;

    ROS_INFO("Creating slave1 Homing Method read SDO requests...\n");
    if (!(fm_auto::slave1_sdo_homing_method = ecrt_slave_config_create_sdo_request(fm_auto::slave_one,
                                                                                            ADDRESS_HOMING_METHOD,
                                                                                            0, 1))) // uint8 data size 1
    {
        ROS_ERROR("Failed to create slave1 SDO slave0_sdo_homing_methiod 0x6098 request.\n");
        return false;
    }
    fm_auto::slave1_homing_method_fmSdo = new fm_sdo();
    fm_auto::slave1_homing_method_fmSdo->sdo = fm_auto::slave1_sdo_homing_method;
    fm_auto::slave1_homing_method_fmSdo->descrption = "slave1 homing_method 0x6098";
    fm_auto::slave1_homing_method_fmSdo->controller = this;

    ROS_INFO( "Creating slave1 operation mode write SDO requests...\n");
    if (!(fm_auto::slave1_sdo_operation_mode_write = ecrt_slave_config_create_sdo_request(fm_auto::slave_one,
                                                                                          ADDRESS_MODES_OF_OPERATION,
                                                                                          0, 1))) // uint8 data size 1
    {
        ROS_ERROR("Failed to create slave1 SDO MODES_OF_OPERATION request.\n");
        return -1;
    }
    fm_auto::slave1_operation_mode_write_fmsdo = new fm_sdo();
    fm_auto::slave1_operation_mode_write_fmsdo->sdo = fm_auto::slave1_sdo_operation_mode_write;
    fm_auto::slave1_operation_mode_write_fmsdo->descrption = "slave1 operation_mode_ 0x6060";
    fm_auto::slave1_operation_mode_write_fmsdo->controller = this;

    ROS_INFO("Creating slave1 controlword write SDO requests...\n");
    if (!(fm_auto::slave1_sdo_controlword_write = ecrt_slave_config_create_sdo_request(fm_auto::slave_one,
                                                                                       ADDRESS_CONTROLWORD,
                                                                                       0, 2))) // uint16 data size 2
    {
        ROS_ERROR("Failed to slave1 create SDO CONTROLWORD request.\n");
        return -1;
    }
    fm_auto::slave1_controlword_fmsdo = new fm_sdo();
    fm_auto::slave1_controlword_fmsdo->sdo = fm_auto::slave1_sdo_controlword_write;
    fm_auto::slave1_controlword_fmsdo->descrption = "slave1 statusword 0x6040";
    fm_auto::slave1_controlword_fmsdo->controller = this;

    ROS_INFO("Creating slave1 statusword read SDO requests...\n");
    if (!(fm_auto::slave1_sdo_statusword_read = ecrt_slave_config_create_sdo_request(slave_one, ADDRESS_STATUSWORD,
                                                                                     0, 2))) // uint16 data size 2
    {
        ROS_ERROR("Failed to create slave1 SDO STATUSWORD request.\n");
        return -1;
    }
    fm_auto::slave1_statusword_fmsdo = new fm_sdo();
    fm_auto::slave1_statusword_fmsdo->sdo = fm_auto::slave1_sdo_statusword_read;
    fm_auto::slave1_statusword_fmsdo->descrption = "slave1 statusword 0x6041";
    fm_auto::slave1_statusword_fmsdo->controller = this;

    ROS_INFO("Creating slave1 position_actual_value read SDO requests...\n");
    if (!(fm_auto::slave1_sdo_position_actual_value_read = ecrt_slave_config_create_sdo_request(slave_one, ADDRESS_POSITION_ACTUAL_VALUE,
                                                                                     0, 4))) // int32 data size 4
    {
        ROS_ERROR("Failed to create slave1 SDO position_actual_value request.\n");
        return -1;
    }
    fm_auto::slave1_position_actual_value_fmsdo = new fm_sdo();
    fm_auto::slave1_position_actual_value_fmsdo->sdo = fm_auto::slave1_sdo_position_actual_value_read;
    fm_auto::slave1_position_actual_value_fmsdo->descrption = "slave1 position_actual_value 0x6064";
    fm_auto::slave1_position_actual_value_fmsdo->controller = this;

    ROS_INFO("Creating slave1 position_actual_value read SDO requests...\n");
    if (!(fm_auto::slave1_sdo_target_position_read_write = ecrt_slave_config_create_sdo_request(slave_one,
                                                                                                ADDRESS_TARGET_POSITION,
                                                                                                0, 4))) // int16 data size 2
    {
        ROS_ERROR("Failed to create slave1 SDO position_actual_value request.\n");
        return -1;
    }
    fm_auto::slave1_target_position_fmsdo = new fm_sdo();
    fm_auto::slave1_target_position_fmsdo->sdo = fm_auto::slave1_sdo_target_position_read_write;
    fm_auto::slave1_target_position_fmsdo->descrption = "slave1 target position";
    fm_auto::slave1_target_position_fmsdo->controller = this;

    ecrt_sdo_request_timeout(fm_auto::slave1_sdo_operation_mode_display, 500); // ms
    ecrt_sdo_request_timeout(fm_auto::slave1_sdo_operation_mode_write, 500); // ms
    ecrt_sdo_request_timeout(fm_auto::slave1_sdo_controlword_write, 500); // ms
    ecrt_sdo_request_timeout(fm_auto::slave1_sdo_statusword_read, 500); // ms
    ecrt_sdo_request_timeout(fm_auto::slave1_sdo_position_actual_value_read, 500); // ms
    ecrt_sdo_request_timeout(fm_auto::slave1_sdo_target_position_read_write, 500); // ms

    return true;
}
bool fm_auto::DuetflEthercatController::initROS()
{
    ros::NodeHandle n;
    n.param("has_slave_one", hasSlaveOne, true);
    n.param("need_do_homing_slave_zero", needDoHoming_SlaveZero, true);
    n.param("need_do_homing_slave_one", needDoHoming_SlaveOne, true);
    n.param("max_steering_angle", maxSteeringCmd, 4500); // 450 degree
    n.param("max_braking_angle", maxBrakingCmd, 600); // 60 degree
    n.param("steering_slave_number", steering_slave_number, 1); // steering is default salve one
    n.param("braking_slave_number", braking_slave_number, 0); // braking is default salve zero

    ROS_INFO("has_slave_one %d\n",hasSlaveOne);
    ROS_INFO("need_do_homing_slave_zero %d\n",needDoHoming_SlaveZero);
    ROS_INFO("need_do_homing_slave_one %d\n",needDoHoming_SlaveOne);
    ROS_INFO("max_steering_angle %f\n",maxSteeringCmd);
    ROS_INFO("max_braking_angle %f\n",maxBrakingCmd);
    ROS_INFO("steering_slave_number %d\n",steering_slave_number);
    ROS_INFO("braking_slave_number %d\n",braking_slave_number);

    ROS_INFO("asdfd");
//    sub = n.subscribe(str,10,&fm_auto::DuetflEthercatController::callback_steering,this);
    sub = n.subscribe("steer_angle", 1, &fm_auto::DuetflEthercatController::callback_steering2, this);
    emergency_button_sub = n.subscribe("joy", 1, &fm_auto::DuetflEthercatController::callback_joy, this);
    braking_sub = n.subscribe("braking_angle", 1, &fm_auto::DuetflEthercatController::callback_braking, this);
    pub = n.advertise<etherlab_master::EthercatPDO>("pdo_ethercat", 1);
    pub_position_cmd = n.advertise<std_msgs::Float64>("position_cmd_receive", 1); // steering position cmd
    pub_braking_cmd = n.advertise<std_msgs::Float64>("braking_cmd_receive", 1); // braking position cmd

}

bool fm_auto::DuetflEthercatController::initEthercat()
{
    // we only have one master,who is g...
    master = ecrt_request_master(0);
    if (!master)
    {
        return -1;
    }

//    fm_auto::slave_zero = NULL;
    fm_auto::slave_zero = ecrt_master_slave_config(master,SlaveZeroAliasAndPosition,VendorID_ProductCode);
    if(!fm_auto::slave_zero)
    {
        ROS_ERROR("Failed to get slave configuration.\n");
        return false;
    }

    if(!initSDOs_SlaveZero())
    {
        ROS_ERROR("init sdos failed!\n");
        return false;
    }
#if 1
    // two domains
    domain_input = ecrt_master_create_domain(master);
    if(!domain_input)
    {
        ROS_ERROR("init domain_input failed!\n");
        return false;
    }
    domain_output= ecrt_master_create_domain(master);
    if(!domain_output)
    {
        ROS_ERROR("init domain_output failed!\n");
        return false;
    }
//    domain_output_target_velocity = ecrt_master_create_domain(master);
//    if(!domain_output_target_velocity)
//    {
//        ROS_ERROR("init domain_output_target_velocity failed!\n");
//        return false;
//    }
    printf("Configuring PDOs...\n");
    if (ecrt_slave_config_pdos(fm_auto::slave_zero, EC_END, fm_auto::slave_0_syncs)) {
        fprintf(stderr, "Failed to configure PDOs.\n");
        return -1;
    }

    if(hasSlaveOne == true)
    {
        // init ethercat slave one
        if(!initEthercat_SlaveOne())
        {
            ROS_ERROR("Failed to init ethercat slave one: %s\n", strerror(errno));
            return false;
        }
    }

    // domain entry list
    if (ecrt_domain_reg_pdo_entry_list(domain_output, fm_auto::domain_output_regs)) {
        ROS_ERROR("Output PDO entry registration failed!\n");
        return false;
    }
//    if (ecrt_domain_reg_pdo_entry_list(domain_output_target_velocity, fm_auto::domain_output_regs_target_velocity)) {
//        ROS_ERROR("Output PDO entry target velocity registration failed!\n");
//        return false;
//    }
    if (ecrt_domain_reg_pdo_entry_list(domain_input, fm_auto::domain_input_regs)) {
        ROS_ERROR("Input PDO entry registration failed!\n");
        return false;
    }
#endif
    ROS_INFO("Activating master...\n");
    if (ecrt_master_activate(master))
    {
        ROS_ERROR("active master failed!\n");
        return false;
    }

#if 1
ROS_INFO_ONCE("debug1");
    // pdo domain data point
    if (!(domain_output_pd = ecrt_domain_data(domain_output))) {
        return false;
    }
//ROS_INFO_ONCE("debug1.1");
//    if (!(domain_output_target_velocity_pd = ecrt_domain_data(domain_output_target_velocity))) {
//        return false;
//    }
ROS_INFO_ONCE("debug1---1");
    if (!(domain_input_pd = ecrt_domain_data(domain_input))) {
        return false;
    }
#endif
    // set pid priority
    pid_t pid = getpid();
    if (setpriority(PRIO_PROCESS, pid, -19))
    {
        ROS_ERROR("Warning: Failed to set priority: %s\n",
                strerror(errno));
    }
ROS_INFO_ONCE("debug2");


    // signal handler
    // handle ctrl+c important
    if (signal(SIGINT, fm_auto::DuetflEthercatController::my_sig_handler) == SIG_ERR)
    {
            ROS_ERROR("\ncan't catch SIGUSR1\n");
            return false;
    }

ROS_INFO_ONCE("debug");
//    // get alarm to control frequcy
//    sa.sa_handler = signal_handler;
//    sigemptyset(&sa.sa_mask);
//    sa.sa_flags = 0;
//    if (sigaction(SIGALRM, &sa, 0)) {
//        ROS_ERROR("Failed to install signal handler!\n");
//        return -1;
//    }

//    ROS_INFO("Starting timer...\n");
//    tv.it_interval.tv_sec = 0;
//    tv.it_interval.tv_usec = 1000000 / FREQUENCY;
//    tv.it_value.tv_sec = 0;
//    tv.it_value.tv_usec = 1000;
//    if (setitimer(ITIMER_REAL, &tv, NULL)) {
//        ROS_ERROR("Failed to start timer: %s\n", strerror(errno));
//        return false;
//    }
    return true;
}
bool fm_auto::DuetflEthercatController::initEthercat_SlaveOne()
{
    if (!master)
    {
        return -1;
    }

    fm_auto::slave_one = ecrt_master_slave_config(master,SlaveOneAliasAndPosition,VendorID_ProductCode);
    if(!fm_auto::slave_one)
    {
        ROS_ERROR("Failed to get slave one configuration.\n");
        return false;
    }

    if(!initSDOs_SlaveOne())
    {
        ROS_ERROR("init sdos failed!\n");
        return false;
    }

    if (ecrt_slave_config_pdos(fm_auto::slave_one, EC_END, fm_auto::slave_1_syncs)) {
        fprintf(stderr, "Failed to configure slave_one PDOs.\n");
        return -1;
    }
    return true;
}
void fm_auto::DuetflEthercatController::run()
{
    ros::Rate loop_rate(FREQUENCY);
//    uint16_t value=0xf;
//    writeControlword_PDO_SlaveZero(value);
//    int32_t target_positon = 0x0;
//    writeTargetPosition_PDO_SlaveZero(target_positon);
//    ROS_INFO("sleep....\n");
//    sleep(10);
//    ROS_INFO("go....\n");
    while (1) {
//        pause();

        ros::spinOnce();
//        if(!cyclic_task_SDO())
        if(!cyclic_task())
        {
            break;
        }
        loop_rate.sleep();

    }
}
bool fm_auto::DuetflEthercatController::sendOneReadSDO(fm_sdo *fmSdo_read)
{
//    ecrt_master_receive(master);
    //  upload
    if(!fmSdo_read->sdo)
    {
        ROS_ERROR("sendOneReadSDO: sdo is NULL");
        return false;
    }
    ecrt_sdo_request_read(fmSdo_read->sdo);
    return true;
//    ecrt_master_send(master);
}
bool fm_auto::DuetflEthercatController::sendOneWriteSDO(fm_sdo *fmSdo_write)
{
//    ecrt_master_receive(master);
    // download
    ecrt_sdo_request_write(fmSdo_write->sdo);
//    ecrt_master_send(master);
}
bool fm_auto::DuetflEthercatController::checkSDORequestState(fm_sdo *fmSdo)
{
    bool state=false;

    switch (ecrt_sdo_request_state(fmSdo->sdo)) {
        case EC_REQUEST_UNUSED: // request was not used yet
            ROS_INFO_ONCE("request was not used yet\n");
            break;
        case EC_REQUEST_BUSY:
            ROS_INFO_ONCE("request is busy...\n");
            break;
        case EC_REQUEST_SUCCESS:
            state=true;
            break;
        case EC_REQUEST_ERROR:
            ROS_ERROR_ONCE("Failed to read SDO!\n");
            break;
    }
    return state;
}
bool fm_auto::DuetflEthercatController::waitSDORequestSuccess(fm_sdo *fmSdo,bool isRead)
{
    bool isSuccess=false;
    ros::Time time_begin = ros::Time::now();
//    ROS_INFO("getMotorHomingModeSDO %f",time_begin.toSec());
    ros::Rate loop_rate(FREQUENCY);
//    ROS_INFO("getMotorHomingModeSDO spinOnce");
    while(!isSuccess)
    {
        //2. check sdo state
        ros::spinOnce();
        ecrt_master_receive(master);

        // check for master state (optional)
        check_master_state();

        // check for islave configuration state(s) (optional)
//        check_slave_config_states();

        if(checkSDORequestState(fmSdo))
        {
//            method_value = EC_READ_S8(ecrt_sdo_request_data(homing_operation_mode_fmsdo->sdo));
//            ROS_INFO("get homing method: 0x%02x %d",method_value,method_value);
//            isSuccess = true;
            return true;
        }
        if(isRead)
        {
            sendOneReadSDO(fmSdo);
        }
        else
        {
            sendOneWriteSDO(fmSdo);
        }
        ros::Time time_now = ros::Time::now();
//        ROS_INFO("getMotorHomingModeSDO %f %f",time_begin.toSec(),time_now.toSec());
        if( (time_now.toSec() - time_begin.toSec()) > 10 ) // 10 sec
        {
            ROS_ERROR("waitSDORequestSuccess timeout");
            break;
        }
        ecrt_master_send(master);
        loop_rate.sleep();
    }
    return false;
}

//fm_auto::HOMING_METHOD fm_auto::DuetflEthercatController::getMotorHomingMode(fm_auto::fm_sdo *homing_operation_mode_fmsdo)
//{
//    int8_t mode_value=0x00;
//    //1. send read sdo request
//    sendOneReadSDO(homing_operation_mode_fmsdo);
//    //2. check sdo state
//    if(checkSDORequestState(homing_operation_mode_fmsdo))
//    {
//        mode_value = EC_READ_S8(ecrt_sdo_request_data(homing_operation_mode_fmsdo->sdo));
//        ROS_INFO_ONCE("get homing method: %02x",mode_value);
//    }
//    else
//    {
//        ROS_INFO_ONCE("get homing method failed");
//    }
////    if(mode_value == fm_auto::HM_current_position)
//    return (fm_auto::HOMING_METHOD)mode_value;
//}
bool fm_auto::DuetflEthercatController::getMotorHomingMethodSDO(fm_auto::fm_sdo *homing_operation_mode_fmsdo,
                                                                fm_auto::HOMING_METHOD &method)
{
    int8_t method_value=0x00;
    //1. send read sdo request
    sendOneReadSDO(homing_operation_mode_fmsdo);
//    bool isGetValue=false;
//    ros::Time time_begin = ros::Time::now();
//    ROS_INFO("getMotorHomingModeSDO %f",time_begin.toSec());
//    ros::Rate loop_rate(100);
//    ROS_INFO("getMotorHomingModeSDO spinOnce");
    if(waitSDORequestSuccess(homing_operation_mode_fmsdo,READ))
    {
        method_value = EC_READ_S8(ecrt_sdo_request_data(homing_operation_mode_fmsdo->sdo));
        ROS_INFO("get homing method: 0x%02x %d",method_value,method_value);
        method = (fm_auto::HOMING_METHOD)method_value;
        return true;
    }
    else
    {
        ROS_ERROR("get homing method failed");
        return false;
    }
//    while(!isGetValue)
//    {
//        //2. check sdo state
//        ros::spinOnce();
//        ecrt_master_receive(master);
//        if(checkSDORequestState(homing_operation_mode_fmsdo))
//        {
//            method_value = EC_READ_S8(ecrt_sdo_request_data(homing_operation_mode_fmsdo->sdo));
//            ROS_INFO("get homing method: 0x%02x %d",method_value,method_value);
//            isGetValue = true;
//            break;
//        }
//        ros::Time time_now = ros::Time::now();
////        ROS_INFO("getMotorHomingModeSDO %f %f",time_begin.toSec(),time_now.toSec());
//        if( (time_now.toSec() - time_begin.toSec()) > 20 ) // 10 sec
//        {
//            ROS_INFO("getMotorHomingModeSDO timeout");
//            break;
//        }
//        ecrt_master_send(master);
//        loop_rate.sleep();
////        else
////        {
////            ROS_INFO_ONCE("get homing method failed");
////        }
//    }
////    if(mode_value == fm_auto::HM_current_position)
//    ROS_INFO("getMotorHomingModeSDO out");
//    return (fm_auto::HOMING_METHOD)method_value;
}
bool fm_auto::DuetflEthercatController::setMotorHomingModeSDO(fm_sdo *homing_operation_mode_fmsdo,fm_auto::HOMING_METHOD &hm)
{
    int8_t v=(int8_t)hm;
    EC_WRITE_S8(ecrt_sdo_request_data(homing_operation_mode_fmsdo->sdo), v);
//    ecrt_master_send(master);
    sendOneWriteSDO(homing_operation_mode_fmsdo);
    if(!waitSDORequestSuccess(homing_operation_mode_fmsdo,WRITE))
    {
        ROS_ERROR("setMotorHomingModeSDO: set homing method %d failed",hm);
    }
    return true;
}
bool fm_auto::DuetflEthercatController::enableControlSDO(fm_sdo *statusword_fmSdo,fm_sdo *controlword_fmSdo)
{
    fm_auto::CONTROLLER_STATE state = fm_auto::CS_UNKNOWN_STATE;
    int i=0;
    while(state != fm_auto::CS_OPERATION_ENABLE)
    {
        // 1.0 check statusword ,serveo controller is in fault state
        uint16_t statusword=0x0000;
        if(!getStatuswordSDO(statusword_fmSdo,statusword))
        {
            ROS_ERROR("enableControlSDO: get statusword failed");
            return false;
        }

        if(!getControllerStateByStatusword(statusword,state))
        {
            ROS_ERROR("enableControlSDO: analyst controller state failed 0x%04x",statusword);
            return false;
        }
        uint16_t value;
        switch (state) {
            case fm_auto::CS_FAULT: // request was not used yet
                // 1.1 TODO: if has error , check error register
                // 1.2 if error ergister has zero error,send 128(bit 7) to controlword to switch_on_disabled
                value = 0x0080;//reset
                setControlwordSDO(controlword_fmSdo,value);
                break;
            case fm_auto::CS_SWITCH_ON_DISABLED:
                // 2.0 controller in switch_on_disabled , send 6 to be ready_to_switch_on
                value = 0x0006;
                setControlwordSDO(controlword_fmSdo,value);
                break;
            case fm_auto::CS_READY_TO_SWITCH_ON:
                // 3.0 in ready_to_switch_on, send 7 to be switched_on
                value = 0x0007;
                setControlwordSDO(controlword_fmSdo,value);
                break;
            case fm_auto::CS_SWITCH_ON:
                // 4.0 in switched_on, send 0x0f 15 to be operation_enable
                value = 0x000f;
                setControlwordSDO(controlword_fmSdo,value);
                break;
            case fm_auto::CS_OPERATION_ENABLE:
                // controller enabled
                return true;
                break;
            case fm_auto::CS_NOT_READY_TO_SWITCH_ON:
                ROS_INFO("CS_NOT_READY_TO_SWITCH_ON");
                return false;
                break;
        default:
            ROS_ERROR("enableControlSDO: unkown state %04x",state);
            return false;
        }
        i++;
        if(i>5)
        {
            ROS_ERROR("enableControlSDO: controller not enabled in 5 steps");
            return false;
        }
    }//while

}
bool fm_auto::DuetflEthercatController::enableControlSDO_SlaveZero()
{
    if(!enableControlSDO(slave0_statusword_fmsdo,slave0_controlword_fmsdo))
    {
        ROS_ERROR("enableControlSDO failed");
        return false;
    }
    return true;
}
bool fm_auto::DuetflEthercatController::enableControlSDO_SlaveOne()
{
    if(!enableControlSDO(fm_auto::slave1_statusword_fmsdo,fm_auto::slave1_controlword_fmsdo))
    {
        ROS_ERROR("enableControlSDO slave one failed");
        return false;
    }
    return true;
}
bool fm_auto::DuetflEthercatController::disableControlSDO_SlaveZero()
{
    if(!disableControlSDO_bool(slave0_statusword_fmsdo,slave0_controlword_fmsdo))
    {
        ROS_ERROR("disableControlSDO_SlaveZero failed");
        return false;
    }
    return true;
}
bool fm_auto::DuetflEthercatController::disableControlSDO_SlaveOne()
{
    if(!disableControlSDO_bool(slave1_statusword_fmsdo,slave1_controlword_fmsdo))
    {
        ROS_ERROR("disableControlSDO_SlaveOne failed");
        return false;
    }
    return true;
}
void fm_auto::DuetflEthercatController::disableControlSDO(fm_sdo *statusword_fmSdo,fm_sdo *controlword_fmSdo)
{
    // write controlword 0x0002
    uint16_t value = 0x0002;//stop
    statusword_fmSdo->controller->setControlwordSDO(controlword_fmSdo,value);
    // check statusword
    fm_auto::CONTROLLER_STATE state = fm_auto::CS_UNKNOWN_STATE;
    uint16_t statusword=0x0000;
    if(!statusword_fmSdo->controller->getStatuswordSDO(statusword_fmSdo,statusword))
    {
        ROS_ERROR("enableControlSDO: get statusword failed");
        return;
    }

    if(!statusword_fmSdo->controller->getControllerStateByStatusword(statusword,state))
    {
        ROS_ERROR("enableControlSDO: analyst controller state failed 0x%04x",statusword);
        return;
    }
    if(state == fm_auto::CS_OPERATION_ENABLE)
    {
        ROS_ERROR("controller still enable after send 0x2,send again");
        statusword_fmSdo->controller->setControlwordSDO(controlword_fmSdo,value);
        return;
    }
    return;
}
bool fm_auto::DuetflEthercatController::disableControlSDO_bool(fm_sdo *statusword_fmSdo,fm_sdo *controlword_fmSdo)
{
    // write controlword 0x0002
    uint16_t value = 0x0002;//stop
    statusword_fmSdo->controller->setControlwordSDO(controlword_fmSdo,value);
    // check statusword
    fm_auto::CONTROLLER_STATE state = fm_auto::CS_UNKNOWN_STATE;
    uint16_t statusword=0x0000;
    if(!statusword_fmSdo->controller->getStatuswordSDO(statusword_fmSdo,statusword))
    {
        ROS_ERROR("enableControlSDO: get statusword failed");
        return false;
    }

    if(!statusword_fmSdo->controller->getControllerStateByStatusword(statusword,state))
    {
        ROS_ERROR("enableControlSDO: analyst controller state failed 0x%04x",statusword);
        return false;
    }
    if(state == fm_auto::CS_OPERATION_ENABLE)
    {
        ROS_ERROR("controller still enable after send 0x2,send again");
        statusword_fmSdo->controller->setControlwordSDO(controlword_fmSdo,value);
        return false;
    }
    return true;
}
void fm_auto::DuetflEthercatController::check_master_state()
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
bool fm_auto::DuetflEthercatController::cyclic_task_SDO()
{

    // read PDO data
    bool res = checkControllerState_SDO();
    if(!PDO_OK)
    {
        return false;
    }
    if(res)
    {
        ROS_INFO_ONCE("cyclic_task_SDO start");
        writeControllerData_SDO_SlaveZero();
    }
}

bool fm_auto::DuetflEthercatController::cyclic_task()
{
//    pthread_mutex_lock( &fm_auto::mutex_PDO );
    // receive process data
    ecrt_master_receive(master);
//    ecrt_domain_process(domain_output);
    ecrt_domain_process(domain_input);


    // check process data state (optional)
//    check_domain1_state();

    // check for master state (optional)
//    check_master_state();

    // check for islave configuration state(s) (optional)
//    check_slave_config_states();

    current_time = ros::Time::now();

    writeControlword_PDO_SlaveZero(controlword_PDO);
    writeControlword_PDO_SlaveOne(controlword_PDO);
    // read PDO data
    bool res = readPDOsData();
    if(!PDO_OK)
    {
        return false;
    }
    if(res)
    {
        ROS_INFO_ONCE("PDO_ok");
        writePDOData_VelocityControl();
//        writePDOData_SlaveZero();
//        writePDOData_SlaveZero2();
//        writePDOData_SlaveZero3();
    }

    dt = (current_time - last_time).toSec();
    last_time = current_time;

    // send process data
//    ecrt_domain_queue(domain_output);
    ecrt_domain_queue(domain_input);
    ecrt_master_send(master);

    return true;
//    pthread_mutex_unlock( &fm_auto::mutex_PDO );
}
//void fm_auto::DuetflEthercatController::callback_steering(const etherlab_master::steering::ConstPtr &steering_cmd)
//{
////    pthread_mutex_lock( &fm_auto::mutex_PDO );

//    steering_cmd_new = steering_cmd->num;
//    waitTick = 10;
//    ROS_INFO("callback_steering: %d",steering_cmd_new);
////    ROS_INFO("callback_steering: %d",steering_cmd->num);
////    if(steering_cmd->num != steering_cmd_old)
////    {
////        steering_cmd_old = (int32_t)steering_cmd->num;
////        writeTargetPosition_PDO_SlaveZero(steering_cmd_old);
////        uint16_t controlword = 0x003f;
////        writeControlword_PDO_SlaveZero(controlword);
////        needWrite_0xf_2controlword = true;
//////        waitTick = 10;
////    }

////    pthread_mutex_unlock( &fm_auto::mutex_PDO );
//}


void fm_auto::DuetflEthercatController::callback_joy(sensor_msgs::Joy joy_cmd)
{
  int button_trig = joy_cmd.buttons[5];
  if(button_trig == 1){
    if(fm_auto::DuetflEthercatController::enable_mode){
        if(steering_slave_number == 0)
        {
            fm_auto::DuetflEthercatController::disableControlSDO_SlaveZero();
        }
        else if(steering_slave_number == 1)
        {
            fm_auto::DuetflEthercatController::disableControlSDO_SlaveOne();
        }
      fm_auto::DuetflEthercatController::enable_mode = false;
      ROS_WARN("Disabling mode");
    }
    else {
        if(steering_slave_number == 0)
        {
            fm_auto::DuetflEthercatController::enableControlSDO_SlaveOne();
        }
        else if(steering_slave_number == 1)
        {
            fm_auto::DuetflEthercatController::enableControlSDO_SlaveZero();
        }
      fm_auto::DuetflEthercatController::enable_mode = true;
      ROS_WARN("Enabling mode");
    }
  }
}
void fm_auto::DuetflEthercatController::callback_steering2(std_msgs::Float64 steering_cmd)
{
//    if(waitTick == -1)
//    {
//        int32_t v = static_cast<int32_t>(steering_cmd.data);
//        if(v != steering_cmd_old)
//        {
//            steering_cmd_new = v*10;
//            waitTick = 2;
//            ROS_INFO("callback_steering new steering value: %d",steering_cmd_new);
//        }
//    }
    int32_t v = static_cast<int32_t>(steering_cmd.data);
//    if(steering_cmd_current != v)
//    {
        steering_cmd_new = v * 10;
//        hasNewSteeringData = true;
//    }
//    ROS_INFO("callback_steering: %d %f %d",steering_cmd_new,steering_cmd.data,positionControlState);

//    ROS_INFO("callback_steering: %f",steering_cmd.data);
}
void fm_auto::DuetflEthercatController::callback_braking(std_msgs::Float64 braking_cmd)
{

    int32_t v = static_cast<int32_t>(braking_cmd.data);

    braking_cmd_new = v * 10;

}
bool fm_auto::DuetflEthercatController::writeTargetVelocity_PDO_SlaveZero(int32_t &value)
{
    // TODO:check boundary
    // write process data
//    std::unique_lock<std::mutex> lock(counter_mutex);
//    pthread_mutex_lock( &fm_auto::mutex_PDO );

    EC_WRITE_U32(domain_output_pd + fm_auto::OFFSET_TARGET_VELOCITY, value);

//    pthread_mutex_unlock( &fm_auto::mutex_PDO );
    return true;
}
bool fm_auto::DuetflEthercatController::writeTargetVelocity_PDO_SlaveOne(int32_t &value)
{
    EC_WRITE_U32(domain_output_pd + fm_auto::OFFSET_TARGET_VELOCITY_SLAVE_ONE, value);

    return true;
}
bool fm_auto::DuetflEthercatController::writeTargetPosition_PDO_SlaveZero(int32_t &value)
{
    // TODO:check boundary
    // write process data
//    std::unique_lock<std::mutex> lock(counter_mutex);
//    pthread_mutex_lock( &fm_auto::mutex_PDO );

    EC_WRITE_U32(domain_output_pd + fm_auto::OFFSET_TARGET_POSITION, value);

//    pthread_mutex_unlock( &fm_auto::mutex_PDO );
    return true;
}
bool fm_auto::DuetflEthercatController::writeTargetPosition_PDO_SlaveOne(int32_t &value)
{
    EC_WRITE_U32(domain_output_pd + fm_auto::OFFSET_TARGET_POSITION_SLAVE_ONE, value);
    return true;
}
bool fm_auto::DuetflEthercatController::writeControlword_PDO_SlaveZero(uint16_t &value)
{
//    std::unique_lock<std::mutex> lock(counter_mutex);
//    pthread_mutex_lock( &fm_auto::mutex_PDO );

    EC_WRITE_U16(domain_output_pd + fm_auto::OFFSET_CONTROLWORD, value);

//    pthread_mutex_unlock( &fm_auto::mutex_PDO );
    return true;
}
bool fm_auto::DuetflEthercatController::writeControlword_PDO_SlaveOne(uint16_t &value)
{
//    std::unique_lock<std::mutex> lock(counter_mutex);
//    pthread_mutex_lock( &fm_auto::mutex_PDO );

    EC_WRITE_U16(domain_output_pd + fm_auto::OFFSET_CONTROLWORD_SLAVE_ONE, value);

//    pthread_mutex_unlock( &fm_auto::mutex_PDO );
    return true;
}
bool fm_auto::DuetflEthercatController::writeControllerData_SDO_SlaveZero()
{
    // positionControlState states:
    //     target position     new_set_point       set_point_acknowledge
    // 6.   not changed,                   clear,              clear
    // 1.   changed,                    clear,              clear
    // 2.   not changed,                   setted,              clear
    // 3.   not changed,                    setted               setted
    // 4.     changed                       setted,             setted
    // 5.     not changed,                 cleard,              setted
    // 6.    not changed,                  cleard,               cleard
    if(hasNewSteeringData)
    {
        uint16_t controlword;
        int beginState = positionControlState;
        // check state
        switch (positionControlState) {
            case 6:
                if(!is_SetPointAcknowledge_Set)
                {

                    steering_cmd_writing = steering_cmd_new;
                    if(!setSlaveZeroTargetPosition(steering_cmd_writing))
                    {
                        ROS_ERROR("writeControllerData_SDO_SlaveZero: set target position failed");
//                        return false;
                    }
//                    writeTargetPosition_PDO_SlaveZero(steering_cmd_writing);
                    positionControlState = 1;
                    restTick = 2;
                }
                break;
            case 1:
            if(restTick>1)
            {
                restTick--;
            }
            else
            {
                if(is_TargetReached_Set)
                    controlword = 0x1f;
                else
                    controlword = 0x3f;
                if(!setControlwordSDO(fm_auto::slave0_controlword_fmsdo,controlword))
                {
                    ROS_ERROR("writeControllerData_SDO_SlaveZero: set controlword 0x3f failed");
                    return false;
                }
//                controlword = 0x3f;
//                writeControlword_PDO_SlaveZero(controlword);

                positionControlState = 2;
            }
                break;
            case 2:
                if(is_SetPointAcknowledge_Set)
                {
                    positionControlState = 3;
                    restTick = 20;
                    steering_cmd_current = steering_cmd_writing;
                }
                break;
            case 3:
//            if(restTick>1)
//                restTick--;
//            else
//                if(steering_cmd_current != steering_cmd_new)
//                {
//                    steering_cmd_writing = steering_cmd_new;
////                    writeTargetPosition_PDO_SlaveZero(steering_cmd_writing);
//                    if(!setSlaveZeroTargetPosition(steering_cmd_writing))
//                    {
//                        ROS_ERROR("writeControllerData_SDO_SlaveZero: set target position failed");
////                        return false;
//                    }

                    positionControlState = 4;
//                }
                break;
            case 4:
                controlword = 0xf;
                if(!setControlwordSDO(fm_auto::slave0_controlword_fmsdo,controlword))
                {
                    ROS_ERROR("writeControllerData_SDO_SlaveZero: set controlword 0xf failed");
                    return false;
                }
//                controlword = 0xf;
//                writeControlword_PDO_SlaveZero(controlword);

                positionControlState = 5;
                break;
            case 5:
                if(!is_SetPointAcknowledge_Set)
                {
                    positionControlState = 6;

                    steering_cmd_current = steering_cmd_writing;
                    if(steering_cmd_current == steering_cmd_new)
                    {
                        hasNewSteeringData = false;
                    }
                }
                break;
            default:
                ROS_ERROR("position control unknown state");
                return false;
                break;
        }//switch
        ROS_INFO("state %d ----> %d   n:%d w:%d c:%d",beginState,positionControlState,
                 steering_cmd_new,steering_cmd_writing,steering_cmd_current);
    }//if
    return true;
}
bool fm_auto::DuetflEthercatController::writePDOData_SlaveZero3()
{
    int beginState = positionControlState;
    // check state
    switch (positionControlState) {
      case 6:
        if(steering_cmd_current != steering_cmd_new)
        {
                steering_cmd_writing = steering_cmd_new;

                ecrt_domain_process(domain_output);
                writeTargetPosition_PDO_SlaveZero(steering_cmd_writing);
                ecrt_domain_queue(domain_output);

                positionControlState = 5;
        }
      break;
    case 5:
        if(is_TargetReached_Set)
        {
            controlword_PDO = 0x1f;
        }
        else
        {
            controlword_PDO = 0x3f;
        }

        ecrt_domain_process(domain_output);
        writeControlword_PDO_SlaveZero(controlword_PDO);
        ecrt_domain_queue(domain_output);

        positionControlState = 4;
    break;

    case 4:
        if(is_SetPointAcknowledge_Changed || is_TargetReached_Set)
        {
            positionControlState = 3;
            steering_cmd_current = steering_cmd_writing;
        }
    break;

    case 3:
        controlword_PDO = 0xf;

        ecrt_domain_process(domain_output);
        writeControlword_PDO_SlaveZero(controlword_PDO);
        ecrt_domain_queue(domain_output);

        positionControlState = 2;
        break;

    case 2:
        if(is_SetPointAcknowledge_Changed)
        {
            positionControlState = 6;
        }
        break;
    default:
      ROS_ERROR("position control unknow state");
      return false;
      break;
    }//switch
    if(steering_cmd_current != steering_cmd_new)
    {
        ROS_INFO("state %d ----> %d   n:%d w:%d c:%d 0x%04x",beginState,positionControlState,
             steering_cmd_new,steering_cmd_writing,steering_cmd_current,controlword_PDO);
    }
    return true;
}
bool fm_auto::DuetflEthercatController::calculateTargetVelocity_SlaveZero(int32_t &target_pos)
{
    // good but over a bit
//    kp = 8.5;
//    ki = 10.0;

    kp = 13.5;
    ki = 0.0;
    kd = 0.0;

    kp_sat = 9000;
    ki_sat = 900;
    kd_sat = 900;

    v_sat = 9000;

    if(dt==0) return false;

//    steering_cmd_new = fmutil::symbound<int32_t>(steering_cmd_new,maxSteeringCmd);
//    std_msgs::Float64 cmd;
//    cmd.data = steering_cmd_new;
//    fm_auto::DuetflEthercatController::pub_position_cmd.publish(cmd);
//    e_now = steering_cmd_new - position_actual_value_PDO_data;
    e_now = target_pos - position_actual_value_PDO_data_slave_zero;
    // P
    double p_gain = fmutil::symbound<double>(kp * e_now, kp_sat);


    // I
    // Accumulate integral error and limit its range
    iTerm += ki * (e_pre + e_now)/2 * dt;
    double i_gain = iTerm = fmutil::symbound<double>(iTerm, ki_sat);

    // D
    double dTerm = kd * (e_now - e_pre) / dt;
    double d_gain = fmutil::symbound<double>(dTerm, kd_sat);

    double u = p_gain + i_gain + d_gain;
    ROS_INFO("kp %f ki %f kd %f"
            ,p_gain,i_gain,d_gain);
    target_velocity_slave_zero = fmutil::symbound<int>(u, v_sat);
    if(abs(target_velocity_slave_zero) < 2)
    {
        target_velocity_slave_zero = 0;
    }

    e_pre = e_now;

    return true;
}
bool fm_auto::DuetflEthercatController::calculateTargetVelocity_SlaveOne(int32_t &target_pos)
{
    // good but over a bit
//    kp = 8.5;
//    ki = 10.0;

    kp_slave_one = 13.5;
    ki_slave_one = 0.0;
    kd_slave_one = 0.0;

    kp_sat_slave_one = 9000;
    ki_sat_slave_one = 900;
    kd_sat_slave_one = 900;

    v_sat_slave_one = 9000;

    if(dt==0) return false;

//    steering_cmd_new = fmutil::symbound<int32_t>(steering_cmd_new,maxSteeringCmd);
//    std_msgs::Float64 cmd;
//    cmd.data = steering_cmd_new;
//    fm_auto::DuetflEthercatController::pub_position_cmd.publish(cmd);
//    e_now = steering_cmd_new - position_actual_value_PDO_data;
    e_now_slave_one = target_pos - position_actual_value_PDO_data_slave_one;
    // P
    double p_gain = fmutil::symbound<double>(kp_slave_one * e_now_slave_one, kp_sat_slave_one);


    // I
    // Accumulate integral error and limit its range
    iTerm_slave_one += ki_slave_one * (e_pre_slave_one + e_now_slave_one)/2 * dt;
    double i_gain = fmutil::symbound<double>(iTerm_slave_one, ki_sat_slave_one);

    // D
    double dTerm = kd_slave_one * (e_now_slave_one - e_pre_slave_one) / dt;
    double d_gain = fmutil::symbound<double>(dTerm, kd_sat_slave_one);

    double u = p_gain + i_gain + d_gain;
    ROS_INFO("kp_slave_one %f ki_slave_one %f kd_slave_one %f"
            ,p_gain,i_gain,d_gain);
    target_velocity_slave_one = fmutil::symbound<int>(u, v_sat_slave_one);
    if(abs(target_velocity_slave_one) < 2)
    {
        target_velocity_slave_one = 0;
    }

    e_pre_slave_one = e_now_slave_one;

    return true;
}
bool fm_auto::DuetflEthercatController::writePDOData_VelocityControl()
{
//    uint16_t controlword = 0xf;
    steering_cmd_new = fmutil::symbound<int32_t>(steering_cmd_new,maxSteeringCmd);
    std_msgs::Float64 cmd;
    cmd.data = steering_cmd_new;
    fm_auto::DuetflEthercatController::pub_position_cmd.publish(cmd);

    braking_cmd_new = fmutil::symbound<int32_t>(braking_cmd_new,maxBrakingCmd);
    std_msgs::Float64 cmd_braking;
    cmd_braking.data = steering_cmd_new;
    fm_auto::DuetflEthercatController::pub_braking_cmd.publish(cmd_braking);



    ecrt_domain_process(domain_output);
//    writeControlword_PDO_SlaveZero(controlword);
    if(steering_slave_number == 0)  // slave zero
    {
        calculateTargetVelocity_SlaveZero(steering_cmd_new);
        writeTargetVelocity_PDO_SlaveZero(target_velocity_slave_zero);

        if(braking_slave_number == 1)
        {
            calculateTargetVelocity_SlaveOne(braking_cmd_new);
            writeTargetVelocity_PDO_SlaveOne(target_velocity_slave_one);
        }
    }
    else if(steering_slave_number == 1)
    {
        calculateTargetVelocity_SlaveOne(steering_cmd_new);
        writeTargetVelocity_PDO_SlaveOne(target_velocity_slave_one);

        if(steering_slave_number == 0)  // slave zero
        {
            calculateTargetVelocity_SlaveZero(steering_cmd_new);
            writeTargetVelocity_PDO_SlaveZero(target_velocity_slave_zero);
        }
    }

    ecrt_domain_queue(domain_output);

    ROS_INFO("steering_cmd_new %d   target_velocity_slave_zero %d "
            ,steering_cmd_new,target_velocity_slave_zero);

    ROS_INFO("braking_cmd_new %d   target_velocity_slave_one %d "
            ,braking_cmd_new,target_velocity_slave_one);
}

bool fm_auto::DuetflEthercatController::writePDOData_SlaveZero2()
{
    uint16_t controlword;
    int beginState = positionControlState;
    // check state
    switch (positionControlState) {
      case 6:
        if(steering_cmd_current != steering_cmd_new)
        {
                steering_cmd_writing = steering_cmd_new;

                ecrt_domain_process(domain_output);
                writeTargetPosition_PDO_SlaveZero(steering_cmd_writing);
                ecrt_domain_queue(domain_output);

                positionControlState = 5;
                ROS_INFO("state %d ----> %d   n:%d w:%d c:%d 0x%04x",beginState,positionControlState,
                     steering_cmd_new,steering_cmd_writing,steering_cmd_current,controlword_PDO);
        }
      break;
    case 5:
//        if(is_TargetReached_Set)
//        {
//            controlword_PDO = 0x1f;
//        }
//        else
        {
            // check last controlword is 0x1f or 0x3f
            bool is_bit5_set = Int16Bits(controlword_PDO).test(5);
            if(is_bit5_set)
            {
                controlword_PDO = 0xf;
            }
            else
            {
                controlword_PDO = 0x3f;
            }
        }

        ecrt_domain_process(domain_output);
        writeControlword_PDO_SlaveZero(controlword_PDO);
        ecrt_domain_queue(domain_output);

        positionControlState = 4;
        ROS_INFO("state %d ----> %d   n:%d w:%d c:%d 0x%04x",beginState,positionControlState,
             steering_cmd_new,steering_cmd_writing,steering_cmd_current,controlword_PDO);
    break;
    case 4:
        if(is_TargetReached_Set)
        {
            positionControlState = 6;
            steering_cmd_current = steering_cmd_writing;
            ROS_INFO("state %d ----> %d   n:%d w:%d c:%d 0x%04x",beginState,positionControlState,
                 steering_cmd_new,steering_cmd_writing,steering_cmd_current,controlword_PDO);
        }
        else
        {
            if(is_SetPointAcknowledge_Changed)
            {
                positionControlState = 6;
                steering_cmd_current = steering_cmd_writing;
                ROS_INFO("state %d ----> %d   n:%d w:%d c:%d 0x%04x",beginState,positionControlState,
                     steering_cmd_new,steering_cmd_writing,steering_cmd_current,controlword_PDO);
            }
        }
    break;
    default:
      ROS_ERROR("position control unknow state");
      return false;
      break;
    }//switch
//    if(steering_cmd_current != steering_cmd_new)
//    {
//        ROS_INFO("state %d ----> %d   n:%d w:%d c:%d 0x%04x",beginState,positionControlState,
//             steering_cmd_new,steering_cmd_writing,steering_cmd_current,controlword_PDO);
//    }
    return true;
}

bool fm_auto::DuetflEthercatController::writePDOData_SlaveZero()
{
    // positionControlState states:
    //     target position     new_set_point       set_point_acknowledge
    // 6.   not changed,                   clear,              clear
    // 1.   changed,                    clear,              clear
    // 2.   not changed,                   setted,              clear
    // 3.   not changed,                    setted               setted
    // 4.     changed                       setted,             setted
    // 5.     not changed,                 cleard,              setted
    // 6.    not changed,                  cleard,               cleard
    if(steering_cmd_current == steering_cmd_new)
    {
        hasNewSteeringData = false;
    }
    else
        hasNewSteeringData = true;
    if(hasNewSteeringData)
    {
//        uint16_t controlword;
        int beginState = positionControlState;
        // check state
        switch (positionControlState) {
            case 6:
            if(restTick>1)
                restTick--;
            else
            {
//                isNeedHal = checkNeedHal(steering_cmd_current,steering_cmd_new);
//                if(isNeedHal && !is_TargetReached_Set)
//                {
//                    positionControlState = 9;
//                }
//                else
                {
                    if(is_TargetReached_Set)
                    {
                        ecrt_domain_process(domain_output);
                        // step 1: only write target position (p114)
                        steering_cmd_writing = steering_cmd_new;
                        writeTargetPosition_PDO_SlaveZero(steering_cmd_writing);
                        controlword_PDO = 0xf;
                        writeControlword_PDO_SlaveZero(controlword_PDO);

                        positionControlState = 1;
                        ecrt_domain_queue(domain_output);
                        restTick = 1;
                    }

                    if(!is_SetPointAcknowledge_Set)
                    {
                        ecrt_domain_process(domain_output);
                        // step 1: only write target position (p114)
                        steering_cmd_writing = steering_cmd_new;
                        writeTargetPosition_PDO_SlaveZero(steering_cmd_writing);
                        controlword_PDO = 0xf;
                        writeControlword_PDO_SlaveZero(controlword_PDO);

                        positionControlState = 1;
                        ecrt_domain_queue(domain_output);
                        restTick = 1;
                    }
                }
            }
                break;
            case 1:
            if(restTick>1)
                restTick--;
            else
            {
                ecrt_domain_process(domain_output);
                writeTargetPosition_PDO_SlaveZero(steering_cmd_writing);
                if(is_TargetReached_Set)
                    controlword_PDO = 0x1f;
                else
                    controlword_PDO = 0x3f;
                writeControlword_PDO_SlaveZero(controlword_PDO);

                positionControlState = 2;
                ecrt_domain_queue(domain_output);
            }
                break;
            case 2:

                if(is_SetPointAcknowledge_Set)
                {
//                    ecrt_domain_process(domain_output);
//                    if(steering_cmd_current != steering_cmd_new)
//                        steering_cmd_writing = steering_cmd_new;
//                    writeTargetPosition_PDO_SlaveZero(steering_cmd_writing);
//                    uint16_t controlword_PDO = 0xf;
//                    writeControlword_PDO_SlaveZero(controlword_PDO);

                    positionControlState = 3;
                    restTick = 1   ;
                    steering_cmd_current = steering_cmd_writing;
//                    hasNewSteeringData = false;
//                    ecrt_domain_queue(domain_output);
                }
//                else
//                {
//                    positionControlState = 1;
//                }
                break;
            case 3:
            if(restTick>1)
                restTick--;
            else
            {
                if(steering_cmd_current != steering_cmd_new)
                {
                    //check need hal
//                    isNeedHal = checkNeedHal(steering_cmd_current,steering_cmd_new);
//                    if(isNeedHal && !is_TargetReached_Set) // target not reach and new cmd is diff direction with last cmd
//                    {
//                        //TODO
//                        positionControlState = 7;
//                    }
//                    else
                    {
                        steering_cmd_writing = steering_cmd_new;
                        ecrt_domain_process(domain_output);
                        writeTargetPosition_PDO_SlaveZero(steering_cmd_writing);
//                        if(is_TargetReached_Set)
//                            controlword_PDO = 0x1f;
//                        else
//                            controlword_PDO = 0x3f;
//                        writeControlword_PDO_SlaveZero(controlword_PDO);

                        positionControlState = 4;
                        ecrt_domain_queue(domain_output);
                        restTick =1;
                    }
                }
            }
                break;
            case 4:
            if(restTick>1)
                restTick--;
            else
            {
                ecrt_domain_process(domain_output);
//                writeTargetPosition_PDO_SlaveZero(steering_cmd_writing);
                if(is_TargetReached_Set)
                    controlword_PDO = 0x1f;
                else
                    controlword_PDO = 0x3f;
                writeControlword_PDO_SlaveZero(controlword_PDO);

                positionControlState = 5;
                ecrt_domain_queue(domain_output);
                restTick = 1;
            }
                break;
            case 5:
            if(restTick>1)
                restTick--;
            else
                if(is_TargetReached_Set)
                {
                    positionControlState = 6;
                }
                if(!is_SetPointAcknowledge_Set)
                {
//                    ecrt_domain_process(domain_output);
//                    writeTargetPosition_PDO_SlaveZero(steering_cmd_writing);
//                    uint16_t controlword = 0xf;
//                    writeControlword_PDO_SlaveZero(controlword);

                    positionControlState = 6;

//                    steering_cmd_current = steering_cmd_writing;
//                    if(steering_cmd_current == steering_cmd_new)
//                    {
//                        hasNewSteeringData = false;
//                    }
//                    ecrt_domain_queue(domain_output);
                    restTick = 1;
                }
                break;
        case 7:
            // TODO: handle hal
            ecrt_domain_process(domain_output);
            controlword_PDO = 0x10f;//set bit 8 of controlword
            writeControlword_PDO_SlaveZero(controlword_PDO);

            positionControlState = 8;
            ecrt_domain_queue(domain_output);
            restTick =1;
            break;
        case 8:
            if(restTick>1)
                restTick--;
            else
            {
                if(is_TargetReached_Set)
                {
                    positionControlState = 3;
                }
            }
            // after hal, wait target reached bit set
            break;
        case 9:
            // TODO: handle hal
            ecrt_domain_process(domain_output);
            controlword_PDO = 0x10f;//set bit 8 of controlword
            writeControlword_PDO_SlaveZero(controlword_PDO);

            positionControlState = 10;
            ecrt_domain_queue(domain_output);
            restTick =1;
            break;
        case 10:
            if(restTick>1)
                restTick--;
            else
            {
                if(is_TargetReached_Set)
                {
                    positionControlState = 6;
                }
            }
            // after hal, wait target reached bit set
            break;
            default:
                ROS_ERROR("position control unknow state");
                return false;
                break;
        }//switch
        ROS_INFO("state %d ----> %d   n:%d w:%d c:%d 0x%04x",beginState,positionControlState,
                 steering_cmd_new,steering_cmd_writing,steering_cmd_current,controlword_PDO);
    }//if
    return true;
}
bool fm_auto::DuetflEthercatController::checkNeedHal(int32_t las_cmd, int32_t new_cmd)
{
    bool res=true;
    if(las_cmd>=0 && new_cmd>=0)
    {
        if(new_cmd >= las_cmd && velocity_actual_value>=0)
        {
            res = false;
        }
    }
    if(las_cmd<=0 && new_cmd<=0)
    {
        if(new_cmd <= las_cmd && velocity_actual_value<=0)
        {
            res = false;
        }
    }
    //TODO
    return res;
}

bool fm_auto::DuetflEthercatController::checkControllerState_SDO()
{
    uint16_t statusword_value;
    if(!getStatuswordSDO(slave0_statusword_fmsdo,statusword_value))
    {
        ROS_ERROR("checkControllerState_SDO: get statusword failed ");
        return false;
    }
    if(statusword_value != statusword_PDO_data)
    {
        statusword_PDO_data = statusword_value;
        is_SetPointAcknowledge_Set = Int16Bits(statusword_PDO_data).test(12); //p94,114 check set_point_acknowledge
        is_TargetReached_Set = Int16Bits(statusword_PDO_data).test(10);
        ROS_INFO("checkControllerState_SDO: statusword 0x%04x",statusword_PDO_data);
    }
    fm_auto::CONTROLLER_STATE state = fm_auto::CS_UNKNOWN_STATE;
    if(!getControllerStateByStatusword(statusword_value,state))
    {
        ROS_ERROR("checkControllerState_SDO: analyst controller state failed 0x%04x",statusword_value);
        return false;
    }
    PDO_OK = true;
    switch (state) {
        case fm_auto::CS_FAULT: // request was not used yet
            ROS_ERROR("readPDOsData: CS_FAULT");
            //TODO: error handle
            PDO_OK = false;
            break;
    default:
//        ROS_ERROR("enableControlSDO: unkown state %04x",state);
        return true;
    }
    return true;
}

bool fm_auto::DuetflEthercatController::readPDOsData()
{
    uint16_t statusword = EC_READ_U16(domain_input_pd + fm_auto::OFFSET_STATUSWORD);
    if(statusword != statusword_PDO_data)
    {
        statusword_PDO_data = statusword;
        bool is_SetPointAcknowledge_Set_tmp = Int16Bits(statusword_PDO_data).test(12); //p94,114 check set_point_acknowledge
        if(is_SetPointAcknowledge_Set != is_SetPointAcknowledge_Set_tmp)
        {
            is_SetPointAcknowledge_Set = is_SetPointAcknowledge_Set_tmp;
            is_SetPointAcknowledge_Changed = true;
        }

        is_TargetReached_Set = Int16Bits(statusword_PDO_data).test(10);
        ROS_INFO("readPDOsData: statusword 0x%04x",statusword_PDO_data);
    }
    ROS_INFO("readPDOsData: statusword 0x%04x",statusword_PDO_data);
    position_actual_value_PDO_data_slave_zero = EC_READ_S32(domain_input_pd + fm_auto::OFFSET_POSITION_ACTURAL_VALUE);
    velocity_actual_value_PDO_data = EC_READ_S32(domain_input_pd + fm_auto::OFFSET_VELOCITY_ACTUAL_VALUE);
    current_actual_value_PDO_data = EC_READ_S16(domain_input_pd + fm_auto::OFFSET_CURRENT_ACTURAL_VALUE);
    torque_actual_value_PDO_data = EC_READ_S16(domain_input_pd + fm_auto::OFFSET_TORQUE_ACTURAL_VALUE);
        printf("pdo pos: %04d  vel: %04d cur: %04d tor: %04d\n",
                position_actual_value_PDO_data_slave_zero, velocity_actual_value_PDO_data, current_actual_value_PDO_data, torque_actual_value_PDO_data);
    etherlab_master::EthercatPDO pdo_msg;
    pdo_msg.position = position_actual_value_PDO_data_slave_zero;
    pdo_msg.velocity = velocity_actual_value_PDO_data;
    pdo_msg.current = current_actual_value_PDO_data;
    pdo_msg.torque = torque_actual_value_PDO_data;
    fm_auto::DuetflEthercatController::pub.publish(pdo_msg);

    // slave one
    position_actual_value_PDO_data_slave_one = EC_READ_S32(domain_input_pd + fm_auto::OFFSET_POSITION_ACTURAL_VALUE_SLAVE_ONE);
    velocity_actual_value_PDO_data_slave_one = EC_READ_S32(domain_input_pd + fm_auto::OFFSET_VELOCITY_ACTUAL_VALUE_SLAVE_ONE);
    current_actual_value_PDO_data_slave_one = EC_READ_S16(domain_input_pd + fm_auto::OFFSET_CURRENT_ACTURAL_VALUE_SLAVE_ONE);
    printf("slave one pdo pos: %04d  vel: %04d cur: %04d \n",
            position_actual_value_PDO_data_slave_one, velocity_actual_value_PDO_data_slave_one, current_actual_value_PDO_data_slave_one);

//    printf("pdo statusword value: %04x offset %u\n",
//            EC_READ_U16(domain_input_pd + OFFSET_STATUSWORD),OFFSET_STATUSWORD);
    
    fm_auto::CONTROLLER_STATE state = fm_auto::CS_UNKNOWN_STATE;
    if(!getControllerStateByStatusword(statusword,state))
    {
        ROS_ERROR("enableControlSDO: analyst controller state failed 0x%04x",statusword);
        return false;
    }

    // read velocity
    velocity_actual_value = EC_READ_U16(domain_input_pd + fm_auto::OFFSET_VELOCITY_ACTUAL_VALUE);
//    ROS_INFO("readPDOsData: velocity_actual_value %d",velocity_actual_value);
    PDO_OK = true;
    switch (state) {
        case fm_auto::CS_FAULT: // request was not used yet
            ROS_ERROR("readPDOsData: CS_FAULT");
            //TODO: error handle
//            return false;
            PDO_OK = false;
            break;
//        case fm_auto::CS_SWITCH_ON_DISABLED:
//            return false;
//            break;
//        case fm_auto::CS_READY_TO_SWITCH_ON:
//            return false;
//            break;
//        case fm_auto::CS_SWITCH_ON:
//            return false;
//            break;
//        case fm_auto::CS_OPERATION_ENABLE:
//            // controller enabled
//            return true;
//            break;
//        case fm_auto::CS_NOT_READY_TO_SWITCH_ON:
//            return false;
//            break;
    default:
//        ROS_ERROR("enableControlSDO: unkown state %04x",state);

        return true;
    }
    return true;
}

bool fm_auto::DuetflEthercatController::processSDOs()
{
    // check has sdos to send?
    std::list<fm_auto::fm_sdo*> sdoPool;
    if(!activeSdoPool.empty())
    {
        std::list<fm_sdo*>::iterator it;
        for(it=activeSdoPool.begin();it!=activeSdoPool.end();++it)
        {
            fm_auto::fm_sdo *fmSdo = *it;
            if(!fmSdo->isOperate) // never operate before
            {
                sdoPool.push_back(fmSdo);
                // check upload or download
                if(fmSdo->isReadSDO)
                {
                    ecrt_sdo_request_read(fmSdo->sdo);
                }
                else{
                    ecrt_sdo_request_write(fmSdo->sdo);
                }
                fmSdo->isOperate=true;
            }
            else
            {
                // check state
                switch (ecrt_sdo_request_state(fmSdo->sdo)) {
                    case EC_REQUEST_UNUSED: // request was not used yet
                        break;
                    case EC_REQUEST_BUSY:
        //                printf( "Still busy...\n");
                    sdoPool.push_back(fmSdo);
                        break;
                    case EC_REQUEST_SUCCESS:
                    // remove from list
                        fmSdo->isOperate = false;
                        fmSdo->callback();
                        break;
                    case EC_REQUEST_ERROR:
                        ROS_ERROR("Failed to operate SDO %s!\n",fmSdo->descrption.c_str());
                        break;
                }//switch
            }//else
        }//for
            activeSdoPool.clear();
            activeSdoPool = sdoPool;

    }//if
}
void fm_auto::DuetflEthercatController::testGetStatuswordSDO()
{
    ROS_INFO("testGetStatusword\n");
//    while (1) {
////        pause();

//        ros::spinOnce();
//        // receive process data
//        ecrt_master_receive(master);
//        ecrt_domain_process(domain_output);
//        ecrt_domain_process(domain_input);


//        // check process data state (optional)
//    //    check_domain1_state();

//        // check for master state (optional)
//        check_master_state();

//        // check for islave configuration state(s) (optional)
//    //    check_slave_config_states();
    HOMING_METHOD method;
    if(getMotorHomingMethodSDO(slave0_homing_method_fmSdo,method))
    {
        ROS_INFO("testGetStatuswordSDO: get homing method %d",method);
    }
    else
    {
        ROS_ERROR("testGetStatuswordSDO: homing method failed");
    }
//        // read PDO data
////        readPDOsData();

//        // send process data
//        ecrt_domain_queue(domain_output);
//        ecrt_domain_queue(domain_input);
//        ecrt_master_send(master);

//    }

}
void fm_auto::DuetflEthercatController::testGetHomingMethodSDO_SlaveZero()
{
    ROS_INFO("testGetHomingMethod");
    fm_auto::HOMING_METHOD method;
    getMotorHomingMethodSDO(slave0_homing_method_fmSdo,method);
}
void fm_auto::DuetflEthercatController::test_getMotorOperatingModeSDO_SlaveZero()
{
//    testGetHomingMethodSDO_SlaveZero();
    ROS_INFO("test_getMotorOperatingModeSDO_SlaveZero");
    fm_auto::OPERATION_MODE mode;
    getMotorOperatingModeSDO(fm_auto::slave0_operation_mode_display_fmsdo,mode);
}

void fm_auto::DuetflEthercatController::testEnableControllerSDO()
{
    ROS_INFO("testEnableControllerSDO");
    enableControlSDO(slave0_statusword_fmsdo,slave0_controlword_fmsdo);
}
void fm_auto::DuetflEthercatController::testOperateHomingMethod_SlaveZero()
{
    // slave zero(steering motor) position zero
    // 1. set operating mode to homing
ROS_INFO("dddd1");
    if(!setSlaveZeroMotorOperatingMode2Homing())
    {
        ROS_ERROR("init: setSlaveZeroMotorOperatingMode2Homing failed");
        return ;
    }
ROS_INFO("dddd2");
    // 2. enable controller
    if(!enableControlSDO(fm_auto::slave0_statusword_fmsdo,fm_auto::slave0_controlword_fmsdo))
    {
        ROS_ERROR("init: enableControlSDO failed");
        return ;
    }
    // 3. trigger homing operation
    if(!operateSteeringMotorHomingMethod_SlaveZero())
    {
        ROS_ERROR("init: operateSteeringMotorHomingMethod failed");
        return ;
    }
    return ;
}
void fm_auto::DuetflEthercatController::test_goToPositionNewSetPoint_SDO_SlaveZero()
{
    // make sure already conduct homing
    // enable controller
    // target position set from cmdline
    // set to profile position mode
    if(!setSlaveZeroMotorOperatingMode2ProfilePosition())
    {
        ROS_ERROR(" set profle position failed");
        return ;
    }
    // set motor operating mode to profile position mode
    if(!enableControlSDO(slave0_statusword_fmsdo,slave0_controlword_fmsdo))
    {
        ROS_ERROR(" enableControlSDO failed");
        return ;
    }
    //
    if(!goToPositionNewSetPoint_SDO_SlaveZero())
    {
        ROS_ERROR(" trigger new_set_point failed");
        return ;
    }
//    // run 20 sec
//    sleep(20);
}
void fm_auto::DuetflEthercatController::test_goToPositionChangeSetImt_SDO_SlaveZero()
{
    // make sure already conduct homing
    // enable controller
    // target position set from cmdline

    // set motor operating mode to profile position mode
    if(!enableControlSDO(slave0_statusword_fmsdo,slave0_controlword_fmsdo))
    {
        ROS_ERROR(" enableControlSDO failed");
        return ;
    }
    // set to profile position mode
    if(!setSlaveZeroMotorOperatingMode2ProfilePosition())
    {
        ROS_ERROR(" set profle position failed");
        return ;
    }
    //
    if(!goToPositionChangeSetImt_SDO_SlaveZero())
    {
        ROS_ERROR(" trigger change_set_immediately failed");
        return ;
    }
}
