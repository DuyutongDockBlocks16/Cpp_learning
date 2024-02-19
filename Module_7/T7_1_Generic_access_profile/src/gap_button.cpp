#include "gap_button.h"
#include "ble_utils.h"
#include <iostream>



DigitalOut led2(LED2);
void CGAPButton::buttonPressedHandler(){
    
    _button_press_count++;
    led2 = !led2;
    _event_queue.call(callback(this, &CGAPButton::updateAdvertisementData));
}

void CGAPButton::toggleLED(){
    _led = !_led;
}

void CGAPButton::updateAdvertisementData(){

    // uint8_t new_data = 8;
    _ble.gap().stopAdvertising(ble::LEGACY_ADVERTISING_HANDLE);

    // ble_error_t error = _adv_data_builder.replaceData(ble::adv_data_type_t::MANUFACTURER_SPECIFIC_DATA,
    //                                   mbed::make_Span(&new_data, 1));
    // std::cout << "&_button_press_count: "  << &_button_press_count << std::endl;


    ble_error_t error = _adv_data_builder.addOrReplaceData(ble::adv_data_type_t::MANUFACTURER_SPECIFIC_DATA,
                           mbed::make_Span(&_button_press_count, 1));

    if (error != 0U) {
        // this is an example error print. You can come up with your own ways to do so.
        // Note that the ble_error_t type variable name is error
        std::cout << ble::BLE::errorToString(error) << std::endl;
    } else {
        std::cout << "addOrReplaceData successed" << std::endl;
    }

    error = _ble.gap().setAdvertisingPayload(
        ble::LEGACY_ADVERTISING_HANDLE,
        _adv_data_builder.getAdvertisingData()
    );


    // if (error != 0U) {
    //     // this is an example error print. You can come up with your own ways to do so.
    //     // Note that the ble_error_t type variable name is error
    //     std::cout << ble::BLE::errorToString(error) << std::endl;
    // } else {
    //     std::cout << "setAdvertisingPayload successed" << std::endl;
    // }
    

    // _ble.gap().startAdvertising(ble::LEGACY_ADVERTISING_HANDLE);
}

void CGAPButton::onBLEInitCompleteHandler(BLE::InitializationCompleteCallbackContext *context){
    // 1. check for the initialization errors using error member of context
    BLE& ble_interface = context->ble;
// check for the initialization errors
    ble_error_t initialization_error = context->error;
    if (initialization_error) {
// handle error
        return;
    }
    // The BLE interface can be accessed now.
    std::cout << "BLE init completed" << std::endl;
    // 2. get and print the device address 
    ble::own_address_type_t addrType;
    ble::address_t address;
    auto error = context->ble.gap().getAddress(addrType, address);
    if (error == BLE_ERROR_NONE) {
        // print the own Bluetooth address using 
        // printBluetoothAddress utility function defined in ble_utils.h
        // note that there are 3 overloads of that function. 
        std::cout << printBluetoothAddress(address) << std::endl;
        
    }
    // 3. start blinking the led

    if(!_led_event_id){
        _led_event_id = _event_queue.call_every(500ms, mbed::callback(this, &CGAPButton::toggleLED));
    }

    // 4. start advertising

    startAdvertising();
}

void CGAPButton::scheduleBLEEventsToProcess(BLE::OnEventsToProcessCallbackContext* context){

    _event_queue.call(callback(&(context->ble), &BLE::processEvents));
    
}


CGAPButton::CGAPButton(ble::BLE& ble, 
                        EventQueue& event_queue, 
                        const std::string& device_name, 
                        PinName button_pin, 
                        PinName led_pin): 
    _ble(ble),
    _event_queue(event_queue),
    _button(button_pin),
    _led(led_pin),
    _button_press_count(0),
    _device_name(device_name),
    _adv_data_builder(_adv_data_buffer),
    _adv_data_buffer{}
{
    // std::cout << "Constructing CGAPButton" << std::endl;
    // std::cout << "&_button_press_count: "  << &_button_press_count << std::endl;
    _button.fall(callback(this, &CGAPButton::buttonPressedHandler));

}


void CGAPButton::run(){
    // 1. Register on events to process callback function.
    _ble.onEventsToProcess(makeFunctionPointer(this, &CGAPButton::scheduleBLEEventsToProcess));
    // std::cout << "events registered" << std::endl;
    // 2. Register GAP event handler 
    _ble.gap().setEventHandler(this);
    // std::cout << "GAP event handler registered" << std::endl;
    
    // 3. Initialize the BLE interface by registering a callback function
    _ble.init(this, &CGAPButton::onBLEInitCompleteHandler);
    // std::cout << "Starting BLE Application " << std::endl;

    // 4. Dispatch events forever from the main thread
    _event_queue.dispatch_forever();
    // never reaches this line!
}

void CGAPButton::startAdvertising(){


    // create an ble::AdvertisingParameters object with the specified configuration

    ble::AdvertisingParameters advParameters(
        ble::advertising_type_t::CONNECTABLE_UNDIRECTED,
        ble::adv_interval_t(ble::millisecond_t(100))
    );

    // std::cout << "&_button_press_count: "  << &_button_press_count << std::endl;
    // 1. Create advertisement data
    _adv_data_builder.addData(ble::adv_data_type_t::MANUFACTURER_SPECIFIC_DATA,
                           mbed::make_Span(&_button_press_count, 1));

    _adv_data_builder.setName(_device_name.c_str());
    _adv_data_builder.setFlags();
    
    // 2. setup the parameters
        ble_error_t error = _ble.gap().setAdvertisingParameters(
        ble::LEGACY_ADVERTISING_HANDLE,
        advParameters
    );


    // error = _ble.gap().startAdvertising(ble::LEGACY_ADVERTISING_HANDLE);
    
    if (error != 0U) {
        // this is an example error print. You can come up with your own ways to do so.
        // Note that the ble_error_t type variable name is error
        std::cout << ble::BLE::errorToString(error) << std::endl;
        return;
    }
    // 3. set the advertisement payload
    error = _ble.gap().setAdvertisingPayload(
        ble::LEGACY_ADVERTISING_HANDLE,
        _adv_data_builder.getAdvertisingData()
    );

    if (error != 0U) {
        std::cout << ble::BLE::errorToString(error) << std::endl;
        return;
    }

    // 4. Start advertising 
    error = _ble.gap().startAdvertising(ble::LEGACY_ADVERTISING_HANDLE);
    
    // 5. Start blinking the Application LED
    if(!_led_event_id){
        _led_event_id = _event_queue.call_every(500ms, mbed::callback(this, &CGAPButton::toggleLED));
    }
    
    std::cout << "Device is advertising" << std::endl;
}

void CGAPButton::onConnectionComplete(const ble::ConnectionCompleteEvent &event){
    // keep the LED on

    if(_led_event_id){
        _event_queue.cancel(_led_event_id);
        _led = 0;
        _led_event_id = 0;
    }

    
    std::cout << "Device is connected" << std::endl;
}
void CGAPButton::onDisconnectionComplete(const ble::DisconnectionCompleteEvent &event){

    if(!_led_event_id){
        _led_event_id = _event_queue.call_every(500ms, mbed::callback(this, &CGAPButton::toggleLED));
    }
    
    std::cout << "Device is disconnected" << std::endl;

    _ble.gap().startAdvertising(ble::LEGACY_ADVERTISING_HANDLE);
}

// void CGAPButton::eventHandler(){
//     // complete the function definition
//     _led = !_led;
// }
