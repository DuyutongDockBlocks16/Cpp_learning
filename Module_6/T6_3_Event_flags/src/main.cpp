/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

#include "nrf52832_app_protect.h"
#include <iostream>

/*
 In this example, we are going to create two tasks with different priorities

Task 1: It will have Normal Priority
    It will get the Button state from task 2, and turn on LED1 when Button 1 is pressed and turn it off when Button 1
is released

Task 2: It will have AboveNormal Priority
    It will turn on LED2 when Button 1 is pressed, and turn it off when Button 1
is released. It will set EventFlag when button state changes

Expected behavior: Task 2 sets EventFlags, and Task 1 gets that info after it

*/

// the following is just a placeholder. You may remove it if you find it fit.
//---------------BEGIN PLACE HOLDER-------------------------/
// Blinking rate in milliseconds
#define BLINKING_RATE     100ms
//---------------END PLACE HOLDER-------------------------/

DigitalIn button(BUTTON1);
// Useful bitmasks that can used for event flag monitoring
#define BUTTON_PRESSED_FLAG_MASK (1 << 0) // this is the Least Significant Bit
#define BUTTON_RELEASED_FLAG_MASK (1 << 1)  // this is the Least Significant Bit
#define BUTTON_STATE_FLAG_MASK  (BUTTON_PRESSED_FLAG_MASK | BUTTON_RELEASED_FLAG_MASK)

// Declare EventFlag object used by the tasks
EventFlags eventflags;

void task1_proc() {
    // create a DigitalOut object in the Task stack memory
    DigitalOut led(LED1);
    
    // turn off the LED
    led = 1;
    uint32_t flags; 
    while (true) {
        // hint:: You can use std::cout prints to observe the operation of the task.
        // std::cout
        // the following is just a placeholder. You may remove it if you find it fit.
        //---------------BEGIN PLACE HOLDER-------------------------/
        // led = !led;

        flags = eventflags.wait_any(BUTTON_STATE_FLAG_MASK, osWaitForever);
        // led = button;
        if (flags & BUTTON_PRESSED_FLAG_MASK){
            led = 0;
            eventflags.clear(BUTTON_PRESSED_FLAG_MASK);
        }
        else { 
            led = 1;
            eventflags.clear(BUTTON_RELEASED_FLAG_MASK);
        }

        

        ThisThread::sleep_for(BLINKING_RATE);
        //---------------END PLACE HOLDER-------------------------/
        
    }
}

void task2_proc() {
    // create a DigitalOut object in the Task stack memory
    DigitalOut led(LED2);
    
    // Turn off the LED
    led = 1;
    while(true){
        // hint:: You can use std::cout prints to observe the operation of the task.
        
        // the following is just a placeholder. You may remove it if you find it fit.
        //---------------BEGIN PLACE HOLDER-------------------------/
        // led = !led;
        // std::cout<<"task2 is running"<<std::endl;
        // led = button;

        if (button == 0){
            eventflags.set(BUTTON_PRESSED_FLAG_MASK);
        }
        else{
            eventflags.set(BUTTON_RELEASED_FLAG_MASK);
        }
        
        ThisThread::sleep_for(BLINKING_RATE);
        //---------------END PLACE HOLDER-------------------------/
        
    }
}

int main()
{
    /////////////////////////////////////////////////////////
    // the following must always present in main files
    nrf52_disable_approtect();
    ///////////////////////////////////////////////////////////
    /*---------------------------------------------------------*/
    // Start your implementation below

    // 1. create two threads with different priorities. 
    // the threads are created in suspended state
    Thread thread1(osPriorityNormal);
    Thread thread2(osPriorityAboveNormal);
    

    // 2. start the threads, and assign their procedures (functions)
    thread1.start(callback(task1_proc));
    thread2.start(callback(task2_proc));
    
    
    // 3. wait for threads to terminate (if they ever terminate)
    thread1.join();
    thread2.join();
    

    // the following code is just a placeholder. You may remove it if you find it fit.
    //---------------BEGIN PLACE HOLDER-------------------------/
    // DigitalOut led(LED1);
    // while (true) {
    //     led = !led;
    //     ThisThread::sleep_for(BLINKING_RATE);
    // }
    //---------------END PLACE HOLDER-------------------------/
    
   return 1;
}