#include "MultithreadProblems.h"


// Producer-Consumer mutex and semaphores
std::mutex dataMut;
std::counting_semaphore fullSem(0), emptySem(10);

// Barber-Customer mutex and semaphores
std::mutex queueMut;
std::binary_semaphore barberSem(0);
std::counting_semaphore customersSem(0);


void producerWithMutex(std::vector<char>& cVec, std::chrono::time_point<std::chrono::system_clock> end) {
    // Convert end time
    auto deadline = std::chrono::system_clock::to_time_t(end);
    // While current time (now) is less than (not reached) the deadline, loop
    while (std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) <= deadline) {
        // Sleep/Wait 0-2 seconds until next operation
        std::this_thread::sleep_for(std::chrono::seconds(rand() % 2));
        // Lock data mutex and produce
        dataMut.lock();
        // 1 second producing time
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Producer = ";
        // Check vector's size and if not full, produce new
        if (cVec.size() < 10) {
            cVec.push_back('c');
            std::cout << "Produced. (+) Size: " << cVec.size() << std::endl;
        }
        else {
            std::cout << "Vector is full." << std::endl;
        }
        // Unlock mutex for consumer or other producer
        dataMut.unlock();
    }
}

void consumerWithMutex(std::vector<char>& cVec, std::chrono::time_point<std::chrono::system_clock> end) {
    // Convert end time
    auto deadline = std::chrono::system_clock::to_time_t(end);
    // While current time (now) is less than (not reached) the deadline, loop
    while (std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) <= deadline) {
        // Sleep/Wait 0-2 seconds until next operation
        std::this_thread::sleep_for(std::chrono::seconds(rand() % 2));
        // Lock/Unlock data mutex via GUARD: automatically locks/unlocks out of scope
        std::lock_guard<std::mutex> guard(dataMut);
        // 1 second consuming time
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "Consumer = ";
        // Check vector's size and if not empty, consume
        if (!cVec.empty()) {
            cVec.pop_back();
            std::cout << "Consumed. (-) Size: " << cVec.size() << std::endl;
        }
        else {
            std::cout << "Vector is empty." << std::endl;
        }
        // No need to UNLOCK, guard will do it
    }
}

void producerWithSemaphore(std::vector<char>& cVec, std::chrono::time_point<std::chrono::system_clock> end) {
    // Convert end time
    auto deadline = std::chrono::system_clock::to_time_t(end);
    // While current time (now) is less than (not reached) the deadline, loop
    while (std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) <= deadline) {

        // Sleep/Wait 0-2 seconds until next operation
        std::this_thread::sleep_for(std::chrono::seconds(rand() % 2));

        // Decrease empty semaphore, which means vector is not empty
        // If empty semaphore is 0 (no empty space), vector is full wait until 1 item is consumed
        emptySem.acquire();

        // 1 second producing time
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cVec.push_back('c');
        std::cout << "+ PRODUCED. Size: " << cVec.size() << std::endl;

        // Increase full semaphore, which means produced new item
        // Added 1 item to the vector
        fullSem.release();
    }
}

void consumerWithSemaphore(std::vector<char>& cVec, std::chrono::time_point<std::chrono::system_clock> end) {
    // Convert end time
    auto deadline = std::chrono::system_clock::to_time_t(end);
    // While current time (now) is less than (not reached) the deadline, loop
    while (std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) <= deadline) {

        // Sleep/Wait 0-2 seconds until next operation
        std::this_thread::sleep_for(std::chrono::seconds(rand() % 2));

        // Decrease full semaphore, which means vector lost one item
        // If fill semaphore is 0 (no item), vector is empty wait until 1 item is produced
        fullSem.acquire();

        // 1 second consuming time
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cVec.pop_back();
        std::cout << "- consumed. Size: " << cVec.size() << std::endl;

        // Increase empty semaphore, which means vector has empty space
        // Added 1 empty space
        emptySem.release();
    }
}

void ConsumerProducer(bool isMutex, unsigned short duration) {
    // Description of the problem
    std::cout << "Consumer-Producer multithread problem." << std::endl;
    std::cout << "Vector with 5 items. Full: 10, Empty: 0" << std::endl;

    // Vector with 5 c characters, max size is going to be 10 so it is half full
    std::vector<char> cVec (5, 'c');

    // Using time point and system_clock 
    std::chrono::seconds sec(duration);
    std::chrono::time_point<std::chrono::system_clock> deadline;
    deadline = std::chrono::system_clock::now() + sec;

    // Mutex solution
    if (isMutex) {
        std::cout << "Using Mutex" << std::endl;
        // Consumer-Producer w/ Mutex
        std::thread t1(producerWithMutex, std::ref(cVec), deadline);
        std::thread t2(consumerWithMutex, std::ref(cVec), deadline);
        t1.detach();
        t2.detach();
    }
    // Semaphore solution
    else {
        std::cout << "Using Semaphores" << std::endl;
        // Consumer-Producer w/ Mutex
        std::thread t3(producerWithSemaphore, std::ref(cVec), deadline);
        std::thread t4(consumerWithSemaphore, std::ref(cVec), deadline);
        t3.detach();
        t4.detach();
    }

    // Sleep duration + 3 seconds until both producer and consumer threads finish their tasks
    std::this_thread::sleep_for(std::chrono::seconds(duration + 3));
    std::cout << "Finished threads." << std::endl;
    return;
}




void barber(std::vector<char>& waitQueue, std::chrono::time_point<std::chrono::system_clock> end) {
    // Convert end time
    auto deadline = std::chrono::system_clock::to_time_t(end);
    // While current time (now) is less than (not reached) the deadline, loop
    while (std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) <= deadline) {

        std::cout << "Barber = Waiting for customer."<< std::endl;
        // Wait until customers arrive
        customersSem.acquire();
        std::cout << "Barber = New customer arrived." << std::endl;

        // Queue mutex lock for pop operation
        queueMut.lock();

        // Decrease the waiting queue
        waitQueue.pop_back();

        // Barber is ready for hair cut operation
        barberSem.release();

        // Queue mutex unlock for pop operation
        queueMut.unlock();

        std::cout << "Barber = Cutting hair..." << std::endl;
        // 5-10 seconds shaving
        unsigned short hairCut = (rand() % 5) + 5;
        std::this_thread::sleep_for(std::chrono::seconds(hairCut));
        std::cout << "Barber = Hair cut finished in " << hairCut << " seconds." << std::endl;
    }
    return;
}

void customer(std::vector<char>& waitQueue, std::chrono::time_point<std::chrono::system_clock> end) {
    // Convert end time
    auto deadline = std::chrono::system_clock::to_time_t(end);
    // While current time (now) is less than (not reached) the deadline, loop
    while (std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) <= deadline) {

        // 0-9 second new customer arrival rate
        unsigned short arrivalTime = rand() % 10;
        std::this_thread::sleep_for(std::chrono::seconds(arrivalTime));
        std::cout << "Customer = Enters the barber shop." << std::endl;

        // Queue mutex lock for push operation
        queueMut.lock();

        // There are spaces for waiting, max 1 waiting customer
        if (waitQueue.size() < 1) {
            // Increase the queue
            waitQueue.push_back('c');

            // Inform barber that there are customers waiting, increase customer semaphore
            customersSem.release();

            // Queue mutex unlock after push operation
            queueMut.unlock();

            std::cout << "Customer " << waitQueue.size() << " = Waiting for the barber." << std::endl;
            // Wait until barber is ready
            barberSem.acquire();

            // Hair cut
        }
        // Waiting queue is full, leave the shop
        else {        
            // Queue mutex unlock: no push, no space for new customer
            queueMut.unlock();
            std::cout << "Customer = No empty space for waiting, leaving." << std::endl;
        }
    }
    return;
}

void BarberCustomer(unsigned short duration) {
    // Description of the problem
    std::cout << "Barber-Customer multithread problem." << std::endl;
    std::cout << "1 barber, 3 customers, waiting queue size: 1" << std::endl;

    // Empty vector for waiting customers, max size is 10
    std::vector<char> waitQueue;

    // Using time point and system_clock 
    std::chrono::seconds sec(duration);
    std::chrono::time_point<std::chrono::system_clock> deadline;
    deadline = std::chrono::system_clock::now() + sec;

    // 1 barber, 3 customer threads
    std::thread barberThread(barber, std::ref(waitQueue), deadline);
    std::thread customerThread1(customer, std::ref(waitQueue), deadline);
    std::thread customerThread2(customer, std::ref(waitQueue), deadline);
    std::thread customerThread3(customer, std::ref(waitQueue), deadline);
    barberThread.detach();
    customerThread1.detach();
    customerThread2.detach();
    customerThread3.detach();

    // Sleep duration + 3 seconds until both all threads finish their tasks
    std::this_thread::sleep_for(std::chrono::seconds(duration + 3));
    std::cout << "Finished threads." << std::endl;
    return;
}