


#include <core.hxx>
#include <command.hxx>


namespace vts 
{
    bool InitCommandModule()
    {

        command::CommandManager & man = command::CommandManager::GetInstance();

        man.Run(3072, 10);

        return true;
    }

    bool command::CommandBase::Post(command::CommandBase * base_ptr)
    {
        command::CommandManager & man = command::CommandManager::GetInstance();

        Core::unique_ptr<CommandBase> temp_ptr(base_ptr);

        return man.Post(Core::move(temp_ptr));
    }

    Core::unique_ptr<command::CommandBase> command::CommandBase::Get(command::PortType type)
    {
        command::CommandManager & man = command::CommandManager::GetInstance();
        return man.Get(type);
    }
}