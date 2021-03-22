


#include <module.hxx>
#include <events.hxx>
#include <core.hxx>
#include <event.hxx>


extern "C"{
	extern uint32_t _sevent_registry, _eevent_registry;
}




namespace vts 
{
    
    namespace event 
    {

        EventManager EventManager::manager;

        void * EventManager::EventThreadRunner(void * arg)
        {
            EventManager & manager = EventManager::GetInstance();

            //std::printf("Event manager thread running.......\n");

            while(1)
            {
                //std::printf("waiting...");
                Core::unique_ptr<EventBase>  event_ptr = manager.NextMessage();
                // iterate through the event subscriber list.
                #if 0
                for(int i = 0; i < manager.event_subscriber_list[event_ptr->GetId()].CurrentSize(); i++)
                {
                    if(manager.event_subscriber_list[event_ptr->GetId()][i] == 0)
                    {

                        // Module id 0 is not accepted. skipping.
                        continue;
                    }

                    module::Module & curr_module = module::Module::CreateModule(manager.event_subscriber_list[event_ptr->GetId()][i]);
                    Core::SmartPtr<MessageBase> msg_ptr = Core::ConvertPointer<EventBase, MessageBase >(event_ptr);
                    curr_module.Write(msg_ptr);
                }

                

                #elif (CONFIG_EVENT_REGISTRY_AT_FLASH)
                //std::printf("Event received and dispatching ID: %d .......\n", event_ptr->Id());
                for(int i = 0; i < CONFIG_MAX_MODULE_COUNT; i++)
                {
                    if(manager.CheckRegistryEntry(i, event_ptr->Id()) == true)
                    {
                        module::Module * curr_module = module::Module::GetModule(i);
                        if(curr_module != nullptr)
                        {
                            Core::unique_ptr<MessageBase> msg_ptr(event_ptr.release());
                            curr_module->Write(Core::move(msg_ptr));
                        }
                        //std::printf("Event dispatched.\n");
                    }
                    //else
                    //{
                    //    std::printf("Module %d not subscribe %d event.\n", i, event_ptr->Id());
                    //}
                }

                #endif
            }
        }



        EventManager::EventManager() : MessageManager<EventBase>(EventThreadRunner)
        {

        }


        EventManager & EventManager::GetInstance()
        {
            return manager;
        }

        bool EventManager::CheckRegistryEntry(module::ModuleId m_id, EventId ev_id)
        {


            #if (CONFIG_EVENT_REGISTRY_AT_FLASH)
            const EventRegistry * ev_registry = (EventRegistry *) &_sevent_registry;
            int registry_count = ((int)&_eevent_registry - (int)&_sevent_registry)/EVENT_REGISTRY_SIZE;
            //std::printf("Registry count: %d\n", registry_count);
            for(int i = 0; i < registry_count; i++)
            {
                if(ev_registry[i].module_id == (uint8_t)m_id)
                {
                    return true;
                }
            }
            #endif
            return false;
        }






        bool EventBase::Post(EventBase * ev)
        {
            Core::unique_ptr<EventBase> base_ptr(ev);           

            EventManager & evman = EventManager::GetInstance(); 

            return evman.Post(Core::move(base_ptr));
        }



        EventBase::EventBase() : MessageBase(MsgType::EVENT)
        {
            _id = NO_EVENT;
            std::memset(_name, 0, CONFIG_EVENT_NAME_LENGTH);
        }


        EventBase::EventBase(EventId id, const char * name) : MessageBase(MsgType::EVENT)
        {
            _id = id;
            std::strncpy(_name, name, CONFIG_EVENT_NAME_LENGTH);
        }


        EventBase::~EventBase()
        {
            _id = NO_EVENT;
            std::memset(_name, 0, CONFIG_EVENT_NAME_LENGTH);
        }


        void EventBase::Name(const char * name)
        {
            std::strncpy(_name, name, CONFIG_EVENT_NAME_LENGTH);
        }


        void EventBase::Id(EventId id)
        {
            _id = id;
        }


        const EventId EventBase::Id() const
        {
            return _id;
        }


        void EventBase::Name(char * buffer, int len)
        {
            if(len >= CONFIG_EVENT_NAME_LENGTH)
            {
                std::strncpy(buffer, _name, CONFIG_EVENT_NAME_LENGTH);
            }
            else 
            {
                std::strncpy(buffer, _name, len);
            }
        }


        void EventBase::Time(int time)
        {
            event_time = time;
        }

        const int EventBase::Time() const
        {
            return event_time;
        }

    }






    bool InitEventModule()
    {
        event::EventManager & ev_man  = event::EventManager::GetInstance();

        ev_man.Run(3072, 10);

        return true;

    }

}