// $Id: ethercat_process_data.cxx,v 1.10 2006/02/20 15:57:33 kgad Exp $
//===========================================================================
//	This file is part of "EtherCAT Master Library".
//	Copyright (C) 2005 FMTC vzw, Diamant Building, A. Reyerslaan 80,
//	B-1030 Brussels, Belgium.
//
//	EtherCAT Master Library is free software; you can redistribute it
//	and/or modify it under the terms of the GNU General Public License
//	as published by the Free Software Foundation; either version 2 or
//	(at your option) any later version.
//
//	EtherCAT Master Code is distributed in the hope that it will be
//	useful, but WITHOUT ANY WARRANTY; without even the implied
//	warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
//	PURPOSE. See the GNU General Public License for more details.
//
//	You should have received a copy of the GNU General Public License
//	along with the EtherCAT Master Library; if not, write to the Free
//	Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
//	02111-1307 USA.
//
//	EtherCAT, the EtherCAT trade name and logo are the intellectual
//	property of, and protected by Beckhoff. You can use "EtherCAT
//	Master Library" for creating and/or selling or otherwise
//	distributing an EtherCAT network master under the terms of the
//	EtherCAT Master License.
//
//	You should have received a copy of the EtherCAT Master License
//	along with the EtherCAT Master Library; if not, write to Beckhoff
//	Automation GmbH, Eiserstrasse 5, D-33415 Verl, Germany.
//===========================================================================

 
#include "al/ethercat_process_data.h"
#include "al/ethercat_slave_handler.h"
#include "al/ethercat_AL.h"
#include "al/ethercat_master.h"
#include "dll/ethercat_dll.h"

EtherCAT_PD_Buffer * EtherCAT_PD_Buffer::m_instance = 0;

EtherCAT_PD_Buffer *
EtherCAT_PD_Buffer::instance()
{
  if (!m_instance) {
    m_instance = new EtherCAT_PD_Buffer();
  }
  return m_instance;
}

// al_instance cannot be initiated right now, since this results in a
// circular instantiation al_instance calls router_instance etc.
EtherCAT_PD_Buffer::EtherCAT_PD_Buffer()
  : m_is_running(0),
    m_lrw_telegram(0x00,0x00010000,0x00,0,NULL), 
    m_lrw_frame(&m_lrw_telegram)
{
  // get pointer to DLL and logic
  m_dll_instance = EtherCAT_DataLinkLayer::instance();
  m_logic_instance = EC_Logic::instance();
}

EtherCAT_PD_Buffer::~EtherCAT_PD_Buffer(){}

void 
EtherCAT_PD_Buffer::start()
{
  ++m_is_running;
}

void 
EtherCAT_PD_Buffer::stop()
{ 
  if (m_is_running > 0)
    --m_is_running;
  else
    log(EC_LOG_INFO, "EtherCAT_PD_Buffer already stopped...\n");
}

bool
EtherCAT_PD_Buffer::txandrx(size_t datalen, unsigned char * data)
{
  if ( m_is_running != 0)
    // In case only starting when all slaves in the appropriate state
    // this becomes something like
    // if ( EtherCAT_PD_Buffer::m_al_instance->get_num_slaves() == m_running)
    {
      m_lrw_telegram.set_idx(m_logic_instance->get_idx());
      m_lrw_telegram.set_wkc(m_logic_instance->get_wkc());
      m_lrw_telegram.set_datalen(datalen);
      m_lrw_telegram.set_data(data);
      if (!(m_dll_instance->txandrx(&m_lrw_frame))){
	log(EC_LOG_ERROR, "PD_Buffer: Error sending PD\n");
	return false;
      }
    }
  return true;
}


	  
      



