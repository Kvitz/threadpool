//
//  Task.h
//  ThreadPool
//
//  Created by Kvitz on 13/02/14.
//  Copyright (c) 2014 Kvitz. All rights reserved.
//

#ifndef __ThreadPool__Task__
#define __ThreadPool__Task__

#include <iostream>
#include <tuple>

#include "Apply.h"
#include "GenericTask.h"

template <typename T, typename U, typename... V>
class Task : public GenericTask {
    T* t;
    U(T::*f)(V...);
    std::tuple<V...> saved_args;
public:
    Task(T* tc, U(T::*fn_ptr)(V...) , V... v) : t(tc), f(fn_ptr), saved_args(std::make_tuple(std::move(v)...)) {}
    
    Task(const Task&)=delete;
    Task& operator=(const Task&)=delete;
    
    Task(Task&&)=delete;
    Task&& operator=(Task&&)=delete;
    
    inline void run() {
        applyTuple(t, f, saved_args);
    }
};

template <typename T, typename... V>
class GlobalTask : public GenericTask {
    T(*f)(V...);
    std::tuple<V...> saved_args;
public:
    GlobalTask(T(*fn_ptr)(V... v), V... v) : f(fn_ptr), saved_args(std::make_tuple(std::move(v)...)) {}
    
    GlobalTask(const GlobalTask&)=delete;
    GlobalTask& operator=(const GlobalTask&)=delete;
    
    GlobalTask(GlobalTask&&)=delete;
    GlobalTask&& operator=(GlobalTask&&)=delete;
    
    inline void run() {
        applyTuple(f, saved_args);
    }
};

#endif /* defined(__ThreadPool__Task__) */
