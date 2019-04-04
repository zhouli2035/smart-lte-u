/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2007,2008,2009 INRIA, UDCAST
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: Amine Ismail <amine.ismail@sophia.inria.fr>
 *                      <amine.ismail@udcast.com>
 *
 */

#ifndef UDP_CLIENT_H
#define UDP_CLIENT_H

#include "ns3/application.h"
#include "ns3/event-id.h"
#include "ns3/ptr.h"
#include "ns3/ipv4-address.h"

namespace ns3 {

class Socket;
class Packet;

/**
 * \ingroup udpclientserver
 * \class UdpClient
 * \brief A Udp client. Sends UDP packet carrying sequence number and time stamp
 *  in their payloads
 *
 */
class UdpClient : public Application
{
public:
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
  static TypeId GetTypeId (void);

  UdpClient ();

  virtual ~UdpClient ();

  /**
   * \brief set the remote address and port
   * \param ip remote IPv4 address
   * \param port remote port
   */
  void SetRemote (Ipv4Address ip, uint16_t port);
  /**
   * \brief set the remote address and port
   * \param ip remote IPv6 address
   * \param port remote port
   */
  void SetRemote (Ipv6Address ip, uint16_t port);
  /**
   * \brief set the remote address and port
   * \param ip remote IP address
   * \param port remote port
   */
  void SetRemote (Address ip, uint16_t port);
  /**
   * \brief get the number of packets already sent
   * \return number sent
   */
  uint32_t GetSent (void) const;

protected:
  virtual void DoDispose (void);

private:

  virtual void StartApplication (void);
  virtual void StopApplication (void);

  /**
   * \brief Send a packet
   */
  void Send (void);

  /**
   * \brief Set type of service on socket
   *
   * Consult documentation for ns3::Socket::SetIpTos() for valid values to use.
   *
   * \see class Socket
   *
   * \param tos Type of Service to use
   */
  void SetTypeOfService (uint8_t tos);

  /**
   * \brief Get type of service on socket
   * \return Type of Service to use
   */
  uint8_t GetTypeOfService (void) const;



  uint32_t m_count; //!< Maximum number of packets the application will send
  Time m_interval; //!< Packet inter-send time
  uint32_t m_size; //!< Size of the sent packet (including the SeqTsHeader)

  uint32_t m_sent; //!< Counter for sent packets
  Ptr<Socket> m_socket; //!< Socket
  uint8_t m_typeOfService; //!< Socket IP_TOS value
  Address m_peerAddress; //!< Remote peer address
  uint16_t m_peerPort; //!< Remote peer port
  EventId m_sendEvent; //!< Event to send the next packet

};

} // namespace ns3

#endif /* UDP_CLIENT_H */