#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <semaphore>
#include <chrono>

// Producer-Consumer
void producerWithSemaphore(std::vector<char>& cVec, std::chrono::time_point<std::chrono::system_clock> end);
void consumerWithSemaphore(std::vector<char>& cVec, std::chrono::time_point<std::chrono::system_clock> end);
void producerWithMutex(std::vector<char>& cVec, std::chrono::time_point<std::chrono::system_clock> end);
void consumerWithMutex(std::vector<char>& cVec, std::chrono::time_point<std::chrono::system_clock> end);

void ConsumerProducer(bool isMutex, unsigned short duration);


// Barber-Customer
void barber(std::vector<char>& waitQueue, std::chrono::time_point<std::chrono::system_clock> end);
void customer(std::vector<char>& waitQueue, std::chrono::time_point<std::chrono::system_clock> end);

void BarberCustomer(unsigned short duration);