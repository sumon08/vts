

#ifndef _PARSER_REGISTRY_H_
#define _PARSER_REGISTRY_H_



#include<utility.hxx>
#include<commands.hxx>



namespace vts
{
    namespace protocol
    {
        using CommandParserCallback = Core::unique_ptr<command::CommandBase> (*)(const uint8_t * cmd_data, uint16_t length);
        using ReplyParserCallback = Core::unique_ptr<command::ReplyBase> (*)(const uint8_t * cmd_data, uint16_t length);

        #define PARSER_REGISTRY __attribute__((section(".parser_registry"),used))
        #define PARSER_CMD_REGISTRY_SIZE 8

        #define REPLY_PARSER_REGISTRY __attribute__((section(".rparser_registry"),used))
        #define REPLY_PARSER_CMD_REGISTRY_SIZE 8

        struct ParserRegistry 
        {
            uint8_t channel;
            uint8_t cmd;
            uint16_t protocol;
            CommandParserCallback callback;
            
        }__attribute__((aligned(PARSER_CMD_REGISTRY_SIZE)));

        struct ReplyParserRegistry 
        {
            uint8_t channel;
            uint8_t cmd;
            uint16_t protocol;
            ReplyParserCallback callback;
            
        }__attribute__((aligned(REPLY_PARSER_CMD_REGISTRY_SIZE)));


    }
}

#endif  //_PARSER_REGISTRY_H_