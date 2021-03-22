

#ifndef _CORE_INCLUDE_H_
#define _CORE_INCLUDE_H_
#include <cxx/cstdbool>

namespace vts
{
    bool InitEventModule(void);
    bool InitCommandModule(void);
    bool InitEngineModule();
    bool InitAcInstance();
}


#endif  //_CORE_INCLUDE_H_