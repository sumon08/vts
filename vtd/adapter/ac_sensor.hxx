
#ifndef _AC_SENSOR_INCLUDE_H_
#define _AC_SENSOR_INCLUDE_H_

namespace adapter
{
    class AcSensor
    {
        bool is_open;
        int ac_fd;


        public: 

        AcSensor()
        {
            is_open = false;
        }

        bool Open()
        {

            is_open = false;
            return true;
        }


        int ReadAdc()
        {
            int ac_value = false;
             // read dev/ac device

             return ac_value;
        }


        bool IsLocked()
        {
            bool lock = false;
            return lock;
        }


        void SetLock()
        {
            // set io pin
        }

        bool Close()
        {
            is_open = false;
            return true;
        }


        ~AcSensor()
        {
            if(is_open)
                Close();
        }




    };
}


#endif      //_ENGINE_SENSOR_INCLUDE_H_

