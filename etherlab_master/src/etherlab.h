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
#include <pthread.h>
/****************************************************************************/
#include "ros/ros.h"
#include <sensor_msgs/Joy.h>
#include <std_msgs/Float64.h>
//#include "etherlab_master/steering.h"
#include "ecrt.h"
#include "ObjectDictionay.h"

typedef std::bitset<16> Int16Bits;

namespace fm_auto
{
class DuetflEthercatController;

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
    DuetflEthercatController* controller;
};
class DuetflEthercatController
{


public:
       DuetflEthercatController();
       ~DuetflEthercatController();
       /// loop trigger
       void run();
       bool init();
       bool initEthercat();
       bool initSDOs();
       bool initROS();
       bool cyclic_task();
       bool cyclic_task_SDO();

       /* ROS callback */
//       void callback_steering(const etherlab_master::steering::ConstPtr& steering_cmd);
       void callback_steering2(std_msgs::Float64 steering_cmd);

public:
       /* homing */
       bool setHomingMethod2CurrentPosition(fm_sdo* homing_method_fmSdo);
       /// trigger home position,shall be current position
       bool operateSteeringMotorHomingMethod();

public:
       // sdo method
       bool sendOneReadSDO(fm_sdo* fmSdo_read);
       bool sendOneWriteSDO(fm_sdo* fmSdo_write);
       bool processSDOs();
       bool checkSDORequestState(fm_sdo* fmSdo);
       bool waitSDORequestSuccess(fm_sdo* fmSdo,bool isRead);
       bool checkControllerState_SDO();
       bool writeControllerData_SDO_SlaveZero();


public:
       // pdo method
       bool readPDOsData();
       bool writeTargetPosition_PDO_SlaveZero(int32_t &value);
       bool writeControlword_PDO_SlaveZero(uint16_t &value);
       bool writePDOData_SlaveZero();

public:
       /// @brief get homing operation mode
       /// @param fm sdo class
       /// @return HOMING_METHOD
//       fm_auto::HOMING_METHOD getMotorHomingMode(fm_sdo *homing_operation_mode_fmsdo);
       /// @brief get homing operation method by SDO
       bool getMotorHomingMethodSDO(fm_sdo *homing_operation_mode_fmsdo, HOMING_METHOD &method);
       /// set homing operation mode
       /// @param hm slave set to which homing method
       /// @return success = true, failure = false
       bool setMotorHomingModeSDO(fm_sdo *homing_operation_mode_fmsdo,fm_auto::HOMING_METHOD &hm);

       bool getStatuswordSDO(fm_sdo *statusword_fmsdo,uint16_t &value);
       bool setControlwordSDO(fm_sdo *controlword_fmsdo,uint16_t &value);
       /// @brief get controller state according to the statusword
       bool getControllerStateByStatusword(uint16_t &value,fm_auto::CONTROLLER_STATE &state);

//       bool conductHomingOperation();

       /// @brief get operating mode
       /// @param slave_config slave point
       /// @return success or failed
       bool getMotorOperatingModeSDO(fm_sdo *operation_mode_display_fmsdo,fm_auto::OPERATION_MODE &mode);
       bool setMotorOperatingModeSDO(fm_sdo *sdo_operation_mode_write,fm_auto::OPERATION_MODE &value);

       bool setSlaveZeroMotorOperatingMode2ProfilePosition();
       bool setSlaveZeroMotorOperatingMode2Homing();

       /* controller */
       /// @brief send SDO to enable control
       /// do check target velocity ,check target position before trigger the motor
       /// make sure motor shaft rolling is safe
       bool enableControlSDO(fm_sdo *statusword_fmSdo,fm_sdo *controlword_fmSdo);
       bool enableControlSDO_SlaveZero();
       static void disableControlSDO(fm_sdo *statusword_fmSdo,fm_sdo *controlword_fmSdo);
       bool disableControlSDO_bool(fm_sdo *statusword_fmSdo,fm_sdo *controlword_fmSdo);
       bool disableControlSDO_SlaveZero();


       void check_master_state();

//       static void disable_operation();
       static void my_sig_handler(int signum);
       static void signal_handler(int signum);
//       static void writeSdoControlword(uint16_t &value);

       /* position control */
       /// @brief motor go to target position ,only set new_set_point (controlword bit 4)
       ///        current positioning order will be processed before starting a new one.
       bool goToPositionNewSetPoint_SDO_SlaveZero();
       /// @brief only use when controller enabled
       bool clearNewSetPoint_ChangeSetPoint_SDO_SlaveZero();
       /// @brief motor go to target position ,set both new_set_point (controlword bit 4) and
       ///        change_set_immediatly (bit 5) together
       ///        current positioning order will be interrupted by the new one.
       bool goToPositionChangeSetImt_SDO_SlaveZero();
       /// get target position setted in 0x607A
       bool getSlaveZeroTargetPositionSetting(int32_t &target_position);
       /// set target position to 0x607A
       bool setSlaveZeroTargetPosition(int32_t &value);

       bool getPositionActualValue(fm_sdo* position_actual_value_fmSdo,int32_t &value);

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
       ec_master_state_t master_state;
       ec_domain_t *domain_output;
//       ec_domain_t *domain_output_controlword;
//       ec_domain_t *domain_output_target_position;
       ec_domain_t *domain_input;

       uint8_t *domain_output_pd;
       uint8_t *domain_input_pd;

       ros::Subscriber sub;
       int32_t steering_cmd_new;
       int32_t steering_cmd_writing;
       int32_t steering_cmd_current;

       bool hasNewSteeringData;
       uint16_t statusword_PDO_data;
       bool PDO_OK;

       bool needWrite_0xf_2controlword;
       int positionControlState;
       int restTick;
       bool is_SetPointAcknowledge_Set;
       bool is_TargetReached_Set;

//       std::mutex counter_mutex;

//       static fm_sdo *slave0_operation_mode_display_fmsdo;
//       static fm_sdo *slave0_operation_mode_write_fmsdo;
//       static fm_sdo *slave0_homing_method_fmSdo;

//       static fm_sdo *slave0_statusword_fmsdo;
//       static fm_sdo *slave0_controlword_fmsdo;

//       static fm_sdo *slave0_position_actual_value_fmsdo;

//       static ec_sdo_request_t *slave0_sdo_operation_mode_display;
//       static ec_sdo_request_t *slave0_sdo_statusword_read;
//       static ec_sdo_request_t *slave0_sdo_velocity_demand_value_read;

//       static ec_sdo_request_t *slave0_sdo_operation_mode_write;
//       static ec_sdo_request_t *slave0_sdo_controlword_write;

public:
       /// @brief test get statusword
       void testGetStatuswordSDO();
       /// @brief test get homing method
       void testGetHomingMethodSDO_SlaveZero();
       void test_getMotorOperatingModeSDO_SlaveZero();
       /// @brief test enable controller use SDO
       void testEnableControllerSDO();
       void testOperateHomingMethod_SlaveZero();
       void test_goToPositionNewSetPoint_SDO_SlaveZero();
       void test_goToPositionChangeSetImt_SDO_SlaveZero();
};

}// fm_auto
#endif
