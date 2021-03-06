//
//  main.cpp
//  ThreadPool
//
//  Created by Kvitz on 13/02/14.
//  Copyright (c) 2014 Kvitz. All rights reserved.
//

#include <iostream>
#include <thread>
#include <functional>

#include "Apply.h"
#include "Task.h"
#include "ThreadPool.h"

int globalFunction(int a) {
    std::cout << "globalFunction: " << a << std::endl;
    return a;
}

class MyTest {
public:
    int memberFunction(int a) {
        std::cout << "memberFunction: " << a << std::endl;
        return a;
    }
};

int main(int argc, const char * argv[])
{
    ThreadPool tp(2);
    MyTest mt;
    
    int (*global_ptr)(int) = &globalFunction;
    int (MyTest::*mf_ptr)(int) = &MyTest::memberFunction;
    
    std::shared_ptr<GlobalTask<int, int> > gt_ptr(new GlobalTask<int, int>(global_ptr, 2));
	std::shared_ptr<Task<MyTest, int, int> > t_ptr(new Task<MyTest, int, int>(&mt, mf_ptr, 4));

    tp.addTask(t_ptr);
    tp.addTask(gt_ptr);

    do {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    } while (tp.hasTasks());
    
	tp.stopThreads();
    return 0;
}

