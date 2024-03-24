#include "gatt_server.h"

#include <iostream>

#include "ble_utils.h"

CGattServer::CGattServer() {
	// TODO:: Implement this functions
	// 1. initially started must be false
    _started = false;
	
}

CGattServer::~CGattServer() {
	// TODO:: Implement this functions
    _services.clear();
	// Note that explicitly calling std::list::clear function destroys all of its elements.
	// This ensures that the services are destroyed properly since
	// their reference counts decrements to 1 (if the application is designed properly).

	
}

bool CGattServer::addService(CGattService& service) {
	// TODO:: Implement this functions
	// 1. Check whether the server has started. If it has been started, we do not want to
	//    add new services when the server is running since it requires registering them with the
	//    system's GattServer instance
	if(_started){
        std::cout << "server already started, addService failed" << std::endl;
        return false;
    }
	// 2. Check whether the service is created by using its bool() operator
	//    i. if not, return false since we do not want to add not created services
	//    ii. if it is, push it to the _services list and return true
    if(service){
        _services.push_back(&service);
        return true;
    }

	return false;
}

void CGattServer::startServer(ble::BLE& ble) {
	// TODO:: Implement this functions
	// 1. Register the services with the system's GattServer instance
	//    i. Iterate over each service
	//    ii. Add each service to the server using CGattService::registerService
	for(auto &i : _services){
        i->registerService(ble);
        // std::cout << "SSService registered!" << std::endl;
    }

	// 2. Register this object as the system's GattServer handler using GattServer::setEventHandler function
    ble.gattServer().setEventHandler(this);
    _started = true;	
}

void CGattServer::onConnected(void) {
	// TODO: implement this function
	// 1. Iterate over the _services
	// 2. call CGattService::onConnected function
    for(auto &service : _services){
        service->onConnected();
    }
	
}

void CGattServer::onDisconnected(void) {
	// TODO: implement this function
	// 1. Iterate over the _services
	// 2. call CGattService::onDisconnected function
    for(auto &service : _services){
        service->onDisconnected();
    }
	
}

void CGattServer::onDataWritten(const GattWriteCallbackParams& e) {
	// TODO:: Implement this functions
	GattCharacteristic* characteristic = nullptr;
	const char* characteristic_description = nullptr;
	const GattAttribute::Handle_t& value_handle = e.handle;
	std::cout << "onDataWritten() using Conn. Handle " << e.connHandle << " for Att. Handle " << value_handle
			  << std::endl;
	std::cout << "\twrite operation: " << e.writeOp << std::endl;
	std::cout << "\toffset: " << e.offset << std::endl;
	std::cout << "\tlength: " << e.len << std::endl;
	std::cout << "\tdata: ";
	std::cout << bufferToHex(e.data, e.len) << std::endl;
	// 1. Try to find the characteristic within the services that has the value_handle
	//    i. Iterate over the _services
	//    ii. call CGattService::getCharacteristicWithValueHandle
	//    iii. if the calls returns a pointer different than nullptr
	//         a. Try to get user description of the characteristic by calling
	//         CGattService::getCharacteristicUserDescription function
	//            - if the call returns a valid address (different than nullptr), print it as follows
	//              `Characteristic with value handle "<user description str>"`
	//              Note surrounding " character of the name (exclude ` characters)
	//            - Otherwise, do not print anything
	//         b. Call CGattService::onDataWrittenHandler function with the required parameters
	//         c. Stop iterating over services
	//    iv. otherwise, continue iterating

    for(auto &service : _services){
        characteristic = service->getCharacteristicWithValueHandle(value_handle);
        if(characteristic){
            characteristic_description = service->getCharacteristicUserDescription(value_handle);
            std::cout << "Characteristic with value handle" << characteristic_description << std::endl;
            service->onDataWrittenHandler(characteristic, e.data, e.len);
            break;
        }
    }

	if (characteristic == nullptr) {
		std::cout << "\tThe characteristic cannot be found" << std::endl;
	}
}

void CGattServer::onDataRead(const GattReadCallbackParams& e) {
	// TODO:: Implement this functions
	GattCharacteristic* characteristic = nullptr;
	const char* characteristic_description = nullptr;
	const GattAttribute::Handle_t& value_handle = e.handle;
	std::cout << "onDataRead() using Conn. Handle " << e.connHandle << " for Att. Handle " << value_handle
			  << std::endl;
	// 1. Try to find the characteristic within the services that has the value_handle
	//    i. Iterate over the _services
	//    ii. call CGattService::getCharacteristicWithValueHandle
	//    iii. stop iterating when the calls returns a pointer different than nullptr
	//         after getting its description
	//         a. Try to get user description of the characteristic by calling
	//         CGattService::getCharacteristicUserDescription function
	//            - if the call returns a valid address (different than nullptr), print it as follows
	//              `Characteristic with value handle "<user description str>"`
	//              Note surrounding " character of the name (exclude ` characters)
	//            - Otherwise, do not print anything
    for(auto &service : _services){
        characteristic = service->getCharacteristicWithValueHandle(value_handle);
        if(characteristic){
            characteristic_description = service->getCharacteristicUserDescription(value_handle);
            if(characteristic_description){
                std::cout << "Characteristic with value handle -> " << characteristic_description << std::endl;
            // service->onDataWrittenHandler(characteristic, e.data, e.len);
            }
            break;
        }
    }

	if (characteristic == nullptr) {
		std::cout << "\tThe characteristic cannot be found" << std::endl;
	}
}

void CGattServer::onUpdatesEnabled(const GattUpdatesEnabledCallbackParams& params) {
	// TODO:: Implement this functions
	GattCharacteristic* characteristic = nullptr;
	const char* characteristic_description = nullptr;
	const GattAttribute::Handle_t& value_handle = params.charHandle;
	std::cout << "onUpdatesEnabled() using Conn. Handle " << params.connHandle << " for Att. Handle "
			  << value_handle << std::endl;
	// 1. Try to find the characteristic within the services that has the value_handle
	//    i. Iterate over the _services
	//    ii. call CGattService::getCharacteristicWithValueHandle
	//    iii. stop iterating when the calls returns a pointer different than nullptr
	//         after getting its description
	//         a. Try to get user description of the characteristic by calling
	//         CGattService::getCharacteristicUserDescription function
	//            - if the call returns a valid address (different than nullptr), print it as follows
	//              `Characteristic with value handle "<user description str>"`
	//              Note surrounding " character of the name (exclude ` characters)
	//            - Otherwise, do not print anything
    for(auto &service : _services){
        characteristic = service->getCharacteristicWithValueHandle(value_handle);
        if(characteristic){
            characteristic_description = service->getCharacteristicUserDescription(value_handle);
            if(characteristic_description){
                std::cout << "Characteristic with value handle" << characteristic_description << std::endl;
            // service->onDataWrittenHandler(characteristic, e.data, e.len);
            }
            break;
        }
    }

	if (characteristic == nullptr) {
		std::cout << "\tThe characteristic cannot be found" << std::endl;
	}
}

void CGattServer::onUpdatesDisabled(const GattUpdatesDisabledCallbackParams& params) {
	// TODO:: Implement this functions
	GattCharacteristic* characteristic = nullptr;
	const char* characteristic_description = nullptr;
	const GattAttribute::Handle_t& value_handle = params.charHandle;
	std::cout << "onUpdatesDisabled() using Conn. Handle " << params.connHandle << " for Att. Handle "
			  << value_handle << std::endl;
	// 1. Try to find the characteristic within the services that has the value_handle
	//    i. Iterate over the _services
	//    ii. call CGattService::getCharacteristicWithValueHandle
	//    iii. stop iterating when the calls returns a pointer different than nullptr
	//         after getting its description
	//         a. Try to get user description of the characteristic by calling
	//         CGattService::getCharacteristicUserDescription function
	//            - if the call returns a valid address (different than nullptr), print it as follows
	//              `Characteristic with value handle "<user description str>"`
	//              Note surrounding " character of the name (exclude ` characters)
	//            - Otherwise, do not print anything

    for(auto &service : _services){
        characteristic = service->getCharacteristicWithValueHandle(value_handle);
        if(characteristic){
            characteristic_description = service->getCharacteristicUserDescription(value_handle);
            if(characteristic_description){
                std::cout << "Characteristic with value handle" << characteristic_description << std::endl;
            // service->onDataWrittenHandler(characteristic, e.data, e.len);
            }
            break;
        }
    }

	if (characteristic == nullptr) {
		std::cout << "\tThe characteristic cannot be found" << std::endl;
	}
}

void CGattServer::onConfirmationReceived(const GattConfirmationReceivedCallbackParams& params) {
	// TODO:: Implement this functions
	GattCharacteristic* characteristic = nullptr;
	const char* characteristic_description = nullptr;
	const GattAttribute::Handle_t& value_handle = params.attHandle;
	std::cout << "onUpdatesDisabled() using Conn. Handle " << params.connHandle << " for Att. Handle "
			  << params.attHandle << std::endl;
	// 1. Try to find the characteristic within the services that has the value_handle
	//    i. Iterate over the _services
	//    ii. call CGattService::getCharacteristicWithValueHandle
	//    iii. stop iterating when the calls returns a pointer different than nullptr
	//         after getting its description
	//         a. Try to get user description of the characteristic by calling
	//         CGattService::getCharacteristicUserDescription function
	//            - if the call returns a valid address (different than nullptr), print it as follows
	//              `Characteristic with value handle "<user description str>"`
	//              Note surrounding " character of the name (exclude ` characters)
	//            - Otherwise, do not print anything
    for(auto &service : _services){
        characteristic = service->getCharacteristicWithValueHandle(value_handle);
        if(characteristic){
            characteristic_description = service->getCharacteristicUserDescription(value_handle);
            if(characteristic_description){
                std::cout << "Characteristic with value handle" << characteristic_description << std::endl;
            // service->onDataWrittenHandler(characteristic, e.data, e.len);
            }
            break;
        }
    }

	if (characteristic == nullptr) {
		std::cout << "\tThe characteristic cannot be found" << std::endl;
	}
}
