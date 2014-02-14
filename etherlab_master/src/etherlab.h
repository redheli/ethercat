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

/****************************************************************************/
#include "ros/ros.h"
#include "ecrt.h"
#include "ObjectDictionay.h"


namespace fm_auto
{

class DuetflEthercatController
{
    struct fm_sdo
    {
        ec_sdo_request_t sdo;
        std::string descrption;
    };

public:
       DuetflEthercatController();
       /// loop trigger
       void run();
       bool init();
       void cyclic_task();

public:
       /// @brief get homing operation mode
       /// @param slave_config slave point
       /// @return HOMING_METHOD
       fm_auto::HOMING_METHOD getMotorHomingMode(const ec_slave_config_t *slave_config);
       /// set homing operation mode
       /// @param hm slave set to which homing method
       /// @return success = true, failure = false
       bool setMotorHomingMode(fm_auto::HOMING_METHOD &hm);

       bool conductHomingOperation();

       /// @brief get operating mode
       /// @param slave_config slave point
       /// @return OPERATIN_MODE
       fm_auto::OPERATIN_MODE getMotorOperatingMode(const ec_slave_config_t *slave_config);
       bool setMotorOperatingMode(OPERATIN_MODE);

       /// do check target velocity ,check target position before trigger the motor
       /// make sure motor shaft rolling is safe
       bool enableControl();

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
       std::vector<fm_sdo> activeSdoPool;

       u_int FREQUENCY;
       struct itimerval tv;

};

}// fm_auto
#endif
