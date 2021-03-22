

#include <config.hxx>
#include <port.hxx>
#include <default.hxx>



namespace vts 
{
    namespace command 
    {
        Port Port::port_instance[3] = {Port(PortType::PORT_SERIAL), Port(PortType::PORT_SMS), Port(PortType::PORT_TCP)};


        Port::Port(PortType _port): port(_port), parser(packet_encryption, packet_pading, protocol_version)
        {
            protocol_version = 1;
            packet_encryption = protocol::EncryptionType::NO_ENCRYPTION;
            packet_pading = protocol::PaddingType::PADDING_8BIT_DEFAULT;
        }

        bool Port::ParseAndPostGeneric(const uint8_t * cmd_packet, uint16_t packet_length)
        {
            bool ret = false;
            Core::unique_ptr<CommandBase> parsed_cmd = parser.Parse(cmd_packet, packet_length);
            if(parsed_cmd.get() != nullptr)
            {
                
                if(parsed_cmd->ClassType() == ObjectToken::ERROR_OBJECT)
                {
                    //ret = out_fifo.Push(Core::move(parsed_cmd));
                    parsed_cmd->CommandFlow(CommandFlowType::OUTGOING);
                }
                else
                {
                    //std::printf("Command: %d, Channel: %d\n", parsed_cmd->Cmd(), parsed_cmd->Channel());
                    parsed_cmd->CommandFlow(CommandFlowType::INCOMING);                    
                }
                CommandBase * base = parsed_cmd.release();
                ret = CommandBase::Post(base);
            }

            return ret;
        }


        Core::unique_ptr<CommandBase> Port::ParseAndPostSms(const uint8_t * cmd_packet, uint16_t packet_length)
        {
            Core::unique_ptr<CommandBase> ret_ptr(nullptr);
            return ret_ptr;
        }



        bool Port::Write(const uint8_t * cmd_packet, uint16_t packet_length)
        {
            bool ret = false;
            switch(port)
            {
                case PortType::PORT_SERIAL:
                ret = ParseAndPostGeneric(cmd_packet, packet_length);
                break;

                case PortType::PORT_SMS: 
                {
                    ParseAndPostSms(cmd_packet, packet_length);
                }
                break;

                case PortType::PORT_TCP: 
                    ret = ParseAndPostGeneric(cmd_packet, packet_length);
                break;

                default: 
                break;
            }

            return ret;
        }


        uint16_t Port::Read(uint8_t * packet_buffer, uint16_t packet_length)
        {
            
            
            uint16_t ret = 0;

            if(packet_buffer == nullptr)
            {
                return ret;
            }

            if(packet_length <= 0)
            {
                return ret;
            }

            Core::unique_ptr<CommandBase> reply_ptr = CommandBase::Get(this->port);
            
            if(reply_ptr.get() == nullptr)
                return ret;

            uint16_t index_counter = 0;
            #ifdef CONFIG_PROTOCOL_HAVE_START_STOP_BYTE
            packet_buffer[index_counter++] = CONFIG_PROTOCOL_START_BYTE;
            #endif

            packet_buffer[index_counter++] = reply_ptr->Channel();
            packet_buffer[index_counter++] = reply_ptr->Cmd();

            

            if(reply_ptr->Source() == CommandSource::SERVER)
            {
                ReplyBase * rep = (ReplyBase *)reply_ptr.get();
                auto var = [&rep]()->uint8_t
                {
                    uint8_t ret = 0;
                    switch(rep->Result())
                    {
                        case ExecutionResult::SUCCESS: 
                            ret = 1;
                        break;

                        case ExecutionResult::SUCCESS_WITH_RESULT: 
                            ret = 2;
                        break;

                        case ExecutionResult::ACCESS_DENIDE: 
                            ret = 3;
                        break;

                        case ExecutionResult::BAD_HANDLER: 
                            ret = 4;
                        break;

                        case ExecutionResult::NOT_HANDLED: 
                            ret = 5;
                        break;

                        case ExecutionResult::PARSING_ERROR: 
                            ret = 6;
                        break;

                        case ExecutionResult::UNKNOWN_FAILURE: 
                            ret = 7;
                        break;
                    }
                    return ret;
                };

                //std::printf("Execution result: %d\n",var());
                packet_buffer[index_counter++] = var();
            }
            {
                //std::printf("Packet from Device..\n");
            }

            uint16_t data_length = reply_ptr->MakePacket(&packet_buffer[index_counter], packet_length - index_counter -1);

            if(data_length == CONFIG_MAKE_PACKET_BUFFER_OVERFLOW_RETURN_VALUE)
            {
                // supplied buffer in make packet function is not enough.
                packet_buffer[index_counter-1] = 7;
                packet_buffer[index_counter++] = 1;
                packet_buffer[index_counter++] = CONFIG_BUFFER_OVERLOAD_ERROR_ID;
            }
            else if(data_length  > CONFIG_MAKE_PACKET_MAX_VALID_RETURN_VALUE)
            {
                // We get a probable bad make packet implementation. solve it first. 
                packet_buffer[index_counter-1] = 7;
                packet_buffer[index_counter++] = 1;
                packet_buffer[index_counter++] = CONFIG_PARAM_OVERLOADED_ERROR_ID;
            }
            else
            {
                if(data_length > 0x7F)
                {
                    // data field is 2 byte
                    uint8_t lsb = data_length / 0x80;
                    uint8_t msb = data_length % 0x80;
                    lsb &= ~0x80; // set MSB to 1.
                    packet_buffer[index_counter++] = lsb;
                    packet_buffer[index_counter++] = msb; 
                }
                else
                {
                    //data field is 1 byte
                    packet_buffer[index_counter++] = data_length;
                }

                reply_ptr->MakePacket(&packet_buffer[index_counter], packet_length - index_counter -1);
                index_counter += data_length;
                
               
                #ifdef CONFIG_PROTOCOL_HAVE_START_STOP_BYTE
                
                uint8_t checksum = parser.CalculateChecksum(&packet_buffer[1], index_counter -1);
                packet_buffer[index_counter++] = checksum;
                packet_buffer[index_counter++] = CONFIG_PROTOCOL_STOP_BYTE;
                #else

                uint8_t checksum = parser.CalculateChecksum(&packet_buffer[0], index_counter);
                packet_buffer[index_counter++] = checksum;

                #endif

            }
            return index_counter;           
        }

    }
}