


#ifndef  _COMMANDS_INCLUDE_H_
    #define _COMMANDS_INCLUDE_H_


#include <utility.hxx>
#include <commands_internal.hxx>

#ifdef __LINUX__
#include <cstring>
#else 
#include <cxx/cstring>
#endif



namespace vts
{
    namespace command 
    {
        #define  CMD_REGISTRY __attribute__((section(".cmd_registry")))
        #define CONFIG_CMD_REGISTRY_SIZE 8
        #define CONFIG_ERROR_FUNC_NOT_IMPLEMENTED   120




        





        struct CommandRegistry 
        {
            uint8_t module_id;
            uint8_t channel_id;
            uint8_t cmd;
            const char *cmd_string;
        }__attribute__(( aligned(CONFIG_CMD_REGISTRY_SIZE)));






        enum class ExecutionResult
        {
            SUCCESS = 0x01,
            SUCCESS_WITH_RESULT,
            ACCESS_DENIDE,
            NOT_HANDLED,
            UNKNOWN_FAILURE,
            BAD_HANDLER,
            PARSING_ERROR
        };


        class ReplyBase: public CommandBase
        {
            ExecutionResult result;

            protected: 
            ReplyBase()
            {
                result = ExecutionResult::UNKNOWN_FAILURE;
            }

            public: 

            void Result(ExecutionResult res)
            {
                result = res;
            }

            const ExecutionResult Result() const
            {
                return result;
            }

            const CommandSource Source() const final
            {
                return CommandSource::SERVER;
            }

            virtual const ObjectToken ClassType() const
            {
                return ObjectToken::REPLY_BASE;
            }

            ~ReplyBase()
            {
                
            }

        };


        class ErrorBase : public ReplyBase
        {
            public: 
            const command::ObjectToken ClassType() const final
            {
                return command::ObjectToken::ERROR_OBJECT;
            }
        };


       
    }
}




#endif // ! _COMMANDS_INCLUDE_H_  


