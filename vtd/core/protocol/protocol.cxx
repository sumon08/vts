

#include <protocol.hxx>
#include <default.hxx>


extern "C"
{
    extern uint32_t _sparser_registry, _eparser_registry, _srparser_registry, _erparser_registry;

};


namespace vts 
{
    namespace protocol
    {
        Core::unique_ptr<command::CommandBase> Parser::ParseVer1(const unsigned char * packet, unsigned int length, EncryptionType encryp_algo, PaddingType padd)
        {
            
            Core::unique_ptr<command::CommandBase> ret_ptr(nullptr);


            switch(padd)
            {
                #ifdef CONFIG_PADDING_7BIT_DEFAULT
                case PaddingType::PADDING_7BIT_DEFAULT: 

                break;
                #endif

                case PaddingType::PADDING_8BIT_DEFAULT:

                break;

                default: 
                break; 
            }



            switch(encryp_algo)
            {
                case EncryptionType::NO_ENCRYPTION: 
                break;
                #ifdef CONFIG_HAVE_ENCRYPTION_RSA
                case EncryptionType::RSA:
                {
                    bool is_valid_packet = true;

                    if(!is_valid_packet)
                    {
                        ret_ptr = new EncryptionErrorReply(BAD_ENCRYPTED_STREAM_COMMAND_ID, PROBLEMATIC_COMMAND_CHANNEL);
                        return ret_ptr;
                    }

                }
                
                break;
                #endif

                #ifdef CONFIG_HAVE_ENCRYPTION_ECC
                case EncryptionType::ECC: 

                break;
                #endif

                #ifdef CONFIG_HAVE_ENCRYPTION_AES
                case EncryptionType::AES: 

                break;
                #endif


                #ifdef CONFIG_HAVE_ENCRYPTION_DES
                case EncryptionType::DES: 

                break;
                #endif

            }            

            if(CheckChecksum(packet, length))
            {
                length--;
                // Checksum is valid. Now search for 
                
                uint16_t index_counter = 0;
                uint16_t data_length = 0;
                command::ExecutionResult exec_result = command::ExecutionResult::UNKNOWN_FAILURE;
                bool is_response = false;
                command::ChannelId channel_id = packet[index_counter++];
                command::CommandId cmd_id = packet[index_counter++];
                if(!(cmd_id & 0x80))
                {
                    uint8_t result_code = packet[index_counter++];
                    is_response = true;

                    auto result_decoder = [&result_code]() -> command::ExecutionResult
                    {
                        command::ExecutionResult ret = command::ExecutionResult::UNKNOWN_FAILURE;
                        switch(result_code)
                        {
                            case 0x01:
                                ret = command::ExecutionResult::SUCCESS; 
                            break;

                            case 0x02: 
                                ret = command::ExecutionResult::SUCCESS_WITH_RESULT;
                            break;
                        }
                        return ret;
                    };

                    exec_result = result_decoder();

                    //std::printf("Reply packet detected..\n");

                }
                


                uint8_t data_length_lsb = packet[index_counter++];
                if(data_length & 0x80)
                {
                    uint8_t data_length_msb = packet[index_counter++];
                    //std::printf("Two byte length found...\n");
                    if(data_length_msb & 0x80)
                    {

                        //Second byte of length field have MSB 1. That is not allowed. returning data length object.
                        DataLengthErrorReply * ret = new DataLengthErrorReply(cmd_id, channel_id);
                        ret->BadLength((data_length_lsb * 0x80) + (data_length_msb & 0x7F));
                        ret->ProbableLength(length - (4 + (is_response? 1 : 0)));
                        ret_ptr = ret;
                        return ret_ptr;
                    }

                    data_length_lsb = (data_length_lsb & ~(0x80));

                    data_length = data_length_lsb * 0x80 + data_length_msb;

                    uint16_t provided_data_length = length - (4 + (is_response? 1 : 0));

                    // Check for is there enough data in the packet.
                    if(provided_data_length != data_length)
                    {
                        //printf("Data length on packet didn't match");
                        DataLengthMissmatchReply * ret = new DataLengthMissmatchReply(cmd_id, channel_id);
                        ret->ActualLength(data_length);
                        ret->ProvidedLength(provided_data_length);
                        ret_ptr = ret;
                        return ret_ptr;
                    }
                    
                }
                else
                {
                    data_length = data_length_lsb;
                    uint16_t provided_data_length = length - (3 + (is_response? 1 : 0));

                    //std::printf("One byte length found: %d %d\n", length, provided_data_length);
                    // Check for is there enough data in the packet.
                    if(provided_data_length != data_length)
                    {
                       // printf("Data length on packet didn't match");
                        DataLengthMissmatchReply * ret = new DataLengthMissmatchReply(cmd_id, channel_id);
                        ret->ActualLength(data_length);
                        ret->ProvidedLength(provided_data_length);
                        ret_ptr = ret;
                        return ret_ptr;
                    }
                }


                if(is_response)
                {
                    const ReplyParserRegistry * reg = SearchReplyParser(cmd_id, channel_id);
                    if(reg == nullptr)
                    {
                        UnknownAcknowledgmentReply * unknown = new UnknownAcknowledgmentReply(cmd_id, channel_id);
                        ret_ptr = unknown;
                        return ret_ptr;
                    }
                    else
                    {
                        if(reg->callback == nullptr)
                        {
                            NotImplementedReply * not_impl = new NotImplementedReply(cmd_id, channel_id);
                            ret_ptr = not_impl;
                            return ret_ptr;
                        }
                        else
                        {
                            Core::unique_ptr<command::ReplyBase> ptr = reg->callback(&packet[index_counter], data_length);
                            ret_ptr = ptr.release();
                            //return ret_ptr;
                        }
                    }
                }
                else
                {
                    const ParserRegistry * reg = SearchCommandParser(cmd_id, channel_id);
                    if(reg == nullptr)
                    {
                        UnknownCommandReply * unknown = new UnknownCommandReply(cmd_id, channel_id);
                        ret_ptr = unknown;
                        return ret_ptr;
                    }
                    else
                    {
                        if(reg->callback == nullptr)
                        {
                            NotImplementedReply * not_impl = new NotImplementedReply(cmd_id, channel_id);
                            ret_ptr = not_impl;
                            return ret_ptr;
                        }
                        else
                        {
                            ret_ptr = reg->callback(&packet[index_counter], data_length);
                            
                            //return ret_ptr;
                        }
                    }
                }

                // Check for is handler function is found for this command

                if(ret_ptr.get() == nullptr)
                {
                    // Parser return null pointer. That should not be. Bad design of parser function. report it.
                    //std::printf("No hndler found..\n");

                    BadParserReply * bad = new BadParserReply(cmd_id, channel_id);
                    ret_ptr = bad;
                    return ret_ptr;

                }

                if(ret_ptr->ClassType() != command::ObjectToken::ERROR_OBJECT)
                {
                    ret_ptr->Cmd(cmd_id);
                    ret_ptr->Channel(channel_id);
                }

                if(is_response)
                {
                    // Packet is respons type come from server or serial
                    // ret_ptr should hold valid object here. Implementor shuld be very carefull here 
                    // if cmd indicate response type then its 

                    command::ReplyBase * reply_base = static_cast<command::ReplyBase *>(ret_ptr.get());
                    // We should carefull here. we are using managed memory out of it control.
                    reply_base->Result(exec_result);
                }
            }
            else 
            {
                BadChecksumReply * checksum = new BadChecksumReply(CHECKSUM_FAILED_COMMAND_ID, PROBLEMATIC_COMMAND_CHANNEL);
                checksum->PacketChecksum(packet[length -1]);
                checksum->CalculatedChecksum(CalculateChecksum(packet, length -1));
                ret_ptr = checksum;
            }

            // We finished up parsing packet. returning parsed command.

            

            return ret_ptr;
        }

        bool Parser::CheckChecksum(const unsigned char * packet, unsigned int length)
        {
            bool ret = false;
            if(packet[length-1] == CalculateChecksum(packet, length - 1))
                ret = true;
            return ret;
        }

        uint8_t Parser::CalculateChecksum(const uint8_t * bufffer, uint16_t length)
        {
            crc.Reset();
            crc.Update(bufffer, length);
            return crc;
        }


        Core::unique_ptr<command::CommandBase> Parser::Parse(int protocol_version, const unsigned char * packet, unsigned int length, EncryptionType encryp_algo, PaddingType padd)
        {
            //currently have only one protocol
            
            Core::unique_ptr<command::CommandBase> cmd_ptr = ParseVer1(packet, length, encryp_algo, padd);
            return cmd_ptr;
        }

        Core::unique_ptr<command::CommandBase> Parser::Parse(const unsigned char * packet, unsigned int length)
        {
            Core::unique_ptr<command::CommandBase> cmd_ptr = ParseVer1(packet, length, encrytion, padding);
            return cmd_ptr;
        }


        const ParserRegistry * Parser::SearchCommandParser(command::CommandId id, command::ChannelId channel)
        {
            uint8_t * start_ponit = (uint8_t *) &(_sparser_registry);
            uint16_t entry_count = ((int) &(_eparser_registry) - (int) & (_sparser_registry))/PARSER_CMD_REGISTRY_SIZE;

            const ParserRegistry * registry = nullptr;


            //std::printf("Entry_count: %d...\n", entry_count);
            for(int i = 0; i < entry_count; i++)
            {
                const ParserRegistry * parse_point =  (const ParserRegistry * ) start_ponit;

                //std::printf("Command: %d, Channel: %d at %02X\n", parse_point->cmd, parse_point->channel, (unsigned int)start_ponit);
                if((parse_point->protocol == 1 ) && (parse_point->channel == channel) && (parse_point->cmd == id))
                {
                    registry = parse_point;

                    break;
                }         
                start_ponit += PARSER_CMD_REGISTRY_SIZE;           
            }

            return registry; 
        }

        const ReplyParserRegistry * Parser::SearchReplyParser(command::CommandId id, command::ChannelId channel)
        {
            uint8_t * start_ponit = (uint8_t *) &(_srparser_registry);
            uint16_t entry_count = ((int) &(_erparser_registry) - (int) & (_srparser_registry))/REPLY_PARSER_CMD_REGISTRY_SIZE;

            const ReplyParserRegistry * registry = nullptr;


            //std::printf("Entry_count: %d...\n", entry_count);
            for(int i = 0; i < entry_count; i++)
            {
                const ReplyParserRegistry * parse_point =  (const ReplyParserRegistry * ) start_ponit;

                //std::printf("Command: %d, Channel: %d at %02X\n", parse_point->cmd, parse_point->channel, (unsigned int)start_ponit);
                if((parse_point->protocol == 1 ) && (parse_point->channel == channel) && (parse_point->cmd == id))
                {
                    registry = parse_point;

                    break;
                }         
                start_ponit += PARSER_CMD_REGISTRY_SIZE;           
            }

            return registry; 
        }
    }
}