#ifndef __ETHERLAB_MASTER_H__
#define __ETHERLAB_MASTER_H__

#include <ros/ros.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <tr1/functional>
#include <bitset>
/****************************************************************************/
#include "ros/ros.h"
#include "ecrt.h"
#include "ObjectDictionay.h"

typedef std::bitset<16> Int16Bits;

namespace fm_auto
{
class fm_sdo
{
public:
    typedef std::tr1::function<void()> CallbackFunc;
    fm_sdo():sdo(NULL),isReadSDO(true),isOperate(false) {}
    ec_sdo_request_t *sdo;
    std::string descrption;
    bool isReadSDO;
    bool isOperate; // the sdo has been operated
    CallbackFunc callback;
};
class DuetflEthercatController
{


public:
       DuetflEthercatController();
       /// loop trigger
       void run();
       bool init();
       bool initEthercat();
       bool initSDOs();
       void cyclic_task();

public:
       /// trigger home position,shall be current position
       bool operateHomingMethod();

public:
       // sdo method
       bool sendOneReadSDO(fm_sdo* fmSdo_read);
       bool sendOneWriteSDO(fm_sdo* fmSdo_write);
       bool processSDOs();
       bool checkSDORequestState(fm_sdo* fmSdo);


public:
       // pdo method
       bool readPDOsData();
       bool writePdoTargetPosition(int32_t &value);
       bool writePdoControlword(uint16_t &value);

public:
       /// @brief get homing operation mode
       /// @param slave_config slave point
       /// @return HOMING_METHOD
       fm_auto::HOMING_METHOD getMotorHomingMode(const ec_slave_config_t *slave_config);
       /// set homing operation mode
       /// @param hm slave set to which homing method
       /// @return success = true, failure = false
       bool setMotorHomingMode(fm_auto::HOMING_METHOD &hm);

       uint16_t getStatusword(fm_sdo *statusword_fmsdo);
       bool setControlword(fm_sdo *controlword_fmsdo,uint16_t &value);

//       bool conductHomingOperation();

       /// @brief get operating mode
       /// @param slave_config slave point
       /// @return OPERATIN_MODE
       fm_auto::OPERATIN_MODE getMotorOperatingMode(const ec_slave_config_t *slave_config);
       bool setMotorOperatingMode(OPERATIN_MODE);

       /// do check target velocity ,check target position before trigger the motor
       /// make sure motor shaft rolling is safe
       bool enableControl();

       void check_master_state();

       static void disable_operation();
       static void my_sig_handler(int signum);
       static void signal_handler(int signum);
       static void writeSdoControlword(uint16_t &value);

       // position control

       /// get target position setted in 0x607A
       int getTargetPositionSetting();
       /// set target position to 0x607A
       bool setTargetPosition(int &value);

       /// 0x6081
       u_int32_t getProfileVelocity();
       bool setProfileVelocity();

       /// 0x6083
       u_int32_t getProfileAcceleration();
       bool setProfileAcceleration();

       /// 0x6084
       u_int32_t getProfilDeceleration();
       bool setProfileDeceleration(u_int32_t &value);

       /// 0x6085
       u_int32_t getQuickStopDeceleration();
       bool setQuickStopDeceleration(u_int32_t &value);

       /// 0x6086
       u_int16_t getMotionProfileType();
       /// @param value, 0=linear ramp ,1=jerk-less acceleration
       bool setMotionProfileType(u_int16_t &value);

private:
       /// download value to address
       bool setValueToAddress(uint &address);

private:
       /// store sdo request
       std::list<fm_sdo*> activeSdoPool;

       u_int FREQUENCY;
       struct itimerval tv;
       struct sigaction sa;

       // EtherCAT
       ec_master_t *master;
       ec_master_state_t master_state;
       ec_domain_t *domain_output;
       ec_domain_t *domain_input;

       uint8_t *domain_output_pd;
       uint8_t *domain_input_pd;

       fm_sdo *slave0_operation_mode_display_fmsdo;
       fm_sdo *slave0_homing_method_fmSdo;

       fm_sdo *slave0_statusword_fmsdo;
       fm_sdo *slave0_controlword_fmsdo;

//       static ec_sdo_request_t *slave0_sdo_operation_mode_display;
//       static ec_sdo_request_t *slave0_sdo_statusword_read;
//       static ec_sdo_request_t *slave0_sdo_velocity_demand_value_read;

//       static ec_sdo_request_t *slave0_sdo_operation_mode_write;
//       static ec_sdo_request_t *slave0_sdo_controlword_write;

};

}// fm_auto
#endif
