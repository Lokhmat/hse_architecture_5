//
// Created by Sergey Lokhmatikov on 12.12.2021.
//

#include "hive.h"

std::mutex mtx;

Hive::Hive(int n, int bees_sleep_time, int bees_gather_time, int bear_sleep_time) {
    bees = n;
    num_of_honey = 0;
    this->bees_sleep_time = bees_sleep_time;
    this->bees_gather_time = bees_gather_time;
    this->bear_sleep_time = bear_sleep_time;
}

Hive::~Hive() {}

bool Hive::tryEat() {
    if (bees < 3){
        return true;
    }
    return false;
}

bool Hive::shouldEat(){
    if(num_of_honey >= 15){
        return true;
    }
    return false;
}

void Hive::gooBee(Hive *h, int i) {
    while(true) {
        if(h->bees > 1) {
            mtx.lock();
            h->bees--;
            std::cout << "Bee " << i << " flew away" << '\n';
            std::cout << "Bee " << i << " took honey" << '\n';
            std::cout << "Bee " << i << " collected honey" << '\n';
            std::cout << "Bee " << i << " started go home" << '\n';
            mtx.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(h->bees_gather_time));
            mtx.lock();
            std::cout << "Bee " << i << " came home" << '\n';
            h->bees++;
            if (h->num_of_honey < 30) {
                h->num_of_honey++;
            }
            std::cout << "Bee " << i << " added honey" << '\n';
            std::cout << "Honey:" << h->num_of_honey << '\n';
            mtx.unlock();
            if (h->num_of_honey == 30) {
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(h->bees_sleep_time));
        }
    }
}

void Hive::initBear(Hive *h) {
    while(true){
        if (h->shouldEat()){
            if (h->tryEat()){
                h->num_of_honey = 0;
                std::cout << "\033[1;32mBEAR ATE ALL HONEY\033[0m" << '\n';
            }
            else {
                std::cout << "\033[1;31mBEAR WAS BITTEN BY BEES\033[0m" << '\n';
                std::this_thread::sleep_for(std::chrono::milliseconds(h->bear_sleep_time));
            }
        }
        if(h->num_of_honey == 30){
            return;
        }
    }
}
