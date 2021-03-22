

#ifndef _ENGINE_SENSOR_INCLUDE_H_
#define _ENGINE_SENSOR_INCLUDE_H_

#include <fcntl.h>
#include <cxx/cstdio>
#include <sys/ioctl.h>
#include <nuttx/clock.h>
#include <nuttx/vts/ioctl.h>

namespace adapter
{
    class EngineSensor
    {
        bool is_open;
        int engine_fd;
        bool locked;

        public: 

        EngineSensor()
        {
            engine_fd = open("/dev/engine",O_RDONLY);
            if(engine_fd<0){
                is_open = false;   
                std::printf("cannot open /dev/engine, errno:%d\n",errno); 
            }
            else{
                int val;
                int status = ioctl(engine_fd,ENGINE_IOC_INIT,(long unsigned)&val);
                if(status < 0){
                    std::printf("Cannot init engine, engine lower->config() failed, errno %d\n",errno);
                    is_open = false;
                }
                else{
                    is_open = true;
                }
            }
            locked = false;
        }

        bool IsOpen()
        {

            return is_open;
        }


        bool IsOn()
        {
            bool eng_value = false;
            int val;
            int status = ioctl(engine_fd,ENGINE_IOC_STATUS,(long unsigned)&val);
            if(status < 0)
            {
                std::printf("Failed to read from Engine Sensor pin.\n");
            }
            eng_value = (val!=0);
            return eng_value;
        }


        bool IsLocked()
        {
            return locked;
        }


        void SetLock()
        {
            // set io pin
            int status = ioctl(engine_fd,ENGINE_IOC_LOCK,(unsigned long)1);
            if(status < 0){
                std::printf("cannot lock engine, errno %d\n",errno);
            }
            else{
                locked = true;
            }

        }

        bool Close()
        {
            int status = close(engine_fd);
            if(status < 0){
                std::printf("Cannot close engine fd, errno :%d\n",errno);
                return false;
            }
            is_open = false;
            return true;
        }


        ~EngineSensor()
        {
            if(is_open)
                Close();
        }




    };
}


#endif      //_ENGINE_SENSOR_INCLUDE_H_