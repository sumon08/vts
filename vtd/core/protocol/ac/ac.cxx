


#include <ac_status.hxx>


namespace vts 
{
    namespace protocol 
    {
        volatile const ParserRegistry ac_status_parser PARSER_REGISTRY = 
        {
            .channel = 0x03,
            .cmd = 0x81,
            .protocol = 1,
            .callback = AcStatusParser
        };
        volatile const ParserRegistry ac_status_ack_parser PARSER_REGISTRY = 
        {
            .channel = 0x03,
            .cmd = 0x01,
            .protocol = 1,
            .callback = NULL
        };
        volatile const ParserRegistry ac_status_query_parser PARSER_REGISTRY = 
        {
            .channel = 0x03,
            .cmd = 0x83,
            .protocol = 1,
            .callback = NULL
        };
        volatile const ParserRegistry ac_status_query_ack_parser PARSER_REGISTRY = 
        {
            .channel = 0x03,
            .cmd = 0x03,
            .protocol = 1,
            .callback = NULL
        };
        volatile const ParserRegistry ac_enable_parser PARSER_REGISTRY = 
        {
            .channel = 0x03,
            .cmd = 0x84,
            .protocol = 1,
            .callback = NULL
        };
        volatile const ParserRegistry ac_enable_ack_parser PARSER_REGISTRY = 
        {
            .channel = 0x03,
            .cmd = 0x04,
            .protocol = 1,
            .callback = NULL
        };
        volatile const ParserRegistry ac_disable_parser PARSER_REGISTRY = 
        {
            .channel = 0x03,
            .cmd = 0x85,
            .protocol = 1,
            .callback = NULL
        };
        volatile const ParserRegistry ac_disable_ack_parser PARSER_REGISTRY = 
        {
            .channel = 0x03,
            .cmd = 0x05,
            .protocol = 1,
            .callback = NULL
        };
    }
}