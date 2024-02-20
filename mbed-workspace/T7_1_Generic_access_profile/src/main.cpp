#include <mbed.h>
#include <BLE.h>
#include "gap_button.h"
#include "nrf52832_app_protect.h"
#include <iostream>

int main() {
    /////////////////////////////////////////////////////////
    // the following must always present in main files
    nrf52_disable_approtect();
    ///////////////////////////////////////////////////////////
    /*---------------------------------------------------------*/
    
    // 1. Create EventQueue object for the application
    EventQueue event_queue;
    
    // 2. Get a reference to system's BLE instance 
    BLE &ble = BLE::Instance();
    // 3. Instantiate CGAPButton object with the required parameters
    CGAPButton cgap_button(ble, event_queue, "BLEButton", BUTTON1, LED1);
    

    // 4. Call CGapButton::run member function to start the application  
    cgap_button.run();
    
    return 0;
}