ThreadPool
==========

C++11 ThreadPool implementation. It is based on Tasks. A task can be a pointer to member function or a static/global function. The function can have any return type and any number of arguments.
It uses std threads, movables, shared_ptrs, lambdas, variadic templates and recursive templates.
