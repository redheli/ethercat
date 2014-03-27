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
#include <etherlab_master/EthercatPDO.h>

#include <fmutil/fm_math.h>
#include <fmutil/fm_filter.h>

typedef std::bitset<16> Int16Bits;

namespace fm_auto
{
class DuetflEthercatController;

class fm_sdo
{
public:
    typedef std::tr1::function<void()> CallbackFunc;
    fm_sdo():sdo(NULL),isReadSDO(true),isOperate(false) 
    {
    }
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
       bool initEthercat_SlaveOne();
       bool initSDOs_SlaveZero();
       bool initSDOs_SlaveOne();
       bool initROS();
       bool cyclic_task();
       bool cyclic_task_SDO();
       bool enable_mode;
       /* ROS callback */
//       void callback_steering(const etherlab_master::steering::ConstPtr& steering_cmd);
       void callback_steering2(std_msgs::Float64 steering_cmd);
       void callback_braking(std_msgs::Float64 braking_cmd);
       void callback_joy(sensor_msgs::Joy joy_cmd);
public:
       /* homing */
       bool setHomingMethod2CurrentPosition(fm_sdo* homing_method_fmSdo);
       /// trigger home position,shall be current position
       bool operateSteeringMotorHomingMethod_SlaveZero();
       bool operateSteeringMotorHomingMethod_SlaveOne();

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
       bool writeTargetPosition_PDO_SlaveOne(int32_t &value);
       bool writeTargetVelocity_PDO_SlaveZero(int32_t &value);
       bool writeTargetVelocity_PDO_SlaveOne(int32_t &value);
       bool writeControlword_PDO_SlaveZero(uint16_t &value);
       bool writeControlword_PDO_SlaveOne(uint16_t &value);
       bool writePDOData_SlaveZero();
       bool writePDOData_SlaveZero2();//only 3 state
       bool calculateTargetVelocity_SlaveZero(int32_t &target_pos); // use pid calculate target velocity slave 0
       bool calculateTargetVelocity_SlaveOne(int32_t &target_pos);
       bool writePDOData_VelocityControl(); // use velocity mode
       bool writePDOData_SlaveZero3();//only change_set_immediately is set

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
       bool setSlaveZeroMotorOperatingMode2ProfileVelocity();
       bool setSlaveZeroMotorOperatingMode2Homing();

       bool doHoming_SlaveZero();

       //slave one
       bool setSlaveOneMotorOperatingMode2Homing();
       bool setSlaveOneMotorOperatingMode2ProfileVelocity();
       bool doHoming_SlaveOne();
       /* controller */
       /// @brief send SDO to enable control
       /// do check target velocity ,check target position before trigger the motor
       /// make sure motor shaft rolling is safe
       bool enableControlSDO(fm_sdo *statusword_fmSdo,fm_sdo *controlword_fmSdo);
       bool enableControlSDO_SlaveZero();
       bool enableControlSDO_SlaveOne();
       static void disableControlSDO(fm_sdo *statusword_fmSdo,fm_sdo *controlword_fmSdo);
       bool disableControlSDO_bool(fm_sdo *statusword_fmSdo,fm_sdo *controlword_fmSdo);
       bool disableControlSDO_SlaveZero();
       bool disableControlSDO_SlaveOne();


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
       bool checkNeedHal(int32_t las_cmd,int32_t new_cmd);

public:
       bool hasSlaveOne; // has two motor connected to master
       bool needDoHoming_SlaveZero; // do homing operate , normally do once
       bool needDoHoming_SlaveOne;
       int steering_slave_number; // steering motor is which slave, default shall be slave one
       int braking_slave_number; // braking motor is which slave ,default slave zero
private:
       /// store sdo request
       std::list<fm_sdo*> activeSdoPool;

       u_int FREQUENCY;
       struct itimerval tv;
       struct sigaction sa;

       // EtherCAT
       ec_master_state_t master_state;
       ec_domain_t *domain_output;
       ec_domain_t *domain_output_target_velocity;
//       ec_domain_t *domain_output_controlword;
//       ec_domain_t *domain_output_target_position;
       ec_domain_t *domain_input;

       uint8_t *domain_output_pd;
       uint8_t *domain_output_target_velocity_pd;
       uint8_t *domain_input_pd;

       ros::Subscriber sub, emergency_button_sub,braking_sub;
       ros::Publisher pub;
       ros::Publisher pub_position_cmd,pub_braking_cmd;
       int32_t steering_cmd_new;
       int32_t braking_cmd_new;
       int32_t steering_cmd_writing;
       int32_t steering_cmd_current;

       bool hasNewSteeringData;
       bool isNeedHal;// when new position cmd is diff direction of last cmd, need hal

       // slave zero PDO data
       uint16_t statusword_PDO_data;
       int32_t position_actual_value_PDO_data_slave_zero;
       int32_t velocity_actual_value_PDO_data;
       int16_t current_actual_value_PDO_data;
       int16_t torque_actual_value_PDO_data;
       uint32_t velocity_actual_value;
       // slave one PDO data
       int32_t position_actual_value_PDO_data_slave_one;
       int32_t velocity_actual_value_PDO_data_slave_one;
       int16_t current_actual_value_PDO_data_slave_one;

       bool PDO_OK;

       bool needWrite_0xf_2controlword;
       int positionControlState;
       uint16_t controlword_PDO;
       int restTick;
       bool is_SetPointAcknowledge_Set;
       bool is_SetPointAcknowledge_Changed;
       bool is_TargetReached_Set;
public:
       fmutil::LowPassFilter vFilter;
       int32_t maxSteeringCmd;
       int32_t maxBrakingCmd;
       int32_t target_velocity_slave_zero;
       int32_t target_velocity_slave_one;
       double kp;
       double ki;
       double kd;

       double kp_sat;
       double ki_sat;
       double kd_sat;
       double v_sat; //velocity limit

       double dt;
       ros::Time last_time;
       ros::Time current_time;
       double e_now;
       double iTerm;
       double e_pre;

       //slave one PID para
       double kp_slave_one;
       double ki_slave_one;
       double kd_slave_one;

       double kp_sat_slave_one;
       double ki_sat_slave_one;
       double kd_sat_slave_one;
       double v_sat_slave_one; //velocity limit

       double e_now_slave_one;
       double iTerm_slave_one;
       double e_pre_slave_one;

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
