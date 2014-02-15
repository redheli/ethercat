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

static unsigned int off_0x6040;
static unsigned int off_0x6060;
static unsigned int off_0x6098;
static unsigned int off_0x607a;
static unsigned int off_0x60ff;
static unsigned int off_0x6071;
static unsigned int off_0x6041;
static unsigned int off_0x6064;
static unsigned int off_0x6061;
static unsigned int off_0x1001;
static unsigned int off_0x606c;
static unsigned int off_0x6077;

// current only have one slave
#define SlaveZeroAliasAndPosition  0, 0
#define VendorID_ProductCode  0x000000e4, 0x00001133

const static ec_pdo_entry_reg_t domain_output_regs[] = {
    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6040, 0, &off_0x6040},
//    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6060, 0, &off_0x6060},
//    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6098, 0, &off_0x6098},
    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x607a, 0, &off_0x607a},
//    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x60ff, 0, &off_0x60ff},
//    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6071, 0, &off_0x6071},
//    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6041, 0, &off_0x6041},
//    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6064, 0, &off_0x6064},
//    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6061, 0, &off_0x6061},
//    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x1001, 0, &off_0x1001},
//    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x606c, 0, &off_0x606c},
//    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6077, 0, &off_0x6077},
    {}
};
const static ec_pdo_entry_reg_t domain_input_regs[] = {
//    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6040, 0, &off_0x6040},
//    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6060, 0, &off_0x6060},
//    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6098, 0, &off_0x6098},
//    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x607a, 0, &off_0x607a},
//    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x60ff, 0, &off_0x60ff},
//    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6071, 0, &off_0x6071},
        {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6061, 0, &off_0x6061},
    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6041, 0, &off_0x6041},
//    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6064, 0, &off_0x6064},
{SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x606c, 0, &off_0x606c},
    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x1001, 0, &off_0x1001},
//
//    {SlaveZeroAliasAndPosition,  VendorID_ProductCode, 0x6077, 0, &off_0x6077},
    {}
};


}//fm_auto

#endif
