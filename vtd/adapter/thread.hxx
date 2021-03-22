#ifndef __INCLUDE_THREAD_HPP
#define __INCLUDE_THREAD_HPP

#include <config.hxx>
#include <pthread.h>
#include <errno.h>
#include <cxx/cstdio>
#include <command_config.h>

namespace adapter{

    using ThreadFunc =  void * (*) (void*);
    using StackSize = int;
    using Priority = int;
    using ThreadStatus = int;
    using ThreadArgument = void *;

    class Thread{
        private:
            pthread_t pid;
            ThreadFunc start_routine;
            ThreadArgument arg;
            pthread_attr_t attr;

        public:
            Thread(){
                start_routine = NULL;
                pthread_attr_init(&attr);
                arg = nullptr;
            }
            Thread(ThreadFunc func){
                start_routine = func;
                pthread_attr_init(&attr);
            }

            void SetStartRoutine(ThreadFunc func)
            {
                start_routine = func;
                pthread_attr_init(&attr);
            }

            ThreadStatus Run()
            {
                ThreadStatus ret;
                if(start_routine == NULL){
                       std::printf("error: no start routine is set\n");
                    return -2;
                }

                ret = pthread_create(&pid,&attr,start_routine,arg);
                if(ret < 0){
                    std::printf("pthread create failed, errno:%d\n",errno);
                }
                return ret;
            }


            void SetArgument(ThreadArgument argument)
            {
                arg = argument;
            }






            ThreadStatus Run(ThreadFunc func)
            {
                start_routine = func;
                if(start_routine == NULL){
                    #if CONFIG_TEST_ON_LINUX > 0
                        printf("error: no start routine is set\n");
                    #endif //CONFIG_TEST_ON_LINUX
                    return -2;
                }
                int ret;
                ret = pthread_create(&pid,&attr,start_routine,arg);
                if(ret < 0){
                    std::printf("pthread create failed, errno:%d\n",errno);
                }
                return ret;
            }







            void SetStackSize(StackSize s_size)
            {
                pthread_attr_setstacksize(&attr, s_size);
            }
            void SetPriority(Priority prio)
            {
                sched_param param;
                param.sched_priority = prio;
                pthread_attr_setschedparam(&attr, &param);
            }
            void SetAttribute(StackSize s_size, Priority prio)
            {
                pthread_attr_setstacksize(&attr, s_size);
                sched_param param;
                param.sched_priority = prio;
                pthread_attr_setschedparam(&attr, &param);
            }
            ThreadStatus Stop()
            {
                 ThreadStatus ret = pthread_cancel(pid);
                 return ret;
            }

    };
}

#endif //__INCLUDE_THREAD_HPP
