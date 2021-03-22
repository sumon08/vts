



#ifndef _PORT_INCLUDE_H_



#include <commands.hxx>
#include <utility.hxx>
#include <protocol.hxx>



namespace vts
{
    namespace command
    {

        #ifdef CONFIG_HAVE_USB_DEBUG
        #define CONFIG_MAX_PORT             4
        #else 
        #define CONFIG_MAX_PORT             3
        #endif 


        class Port 
        {
            const PortType port;
            static Port port_instance[3];
            uint8_t protocol_version;
            protocol::EncryptionType packet_encryption;
            protocol::PaddingType packet_pading;
            protocol::Parser  parser;
            


            Core::unique_ptr<CommandBase> ParseAndPostSms(const uint8_t * cmd_packet, uint16_t packet_length);
            bool ParseAndPostGeneric(const uint8_t * cmd_packet, uint16_t packet_length);
            
            public: 
            
            Port(PortType _port);

            static Port * GetInstance(PortType _port)
            {
                for(int i = 0; i < CONFIG_MAX_PORT; i++)
                {
                    if(port_instance[i].port == _port)
                    {
                        return &port_instance[i];
                    }
                }
                return nullptr;

            }
            
            

            bool Write(const uint8_t * cmd_packet, uint16_t packet_length);
            uint16_t Read( uint8_t * packet_buffer, uint16_t packet_length);
        };
    }
}

#endif