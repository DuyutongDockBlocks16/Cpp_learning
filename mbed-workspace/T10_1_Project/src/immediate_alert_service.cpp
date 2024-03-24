#include "immediate_alert_service.h"

CImmediateAlertService::CImmediateAlertService(PinName led_pin)
	: _led(led_pin), _alert_level(IAS_ALERT_LEVEL_NO_ALERT), _alert_level_value(IAS_ALERT_LEVEL_NO_ALERT) {
	// TODO:: implement this constructor
	// 1. set the PWM period to 1 seconds
    _led.period(1.0f);
	// 2. create the characteristics with UUID GattCharacteristic::UUID_ALERT_LEVEL_CHAR
	//    assert that the characteristic is successfully created
    const char *description = "IAS";

    assert(this->addCharacteristic(
	GattCharacteristic::UUID_ALERT_LEVEL_CHAR,
	GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_WRITE_WITHOUT_RESPONSE /*= GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NONE*/,
	description /*= nullptr*/,
	&_alert_level_value /*= nullptr*/,
	sizeof(_alert_level_value) /*= 0*/) && "error adding characteristic");

    for( auto i: _characteristics){
        i->setSecurityRequirements(ble::att_security_requirement_t::UNAUTHENTICATED,
                                    ble::att_security_requirement_t::UNAUTHENTICATED,
                                    ble::att_security_requirement_t::UNAUTHENTICATED);
    }

	// 3. create the service with UUID GattService::UUID_IMMEDIATE_ALERT_SERVICE
	//    assert that the service is successfully created
    assert(!(this->CGattService::createService(GattService::UUID_IMMEDIATE_ALERT_SERVICE)) && "error creating service");
	
}

CImmediateAlertService::~CImmediateAlertService() {}

void CImmediateAlertService::onDataWrittenHandler(GattCharacteristic* characteristic,
												  const uint8_t* data,
												  uint16_t size) {
	// TODO:: implement this function
	// 1. Validate that characteristics has the value handle of this service's characteristic's value handle

	// 2. Cast the new value to AlertLevel enum type
    if (size != sizeof(AlertLevel)) return;

    _alert_level = static_cast<AlertLevel>(*data);
	_alert_level_value = *data;

    setCharacteristicValue(*_characteristics[0], _alert_level_value);

	// 3. Switch between supported different options
	// 4. Set the PwM duty cycle according to alert level.
	//    i. NO_ALERT -> OFF (100%)
	//    ii. MEDIUM -> around 50%
	//    iii. HIGH  -> ON (0%)
    switch (_alert_level) {

        case IAS_ALERT_LEVEL_NO_ALERT:
            // 4. 根据警报级别设置PWM占空比
            _led.write(1.0f); // NO_ALERT -> OFF (100%)
            break;
        case IAS_ALERT_LEVEL_MEDIUM:
            _led.write(0.5f); // MEDIUM -> 约50%
            break;
        case IAS_ALERT_LEVEL_HIGH:
            _led.write(0.0f); // HIGH -> ON (0%)
            break;
        default:
            // 处理未知警报级别
            break;
    }

	
}

void CImmediateAlertService::onConnected(void) {
	// TODO:: implement this function
	_alert_level = IAS_ALERT_LEVEL_NO_ALERT;
	_alert_level_value = IAS_ALERT_LEVEL_NO_ALERT;
	// set the characteristic value
	// ble::GattServer &server = ble::BLE::Instance().gattServer();

    setCharacteristicValue(*_characteristics[0], _alert_level_value);

    switch (_alert_level) {

    case IAS_ALERT_LEVEL_NO_ALERT:
        // 4. 根据警报级别设置PWM占空比
        _led.write(1.0f); // NO_ALERT -> OFF (100%)
        break;
    case IAS_ALERT_LEVEL_MEDIUM:
        _led.write(0.5f); // MEDIUM -> 约50%
        break;
    case IAS_ALERT_LEVEL_HIGH:
        _led.write(0.0f); // HIGH -> ON (0%)
        break;
    default:
        // 处理未知警报级别
        break;
}

}

void CImmediateAlertService::onDisconnected(void) {
	// TODO:: implement this function
	_alert_level = IAS_ALERT_LEVEL_MEDIUM;
	_alert_level_value = IAS_ALERT_LEVEL_MEDIUM;
	// set the characteristic value
	// ble::GattServer &server = ble::BLE::Instance().gattServer();

    setCharacteristicValue(*_characteristics[0], _alert_level_value);

    switch (_alert_level) {

    case IAS_ALERT_LEVEL_NO_ALERT:
        // 4. 根据警报级别设置PWM占空比
        _led.write(1.0f); // NO_ALERT -> OFF (100%)
        break;
    case IAS_ALERT_LEVEL_MEDIUM:
        _led.write(0.5f); // MEDIUM -> 约50%
        break;
    case IAS_ALERT_LEVEL_HIGH:
        _led.write(0.0f); // HIGH -> ON (0%)
        break;
    default:
        // 处理未知警报级别
        break;
}
}

void CImmediateAlertService::registerService(ble::BLE& ble) {
	// TODO:: implement this function
	// call the registerService function of the base class
    CGattService::registerService(ble);
}
