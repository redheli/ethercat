#ifndef __OBJECT_DICTIONARY_H__
#define __OBJECT_DICTIONARY_H__

namespace fm_auto
{

enum HOMING_METHOD
{
    HM_Method_1 = -1, //Negative stop evaluating the zero impulse
    HM_current_position= 37,

    HM_fail = 100
};

enum OPERATIN_MODE
{
    OM_NOT_READY_TO_SWITCH_ON = 0x0000,
    OM_QUICK_STOP_ACTIVE = 0x0007,
    OM_FAULT_OR_FAULT_REACTION_ACTIVE = 0x000F,

    OM_READY_TO_SWITCH_ON  = 0x0021,
    OM_SWITCHED_ON  = 0x0023,
    OM_OPERATION_ENABLE = 0x0027,

    OM_SWITCH_ON_DISABLED = 0x0040

};


}//fm_auto

#endif
