


#ifndef _CMD_INCLUDE_H_
#define _CMD_INCLUDE_H_

#include <cxx/cstdint>
#include <cxx/cstdbool>
#include <msg.hxx>
#include <commands.hxx>
#include <module.hxx>
#include <adapter.hxx>

extern "C"{
    extern uint32_t _scmd_registry, _ecmd_registry;
}


namespace vts
{
    namespace command
    {
        //temporary
        typedef int PortId;
        typedef int CmdId;

        #ifndef CONFIG_OUTGOING_COMMAND_BUFFER_SIZE
            #define CONFIG_OUTGOING_COMMAND_BUFFER_SIZE         100
        #endif


        #ifndef CONFIG_FAILED_COMMAND_BUFFER_SIZE
            #define CONFIG_FAILED_COMMAND_BUFFER_SIZE           100
        #endif


        #ifndef CONFIG_ACK_COMMAND_BUFFER_SIZE
            #define CONFIG_ACK_COMMAND_BUFFER_SIZE              100
        #endif


        #define COMMAND_INTERNAL_CHECK_TIME_OUT                 0x01
        //#define COMMAND_INTERNAL_



        volatile int time_counter = 0;

        class CommandManager : public MessageManager<CommandBase>
        {

            // type declaration

            using MessageBasePtr = Core::unique_ptr<MessageBase>;
            using CommandBasePtr = Core::unique_ptr<CommandBase>;
            using Fifo = Core::Fifo<CommandBasePtr>;
            int time_out;






            Fifo obj_to_send[3];
            Fifo obj_send_fail;

            class ObjectNode 
            {
                public: 
                int post_time;
                Core::unique_ptr<CommandBase> obj;
            };

            ObjectNode obj_waiting_to_ack[CONFIG_ACK_COMMAND_BUFFER_SIZE];
            //Adapter::









            public:

            CommandManager():MessageManager<CommandBase>(CommandThreadRunner) , 
            obj_to_send{Fifo(CONFIG_OUTGOING_COMMAND_BUFFER_SIZE),
            Fifo(CONFIG_OUTGOING_COMMAND_BUFFER_SIZE),
            Fifo(CONFIG_OUTGOING_COMMAND_BUFFER_SIZE)}, 
            obj_send_fail(CONFIG_FAILED_COMMAND_BUFFER_SIZE)
            {

            }
            static CommandManager & GetInstance()
            {
                return man;
            }

            Core::unique_ptr<CommandBase> Get(PortType type)
            {
                return obj_to_send[PortIndex(type)].Pop();
            }

            Core::unique_ptr<CommandBase> FindInAckList()
            {
                Core::unique_ptr<CommandBase> temp(nullptr);
                for(int i = 0; i < CONFIG_ACK_COMMAND_BUFFER_SIZE; i++)
                {
                    //if(obj_waiting_to_ack[i])
                    //{
                    //    if(obj_waiting_to_ack[i]->GetChannel() && obj_waiting_to_ack[i]->GetCmd())
                    //        temp = obj_waiting_to_ack[i].release();
                    //}
                }
                return temp;
            }

            const int PortIndex(PortType port_type) const
            {
                int ret = 0;
                switch(port_type)
                {
                    case PortType::PORT_SERIAL: 
                    ret = 0;
                    break;

                    case PortType::PORT_SMS: 
                    ret = 1;
                    break;


                    case PortType::PORT_TCP: 
                    ret = 2;
                    break;

                    default: 
                    break;
                }
                return ret;
            }


            const char * PortName(PortType port_type) const
            {
                const char * ret = 0;
                switch(port_type)
                {
                    case PortType::PORT_SERIAL: 
                    ret = "Serial Port";
                    break;

                    case PortType::PORT_SMS: 
                    ret = "SMS Port";
                    break;


                    case PortType::PORT_TCP: 
                    ret = "TCP Port";
                    break;

                    default: 
                        ret = "Unknown Port";
                    break;
                }
                return ret;
            }


            module::ModuleId CheckRegistry(int cmd, int channel)
            {

                int count = ((int)&_scmd_registry - (int)_ecmd_registry) / CONFIG_CMD_REGISTRY_SIZE;

                const CommandRegistry * reg = (CommandRegistry *) &_scmd_registry;


                for(int i = 0; i < count; i++)
                {
                    if(reg[i].cmd == cmd && reg[i].channel_id == channel)
                    {
                        return reg[i].module_id;
                    }
                }
               return 0;
            }


            static void * CommandThreadRunner(void * arg)
            {
                CommandManager & cmd_man = CommandManager::GetInstance();

                while(1)
                {
                    CommandBasePtr cmd_ptr = cmd_man.NextMessage();

                    switch(cmd_ptr->CommandFlow())
                    {
                        case CommandFlowType::OUTGOING: 
                        {
                            if(!cmd_man.obj_to_send[cmd_man.PortIndex(cmd_ptr->Port())].Full())
                                cmd_man.obj_to_send[cmd_man.PortIndex(cmd_ptr->Port())].Push(Core::move(cmd_ptr));
                            else
                            {
                                // data is not dispatched in time buffer is full now. Write those object to file for future send when network condition become good.
                                std::printf("Out going buffer of %s is full.\n", cmd_man.PortName(cmd_ptr->Port()));
                            }
                        }
                        break;
                        case CommandFlowType::INCOMING:
                        {
                            if(cmd_ptr->Cmd() >= 0x80)
                            {
                                if(cmd_ptr->Channel() != 0)
                                {
                                    module::Module * md = module::Module::GetModule(cmd_ptr->Channel());
                                    if(md != nullptr)
                                    {
                                        MessageBasePtr  msg_ptr(cmd_ptr.release());
                                        md->Write(Core::move(msg_ptr));
                                    }
                                    else
                                    {
                                        std::printf("Module for id: %d is not running\n", cmd_ptr->Channel());
                                    }
                                }
                                else if(cmd_ptr->Channel() > CONFIG_MAX_MODULE_COUNT)
                                {
                                   std::printf("Out of channel command received. May there is bug. Solve it.\n");
                                }
                                else
                                {
                                    std::printf("Control chenel command received from port %s.\n Command ID: %d\n", cmd_man.PortName(cmd_ptr->Port()));
                                }
                            }
                            else
                            {
                                // Find the command who is waiting for this reply.
                                CommandBasePtr obj_to_finish = cmd_man.FindInAckList();

                                if(obj_to_finish == false)
                                {
                                    // Not found in the list may be timed out. write logic if you need.
                                    std::printf("Acknowledgment packet for cmd: %d of channel: %d received from %s. But not found in acknowledgment list. May be \
                                    wrong command received or timeout detected\n", cmd_man.PortName(cmd_ptr->Port()));
                                }
                                std::printf("Command acknowledgment finished. now it is safe to delete the object.\n");
                                //object is removed from list will be deleted automatically with obj_to_finish go out of scope.
                            }
                        }
                        break;

                        case CommandFlowType::INTERNAL: 
                        {
                            switch(cmd_ptr->Cmd())
                            {
                                case COMMAND_INTERNAL_CHECK_TIME_OUT: 
                                {
                                    for(int i = 0; i < CONFIG_ACK_COMMAND_BUFFER_SIZE; i++)
                                    {
                                        if((time_counter - cmd_man.obj_waiting_to_ack[i].post_time) >= cmd_man.time_out)
                                        {
                                            // this object has timed out. so lets remove it from waiting list. move it to failure list.

                                            if(!cmd_man.obj_send_fail.Full())
                                            {
                                                CommandBasePtr time_out_obj(cmd_man.obj_waiting_to_ack[i].obj.release());
                                            }
                                            else
                                            {
                                                std::printf("Send fail object list become full. \n");
                                                // Decide what to do now. Initail case is to save those object file to send later.
                                            }
                                            cmd_man.obj_waiting_to_ack[i].post_time = 0;
                                        }
                                    }
                                }
                                break;

                                default: 
                                    std::printf("Unknown internal command received. Please debug to solve.\n");
                                break;
                            }
                        }
                        break;

                        default: 
                            std::printf("Unknown command direction.\n");
                        break;
                    }

                }
            }
            private:
                static CommandManager man;
        };
        CommandManager CommandManager::man;
    }
}


#endif     //_CMD_INCLUDE_H_
