/*!
 * \file scheduler_communicator.h
 * \brief 条件变量的封装
 *
 * \author Jiang Jiazhi
 * \version 1.0
 * \date 2014.9.8
 */
#ifndef __DCR__condition_variable__
#define __DCR__condition_variable__

#include <pthread.h>
#include <iostream>
#include <string>

#include "../util/mutex.h"

using namespace std;

///
/// \brief 条件变量的封装， 暂时没用到
///
class ConditionVariable{
public:
    ConditionVariable();
    
    ~ConditionVariable();
    
    void signal();
    
    void broadcast();
    
    bool wait(Mutex *mutex, int timeout_in_milsecs);
    
    void wait(Mutex *mutex);
    
private:
    pthread_cond_t m_condition;
    static void checkError(const char *error_msg, int error);
};

#endif 