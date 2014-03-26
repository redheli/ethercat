#ifndef __OBJECT_DICTIONARY_H__
#define __OBJECT_DICTIONARY_H__

#include "ecrt.h"
#include "etherlab.h"
#include <pthread.h>

namespace fm_auto
{
class fm_sdo;

enum HOMING_METHOD
{
    HM_Method_1 = -1, //Negative stop evaluating the zero impulse
    HM_current_position= 35,

    HM_fail = 100
};

enum OPERATION_MODE
{
    OM_PROFILE_POSITION_MODE=1,
    OM_PROFILE_VELOCITY_MODE=2,
    OM_TORQUE_PROFILE_MODE=3,
    OM_HOMING_MODE=6,
    OM_UNKNOW_MODE=9

};
enum OPERATION_MODE_DISPALY
{
    OMD_PROFILE_POSITION_MODE=1,
    OMD_PROFILE_VELOCITY_MODE=3

};
// canopen doc p91
enum CONTROLLER_STATE
{
    CS_NOT_READY_TO_SWITCH_ON = 0x0000,
    CS_QUICK_STOP_ACTIVE = 0x0007,
    CS_FAULT = 0x000F,
    CS_READY_TO_SWITCH_ON = 0x0021,
    CS_SWITCH_ON = 0x0023,
    CS_OPERATION_ENABLE = 0x0027,
    CS_SWITCH_ON_DISABLED = 0x0040,
    CS_UNKNOWN_STATE = 0xffff

};

static unsigned int OFFSET_CONTROLWORD;/* Controlword */
static unsigned int OFFSET_PROFILE_VELOCITY;/* Profile_Velocity */
static unsigned int OFFSET_PROFILE_ACCELERATION;/* Profile_Acceleration */
static unsigned int OFFSET_MODE_OF_OPERATION;/* Mode_of_Operation */
static unsigned int OFFSET_HOMING_METHOD;/* Homing_Method */
static unsigned int OFFSET_TARGET_POSITION;/* Target_Position */
static unsigned int OFFSET_TARGET_VELOCITY;/* Target_Velocity */
static unsigned int OFFSET_TARGET_TORQUE;/* Target_Torque */

static unsigned int OFFSET_STATUSWORD;/* Statusword */
static unsigned int OFFSET_POSITION_ACTURAL_VALUE;/* Position_Actual_Value */
static unsigned int OFFSET_CURRENT_ACTURAL_VALUE;/* Current_Actual_Value */
static unsigned int OFFSET_MODES_OF_OPERATION_DISPLAY;/* Modes_Of_Operation_Display */
static unsigned int OFFSET_REGISTER;/* Error_Register */
static unsigned int OFFSET_VELOCITY_ACTUAL_VALUE;/* Velocity_Actual_Value */
static unsigned int OFFSET_TORQUE_ACTURAL_VALUE;/* Torque_Actual_Value */

#define ADDRESS_MODES_OF_OPERATION_DISPLAY  0x6061
#define ADDRESS_MODES_OF_OPERATION          0x6060
#define ADDRESS_HOMING_METHOD               0X6098
#define ADDRESS_CONTROLWORD                 0x6040
#define ADDRESS_STATUSWORD                  0x6041
#define ADDRESS_POSITION_ACTUAL_VALUE       0x6064
#define ADDRESS_TARGET_POSITION             0x607a
#define READ  true
#define WRITE false

// current only have one slave
#define SlaveZeroAliasAndPosition  0, 0
#define VendorID_ProductCode  0x000000e4, 0x00001133

const static ec_pdo_entry_reg_t domain_output_regs[] = {
    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6040, 0, &OFFSET_CONTROLWORD,NULL},
    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6081, 0, &OFFSET_PROFILE_VELOCITY,NULL},
    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x60ff, 0, &OFFSET_TARGET_VELOCITY,NULL},
    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6083, 0, &OFFSET_PROFILE_ACCELERATION,NULL},
    {}
};
const static ec_pdo_entry_reg_t domain_output_regs_target_velocity[] = {
    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x60ff, 0, &OFFSET_TARGET_VELOCITY,NULL},
    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6083, 0, &OFFSET_PROFILE_ACCELERATION,NULL},
    {}
};
const static ec_pdo_entry_reg_t domain_input_regs[] = {
    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6061, 0, &OFFSET_MODES_OF_OPERATION_DISPLAY,NULL},
    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6041, 0, &OFFSET_STATUSWORD,NULL},
    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x606c, 0, &OFFSET_VELOCITY_ACTUAL_VALUE,NULL},
    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x1001, 0, &OFFSET_REGISTER,NULL},
    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6064, 0, &OFFSET_POSITION_ACTURAL_VALUE,NULL},
    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6078, 0, &OFFSET_CURRENT_ACTURAL_VALUE,NULL},
    //{SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6077, 0, &OFFSET_TORQUE_ACTURAL_VALUE, NULL},
    {}
};

static ec_pdo_entry_info_t slave_0_pdo_entries[] = {
    {0x6040, 0x00, 16}, /* Controlword */
    {0x6081, 0x00, 32}, /* Profile_Velocity */

    {0x60ff, 0x00, 32}, /* Target_Velocity */
    {0x6083, 0x00, 32}, /* Profile_Acceleration */


    {0x6061, 0x00, 8}, /* Modes_Of_Operation_Display */
    {0x6041, 0x00, 16}, /* Statusword */
    {0x606c, 0x00, 32}, /* Velocity_Actual_Value */
    {0x1001, 0x00, 8}, /* Error_Register */

    {0x6064, 0x00, 32}, /* Position_Actual_Value */
    {0x6078, 0x00, 16}, /* Current_Actual_Value */
//    {0x606c, 0x00, 32}, /* Velocity_Actual_Value */
//    {0x6077, 0x00, 16}, /* Torque_Actual_Value */
};
static ec_pdo_info_t slave_0_pdos[] = {
    {0x1600, 2, slave_0_pdo_entries + 0}, /* Outputs */
    {0x1601, 2, slave_0_pdo_entries + 2}, /* Outputs */
    {0x1A00, 4, slave_0_pdo_entries + 4}, /* Inputs */
    {0x1A01, 2, slave_0_pdo_entries + 8}, /* Inputs */
};

static ec_sync_info_t slave_0_syncs[] = {
    {0, EC_DIR_OUTPUT, 0, NULL, EC_WD_DISABLE},
    {1, EC_DIR_INPUT, 0, NULL, EC_WD_DISABLE},
    {2, EC_DIR_OUTPUT, 2, slave_0_pdos + 0, EC_WD_DISABLE},
    {3, EC_DIR_INPUT, 2, slave_0_pdos + 2, EC_WD_DISABLE},
    {0xff}
};

// slave
static ec_master_t *master = NULL;
static ec_slave_config_t *slave_zero = NULL;
static ec_slave_config_state_t sc_ana_in_state = {};

static ec_sdo_request_t *slave0_sdo_operation_mode_display = NULL;
static ec_sdo_request_t *slave0_sdo_homing_method = NULL;
static ec_sdo_request_t *slave0_sdo_statusword_read = NULL;
static ec_sdo_request_t *slave0_sdo_velocity_demand_value_read = NULL;

static ec_sdo_request_t *slave0_sdo_operation_mode_write = NULL;
static ec_sdo_request_t *slave0_sdo_controlword_write = NULL;

static ec_sdo_request_t *slave0_sdo_position_actual_value_read = NULL;
static ec_sdo_request_t *slave0_sdo_target_position_read_write = NULL;


static fm_sdo *slave0_operation_mode_display_fmsdo = NULL;
static fm_sdo *slave0_operation_mode_write_fmsdo = NULL;
static fm_sdo *slave0_homing_method_fmSdo = NULL;

static fm_sdo *slave0_statusword_fmsdo = NULL;
static fm_sdo *slave0_controlword_fmsdo = NULL;

static fm_sdo *slave0_position_actual_value_fmsdo = NULL;
static fm_sdo *slave0_target_position_fmsdo = NULL;

static pthread_mutex_t mutex_PDO = PTHREAD_MUTEX_INITIALIZER;
}//fm_auto

#endif
