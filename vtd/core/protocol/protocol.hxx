

#ifndef _PROTOCOL_INCLUDE_H_
#define _PROTOCOL_INCLUDE_H_

#include <config.hxx>
#include <utility.hxx>
#include <commands.hxx>
#include <parser_registry.hxx>
#include <adapter.hxx>

namespace vts
{
    namespace protocol 
    {

        #ifndef CONFIG_PROTOCOL_HAVE_START_STOP_BYTE
            #define CONFIG_PROTOCOL_HAVE_START_STOP_BYTE        1
            #define CONFIG_PROTOCOL_START_BYTE                  0xF8
            #define CONFIG_PROTOCOL_STOP_BYTE                   0xF8
        #endif

        #ifndef CONFIG_HAVE_PACKET_ENCRYPTION
            #define CONFIG_HAVE_PACKET_ENCRYPTION               1


            #define CONFIG_HAVE_ENCRYPTION_RSA                  1


            #ifndef CONFIG_MULTIPLE_ENCRYPTION_SUPPORT          
                #define CONFIG_MULTIPLE_ENCRYPTION_SUPPORT      1
            #endif
        #endif


        #define PROBLEMATIC_COMMAND_CHANNEL                     0x7F
        #define NOT_IMPLEMENTED_COMMAND_ID                      0x01
        #define BAD_FORMATED_COMMAND_ID                         0x02
        #define CHECKSUM_FAILED_COMMAND_ID                      0x03
        #define DATA_LENGTH_ERROR_COMMAND_ID                    0x04
        #define BAD_ENCRYPTED_STREAM_COMMAND_ID                 0x05
        #define DATA_LENGTH_MISSMATCHED_COMMAND_ID              0x06
        #define UNKNOWN_COMMAND_ID                              0x07


        //#define CONFIG_PACKET_PADDING_SCHEAM


        #ifdef CONFIG_HAVE_PACKET_PADDING_SCHEAM
            #ifdef CONFIG_PADDING_7BIT_DEFAULT

            #endif



            #ifdef CONFIG_PADDING_8BIT_DEFAULT

            #endif

        #else
            #define CONFIG_PADDING_8BIT_DEFAULT
        #endif


        enum class PaddingType 
        {
        #ifdef CONFIG_PADDING_7BIT_DEFAULT
            PADDING_7BIT_DEFAULT,
        #endif
            PADDING_8BIT_DEFAULT
        };


        enum class EncryptionType
        {
        #ifdef CONFIG_HAVE_ENCRYPTION_RSA
            RSA,
        #endif

        #ifdef CONFIG_HAVE_ENCRYPTION_ECC
            ECC,
        #endif

        #ifdef CONFIG_HAVE_ENCRYPTION_AES
            AES,
        #endif

        #ifdef CONFIG_HAVE_ENCRYPTION_DES
            DES
        #endif

            NO_ENCRYPTION
        };




        class Parser 
        {
            
            bool is_valid;
            EncryptionType encrytion;
            PaddingType padding;
            uint8_t ver;
            adapter::CrcEight crc;
            

            bool CheckChecksum(const unsigned char * packet, unsigned int length);
            Core::unique_ptr<command::CommandBase> ParseVer1(const unsigned char * packet, unsigned int length, EncryptionType encryp_algo, PaddingType padd);
            const ParserRegistry * SearchCommandParser(command::CommandId id, command::ChannelId channel);
            const ReplyParserRegistry * SearchReplyParser(command::CommandId id, command::ChannelId channel);
            
            public: 

            Parser()
            {
                is_valid = false;
                encrytion = EncryptionType::NO_ENCRYPTION;
                padding = PaddingType::PADDING_8BIT_DEFAULT;
                ver = 1;
            }

            Parser(EncryptionType enc_type, PaddingType padd, uint8_t version)
            {
                is_valid = false;
                encrytion = enc_type;
                padding = padd;
                ver =version;

            }
            

            Core::unique_ptr<command::CommandBase> Parse(int protocol_version, const unsigned char * packet, unsigned int length, EncryptionType encryp_algo, PaddingType padd);

            Core::unique_ptr<command::CommandBase> Parse(const unsigned char * packet, unsigned int length);
            uint8_t CalculateChecksum(const uint8_t * bufffer, uint16_t length);

        };

        class CommandWithNoData : public command::CommandBase
        {

            public: 
            CommandWithNoData()
            {
                
            }
        };


    }
}





#endif      // _PROTOCOL_INCLUDE_H_