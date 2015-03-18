//
//  GenericTask.h
//  ThreadPool
//
//  Created by Kvitz on 14/02/14.
//  Copyright (c) 2014 Kvitz. All rights reserved.
//

#ifndef ThreadPool_GenericTask_h
#define ThreadPool_GenericTask_h

class GenericTask {
public:
    virtual void run() = 0;
};

#endif
