// /*
//  * Copyright (c) 2020 Arm Limited and affiliates.
//  * SPDX-License-Identifier: Apache-2.0
//  */
// #include "mbed.h"
// #include <iostream>
// #include "nrf52832_app_protect.h"

// Thread thread;
// DigitalOut led1(LED1);
// volatile bool running = true;

// // Blink function toggles the led in a long running loop
// void blink(DigitalOut *led)
// {
//     while (running) {
//         *led = !*led;
//         ThisThread::sleep_for(100ms);
//     }
// }

// // Spawns a thread to run blink for 5 seconds
// int main()
// {

//     nrf52_disable_approtect();

//     running = true;
//     std::cout<<"main running"<<std::endl;
//     thread.start(callback(blink, &led1));
//     thread.join();
//     ThisThread::sleep_for(5000ms);
//     running = false;

// }