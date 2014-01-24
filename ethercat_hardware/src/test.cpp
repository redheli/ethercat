/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2008, Willow Garage, Inc.
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of the Willow Garage nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

#include <map>
#include <stdio.h>
#include <getopt.h>
#include <sys/mman.h>

#include <tinyxml.h>

#include <ethercat/ethercat_xenomai_drv.h>
#include <dll/ethercat_dll.h>
#include <al/ethercat_AL.h>
#include <al/ethercat_master.h>
#include <al/ethercat_slave_handler.h>

#include "ethercat_hardware/motor_heating_model.h"
#include <ethercat_hardware/wg0x.h>
#include <ethercat_hardware/wg05.h>
#include <ethercat_hardware/wg06.h>
#include <ethercat_hardware/wg021.h>
#include <ethercat_hardware/wg014.h>

#include <boost/crc.hpp>
#include <boost/foreach.hpp>

#include <net/if.h>
#include <sys/ioctl.h>
#include <netinet/in.h>

void init(char *interface)
{
  // open temporary socket to use with ioctl
  int sock = socket(PF_INET, SOCK_DGRAM, 0);
  if (sock < 0) {
    int error = errno;
    fprintf(stderr,"Couldn't open temp socket : %s", strerror(error));
    exit(-1);
  }

  struct ifreq ifr;
  strncpy(ifr.ifr_name, interface, IFNAMSIZ);
  if (ioctl(sock, SIOCGIFFLAGS, &ifr) < 0) {
    int error = errno;
    fprintf(stderr,"Cannot get interface flags for %s: %s\n", interface, strerror(error));
    exit(-1);
  }

  close(sock);
  sock = -1;

  if (!(ifr.ifr_flags & IFF_UP)) {
    fprintf(stderr,"Interface %s is not UP. Try : ifup %s\n", interface, interface);
    exit(-1);
  }
  if (!(ifr.ifr_flags & IFF_RUNNING)) {
    fprintf(stderr,"Interface %s is not RUNNING. Is cable plugged in and device powered?\n", interface);
    exit(-1);
  }

  ROS_INFO("Interface <%s> ok",interface);

  struct netif *ni;

  // Initialize network interface
  if ((ni = init_ec(interface)) == NULL)
  {
    fprintf(stderr, "Unable to initialize interface: %s\n", interface);
    exit(-1);
  }

  ROS_INFO("init socket ok");

  // Initialize Application Layer (AL)
  EtherCAT_DataLinkLayer::instance()->attach(ni);
  EtherCAT_AL *al;
  if ((al = EtherCAT_AL::instance()) == NULL)
  {
    fprintf(stderr, "Unable to initialize Application Layer (AL): %p\n", al);
    exit(-1);
  }
  ROS_INFO("Initialize Application Layer (AL) ok");

//  uint32_t num_slaves = al->get_num_slaves();
//  if (num_slaves == 0)
//  {
//    fprintf(stderr, "Unable to locate any slaves\n");
//    exit(-1);
//  }

//  // Initialize Master
//  EtherCAT_Master *em;
//  if ((em = EtherCAT_Master::instance()) == NULL)
//  {
//    fprintf(stderr, "Unable to initialize EtherCAT_Master: %p", em);
//    exit(-1);
//  }

//  static int start_address = 0x00010000;

//  for (unsigned int slave = 0; slave < num_slaves; ++slave)
//  {
//    EC_FixedStationAddress fsa(slave + 1);
//    EtherCAT_SlaveHandler *sh = em->get_slave_handler(fsa);
//    if (sh == NULL)
//    {
//      fprintf(stderr, "Unable to get slave handler #%d", slave);
//      exit(-1);
//    }

//    if (sh->get_product_code() == WG05::PRODUCT_CODE)
//    {
//      WG05 *dev = new WG05();
//      dev->construct(sh, start_address);
//      devices.push_back(dev);
//    }
//    else if (sh->get_product_code() == WG06::PRODUCT_CODE)
//    {
//      WG06 *dev = new WG06();
//      dev->construct(sh, start_address);
//      devices.push_back(dev);
//    }
//    else if (sh->get_product_code() == WG021::PRODUCT_CODE)
//    {
//      WG021 *dev = new WG021();
//      dev->construct(sh, start_address);
//      devices.push_back(dev);
//    }
//    else if (sh->get_product_code() == WG014::PRODUCT_CODE)
//    {
//      WG014 *dev = new WG014();
//      dev->construct(sh, start_address);
//      devices.push_back(dev);
//    }
//    else
//    {
//      devices.push_back(NULL);
//    }
//  }

//  BOOST_FOREACH(EthercatDevice *device, devices)
//  {
//    if (!device) continue;
//    if (!device->sh_->to_state(EC_OP_STATE))
//    {
//      fprintf(stderr, "Unable set device %d into OP_STATE", device->sh_->get_ring_position());
//    }
//  }

//  BOOST_FOREACH(EthercatDevice *device, devices)
//  {
//    if (!device) continue;
//    device->use_ros_ = false;
//    device->initialize(NULL, true);
//  }
}

int main(int argc, char *argv[])
{
    char interface[16] = "0x00";
    sprintf(interface,"eth0");
    init(interface);
    return 0;
}
