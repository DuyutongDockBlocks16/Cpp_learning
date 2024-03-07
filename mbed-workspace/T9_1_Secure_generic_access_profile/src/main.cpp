#include <BLE.h>
#include <mbed.h>

#include <iostream>

#include "example_gatt_service.h"
#include "gatt_server.h"
#include "nrf52832_app_protect.h"
#include "secure_gap.h"

int main() {
	/////////////////////////////////////////////////////////
	// the following must always present in main files
	nrf52_disable_approtect();
	///////////////////////////////////////////////////////////
	/*---------------------------------------------------------*/

	// TODO:: Implement this functions

	std::cout << "Starting GattServer application" << std::endl;
	

	// 1. Create EventQueue object for the application
    EventQueue event_queue;
	// 2. Get a reference to system's BLE instance
    BLE &ble = BLE::Instance();
	// 3. Instantiate CSecureGap object with the required parameters
    CSecureGap csecurgap(ble, event_queue, "SecureGattServer", LED1);
	// 4. Instantiate CExampleGattService object (use the provided global uuids, and characteristics
	// descriptions)
    CExampleGattService cexamplegattservice(event_queue, LED2);
	// 5. instantiate CGattServer object
    CGattServer cgattserver;
	// 6. Add CExampleGattService object to CGattServer
    cgattserver.addService(cexamplegattservice);
	// 7. Set onBLEInitComplete callback of Gap to CGattServer::startServer function
	//    of the instantiated object.
    csecurgap.setOnBLEInitCompleteCallback(mbed::callback(&cgattserver, &CGattServer::startServer));
	// 8. Call CSecureGap::run member function to start the application
    csecurgap.run();
    
	return 0;
}