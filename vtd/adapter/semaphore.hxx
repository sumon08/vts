#ifndef __INCLUDE_SEMAPHORE_HPP
#define __INCLUDE_SEMAPHORE_HPP

#include<config.hxx>
#include <semaphore.h>
#include <errno.h>
#include <stdint.h>




namespace adapter{

    class Semaphore{
        private:
        sem_t mutex;

        public:

        #ifdef CONFIG_FS_NAMED_SEMAPHORES
        int SemOpen(PathName pname, int flags, int modes);
        int SemClose();
        int SemUnlink(PathName pname);
        #endif //CONFIG_FS_NAMED_SEMAPHORES

        Semaphore()
        {

        }

        ~Semaphore()
        {
            
        }

        int SemInit(int pshared, uint32_t value)
        {
            int ret;
            
            ret = sem_init(&mutex, pshared, value);
    
            if(ret < 0)
            {
                #if CONFIG_TEST_ON_LINUX > 0 
                    std::printf("can't init semaphore, error: %d\n",errno);
                #endif
            }
            return ret;
        }

        int SemDestroy()
        {
            int ret;

            ret = sem_destroy(&mutex);

            if(ret < 0)
            {
                #if CONFIG_TEST_ON_LINUX > 0 
                    std::printf("semaphore destroy failed, error:% d\n",errno);
                #endif
            }
            return ret;
        }

        int SemWait()
        {
            int ret;

            ret = sem_wait(&mutex);

            if(ret < 0)
            {
                #if CONFIG_TEST_ON_LINUX > 0
                    std::printf("sem_wait() failed, error: %d\n",errno);
                #endif
            }
            return ret;
        }

        int SemTimedWait(uint32_t usec)
        {
            struct timespec timeout;
            int ret;

            timeout.tv_sec = usec/1000000;
            timeout.tv_nsec=(usec%1000)*1000;

            ret = sem_timedwait(&mutex,&timeout);

            if(ret < 0)
            {
                #if CONFIG_TEST_ON_LINUX > 0 
                    std::printf("sem_timedwait() failed, error: %d\n",errno);
                #endif
            }
            return ret;
        }

        int SemTryWait()
        {
            int ret;

            ret = sem_trywait(&mutex);

            if(ret < 0)
            {
                #if CONFIG_TEST_ON_LINUX > 0
                    std::printf("sem_trywait() failed, error:%d\n",errno);
                #endif
            }
            return ret;
        }

        int SemPost()
        {
            int ret;

            if(ret < 0)
            {
                ret = sem_post(&mutex);
            }
            return ret;
        }

        int SemGetValue(int *sval)
        {
            int ret;
            int val;
            ret = sem_getvalue(&mutex, &val);
            *sval = val;

            if(ret < 0)
            {
                #if CONFIG_TEST_ON_LINUX > 0
                    std::printf("sem_getvalue() failed,error: %d\n",errno);
                #endif
            }
            return ret;
        }
    };
}

#endif //__INCLUDE_SEMAPHORE_HPP
