#if defined(_WIN32) || defined(__APPLE__)   // Only for Linux Operating System that supports bonjour
#pragma once  // Header guard see https://en.wikipedia.org/wiki/Include_guard

// Copyright (c) 2023 Sri Lakshmi Kanthan P
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

// C++ headers
#include <algorithm>
#include <vector>

// Qt headers
#include <QByteArray>
#include <QHostAddress>
#include <QHostInfo>
#include <QObject>
#include <QSocketNotifier>
#include <QTimer>
#include <QUdpSocket>
#include <QtLogging>

// mDNS headers
#include <dns_sd.h>

// Local headers
#include "constants/constants.hpp"
#include "interfaces/imdnsregister/imdnsregister.hpp"
#include "types/enums/enums.hpp"
#include "utility/functions/ipconv/ipconv.hpp"

namespace srilakshmikanthanp::clipbirdesk::network::service::dnsd {
/**
 * @brief Abstract Discovery server that Listens for the client that send
 * the broadcast message The user of this class should implement the
 * getIpType(), getIPAddress() and getPort() functions to return the
 * IP type, IP address and port number respectively
 */
class Register : public interfaces::ImDNSRegister {
 signals:  // signals for this class
  /// @brief On Error Occurred
  void OnErrorOccurred(QString error);

 private:  // typedefs for this class

  using IPType = types::enums::IPType;

 private:  // Just for Qt

  Q_OBJECT

 private:  // disable copy and move

  Q_DISABLE_COPY_MOVE(Register)

 private: // private variables

  QSocketNotifier* m_notifier = nullptr; ///< Socket notifier
  DNSServiceRef m_serviceRef = nullptr;  ///< Service ref

 private: // private functions

  /**
   * @brief Callback function for DNSServiceRegister
   */
  static void publishCallback(
    DNSServiceRef serviceRef,       // DNSServiceRef
    DNSServiceFlags flags,          // DNSServiceFlags
    DNSServiceErrorType errorCode,  // DNSServiceErrorType
    const char* name,               // name of service
    const char* regtype,            // regtype
    const char* domain,             // domain
    void* context                   // context
  );

  /**
   * @brief Process Activated
   */
  void processActivated();

 public:  // public functions

  /**
   * @brief Construct a new Discovery Register object
   *
   * @param parent Parent object
   */
  explicit Register(QObject* parent = nullptr);

 protected:  // protected functions

  /**
   * @brief Destroy the Discovery Register object
   */
  virtual ~Register();

 public:

  /**
   * @brief Register the service
   */
  virtual void registerServiceAsync() override;

  /**
   * @brief Stop the server
   */
  virtual void unregisterService() override;
};
}  // namespace srilakshmikanthanp::clipbirdesk::network::service
#endif
