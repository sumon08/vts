#ifndef __INCLUDE_PTHREAD_CONDITION_H
#define __INCLUDE_PTHREAD_CONDITION_H


#ifdef __LINUX__
#include <cstdio>
#else 
#include<cxx/cstdio>
#endif


#include <pthread.h>
#include <errno.h>
#include <pthread_mutex.hxx>

namespace adapter
{
    class PthreadCondition
    {
        pthread_cond_t cond;
        pthread_condattr_t attr;

        public:
        int success;
        PthreadCondition()
        {
          success = -1;
          //std::printf("Initiate a pthread_condition\n");

          int ret =  pthread_condattr_init(&attr); 

          if(!(ret<0))
          {
              ret = pthread_cond_init(&cond,&attr);
              if(ret<0)
              {
                  std::printf("pthread_condition initialization failed,errno %d\n", errno);
                  success = 0;
              }
              else
              {
                  success = -1;
              }
          }
          else
          {
              success = 0;          
          }
        }

        ~PthreadCondition()
        {
            pthread_condattr_destroy(&attr);
            pthread_cond_destroy(&cond);
        }

        int Broadcast()
        {
            int ret = pthread_cond_broadcast(&cond);
            if(ret<0)
            {
                std::printf("pthread_broadcast failed, errno %d\n",errno);
            }

            return ret;
        }

        int Signal()
        {
            int ret = pthread_cond_signal(&cond);
            if(ret<0)
            {
                std::printf("pthread_signal failed, errno %d\n",errno);
            }

            return ret;
        }
        int Wait(PthreadMutex & mutex)
        {
            pthread_mutex_t & mt = mutex;
            int ret = pthread_cond_wait(&cond, &mt);
            if(ret<0)
            {
                std::printf("pthread_wait failed, errno %d\n",errno);
            }

            return ret;
        }
        int TimedWait(PthreadMutex & mutex)
        {
            pthread_mutex_t & mt = mutex;
            struct timespec tim;
            clock_gettime(CLOCK_REALTIME, &tim);
            tim.tv_sec += 5;

            int ret = pthread_cond_timedwait(&cond, &mt, &tim);
            if(ret<0)
            {
                std::printf("pthread_timedwait failed, errno %d\n",errno);
            }
            else 
            {
                //std::printf("Timed wait success...\n");
            }


            //std::printf("Not implemented TimedWait\r\n");

            return 0;
        }

    };

}
#endif