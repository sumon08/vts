

#ifndef _MSG_INCLUDE_H_
#define _MSG_INCLUDE_H_


#include <adapter.hxx>
#include <utility.hxx>

namespace vts
{


    

    enum class MsgType 
    {
        UNKNOWN,
        EVENT,
        COMMAND
    };

    class MessageBase 
    {
        MsgType msg_type;


        protected: 
        MessageBase()
        {
            msg_type = MsgType::UNKNOWN;
        }

        MessageBase(MsgType type):msg_type(type)
        {

        }

        public:        

        void MessageType(MsgType type)
        {
            msg_type = type;
        }

        const MsgType MessageType() const
        {
            return msg_type;
        }

        virtual ~MessageBase()
        {
            
        }
    };


    #ifndef  CONFIG_MAIN_EVENT_BUFFER_SIZE
        #define CONFIG_MAIN_EVENT_BUFFER_SIZE       100
    #endif // ! CONFIG_MAIN_EVENT_BUFFER_SIZE


    template<typename T>
    class MessageManager
    {
        private: 

        static void * MsgThread(void * arg)
        {
            MessageManager * msg_manager = (MessageManager *) (arg);
            if(msg_manager->callback != NULL)
            {
                msg_manager->callback(arg);
            }
            return NULL;
        }

        protected: 

        using ThreadCallBack = adapter::ThreadFunc;

        MessageManager(ThreadCallBack cb):callback(cb), data_buffer(CONFIG_MAIN_EVENT_BUFFER_SIZE)
        {

        }


        Core::unique_ptr<T> NextMessage()
        {
            Core::unique_ptr<T> msg_ptr = data_buffer.Pop();
            return msg_ptr;
        }



       

        public:
        bool Run(int stack_size, int priority)
        {
            pid_thread.SetAttribute(stack_size, priority);
            pid_thread.SetStartRoutine(MsgThread);
            pid_thread.SetArgument(this);

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

        bool Post(Core::unique_ptr<T> data_ptr)
        {
            //std::printf("MessageManager received packet of type: %02X\n", data_ptr->MessageType());
            return data_buffer.Push( Core::move(data_ptr) );
        }

        



        private: 
        ThreadCallBack callback;
        adapter::Thread pid_thread;
        Core::Fifo<Core::unique_ptr<T> > data_buffer;

    };








}


#endif  //_MSG_INCLUDE_H_