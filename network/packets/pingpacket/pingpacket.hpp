#pragma once  // Header guard see https://en.wikipedia.org/wiki/Include_guard

// Copyright (c) 2023 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

// Standard header files
#include <iostream>
#include <stdexcept>

// Qt header files
#include <QByteArray>
#include <QDataStream>
#include <QIODevice>
#include <QtTypes>

// Local header files
#include "types/enums/enums.hpp"
#include "types/except/except.hpp"

namespace srilakshmikanthanp::clipbirdesk::network::packets {
/**
 * @brief Clipboard Ping Packet's to check the connection
 */
class PingPacket {
 private:  // private members

  quint32 packetLength;
  quint32 packetType = 0x03;
  quint32 pingType;

 public:

  /// @brief Allowed Packet Types
  enum PacketType : quint32 {
    PingPong = 0x03
  };

  /// @brief Allowed Ping Types
  enum PingType : quint32 {
    Ping = 0x01, Pong = 0x02
  };

 public:

  /**
   * @brief Set the Packet Length object
   *
   * @param length
   */
  void setPacketLength(quint32 length);

  /**
   * @brief Get the Packet Length object
   *
   * @return qint32
   */
  quint32 getPacketLength() const noexcept;

  /**
   * @brief Set the Packet Type object
   *
   * @param type
   */
  void setPacketType(quint32 type);

  /**
   * @brief Get the Packet Type object
   *
   * @return quint32
   */
  quint32 getPacketType() const noexcept;

  /**
   * @brief Set the Ping Type object
   *
   * @param type
   */
  void setPingType(quint32 type);

  /**
   * @brief Get the Ping Type object
   *
   * @return quint32
   */
  quint32 getPingType() const noexcept;

    /**
   * @brief Get the size of the packet
   *
   * @return size_t
   */
  quint32 size() const noexcept;

  /**
   * @brief to Bytes
   */
  QByteArray toBytes() const;

  /**
   * @brief From Bytes
   */
  static PingPacket fromBytes(const QByteArray &array);
};
}
