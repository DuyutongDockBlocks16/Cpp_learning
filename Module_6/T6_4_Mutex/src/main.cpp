/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 In this example, we are going to create two tasks with the same priority
LED3 will be accessed by both of the threads, and it will be guarded by a mutex.
When a Task sets the state of LED3, it will remain in that state at least for 1
seconds

Task 1: It will have Normal Priority
    It will get the state of Button 1, and turn on LED1 when Button 1 is pressed
and turn it off when Button 1 is released. It will try to set the state of LED 3
according to Button 1 state

Task 2: It will have Normal Priority
    It will turn on LED2 when Button 2 is pressed, and turn it off when Button 2
is released. It will also try to set the state of LED 3 according to Button 2
state

Expected behavior: The tasks will be blocked when the other has an access right
to LED 3

*/

#include "mbed.h"
#include <iostream>
#include <string>
#include "nrf52832_app_protect.h"

// the following code is just a placeholder. You may remove it if you find it fit.
//---------------BEGIN PLACE HOLDER-------------------------/
// Blinking rate in milliseconds
#define BLINKING_RATE     100ms
//---------------END PLACE HOLDER-------------------------/


// Declare LED 3 object used by both of the threads
DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);

DigitalIn button1(BUTTON1);
DigitalIn button2(BUTTON2);
// Declare the mutex object used by both of the threads
Mutex mu;

// You can use the following function from task functions 
// to change the LED3 state

/**
 * @brief Set the state of led3
 * 
 * @param turnOn The LED state; recommended to use true value to indicate on state
 * @param taskName The name of the task calling this function
 */
void set_led3(bool turnOn, const char* taskName) {
    uint64_t ticks = Kernel::Clock::now().time_since_epoch().count();
    // mu.lock();
    led3 = 0;
    std::cout << taskName
              << " trying to get LED3 lock to set its state to " << turnOn
              << std::endl;
    
    std::cout << taskName
              << " set the LED 3 state for 1s" 
              << std::endl;
    
    uint64_t time_diff = Kernel::Clock::now().time_since_epoch().count() - ticks;

    std::string taskNameString = std::string(taskName);

    if(taskNameString == "task1"){

        while(time_diff<=1000 || button1 == 0){
            led1 = button1;
            time_diff = Kernel::Clock::now().time_since_epoch().count() - ticks;
        }

    }else if (taskNameString == "task2") {

        while(time_diff<=1000 || button2 == 0){
            led2 = button2;
            time_diff = Kernel::Clock::now().time_since_epoch().count() - ticks;
        }
    
    }




    // ThisThread::sleep_for(1000ms);
    led3 = 1;
    // mu.unlock();
}

void task1_proc() {

    // create a DigitalOut object in the Task stack memory
    std::cout<<"task1 running" << std::endl;
    // DigitalOut led(LED1);
    // create a DigitalIn object in the Task stack memory
    
    // turn off the LED
    led1 = 1;
    while (true) {
        // mu.lock();
        
        led1 = button1;
        ThisThread::sleep_for(BLINKING_RATE);
        
        if(!button1){
            mu.lock();
            set_led3(1 ,"task1");
            mu.unlock();  
        }// the following is just a placeholder. You may remove it if you find it fit.
        //---------------BEGIN PLACE HOLDER-------------------------/
        

        
        //---------------END PLACE HOLDER-------------------------/


        
    }


}

void task2_proc() {
    // create a DigitalOut object in the Task stack memory
    std::cout<<"task2 running" << std::endl;
    // DigitalOut led(LED2);
    // create a DigitalIn object in the Task stack memory
    
    // Turn off the LED
    led2 = 1;
    while (true) {
        
        led2 = button2;
        ThisThread::sleep_for(BLINKING_RATE);

        if (!button2){
            mu.lock();
            set_led3(1 ,"task2");
            mu.unlock();  
        }
        // the following is just a placeholder. You may remove it if you find it fit.
        //---------------BEGIN PLACE HOLDER-------------------------/
        
        
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
    led3 = 1;
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
    // while (true) {
    //     led = !led;
    //     ThisThread::sleep_for(BLINKING_RATE);
    // }
    //---------------END PLACE HOLDER-------------------------/
    return 1;
}





// /* mbed Microcontroller Library
//  * Copyright (c) 2019 ARM Limited
//  * SPDX-License-Identifier: Apache-2.0
//  */

// #include "mbed.h"

// #include "nrf52832_app_protect.h"
// #include <iostream>

// /*
//  In this example, we are going to create two tasks with different priorities

// Task 1: It will have Normal Priority
//     It will get the Button state from task 2, and turn on LED1 when Button 1 is pressed and turn it off when Button 1
// is released

// Task 2: It will have AboveNormal Priority
//     It will turn on LED2 when Button 1 is pressed, and turn it off when Button 1
// is released. It will set EventFlag when button state changes

// Expected behavior: Task 2 sets EventFlags, and Task 1 gets that info after it

// */

// // the following is just a placeholder. You may remove it if you find it fit.
// //---------------BEGIN PLACE HOLDER-------------------------/
// // Blinking rate in milliseconds
// #define BLINKING_RATE     100ms
// //---------------END PLACE HOLDER-------------------------/
// #define UN_PRESSED (0)
// #define PRESSED (1)

// DigitalOut led(LED3);
// DigitalIn button(BUTTON1);

// // Useful bitmasks that can used for event flag monitoring
// #define BUTTON_PRESSED_FLAG_MASK (1 << 0) // this is the Least Significant Bit
// #define BUTTON_RELEASED_FLAG_MASK (1 << 1)  // this is the Least Significant Bit
// #define BUTTON_STATE_FLAG_MASK  (BUTTON_PRESSED_FLAG_MASK | BUTTON_RELEASED_FLAG_MASK)

// // Declare EventFlag object used by the tasks
// EventFlags eventFlags;

// Mutex mu;
// void set_led3(bool turnOn, const char* taskName) {

//     mu.lock();
//     led = 0;
//     std::cout << taskName
//               << " trying to get LED3 lock to set its state to " << turnOn
//               << std::endl;
    
//     std::cout << taskName
//               << " set the LED 3 state for 1s" 
//               << std::endl;

//     // ThisThread::sleep_for(1000ms);
//     mu.unlock();
// }

// void task1_proc() {
//     // create a DigitalOut object in the Task stack memory
//     DigitalOut led1(LED1);
    
//     // turn off the LED
//     led1 = 1;
//     while (true) {
//         // hint:: You can use std::cout prints to observe the operation of the task.
//         // std::cout
//         // the following is just a placeholder. You may remove it if you find it fit.
//         //---------------BEGIN PLACE HOLDER-------------------------/
//         // led = !led;
 
//         led1 = button;


        

//         ThisThread::sleep_for(BLINKING_RATE);
//         //---------------END PLACE HOLDER-------------------------/
        
//     }
// }

// void task2_proc() {
//     // create a DigitalOut object in the Task stack memory
//     DigitalOut led2(LED2);
    
//     // Turn off the LED
//     led2 = 1;
//     while(true){
//         // hint:: You can use std::cout prints to observe the operation of the task.
        
//         // the following is just a placeholder. You may remove it if you find it fit.
//         //---------------BEGIN PLACE HOLDER-------------------------/
//         // led = !led;
//         // std::cout<<"task2 is running"<<std::endl;
//         // led = button;
//         led2 = BUTTON2;

        
//         ThisThread::sleep_for(BLINKING_RATE);
//         //---------------END PLACE HOLDER-------------------------/
        
//     }
// }

// int main()
// {
//     /////////////////////////////////////////////////////////
//     // the following must always present in main files
//     nrf52_disable_approtect();
//     ///////////////////////////////////////////////////////////
//     /*---------------------------------------------------------*/
//     // Start your implementation below

//     // 1. create two threads with different priorities. 
//     // the threads are created in suspended state
//     Thread thread1(osPriorityNormal);
//     Thread thread2(osPriorityAboveNormal);
    

//     // 2. start the threads, and assign their procedures (functions)
//     thread1.start(callback(task1_proc));
//     thread2.start(callback(task2_proc));
    
    
//     // 3. wait for threads to terminate (if they ever terminate)
//     thread1.join();
//     thread2.join();
    

//     // the following code is just a placeholder. You may remove it if you find it fit.
//     //---------------BEGIN PLACE HOLDER-------------------------/
//     // DigitalOut led(LED1);
//     // while (true) {
//     //     led = !led;
//     //     ThisThread::sleep_for(BLINKING_RATE);
//     // }
//     //---------------END PLACE HOLDER-------------------------/
    
//    return 1;
// }