#ifndef __INCLUDE_WDTIMER_HPP
#define __INCLUDE_WDTIMER_HPP

#include <nuttx/config.h>
#include <unistd.h>
#include <nuttx/wdog.h>

#ifdef __LINUX__
#include <cstdio>
#else 
#include<cxx/cstdio>
#endif

#include <errno.h>

#ifndef CONFIG_MAX_ALLOWED_WATCHDOG_TIMERS
    #define CONFIG_MAX_ALLOWED_WATCHDOG_TIMERS 8
#endif //CONFIG_MAX_ALLOWED_WATCHDOG_TIMERS

namespace adapter {

    typedef void (*func_ptr) (int param);
    typedef unsigned int TimerId;
    
    class WDTimer{
    
        private:
        unsigned long time_passed;
        unsigned long wd_timeout;
        WDOG_ID timer_id;
        func_ptr callback_func;
        static WDTimer wdObject[CONFIG_MAX_ALLOWED_WATCHDOG_TIMERS];
        bool auto_reload;
        TimerId id;
        
        WDTimer()
        {
            wd_timeout = 0;
            time_passed = 0;
        }
        
        WDTimer(bool runnable)
        {
            wd_timeout = 0;
            time_passed = 0;
        }

        static void WDHandlerFunction(int a1, TimerId id, ...)
        {
            if(wdObject[id].callback_func == NULL){
                std::printf("Callback function not set\n");
            }
            else{
                wdObject[id].callback_func(id);
                if(wdObject[id].auto_reload)
                {
                    wdObject[id].StartTimer(wdObject[id].wd_timeout,wdObject[id].auto_reload);
                }
            }
        }


        public:
        ~WDTimer()
        {
            
        }
        int StopTimer()
        {
            int ret;
            ret = wd_cancel(wdObject[id].timer_id);

            if(ret < 0)
            {
                std::printf("error stopping timer, errno: %d\n",errno);
            }
            return ret;
        }
        int CreateTimer()
        {
            wdObject[id].timer_id = wd_create();

            return 0;
        }

        int StartTimer(uint32_t timeout, bool reload)
        {
            wdObject[id].wd_timeout = timeout;
            wdObject[id].auto_reload = reload;
            int ret;
            ret = wd_start(wdObject[id].timer_id,wd_timeout,wdObject[id].WDHandlerFunction,1,id);

            if(ret < 0 ){
                std::printf("cannot start timer, errno: %d %d\n",errno, ret);
            }
            return ret;
        }
        
        unsigned long PassedTime()
        {
            wdObject[id].time_passed = wd_gettime(wdObject[id].timer_id);
            return wdObject[id].time_passed;
        }
    
        static WDTimer * CreateInstance(TimerId id)
        {
            if(id < CONFIG_MAX_ALLOWED_WATCHDOG_TIMERS)
            {
                WDTimer * wd = &wdObject[id];
                wd->id = id;
                return wd;
            }
            else
                return nullptr;
        }

        void SetCallingFunction(func_ptr func)
        {
                wdObject[id].callback_func = func;
        }

        bool isValid()
        {
            return true;
        }
    };


    
} // Adapter

#endif //__INCLUDE_WDTIMER_HPP
