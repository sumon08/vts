
#ifndef _COMMAND_INTERNAL_INCLUDE_H_
#define _COMMAND_INTERNAL_INCLUDE_H_

#ifdef __LINUX__
#include <cstring>
#else
#include <cxx/cstring>
#include <cxx/cstdint>
#endif

#include <msg.hxx>


namespace vts
{
    namespace command 
    {


        enum class PortType
        {
            PORT_TCP,
            PORT_SMS,
            PORT_SERIAL,
        #ifdef CONFIG_HAVE_USB_DEBUG
            PORT_USB,
        #endif  //CONFIG_HAVE_USB_DEBUG
            PORT_UNKNOWN,
        };

        enum class CommandFlowType 
        {
            INCOMING,
            OUTGOING,
            INTERNAL,
            UNKNOWN
        };

        using CommandId = uint8_t;
        using ChannelId = uint8_t;

        enum class CommandSource 
        {
            DEVICE,
            SERVER
        };

        enum class ObjectToken
        {
            COMMAND_BASE,
            REPLY_BASE,
            ERROR_OBJECT
        };
        


        class CommandBase: public MessageBase
        {
            PortType cmd_port;            
            ChannelId channel;
            CommandId cmd;
            CommandFlowType flow_type;

            protected: 
            CommandBase() : MessageBase(MsgType::COMMAND) 
            {
                cmd_port = PortType::PORT_UNKNOWN;
            }

            


            public:

            static bool Post(CommandBase * base_ptr);
            static Core::unique_ptr<CommandBase> Get(PortType type);

            void Port(PortType port)
            {
                cmd_port = port;
            }

            const PortType Port() const
            {
                return cmd_port;
            }

            virtual const ObjectToken ClassType() const
            {
                return ObjectToken::COMMAND_BASE;
            }

            
            const CommandId Cmd() const
            {
                return cmd;
            }


            const ChannelId Channel() const
            {
                return channel;
            }

            void Cmd(CommandId cmd)
            {
                this->cmd = cmd;
            }

            void Channel(ChannelId channel)
            {
                this->channel = channel;
            }


            void CommandFlow(CommandFlowType flow)
            {
                this->flow_type = flow;
            }

            const CommandFlowType CommandFlow() const 
            {
                return this->flow_type;
            }

            virtual uint16_t MakePacket(uint8_t * buffer, uint16_t length)
            {
                uint16_t index_counter = 0;
                return index_counter;
            }

            virtual const CommandSource Source() const
            {
                return CommandSource::DEVICE;
            }

            virtual ~CommandBase()
            {
                
            }
        };
    }
}
#endif
