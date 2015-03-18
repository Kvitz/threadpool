//
//  ThreadPool.h
//  ThreadPool
//
//  Created by Kvitz on 13/02/14.
//  Copyright (c) 2014 Kvitz. All rights reserved.
//

#ifndef __ThreadPool__ThreadPool__
#define __ThreadPool__ThreadPool__

#include <iostream>
#include <condition_variable>
#include <deque>
#include <memory>
#include <thread>
#include <vector>

#include "Task.h"
#include "TaskRunner.h"

class ThreadPool {    

public:
    ThreadPool(const size_t pool_size);
    ~ThreadPool();
    
    ThreadPool(const ThreadPool&)=delete;
    ThreadPool& operator=(const ThreadPool&)=delete;

    void addTask(std::shared_ptr<GenericTask> task);
	GenericTask* popAndReturnNextTask();

	inline std::mutex& getTaskMutex() {
		return task_mutex;
	}

	inline std::condition_variable& getTaskConditionVariable() {
		return task_cond_var;
	}

	inline bool isStopping() {
		return stop;
	}

	inline bool hasTasks() {
		return !tasks.empty();
	}

	void stopThreads();

private:
	std::vector<std::thread> threads;
	std::deque<std::shared_ptr<GenericTask> > tasks;
    std::condition_variable task_cond_var;
	std::mutex task_mutex;
	volatile bool stop = false;
};

#endif /* defined(__ThreadPool__ThreadPool__) */
