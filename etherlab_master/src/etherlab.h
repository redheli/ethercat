#ifndef __ETHERLAB_MASTER_H__
#define __ETHERLAB_MASTER_H__

#include <ros/ros.h>

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
       fm_auto::homing_method getMotorHomingMode();
};

}// fm_auto
#endif
