// gap_button.cpp

#include "gap_button.h"

GAPButton::GAPButton(ble::InstanceHandle_t ble, events::EventQueue &event_queue) :
        ble(BLE::Instance(ble)),
        event_queue(event_queue),
        button_press_count(0)
{
    // Initialize BLE
    ble.onEventsToProcess(
            makeFunctionPointer(this, &GAPButton::onBLEInitComplete)
    );
}

void GAPButton::run() {
    // Start BLE advertising
    startAdvertising();

    // Dispatch events forever
    event_queue.dispatch_forever();
}

void GAPButton::onBLEInitComplete(BLE::InitializationCompleteCallbackContext *params) {
    if (params->error != BLE_ERROR_NONE) {
        // Handle initialization error
        return;
    }

    // Print device address
    printf("Device Address: %s\n", ble::address_t(ble::pal::get_device_address()).toString().c_str());

    // Start blinking LED every 500 milliseconds
    event_queue.call_every(500, this, &GAPButton::blinkLED);

    // Update advertisement data
    updateAdvertisement();
}

void GAPButton::startAdvertising() {
    // Set advertisement parameters
    ble.gap().setAdvertisingParameters(
            ble::AdvertisingParameters()
    );

    // Start advertising
    ble.gap().startAdvertising();
}

void GAPButton::updateAdvertisement() {
    // Update button press count in manufacturer specific data
    adv_data_builder.setManufacturerSpecificData(
            ble::adv_data_appearance_t::BUTTON, (uint8_t *)&button_press_count, sizeof(button_press_count)
    );

    // Set device name
    adv_data_builder.setName("BLEButton");

    // Replace advertisement data
    ble.gap().setAdvertisingPayload(
            ble::AdvertisingDataBuilder::LE_GENERAL_DISCOVERABLE, adv_data_builder.getAdvertisingData()
    );
}

void GAPButton::onConnectionComplete(const ble::ConnectionCompleteEvent &event) {
    // Stop blinking LED
    // Keep LED turned on
}

void GAPButton::onDisconnectionComplete(const ble::DisconnectionCompleteEvent &event) {
    // Start advertising
    startAdvertising();

    // Start blinking LED
}

void GAPButton::onButtonPress() {
    // Update button press count
    button_press_count++;

    // Update advertisement data
    event_queue.call(this, &GAPButton::updateAdvertisement);
}
