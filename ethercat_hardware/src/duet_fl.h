#ifndef DUET_FL_H
#define DUET_FL_H

#include <ethercat_hardware/ethercat_device.h>

class DUET_FL : public EthercatDevice
{
public:
  void construct(EtherCAT_SlaveHandler *sh, int &start_address);
  int initialize(pr2_hardware_interface::HardwareInterface *, bool);
  void diagnostics(diagnostic_updater::DiagnosticStatusWrapper &d, unsigned char *);
  void packCommand(unsigned char *buffer, bool halt, bool reset);
  bool unpackState(unsigned char *this_buffer, unsigned char *prev_buffer);
  uint get_producer_hearbeat_time();
 
  DUET_FL();
  ~DUET_FL();

  enum
  {
    PRODUCT_CODE = 4403
  };

protected:
  int counter_;
};

#endif /* DUET_FL_H */
