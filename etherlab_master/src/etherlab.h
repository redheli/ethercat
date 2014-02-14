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

#include "ecrt.h"
#include "ObjectDictionay.h"


namespace fm_auto
{

class EtherlabMaster
{
   public:
       EtherlabMaster();
       /// loop trigger
       void run();

public:
       /// get homing operation mode
       /// @param slave_config slave point
       /// @return HOMING_METHOD
       fm_auto::HOMING_METHOD getMotorHomingMode(const ec_slave_config_t *slave_config);

       /// set homing operation mode
       /// @param hm slave set to which homing method
       /// @return success = true, failure = false
       bool setMotorHomingMode(fm_auto::HOMING_METHOD &hm);

       bool conductHomingOperation();

       /// get operating mode
       /// @param slave_config slave point
       /// @return OPERATIN_MODE
       fm_auto::OPERATIN_MODE getMotorOperatingMode(const ec_slave_config_t *slave_config);

       bool setMotorOperatingMode(OPERATIN_MODE);

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

};

}// fm_auto
#endif
