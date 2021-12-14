#include <iostream>
#include "hive.h"
#include <vector>
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[]) {
    std::cout.tie(NULL);
    srand(time(NULL));
    std::ios_base::sync_with_stdio(false);
    int n, bees_sleep_time, bees_gather_time, bear_sleep_time;
    if (argc != 6 && argc != 2) {
        std::cout << "Proper start line: ./task5 -n {num of bees} {bees sleep time} {bees gathering time} {bear sleep time}" << std::endl;
        std::cout << "Or: ./task5 -r" << std::endl;
        return 1;
    }
    if (strcmp(argv[1], "-n") && strcmp(argv[1], "-r")){
        std::cout << "Proper start line: ./task5 -n {num of bees} {bees sleep time} {bees gathering time} {bear sleep time}" << std::endl;
        std::cout << "Or: ./task5 -r" << std::endl;
        return 3;
    }
    if(argc == 6) {
        n = atoi(argv[2]);
        bees_sleep_time = atoi(argv[3]);
        bees_gather_time = atoi(argv[4]);
        bear_sleep_time = atoi(argv[5]);
    } else{
        n = rand() % 100 + 3;
        bees_sleep_time = rand() % 100 + 20;
        bees_gather_time = rand() % 100 + 20;
        bear_sleep_time = rand() % 100 + 20;
    }
    if (n < 3){
        std::cout << "Num of bees should be more than 3" << std::endl;
        return 2;
    }
    std::cout << '\n';
    std::cout << "Random vars are:" << '\n';
    std::cout << "N: " << n  << '\n';
    std::cout << "bear sleep time: " << bear_sleep_time << '\n';
    std::cout << "bees sleep time: " << bees_sleep_time << '\n';
    std::cout << "bees gathering time " << bees_gather_time << '\n';
    std::vector<std::thread> thread_pool;
    thread_pool.reserve(n);
    Hive *h = new Hive(n, bees_sleep_time, bees_gather_time, bear_sleep_time);
    for(int i = 0; i < n; i++){
        thread_pool.push_back(std::thread(Hive::gooBee, h, i));
    }
    std::thread thr(Hive::initBear, h);
    thr.join();
    for(int i = 0; i < n; i++){
        thread_pool[i].join();
    }
    delete h;
    return 0;
}
