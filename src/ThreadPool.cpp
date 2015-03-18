//
//  ThreadPool.cpp
//  ThreadPool
//
//  Created by Kvitz on 13/02/14.
//  Copyright (c) 2014 Kvitz. All rights reserved.
//

#include "ThreadPool.h"

ThreadPool::ThreadPool(const size_t pool_size) {
    threads.reserve(pool_size);
    
    for (size_t i=0; i<pool_size; i++) {
        std::thread t(TaskRunner(*this));
        threads.push_back(std::move(t));
    }
}

ThreadPool::~ThreadPool() {
//    task_mutex.lock();
    stop = true;
//    task_mutex.unlock();
    std::cout << "destroying all threads" << std::endl;
    
    task_cond_var.notify_all();
    
    for (size_t i=0; i<threads.size(); i++) {
        threads[i].join();
        task_cond_var.notify_all(); // what for?
    }
}

void ThreadPool::addTask(std::shared_ptr<GenericTask> task) {
	std::unique_lock<std::mutex>(task_mutex);
    tasks.push_back(task);
    task_cond_var.notify_one();
}

GenericTask* ThreadPool::popAndReturnNextTask() {
	GenericTask* task = &*tasks.front();
	tasks.pop_front();
	return task;
}

void ThreadPool::stopThreads() {
	stop = true;
	task_cond_var.notify_all();
}