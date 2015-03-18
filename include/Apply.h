//
//  Apply.h
//  ThreadPool
//
//  Created by Kvitz on 15/02/14. Based on code found at: http://stackoverflow.com/questions/687490/how-do-i-expand-a-tuple-into-variadic-template-functions-arguments
//  Copyright (c) 2014 Kvitz. All rights reserved.
//

#ifndef ThreadPool_Apply_h
#define ThreadPool_Apply_h

#include <tuple>

/**
 * Object Function Tuple Argument Unpacking
 *
 * This recursive template unpacks the tuple parameters into
 * variadic template arguments until we reach the count of 0 where the function
 * is called with the correct parameters
 *
 * @tparam N Number of tuple arguments to unroll
 *
 * @ingroup g_util_tuple
 */
template < unsigned int N >
struct apply_obj_func
{
    template < typename T, typename U, typename... ArgsF, typename... ArgsT, typename... Args >
    static void applyTuple( T* pObj,
                           U (T::*f)( ArgsF... ),
                           const std::tuple<ArgsT...>& t,
                           Args... args )
    {
        apply_obj_func<N-1>::applyTuple( pObj, f, t, std::get<N-1>( t ), args... );
    }
};

//-----------------------------------------------------------------------------

/**
 * Object Function Tuple Argument Unpacking End Point
 *
 * This recursive template unpacks the tuple parameters into
 * variadic template arguments until we reach the count of 0 where the function
 * is called with the correct parameters
 *
 * @ingroup g_util_tuple
 */
template <>
struct apply_obj_func<0>
{
    template < typename T, typename U, typename... ArgsF, typename... ArgsT, typename... Args >
    static void applyTuple( T* pObj,
                           U (T::*f)( ArgsF... ),
                           const std::tuple<ArgsT...>& /* t */,
                           Args... args )
    {
        (pObj->*f)( args... );
    }
};

//-----------------------------------------------------------------------------

/**
 * Object Function Call Forwarding Using Tuple Pack Parameters
 */
// Actual apply function
template < typename T, typename U, typename... ArgsF, typename... ArgsT >
void applyTuple( T* pObj,
                U (T::*f)( ArgsF... ),
                std::tuple<ArgsT...> const& t )
{
    apply_obj_func<sizeof...(ArgsT)>::applyTuple( pObj, f, t );
}

//-----------------------------------------------------------------------------

/**
 * Static Function Tuple Argument Unpacking
 *
 * This recursive template unpacks the tuple parameters into
 * variadic template arguments until we reach the count of 0 where the function
 * is called with the correct parameters
 *
 * @tparam N Number of tuple arguments to unroll
 *
 * @ingroup g_util_tuple
 */
template < unsigned int N >
struct apply_func
{
    template < typename T, typename... ArgsF, typename... ArgsT, typename... Args >
    static void applyTuple( T (*f)( ArgsF... ),
                           const std::tuple<ArgsT...>& t,
                           Args... args )
    {
        apply_func<N-1>::applyTuple( f, t, std::get<N-1>( t ), args... );
    }
};

//-----------------------------------------------------------------------------

/**
 * Static Function Tuple Argument Unpacking End Point
 *
 * This recursive template unpacks the tuple parameters into
 * variadic template arguments until we reach the count of 0 where the function
 * is called with the correct parameters
 *
 * @ingroup g_util_tuple
 */
template <>
struct apply_func<0>
{
    template < typename T, typename... ArgsF, typename... ArgsT, typename... Args >
    static void applyTuple( T (*f)( ArgsF... ),
                           const std::tuple<ArgsT...>& /* t */,
                           Args... args )
    {
        f( args... );
    }
};

//-----------------------------------------------------------------------------

/**
 * Static Function Call Forwarding Using Tuple Pack Parameters
 */
// Actual apply function
template < typename T, typename... ArgsF, typename... ArgsT >
void applyTuple( T (*f)(ArgsF...),
                std::tuple<ArgsT...> const& t )
{
    apply_func<sizeof...(ArgsT)>::applyTuple( f, t );
}

// ***************************************
// Usage
// ***************************************

//template < typename T, typename... Args >
//class Message : public IMessage
//{
//    
//    typedef void (T::*F)( Args... args );
//    
//public:
//    
//    Message( const std::string& name,
//            T& obj,
//            F pFunc,
//            Args... args );
//    
//private:
//    
//    virtual void doDispatch( );
//    
//    T*  pObj_;
//    F   pFunc_;
//    std::tuple<Args...> args_;
//};
//
////-----------------------------------------------------------------------------
//
//template < typename T, typename... Args >
//Message<T, Args...>::Message( const std::string& name,
//                             T& obj,
//                             F pFunc,
//                             Args... args )
//: IMessage( name ),
//pObj_( &obj ),
//pFunc_( pFunc ),
//args_( std::forward<Args>(args)... )
//{
//    
//}
//
////-----------------------------------------------------------------------------
//
//template < typename T, typename... Args >
//void Message<T, Args...>::doDispatch( )
//{
//    try
//    {
//        applyTuple( pObj_, pFunc_, args_ );
//    }
//    catch ( std::exception& e )
//    {
//        
//    }
//}


#endif
