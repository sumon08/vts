


#ifndef _MODULE_INCLUDE_H_
#define _MODULE_INCLUDE_H_

#include <config.hxx>
#include <cstring>
#include <module_internal.hxx>


namespace  vts
{
    namespace module
    {




        #if !(CONFIG_DEBUG_LEVEL < CONFIG_DEBUG_LEVEL_HIGH)
            
            #ifndef CONFIG_MAX_MODULE_NAME_LENGTH
                #define CONFIG_MAX_MODULE_NAME_LENGTH 10
            #endif

        #endif

        #ifndef CONFIG_MAX_MODULE_COUNT
                #define CONFIG_MAX_MODULE_COUNT 10
        #endif

        typedef int ModuleId;
       

        class Module : public ModuleInternal
        {

            public:



            private: 

            ModuleId _id;
            #if !(CONFIG_DEBUG_LEVEL <  CONFIG_DEBUG_LEVEL_HIGH)
            char  name[CONFIG_MAX_MODULE_NAME_LENGTH];
            #endif
            static Module * module_var [CONFIG_MAX_MODULE_COUNT+1];


            void StoreRef()
            {
                module_var[_id] = this; 
            }


            protected: 

            
            Module()
            {
                _id = 0;
                #if !(CONFIG_DEBUG_LEVEL <  CONFIG_DEBUG_LEVEL_HIGH)
                  name[0] = 0;;
                #endif
                InitModule();
                StoreRef();
            }

            //constructor made protected not to allow creating this class object from user code.

            

            Module(ModuleId id)
            {
                _id = id;
                #if !(CONFIG_DEBUG_LEVEL <  CONFIG_DEBUG_LEVEL_HIGH)
                  name[0] = 0;;
                #endif
                InitModule();
                StoreRef();
            }

            #if !(CONFIG_DEBUG_LEVEL <  CONFIG_DEBUG_LEVEL_HIGH)
            Module(ModuleId id, const char * module_name)
            {
                _id = id;
                std::strncpy(name, module_name, CONFIG_MAX_MODULE_NAME_LENGTH);
                InitModule();
                StoreRef();
            }      

            public:     

            void SetName(const char * module_name)
            {
                std::strncpy(name, module_name, CONFIG_MAX_MODULE_NAME_LENGTH);
            }
            #endif


            public:

            ModuleId GetId()
            {
                return _id;
            }

            void SetId(ModuleId id)
            {
                _id = id;
            }

            #if 1
            static Module * GetModule(int id)
            {

                if(id >= CONFIG_MAX_MODULE_COUNT)
                {
                    return module_var[0];
                }
                return module_var[id];
            }
            #endif
        };        
    }
}



#endif  // _MODULE_INCLUDE_H_