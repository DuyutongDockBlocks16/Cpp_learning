#ifndef _BLE_UTILS_H_
#define _BLE_UTILS_H_

#include <BLE.h>

#include <iomanip>
#include <sstream>
/**
 * @brief This fails has definitions of common utility functions.
 * See individual function documentations for details.
 */

/**
 * @brief Returns bluetooth address as a human readable hex string
 *
 * @param address The address to be printed
 * @return The address string
 */
std::string printBluetoothAddress(const ble::address_t& address);

/**
 * @brief Returns human readable string for own Bluetooth device address
 *
 * @param type The address type
 * @param address The bluetooth address
 * @return The address string
 */
std::string printBluetoothAddress(const ble::own_address_type_t type, const ble::address_t& address);

/**
 * @brief Returns human readable string for peer Bluetooth device address
 *
 * @param type The address type
 * @param address The bluetooth address of the peer device
 * @return The address string
 */
std::string printBluetoothAddress(const ble::peer_address_type_t type, const ble::address_t& address);
/**
 * @brief Creates a string representation of the buffer in hex format
 *
 * @param buffer The buffer to be printed
 * @param size The size of the buffer
 * @return Hex string of the buffer
 */
std::string bufferToHex(const uint8_t* buffer, size_t size);

#endif	//! _BLE_UTILS_H_