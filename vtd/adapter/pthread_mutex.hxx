#ifndef __INCLUDE_PTHREAD_MUTEX_H
#define __INCLUDE_PTHREAD_MUTEX_H

#ifdef __LINUX__
#include <cstdio>
#else 
#include<cxx/cstdio>
#endif


#include <pthread.h>
#include <errno.h>

namespace adapter {

    class PthreadMutex{

        pthread_mutexattr_t attr;
        pthread_mutex_t mutex;
        
        public:
        int success;
        PthreadMutex()
        {
            success = -1;
            //std::printf("initiate a pthread_mutex\n");

            int ret = pthread_mutexattr_init(&attr);
            if(!(ret < 0))
            {
                ret = pthread_mutex_init(&mutex,&attr);
                if(ret < 0){
                    std::printf("pthread_mutex initialization failed, errno %d\n",errno);
                    success =0;
                }
                else{
                    success =1;
                }
            }
            else{
                success = 0;
            }
        }

        ~PthreadMutex()
        {
            pthread_mutexattr_destroy(&attr);
            pthread_mutex_destroy(&mutex);
        }


        operator pthread_mutex_t & ()
        {
            return mutex;
        }

        int Lock()
        {
            int ret = pthread_mutex_lock(&mutex);
            if(ret < 0)
            {
                //std::printf("pthread_mutex lock failed, errno: %d\n",errno);
            }
            return ret;
        }

        int TryLock()
        {
            int ret = pthread_mutex_trylock(&mutex);

            if(ret < 0)
            {
                //std::printf("pthread_mutex trylock failed, errno: %d\n",errno);
            }
            return ret;
        }

        int Unlock()
        {
            int ret = pthread_mutex_unlock(&mutex);

            if(ret < 0){
                //std::printf("pthread_mutex unlock failed, errno: %d\n",errno);
            }
            return ret;
        }

    };    
} // Adapter


#endif //__INCLUDE_PTHREAD_MUTEX_H
