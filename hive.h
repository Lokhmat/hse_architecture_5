//
// Created by Sergey Lokhmatikov on 12.12.2021.
//

#ifndef UNTITLED7_HIVE_H
#define UNTITLED7_HIVE_H
#include <thread>
#include <mutex>
#include <chrono>
#include <iostream>
#include <atomic>

class Hive {
public:
    explicit Hive(int n, int bees_sleep_time, int bees_gather_time, int bear_sleep_time);

    ~Hive();

    int bees;

    int num_of_honey;

    int bees_sleep_time;
    int bees_gather_time;
    int bear_sleep_time;

    bool tryEat();

    bool shouldEat();

    static void gooBee(Hive *h, int i);

    static void initBear(Hive *h);
};


#endif //UNTITLED7_HIVE_H
