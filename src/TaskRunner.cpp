//
//  TaskRunner.cpp
//  ThreadPool
//
//  Created by Kvitz on 13/02/14.
//  Copyright (c) 2014 Kvitz. All rights reserved.
//

#include "TaskRunner.h"

TaskRunner::TaskRunner(ThreadPool &thread_pool) : tp(thread_pool) {
}

void TaskRunner::operator()() {
    std::cout << "executeThread" << std::endl;
    
    GenericTask* task = nullptr;
    while (true) {
		{
			std::unique_lock<std::mutex> lock(tp.getTaskMutex());
			tp.getTaskConditionVariable().wait(lock, [this]() {
				return tp.isStopping() || tp.hasTasks();
			});

			if (tp.isStopping()) {
				break;
			}

			task = tp.popAndReturnNextTask();
		}

        task->run();
    }
}