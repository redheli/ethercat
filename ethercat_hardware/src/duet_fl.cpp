#include "duet_fl.h"
#include <ros/console.h>
#include <sstream>
#include <iomanip>
using namespace std;

PLUGINLIB_DECLARE_CLASS(ethercat_hardware,4403, DUET_FL, EthercatDevice);

DUET_FL::DUET_FL()
{
  counter_ = 0;  
}

void DUET_FL::construct(EtherCAT_SlaveHandler *sh, int &start_address)
{
  EthercatDevice::construct(sh, start_address);
  sh->set_fmmu_config( new EtherCAT_FMMU_Config(0) );
  sh->set_pd_config( new EtherCAT_PD_Config(0) );
}

DUET_FL::~DUET_FL()
{
  delete sh_->get_fmmu_config();
  delete sh_->get_pd_config();
}

int DUET_FL::initialize(pr2_hardware_interface::HardwareInterface *hw, bool allow_unprogrammed)
{
  ROS_WARN("Device #%02d: DUET_FL (%d) revision (%d)",
            sh_->get_ring_position(), sh_->get_product_code(),sh_->get_revision());
  return 0;
}

void DUET_FL::diagnostics(diagnostic_updater::DiagnosticStatusWrapper &d, unsigned char *)
{
  stringstream name;
  name << "EtherCAT Device #" << setw(2) << setfill('0') 
       << sh_->get_ring_position() << " (DUET_FL)";
  d.name = name.str();
  d.summary(d.OK, "OK");
  stringstream hwid;
  hwid << sh_->get_product_code() << "-" << sh_->get_serial();
  d.hardware_id = hwid.str();

  d.clear();
  d.addf("Position", "%02d", sh_->get_ring_position());
  d.addf("Product Code", "%d", sh_->get_product_code());
  d.addf("Serial Number", "%d", sh_->get_serial());
  d.addf("Revision", "%d", sh_->get_revision());
  d.addf("Counter", "%d", ++counter_);

  EthercatDevice::ethercatDiagnostics(d, 2);
}

void DUET_FL::packCommand(unsigned char *buffer, bool halt, bool reset)
{
}

bool DUET_FL::unpackState(unsigned char *this_buffer, unsigned char *prev_buffer)
{
  ROS_INFO("DUET_FL: <%X>",this_buffer);
  return true;
}

uint DUET_FL::get_producer_hearbeat_time()
{

}
