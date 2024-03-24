#include <BLE.h>
#include <mbed.h>

#include <iostream>

#include "alert_notification_service.h"
#include "gatt_server.h"
#include "immediate_alert_service.h"
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
    CSecureGap csecurgap(ble, event_queue, "MTC-BLE", LED1);
	// 4. Instantiate a CImmediateAlertService object and a CAlertNotificationService object
    CImmediateAlertService ias(LED2);

    CAlertNotificationService ans(BUTTON1);

	// 5. instantiate CGattServer object
    CGattServer cgattserver;
	// 6. Add service objects to CGattServer
    cgattserver.addService(ias);
    
    cgattserver.addService(ans);
    
	// 7. Set onBLEInitComplete callback of Gap to CGattServer::startServer function
	//    of the instantiated object.
    csecurgap.setOnBLEInitCompleteCallback(mbed::callback(&cgattserver, &CGattServer::startServer));
	// 8. Set onConnected callback of Gap to CGattServer::onConnected function
	//    of the instantiated object.
    csecurgap.setOnConnectedCallback(mbed::callback(&cgattserver, &CGattServer::onConnected));
	// 9. Set onDisconnected callback of Gap to CGattServer::onDisconnected function
	//    of the instantiated object.
    csecurgap.setOnDisconnectedCallback(mbed::callback(&cgattserver, &CGattServer::onDisconnected));
	// 10. Call CSecureGap::run member function to start the application
    csecurgap.run();

	return 0;
}