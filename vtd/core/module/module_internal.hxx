
#ifndef _MODULE_INTERNAL_INCLUDE_H_
#define _MODULE_INTERNAL_INCLUDE_H_

#include <adapter.hxx>
#include <utility.hxx>
#include <events.hxx>
#include <commands.hxx>
#include <default.hxx>

namespace vts 
{
    namespace module 
    {
        

        #define PER_MODULE_FIFO_SIZE    20

        


        using EventCallBackFunc     = bool (*)(const event::EventBase & event_ref);
        using CommandCallBackFunc   = command::ExecutionResult (*)(const command::CommandBase * cmd_ref, Core::unique_ptr<command::ReplyBase> & reply_buffer);

        class ModuleInternal
        {
            private:
            using MessagePtr = Core::unique_ptr<vts::MessageBase>;
            bool is_initialised;
            adapter::Thread pid_thread;
            Core::Fifo<MessagePtr> msg_buffer;

            CommandCallBackFunc cmd_func;
            EventCallBackFunc event_func;

            


           static void * ThreadRunner(void * arg)
           {
                ModuleInternal * pmodule = (ModuleInternal *)arg; 
                ModuleInternal & running_module = ( ModuleInternal & )*pmodule;

                // loop for module main thread.
                while(1)
                {
                    //std::printf("Engine OFF\n");

                    MessagePtr msg = Core::move(running_module.msg_buffer.Pop());
                    switch(msg->MessageType())
                    {
                        case MsgType::COMMAND:
                        {
                            Core::unique_ptr<command::ReplyBase> reply;
                            command::CommandBase * cmd_base =  static_cast<command::CommandBase *>(msg.get());// (command::CommandBase *)msg.get();
                            command::ExecutionResult result = running_module.cmd_func((cmd_base), reply);

                            switch(result)
                            {
                                case command::ExecutionResult::SUCCESS :
                                {
                                    //std::printf("Execution of command ID: %d success.\n",cmd_base->Cmd());
                                    reply = new protocol::SuccessReply(cmd_base->Cmd(), cmd_base->Channel());

                                }
                                break;

                                case command::ExecutionResult::SUCCESS_WITH_RESULT :
                                {

                                    // Execution result chould set from the handler function. 
                                    if(reply.get() == nullptr)
                                    {
                                        reply->Result(command::ExecutionResult::SUCCESS_WITH_RESULT);
                                        reply->Cmd(cmd_base->Cmd() & ~(0x80));
                                    }
                                    else
                                    {
                                        reply = new protocol::BadHandlerReply(cmd_base->Cmd(), cmd_base->Channel());
                                    }
                                }
                                break;
                                
                                case command::ExecutionResult::UNKNOWN_FAILURE: 
                                {
                                    reply = new protocol::UnknownFailureReply(cmd_base->Cmd(), cmd_base->Channel());
                                }
                                break;

                                case command::ExecutionResult::NOT_HANDLED: 
                                {
                                    //std::printf("Command: %d Channel: %d\n", cmd_base->Cmd(), cmd_base->Channel());
                                    reply = new protocol::NotHandledReply(cmd_base->Cmd(), cmd_base->Channel());
                                }
                                break;

                                default:
                                {
                                    reply = new protocol::BadHandlerReply(cmd_base->Cmd(), cmd_base->Channel());
                                }
                                break;
                            }
                            reply->CommandFlow(command::CommandFlowType::OUTGOING);

                            if(!reply->Post(reply.release()))
                            {
                                // command posting failed. that is bad. do whatever something........
                            }
                            
                        }
                        break;

                        case MsgType::EVENT: 
                        {
                            //std::printf("New event received\n");
                            event::EventBase & event_base = *((event::EventBase *)msg.get());

                            switch(event_base.Id())
                            {
                                default: 
                                {
                                    
                                }
                                break;
                            }

                            if(running_module.event_func != NULL)
                            {
                                running_module.event_func(event_base);
                            }
                        }
                        break;
                        default: 
                        break;
                    }
                }
           }

            protected:
            ModuleInternal() :  is_initialised(false), msg_buffer(PER_MODULE_FIFO_SIZE)
            {                
                //is_initialised = false;
                
            }

            ~ModuleInternal()
            {
                is_initialised = false;
            }




            public: 

            bool Register(EventCallBackFunc func)
            {
                event_func = func;
                return true;
            }

            bool Register(CommandCallBackFunc func)
            {
                cmd_func = func;
                return true;
            }


           bool Write(MessagePtr data)
           {
               return msg_buffer.Push(Core::move(data));
           }


            void InitModule()
            {
                pid_thread.SetStartRoutine(ThreadRunner);
                pid_thread.SetArgument(this);

                is_initialised = true;
            }


            bool Run(int stack_size, int priority)
            {
                pid_thread.SetAttribute(stack_size, priority);

                bool ret = false;


                if(pid_thread.Run() == -1)
                {
                    ret = false;
                }
                else 
                {
                    ret = true;
                }


                return ret;
            }


            bool Stop()
            {
                is_initialised = false;

                bool ret = false;


                if(pid_thread.Stop() == -1)
                    ret = false;
                else
                    ret = true;
                

                
                return ret;
            }
        };
    }
}

#endif  //_MODULE_INTERNAL_INCLUDE_H_
