//
//  TaskRunner.h
//  ThreadPool
//
//  Created by Kvitz on 13/02/14.
//  Copyright (c) 2014 Kvitz. All rights reserved.
//

#ifndef __ThreadPool__TaskRunner__
#define __ThreadPool__TaskRunner__

#include <iostream>
#include <memory>
#include <thread>

#include "Task.h"
#include "ThreadPool.h"

class ThreadPool;

class TaskRunner {
    
public:
    TaskRunner(ThreadPool& thread_pool);
        
    void operator()();

private:
	ThreadPool& tp;
};

#endif /* defined(__ThreadPool__TaskRunner__) */
