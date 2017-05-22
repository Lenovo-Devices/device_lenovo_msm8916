#ifndef WIFI_OFFLOAD_SERVER_H_
#define WIFI_OFFLOAD_SERVER_H_

#include <android/hardware/wifi/offload/1.0/IOffload.h>

#include "chre_interface_callbacks.h"

namespace android {
namespace hardware {
namespace wifi {
namespace offload {
namespace V1_0 {
namespace implementation {

class OffloadServer;

class ChreInterfaceCallbacksImpl : public ChreInterfaceCallbacks {
  public:
    ChreInterfaceCallbacksImpl(OffloadServer* server);
    ~ChreInterfaceCallbacksImpl() override;

    void handleConnectionEvents(ChreInterfaceCallbacks::ConnectionEvent event);
    void handleMessage(uint32_t messageType, const std::vector<uint8_t>& message);

  private:
    OffloadServer* mServer;
};

/**
 * Interface object to communicate with Offload HAL
 */
class OffloadServer {
  public:
    OffloadServer();

    bool configureScans(const ScanParam& param, const ScanFilter& filter);
    std::pair<ScanStats, bool> getScanStats();
    bool subscribeScanResults(uint32_t delayMs);
    bool unsubscribeScanResults();
    bool setEventCallback(const sp<IOffloadCallback>& cb);

  private:
    ScanStats mScanStats;
    std::unique_ptr<ChreInterfaceCallbacksImpl> mChreInterfaceCallbacks;
    sp<IOffloadCallback> mEventCallback;

    friend class ChreInterfaceCallbacksImpl;
};

}  // namespace implementation
}  // namespace V1_0
}  // namespace offload
}  // namespace wifi
}  // namespace hardware
}  // namespace android

#endif  // WIFI_OFFLOAD_SERVER_H_
