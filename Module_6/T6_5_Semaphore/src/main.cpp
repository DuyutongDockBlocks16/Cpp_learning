/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 In this example, we are going to create three tasks with the same priority
LED3 will be accessed by both of the threads, and it will be guarded by a mutex.
When a Task sets the state of LED3, it will remain in that state at least for 1
seconds

Task 1: It will have Normal Priority
    It will get the state of Button 1, and try to get one LED to show the Button
1 state

Task 2: It will have Normal Priority
    It will get the state of Button 2, and try to get one LED to show the Button
2 state

Task 3: It will have Normal Priority
    It will get the state of Button 3, and try to get one LED to show the Button
3 state

In total 2 LEDs will be available, and 3 tasks will race to get a LED.
The tasks will be blocked when two LEDs are already occupied. When one
thread gets a button it will keep it for 1s

Expected Behavior: One of the tasks will be blocked when two of them gets the
LEDs
 */

#include "mbed.h"
#include <iostream>
#include <list>
#include <sstream>

#include "nrf52832_app_protect.h"

// 
/**
 * @brief This is a led class, with identifier. You can use inheritance to
 * add new attributes to the base classes.
 * 
 * This class has "id" and "name" attributes.
 */
class AppLED: public DigitalOut{
private:
    // the id of the LED
    int id;
    // the name of the LED
    std::string name;
public:
    AppLED(PinName pin, int id) : DigitalOut(pin, 1), id(id){
        std::ostringstream oss;
        oss << "LED " << this->id;
        this->name = oss.str();
    }

    void set_id(int id){
        this->id = id;
    }

    int get_id(){
        return this->id;
    } 

    const std::string& str(){
        return this->name;
    }
};

Mutex mu_acquire,mu_release;

/**
 * @brief This class the manager of the Application LEDs. 
 * 
 * It has the leds that can be used at a time, and provides 
 * a LED to the caller if one is available. 
 */
class AppLEDs{
private:
    // The application LEDs of AppLED type. -- all leds have id and name attributes
    std::list<AppLED> leds; 
    // declare a semaphore guard to the application LEDs
    Semaphore guard;
    
public:
    // Default Constructor for our two LEDs
    /**
     * @brief Construct a new AppLEDs object
     * 
     * @note Since Semaphore is non-copyable, you must use initializer list to properly construct it!
     */
    /*BEGIN SOLUTION*/
    AppLEDs():guard(2){
        // Complete the constructor according to the task description
        leds.push_back(AppLED(LED1,1));
        leds.push_back(AppLED(LED2,2)); 
    
    }

    /**
     * @brief Acquires a LED from the application LEDs list if available. 
     * 
     * If no LED is available, blocks the caller task until a LED becomes available.
     * 
     * @param taskName The name of the caller task
     * @return A reference to the acquired led 
     */
    AppLED& acquire(const char* taskName){
        uint64_t ticks = Kernel::Clock::now().time_since_epoch().count();
        std::cout << taskName << " tries to acquire a LED" << std::endl;
        // try to acquire the semaphore
        guard.acquire();
        // get the first led from the list, and assign it to local `led` variable
        // of AppLED reference type.

        mu_acquire.lock();
        AppLED& led = leds.front();
        leds.pop_front();
        mu_acquire.unlock();

        std::cout << taskName << " acquired " 
                  << led.str() <<" in " << Kernel::Clock::now().time_since_epoch().count() - ticks 
                  << "ms" << std::endl;

        return led;
        
    }
    /**
     * @brief Releases an acquired LED
     * 
     * @param led A reference to the LED that will be released
     * @param taskName The name of the task releasing the LED
     */
    void release(AppLED& led, const  char* taskName){
        std::cout << taskName << " releases " << led.str() << std::endl;
        // put the LED to the list
        mu_release.lock();
        leds.push_back(led);
        // turn off the LED
        led.write(1);
        // increase the semaphore count
        mu_release.unlock();
        guard.release();
        
    }
};

// this is the LEDs manager of the application
AppLEDs ledManager;


void task1_proc() {
    // create a DigitalIn object in the Task stack memory
    DigitalIn button(BUTTON1);
    DigitalOut led1(LED1);
    led1 = 1;

    while (true) {
        // complete the task function according to the instruction.
        // you can use "Task 2" as task name
        AppLED led = ledManager.acquire("Task 1");
        uint64_t ticks = Kernel::Clock::now().time_since_epoch().count();
        while(Kernel::Clock::now().time_since_epoch().count() - ticks <= 1000){
            led.write(button);
            // led1 = 0;
        }
        // led1 = 1;
        ledManager.release(led, "Task 1");
    }
}

void task2_proc() {
    // create a DigitalIn object in the Task stack memory
    DigitalIn button(BUTTON2);
    DigitalOut led2(LED2);
    led2 = 1;
    
    while (true) {
        // complete the task function according to the instruction.
        // you can use "Task 2" as task name
        AppLED led = ledManager.acquire("Task 2");
        uint64_t ticks = Kernel::Clock::now().time_since_epoch().count();
        while(Kernel::Clock::now().time_since_epoch().count() - ticks <= 1000){
            led.write(button);
            // led2 = 0;
        }
        // led2 = 1;
        ledManager.release(led, "Task 2");
    }
}

void task3_proc() {
    // create a DigitalIn object in the Task stack memory
    DigitalIn button(BUTTON3);
    DigitalOut led3(LED3);
    led3 = 1;


    while (true) {
        // complete the task function according to the instruction.
        // you can use "Task 2" as task name
        AppLED led = ledManager.acquire("Task 3");
        uint64_t ticks = Kernel::Clock::now().time_since_epoch().count();
        while(Kernel::Clock::now().time_since_epoch().count() - ticks <= 1000){
            led.write(button);
            // led3 = 0;
        }
        // led3 = 1;
        ledManager.release(led, "Task 3");
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

    // 1. create three threads with required priorities. 
    // the threads are created in suspended state
    Thread thread1(osPriorityNormal, OS_STACK_SIZE, nullptr, "Thread 1");
    Thread thread2(osPriorityNormal, OS_STACK_SIZE, nullptr, "Thread 2");
    Thread thread3(osPriorityNormal, OS_STACK_SIZE, nullptr, "Thread 3");
    
    // 2. start the threads, and assign their procedures (functions)
    thread1.start(callback(task1_proc));
    thread2.start(callback(task2_proc));    
    thread3.start(callback(task3_proc));

    // 3. wait for threads to terminate (if they ever terminate)
    thread1.join();
    thread2.join();    
    thread3.join();

    // the following code is just a placeholder. You may remove it if you find it fit.
    //---------------BEGIN PLACE HOLDER-------------------------/
    while (true) {
        ThisThread::sleep_for(1s);
    }
    //---------------END PLACE HOLDER-------------------------/
    
}