


#ifndef _PARSER_INCLUDE_H_
#define _PARSER_INCLUDE_H_


#include <commands.hxx>


namespace vts 
{
    namespace protocol
    {

        enum class ParserError
        {
            SUCCESS,
            INVALID_PARAMETER,
            PARAMETER_OVERLOADED,
            NOT_ENOUGH_PARAM,
            UNKNOWN_COMMAND,
            NOT_IMPLEMENTED,
            UNKNOWN_FAILURE
        };


        class ParserBase 
        {
            command::CommandId cmd_id;
            command::ChannelId channel_id;

        };
    }
}

#endif  //_PARSER_INCLUDE_H_