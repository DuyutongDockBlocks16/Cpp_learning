// gap_button.h

#include "mbed.h"
#include "ble/BLE.h"

class GAPButton : private mbed::NonCopyable<GAPButton>, public ble::Gap::EventHandler {
public:
    // Constructor
    GAPButton(ble::InstanceHandle_t ble, events::EventQueue &event_queue);

    // Function to start BLE operation
    void run();

private:
    // BLE event handlers
    void onBLEInitComplete(BLE::InitializationCompleteCallbackContext *params);
    void onConnectionComplete(const ble::ConnectionCompleteEvent &event);
    void onDisconnectionComplete(const ble::DisconnectionCompleteEvent &event);

    // Function to update advertisement data
    void updateAdvertisement();

    // Button press callback function
    void onButtonPress();

    // Member variables
    BLE &ble;
    events::EventQueue &event_queue;
    ble::AdvertisingDataBuilder adv_data_builder;
    uint32_t button_press_count;
};

