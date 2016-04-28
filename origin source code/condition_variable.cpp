#include "../util/condition_variable.h"

#include <sys/time.h>

void ConditionVariable::checkError(const char *error_msg, int error) {
    if (error != 0) {
        string msg = error_msg;
        msg += " error: ";
        msg += strerror(error);
        throw runtime_error(error_msg);
    }
}

ConditionVariable::ConditionVariable() {
    pthread_condattr_t cond_attr;
    pthread_condattr_init(&cond_attr);
    int ret_val = pthread_cond_init(&m_condition, &cond_attr);
    pthread_condattr_destroy(&cond_attr);
    this->checkError("ConditionVariable::ConditionVariable", ret_val);
}

ConditionVariable::~ConditionVariable() {
    pthread_cond_destroy(&m_condition);
}

void ConditionVariable::signal() {
    this->checkError("ConditionVariable::Signal",
                     pthread_cond_signal(&m_condition));
}

void ConditionVariable::broadcast() {
    this->checkError("ConditionVariable::Broadcast",
                     pthread_cond_broadcast(&m_condition));
}

void ConditionVariable::wait(Mutex *mutex) {
    this->checkError("ConditionVariable::wait",
                     pthread_cond_wait(&m_condition, &mutex->m_Mutex));
}

bool ConditionVariable::wait(Mutex *mutex, int timeout_in_milsecs) {
    if (timeout_in_milsecs < 0) {
        this->wait(mutex);
        return true;
    }
    
    struct timeval tv;
    gettimeofday(&tv, NULL);
    
    tv.tv_sec += timeout_in_milsecs / 1000;
    tv.tv_usec += (timeout_in_milsecs % 1000) * 1000;
    
    int32 million = 1000000;
    if (tv.tv_usec >= million) {
        tv.tv_sec += tv.tv_usec / million;
        tv.tv_usec %= million;
    }
    
    struct timespec ts;
    ts.tv_sec = tv.tv_sec;
    ts.tv_nsec = tv.tv_usec * 1000;
    
    int32 error = pthread_cond_timedwait(&m_condition, &mutex->m_Mutex, &ts);
    
    if (error == ETIMEDOUT) {
        return false;
    } else {
        this->checkError("CondtionVariable::Wait", error);
    }
    
    return true;
    
}